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

    for (int i = 0; i < t.size; i++)
        ready.push(t.jobs[i]);

    for (int i = 0; i < t.size; i++)
    {
        Job a = ready.top();
        ready.pop();
        cout <<  a.getReleaseTime();

    }


}
