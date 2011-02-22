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

#include <sstream>
#include <algorithm>

#define REPETITION 3

SchedulerRR::SchedulerRR(float timeslice, float duration): T(timeslice), D(duration), U(0), jobID(0), taskID(0){}

float SchedulerRR::getUtilization()
{
    return U;
}

void SchedulerRR::enqueueJob(Job& j)
{
    list<Job>::reverse_iterator rit;
    list<Job>::iterator it;

    /*
    Scorro la lista dei job ready finchè non trovo la testa della coda o un job di priorità maggiore o uguale
    a quello che sto inserendo, in quella posizione inserisco il job
    */
    rit = ready.rbegin();
    while(rit != ready.rend() && j.getPriority() > rit->getPriority())
        rit++;

    it = rit.base();

    ready.insert(it,j);
}

Job SchedulerRR::popJob()
{
   Job j = ready.front();
   ready.pop_front();
   return j;
}

void SchedulerRR::taskLabel(bool periodic, int id, int size)
{
    stringstream ss;
    string type =  (periodic) ? "PT" : "T";
    ss << type << taskID++ << "-";
    string taskLabel = ss.str();
    for (int i = 0; i < size; i++)
    {
        ss.str(taskLabel);
        ss.seekp(0,ios::end);
        ss << id;
        proc.rowLabel(id++,ss.str());
    }
    proc.rowLabel(id,"A");
}


int SchedulerRR::loadTask(Task t, bool periodic)
{
    //Se il task non è valido, termino e segnalo al chiamante
    if(!t.isValid())
        return 1;

    Job j;

    /*
    Stampo le etichette sulle righe di kiwi (solo se la funzione non è stata chiamata dal
    metodo per caricare i task periodici)
    */
    if(!periodic)
    {
        taskLabel(periodic,jobID,t.size());
    }

    /*
    Per ogni job del task: imposto l'id univoco, lo accodo nella coda waiting e stampo le deadline sull'output.
    La coda waiting è una coda a priorità che utilizza un vettore dinamico di Job come struttura dati.
    L'operazione di push effettua l'inserimento dei Job utilizzando l'operatore > della classe Job per effettuare il test
    di prioritaà tra i vari Job
    */
    for (int i = 0; i < t.size(); i++)
    {
        j = t.getJob(i);
        j.setID(jobID++);

        waiting.push(j);

        if(j.getDeadline() != 0)
        {
            proc.print(DEADLINE,j.getID(),j.getDeadline());
            proc.setMaxDeadline(j.getDeadline());
        }
    }
    jobID++;
    return 0;
}


int SchedulerRR::loadTask(PeriodicTask t)
{
    //Se il task non è valido, termino e segnalo al chiamante
    if(!t.isValid())
        return 1;

    float u = t.getExecTime() / t.getPeriod();

    //Se inserendo il task sforo l'utilizzazione massima del processore, non lo inserisco e segnalo al chimante
    if (u + U > 1)
        return 2;

    U += u;

    /*
    Assegno alla durata massima di esecuzione il massimo tra la durata attuale e il periodo del task ripetuto
    REPETITION volte
    */
    D = max(D,t.getPeriod()*REPETITION);

    stringstream ss;
    ss << "EOP" << taskID;

    /*
    "Clono" i job del mio task tante volte quante ne stanno nella durata totale della simulazione (simulando il loro
    ripetersi) e li inserisco nella coda dei processi in attesa chiamando il metodo loadTask per task non periodici
    */
    for (float q = 0; q < D; q+=t.getPeriod())
    {
        vector<Job> newJobs;
        for (int i=0; i < t.size(); i++)
        {
            Job j = t.getJob(i);
            float dead = t.getPeriod()+q;
            if(j.getDeadline() != 0)
                dead = min(dead,j.getDeadline()+q);

            Job nw(j.getReleaseTime()+q,dead,j.getExecTime(),j.getPriority());
            newJobs.push_back(nw);
        }
        Task newTask(newJobs);

        loadTask(newTask,true);

        jobID-=t.size()+1;

        //proc.print(VLINE,-1,t.getPeriod()+q,ss.str());
    }

    taskLabel(true,jobID,t.size());

    jobID+=t.size()+1;

    return 0;
}


int SchedulerRR::schedule()
{
    Job  r,j,*currentJob = NULL;
    int sliceEl = 0;
    int end = -1;
    string failed("_Failed");

    //Se non ci sono job nella coda dei job in attesa, termino
    if (waiting.empty())
        return 1;

    do
    {

        vector<Job> vct;

        //Fine della timeslice o processorre idle
        if(sliceEl == 0)
        {
            //Controllo se ci sono processi READY e li inserisco in un vettore temporaneo
            while(!waiting.empty() && (r = waiting.top()).getReleaseTime() <= proc.getClock())
            {
                vct.push_back(r);
                waiting.pop();
            }

            //Ordino i job appena rilasciati decondo deadline crescenti, utilizzando l'operatore < della classe Job
            if(!vct.empty())
                sort(vct.begin(),vct.end());

            //Accodo i job appena rilasciati ordinati e stampo su output
            for (int i = 0; i < vct.size(); i++)
            {
                enqueueJob(vct[i]);

                proc.print(ARROWUP,vct[i].getID(),vct[i].getReleaseTime());
                proc.print(READYB,vct[i].getID(),vct[i].getReleaseTime());
                proc.print(START,vct[i].getID(),vct[i].getReleaseTime());

            }

            /*
            Se il processore non è idle significa che è terminato il timeslicen o che il job ha terminato in anticipo la
            la sua esecuzione
            */
            if(!proc.idle())
            {
                //Forzo il preempt dal processore del job corrente
                proc.preempt();

                /*
                Se sono al termine del timeslice (e non al terimine dell'esecuzione del job) calcolo lo slack time
                e se minore di zero non riaccodo il job e segnalo un deadline miss, altrimenti riaccodo il job
                */
                if(!end)
                {
//                    if ( ( currentJob->getDeadline() != 0 && (currentJob->getDeadline() - proc.getClock() ) < ( currentJob->getExecTime() - currentJob->getElapsedTime() ) ) )
//                    {
//                        proc.print(READYE,currentJob->getID(),proc.getClock());
//                        proc.print(TEXTOVER,currentJob->getID(),proc.getClock(),failed);
//                    }
//                    else
                        enqueueJob(*currentJob);
                }

                //Imposto il job corrente a NULL
                currentJob = NULL;
            }

            /*
            Se ci sono processi READY in attesa di essere eseguiti li estraggo uno alla volta dalla lista e controllo
            se hanno mancato la deadline segnalandolo finchè non ne trovo uno che possa essere
            eseguito o finchè la lista non è vuota. Se tutti hanno mancato la deadline imposto a NULL il job corrente
            e imposto sliceEl a zero indicando che il processore è libero altrimenti imposto il job corrente con quello
            estratto dalla lista
            */
            if(!ready.empty())
            {
                sliceEl = T;
                j = popJob();
                currentJob = &j;

                while(currentJob->getDeadline() != 0 && ( currentJob->getDeadline() <= proc.getClock() ) )
                {
                    proc.print(READYE,currentJob->getID(),currentJob->getDeadline(),"",true);
                    proc.print(TEXTOVER,currentJob->getID(),currentJob->getDeadline(),failed);

                    if(!ready.empty())
                    {
                        j = popJob();
                        currentJob = &j;
                    }
                    else
                    {
                        currentJob = NULL;
                        sliceEl = 0;
                        break;
                    }
                }
            }
        }

        //Eseguo un passo del processore e decremento il tempo di slice corrente solo se il processore non è idle
        end = proc.execute(currentJob);

        if (currentJob != NULL)
            sliceEl--;

        //Se il processo termina prima della fine della timeslice libero il processore
        if(end)
        {
            sliceEl = 0;
            currentJob = NULL;
        }

    }while(!waiting.empty() || !ready.empty() || !proc.idle());

    //Stampo su file tutto l'output generato
    proc.filePrint();

    return 0;
}
