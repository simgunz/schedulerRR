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

#include "job.h"
#include "processor.h"
#include "schedulerRR.h"

#include <iostream>

//using namespace std;

SchedulerRR::SchedulerRR(Processor &proc)
{

}

void SchedulerRR::loadTask(Task t){

    for (int i = 0; i < t.size(); i++)
    {
        waiting.push(t.getJob(i));
        ready.push(t.getJob(i));
    }

    Job a(1,2,3),b(1,2,3);
    for (int i = 0; i < t.size(); i++)
    {

        a = waiting.top();
        waiting.pop();
        cout <<  "A=" << a.getReleaseTime() << endl;
    }

    for (int i = 0; i < t.size(); i++)
    {
        b = ready.top();
        ready.pop();
        cout <<  "B=" << b.getReleaseTime() << endl;
    }
}
