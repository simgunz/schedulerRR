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

#ifndef SCHEDULERRR_H
#define SCHEDULERRR_H

using namespace std;

#include "job.h"
#include "task.h"
#include "processor.h"

#include <fstream>
#include <queue>
#include <list>
#include <deque>

class SchedulerRR
{
public:
    SchedulerRR(Processor &proc);
    void loadTask(Task t);



private:
    //priority_queue<Job,vector<Job>,greater> ready;
    priority_queue<Job,deque<Job> > waiting;
    priority_queue< Job,deque<Job>,greater<Job> > ready;
    float T; //Timeslice
};

#endif // SCHEDULERRR_H
