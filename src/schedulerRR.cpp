/*
*  Copyright (C) 2010 Simone Gaiarin <simgunz@gmail.com>
*
*  This file is part of SchedulerRR.
*
*  SchedulerRR is free software: you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation, either version 3 of the License, or
*  (at your option) any later version.
*
*  SchedulerRR is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with SchedulerRR.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "schedulerRR.h"

#include <sstream>
#include <algorithm>


SchedulerRR::SchedulerRR(Processor &p, float timeslice, float duration): proc(p), T(timeslice), D(duration), U(0), jobID(0), taskID(0){}

void SchedulerRR::enqueueJob(Job& j)
{
    list<Job>::reverse_iterator rit;
    list<Job>::iterator it;

    rit = ready.rbegin();
    while(rit != ready.rend() && j.getPriority() > rit->getPriority())
        rit++;

    it = rit.base();

    ready.insert(it,j);
}

Job SchedulerRR::popJob()
{
   Job j = ready.front();
   ready.pop_front();
   return j;
}

void SchedulerRR::taskLabel(bool periodic, int id, int size)
{
    stringstream ss;
    string type =  (periodic) ? "PT" : "T";
    ss << type << taskID++ << "-";
    string taskLabel = ss.str();
    for (int i = 0; i < size; i++)
    {
        ss.str(taskLabel);
        ss.seekp(0,ios::end);
        ss << id;
        proc.rowLabel(id++,ss.str());
    }
}

int SchedulerRR::loadTask(Task &t, bool periodic)
{
    Job j;
    int ret = 0;

    if(!periodic)
    {
        taskLabel(periodic,jobID,t.size());
    }

    for (int i = 0; i < t.size(); i++)
    {
        j = t.getJob(i);
        j.setID(jobID++);

        //Controllo che la deadline sia maggiore del release time
        if((j.getDeadline() == 0) || (j.getReleaseTime() < j.getDeadline()))
        {
            waiting.push(j);

            if(j.getDeadline() != 0)
            {
                proc.print(DEADLINE,j.getID(),j.getDeadline());
                proc.setMaxDeadline(j.getDeadline());
            }
        }
        else
        {
            string bad = "Job_bad_formatted";
            proc.print(TEXTOVER,j.getID(),-1,bad);
            ret = 1;
        }
    }
    return ret;
}

int SchedulerRR::loadTask(PeriodicTask &t)
{
    int id = jobID, ret = 0;
    stringstream ss;
    ss << "EOP" << taskID;

    //Job non valido
    if(t.getPeriod() == 0)
    {
        return 2;
    }


    float u = t.getExecTime() / t.getPeriod();

    //Total utilization grater then 1: system overload
    if (u + U > 1)
        return 3;

    U += u;

    for (float q = 0; q < D; q+=t.getPeriod())
    {
        vector<Job> newJobs;
        for (int i=0; i < t.size(); i++)
        {
            Job j = t.getJob(i);
            float dead = t.getPeriod()+q;
            if(j.getDeadline() != 0)
                dead = min(dead,j.getDeadline()+q);

            Job nw(j.getReleaseTime()+q,dead,j.getExecTime(),j.getPriority());
            newJobs.push_back(nw);
        }
        Task newTask(newJobs);

        ret = loadTask(newTask,true);

        jobID-=t.size();

        proc.print(VLINE,-1,t.getPeriod()+q,ss.str());
    }

    taskLabel(true,jobID,t.size());

    jobID+=t.size();

    return ret;
}

void SchedulerRR::schedule()
{
    Job  r,*currentJob = NULL;
    int sliceEl = 0;
    int end = -1;


    while(!waiting.empty() || !ready.empty() || !proc.idle())
    {
        //Controlla se ci sono processi Ready e li accoda
        vector<Job> vct;


        while(!waiting.empty() && (r = waiting.top()).getReleaseTime() == proc.getClock())
        {
            vct.push_back(r);
            waiting.pop();
        }

        if(!vct.empty())
            sort(vct.begin(),vct.end());

        for (int i = 0; i < vct.size(); i++)
        {
            enqueueJob(vct[i]);
        }

            //Fine della timeslice o processorre idle
        if(sliceEl == 0)
        {
            if(!proc.idle())
            {
                //Forza il preempt del processore visto che la time slice è finita
                proc.preempt();

                if(!end)
                    enqueueJob(*currentJob);

                currentJob = NULL;
            }

            if(!ready.empty())
            {
                sliceEl = T;
                string failed("_Failed");
                currentJob = &(popJob());
                bool d = false, s = false;
                while(currentJob->getDeadline() != 0 && ( ( d = ( currentJob->getDeadline() <= proc.getClock() ) )  || ( s = ( ( currentJob->getDeadline() - proc.getClock() ) < ( currentJob->getExecTime() - currentJob->getElapsedTime() ) ) ) ) )
                {
                    if(d)
                    {
                        proc.print(READYE,currentJob->getID(),currentJob->getDeadline());
                        proc.print(TEXTOVER,currentJob->getID(),currentJob->getDeadline(),failed);
                    }
                    else if(s)
                    {
                        proc.print(READYE,currentJob->getID(),proc.getClock());
                        proc.print(TEXTOVER,currentJob->getID(),proc.getClock(),failed);
                    }

                    d = s = false;

                    if(!ready.empty())
                        currentJob = &(popJob());
                    else
                    {
                        currentJob = NULL;
                        sliceEl = 0;
                        break;
                    }

                }
            }
        }

        for (int i = 0; i < vct.size(); i++)
        {
            proc.print(READYB,vct[i].getID());
            proc.print(START,vct[i].getID());
        }

        //Eseguo un passo del processore e decremento il tempo di slice corrente solo se il processore non è idle
        end = proc.execute(currentJob);
        if (currentJob != NULL)
            sliceEl--;

        //Se il processo termina prima della fine della timeslice libero il processore
        if(end)
        {
            sliceEl = 0;
            currentJob = NULL;
        }
    }
    proc.filePrint();
}
