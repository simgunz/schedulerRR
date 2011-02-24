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

#define MAXPRLEVEL 4

class SchedulerRR
{
public:    
    SchedulerRR(float timeslice = 3,float duration = 100);
    int loadTask(Task t);                                       //Permette di caricare un task   aperiodico/sporadico
    int loadTask(PeriodicTask t);                               //Permette di caricare un task periodico
    int schedule();                                             //Simula l'esecuzione ed effettua la schedulazione
    inline float getUtilization() { return U; }                 //Restituisce l'utilizzazione del processore

private:
    int enqueueJob(Job& j);                                     //Inserisce un job in alla fine della coda appropriata
    int popJob(Job &j);                                         //Estrae un job dalla testa della coda appropriata
    bool readyempty();                                          //Verifica se tutte le code sono vuote
    bool checkdeadline();                                       //Verifica se i job ready hanno mancato la deadline


    priority_queue<Job,vector<Job> ,greater<Job> > waiting;   //Lista dei job in attesa di essere rilasciati
    list<Job> ready[MAXPRLEVEL+1];                            //Array di liste a diversa priorità contenenti i job in pronti a essere eseguiti
    Processor proc;                                           //Processore associato allo scheduler
    float T;                        //Timeslice
    float D;                        //Duration
    float U;                        //Processor utilization
    int taskID;                     //ID da assegnare al prossimo nuovo task
};

#endif // SCHEDULERRR_H
