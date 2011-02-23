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

#include <iostream>

#define MAXPRLEVEL 3

class SchedulerRR
{
public:    
    SchedulerRR(float timeslice = 3,float duration = 100);
    int loadTask(Task t);                //Permette di caricare un task non periodici
    int loadTask(PeriodicTask t);                               //Permette di caricare un task periodico
    int schedule();                                            //Simula l'esecuzione ed effettua la schedulazione
    float getUtilization();                                     //Restituisce l'utilizzazione del processore

private:
    int enqueueJob(Job& j);                                    //Inserisce un job in coda alla coda
    int popJob(Job &j);                                               //Estrae un job dalla testa della coda
    bool readyempty();
    bool checkdeadline();


    priority_queue<Job,vector<Job> ,greater<Job> > waiting;   //Lista dei job in attesa di essere rilasciati
    list<Job> ready[MAXPRLEVEL+1];                                          //Lista dei job in pronti a essere eseguiti
    Processor proc;                                           //Processore associato allo scheduler
    float T;                        //Timeslice
    float D;                        //Duration
    float U;                        //Utilizazzione del processore
    int jobID;                      //ID da assegnare al prossimo nuovo job
    int taskID;                     //ID da assegnare al prossimo nuovo task
};



#endif // SCHEDULERRR_H
