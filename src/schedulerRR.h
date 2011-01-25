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

#include <queue>
#include <list>

static int lastID = 0;

class SchedulerRR
{
public:    
    SchedulerRR(Processor &p,float timeslice);
    void loadTask(Task t);
    void schedule();

    class Dead{
    public:
        Dead() : id(-1), d(-1) {}
        Dead (int ID, float D) : id(ID), d(D) {}
        bool operator<(const Dead &a) const { return (d > a.d); }
        int getID () { return id; }
        float getDeadline () { return d; }
    private:
        int id;
        float d;
    };

private:


    Job popJob();
    void enqueueJob(Job& j);

    list<Job> ready;
    priority_queue<Job,vector<Job> > waiting;   //LISTA priority_queue< Job,deque<Job>,greater<Job> > ready;
    priority_queue<Dead> deadline;
    Processor& proc;
    float T; //Timeslice
};



#endif // SCHEDULERRR_H
