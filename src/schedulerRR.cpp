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

#include <iostream>
#include <typeinfo>

SchedulerRR::SchedulerRR(Processor &p, float timeslice): proc(p), T(timeslice){}

int SchedulerRR::loadTask(Task &t) //Il task t è polimorfico
{
    Job j;

    for (int i = 0; i < t.size(); i++)
    {
        j = t.getJob(i);
        j.setID(lastID++);

        //Controllo che la deadline sia maggiore del release time
        if((j.getDeadLine() == -1) || (j.getReleaseTime() < j.getDeadLine()))
        {
            waiting.push(j);

            Dead d (j.getID(),j.getDeadLine());
            if(d.getDeadline() != -1)
                deadline.push(d);
        }
        else
        {
            string bad = "_Job_bad_formatted";
            proc.print(TEXTOVER,j.getID(),-1,bad);
        }
    }
    return 0;
}

Job SchedulerRR::popJob()
{
   Job j = ready.front();
   ready.pop_front();
   return j;
}

void SchedulerRR::enqueueJob(Job& j)
{
    list<Job>::reverse_iterator rit;
    list<Job>::iterator it;

    for(rit = ready.rbegin();rit != ready.rend() && j.getPriority() > rit->getPriority();rit++)
    {
        cout << rit->getDeadLine() << "*";
    }
    it = rit.base();

//    cout << "N=" << ready.size() <<endl;
    ready.insert(it,j);
}

void SchedulerRR::schedule()
{
    Job  r,*currentJob = NULL;
    Dead d;
    int sliceEl = 0;
    int end = -1;

    while(!waiting.empty() || !ready.empty() || !deadline.empty() || !proc.idle())
    {

        list<Job>::reverse_iterator it = ready.rbegin();
        for(;it != ready.rend();it++)
            cout << it->getID() << " ";

        cout << "*C="<< proc.getClock() <<endl;


        //Controlla se ci sono processi Ready e li accoda
        while(!waiting.empty() && (r = waiting.top()).getReleaseTime() == proc.getClock())
        {
            proc.print(READYB,r.getID());
            proc.print(START,r.getID());
            enqueueJob(r);
            waiting.pop();
        }

        //Disegna le deadline sul grafico
        while(!deadline.empty() && (d = deadline.top()).getDeadline() == proc.getClock())
        {
            proc.print(DEADLINE,d.getID());
            deadline.pop();
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
                while(!ready.empty() && currentJob->getDeadLine() != -1 && currentJob->getDeadLine() <= proc.getClock())
                {
                    proc.print(READYE,currentJob->getID());
                    proc.print(TEXTOVER,currentJob->getID(),-1,failed);
                    currentJob = &(popJob());
                }
            }
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


}
