/*
 * Copyright (C) 2010 Simone Gaiarin <simgunz@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#ifndef SCHEDULERRR_H
#define SCHEDULERRR_H

using namespace std;

#include "job.h"
#include "task.h"
#include "processor.h"


#include <fstream>
#include <queue>



class SchedulerRR
{
public:
    SchedulerRR(Processor &proc);
    void loadTask(Task t);



private:
    //priority_queue<Job,vector<Job>,greater> ready;
    priority_queue<Job> ready;
    //priority_queue<Job> waiting;
};

#endif // SCHEDULERRR_H
