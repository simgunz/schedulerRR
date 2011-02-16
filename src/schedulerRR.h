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

#include "task.h"
#include "periodictask.h"
#include "processor.h"

#include <string>
#include <queue>
#include <list>


class SchedulerRR
{
public:    
    SchedulerRR(float timeslice = 3,float duration = 200);
    int loadTask(Task t, bool periodic = false);                //Permette di caricare un task aperiodico/sporadico
    int loadTask(PeriodicTask t);                               //Permette di caricare un task periodico
    void schedule();                                            //Simula l'esecuzione ed effettua la schedulazione
    float getUtilization();                             //Restituisce l'utilizzazione

private:
    void enqueueJob(Job& j);
    Job popJob();
    void taskLabel(bool periodic, int id, int size);

    priority_queue<Job,vector<Job> ,greater<Job> > waiting;   //LISTA priority_queue< Job,deque<Job>,greater<Job> > ready;
    list<Job> ready;
    Processor proc;
    float T; //Timeslice
    float D; //Duration
    float U;                        //Utilizazzione del processore
    int jobID;
    int taskID;
};



#endif // SCHEDULERRR_H
