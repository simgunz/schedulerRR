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


SchedulerRR::SchedulerRR(Processor &p, float timeslice): proc(p), T(timeslice){}

void SchedulerRR::loadTask(Task t)
{

    Job j;

    for (int i = 0; i < t.size(); i++)
    {
        j = t.getJob(i);
        j.setID(lastID++);
        waiting.push(j);
    }
}

Job SchedulerRR::popJob()
{
   Job j = ready.front();
   ready.pop_front();
   return j;
}

void SchedulerRR::enqueueJob(Job& j)
{
   ready.push_back(j);
}

void SchedulerRR::schedule()
{
    Job r, currentJob;
    int sliceEl = 0;

    while(!ready.empty() || !waiting.empty())
    {
        while(!waiting.empty() && (r = waiting.top()).getReleaseTime() == proc.getClock())
        {
            proc.print(READYB,r.getID());
            proc.print(START,r.getID());
            enqueueJob(r);
            waiting.pop();
        }

        if( sliceEl > 0)
        {
            proc.execute();
            sliceEl--;
        }
        else
        {
            //Implementabile nel processore? Return TERM
            if(!proc.idle())
            {
                proc.preempt();

                if (!(currentJob.getElapsedTime() == currentJob.getExecTime()))
                {
                    enqueueJob(currentJob);
                }
            }

            if(!ready.empty())
            {
                sliceEl = T;
                currentJob = popJob();
                proc.execute(&currentJob);
                sliceEl--;                  //slice-=proc.STEP
            }
            else
            {
                proc.execute();
            }
        }

        //Implementabile nel processore
        if(!proc.idle())
        {
            if (currentJob.getElapsedTime() == currentJob.getExecTime())
            {
                sliceEl = 0;
                proc.preempt();
                proc.print(STOP,currentJob.getID());
                proc.print(READYE,currentJob.getID());
            }
        }
    }
}
