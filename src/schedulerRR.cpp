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
#include "job.h"
#include "processor.h"


#include <iostream>

//using namespace std;

SchedulerRR::SchedulerRR(Processor &p, float timeslice): proc(p)
{
    T = timeslice;
}

void SchedulerRR::loadTask(Task t){

    for (int i = 0; i < t.size(); i++)
    {
        Job j = t.getJob(i);
        j.setID(lastID);
        proc.print(DEADLINE,j.getID(),j.getDeadLine());
        lastID++;
        waiting.push(j);
    }

//    Job a(1,2,3),b(1,2,3);
//    for (int i = 0; i < t.size(); i++)
//    {

//        a = waiting.top();
//        waiting.pop();
//        cout <<  "A=" << a.getReleaseTime() << " " << a.getPriority() << endl;
//    }
}

Job& SchedulerRR::popJob(){
   Job j = ready.front();
   cout << "test" <<endl;
   ready.pop_front();
   return j;
}

void SchedulerRR::enqueueJob(Job& j){
   ready.push_back(j);
}

void SchedulerRR::schedule(){
//int r=0;
    while(!ready.empty() || !waiting.empty())
    {
//        if (r==10)
//            break;
//        r++;
        if (!waiting.empty())
        {
            Job r = waiting.top();
            cout << r.getReleaseTime();
            cout <<"Size=" << waiting.size();
            while(r.getReleaseTime() <= proc.getClock())
            {
                enqueueJob(r);
                waiting.pop();
                if(!waiting.empty())
                    r = waiting.top();
                else
                    break;
            }
        }

        if(!ready.empty())
        {
            Job currentJob = popJob();
            cout <<"OK";
            proc.execute(currentJob,T);
        }
        else
        {
            Job j(-1,-1,-1);
            proc.execute(j);
        }
        cout << "SS=" << proc.getClock();

    }
}
