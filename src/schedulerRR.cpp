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

#define REPETITION 5

string failed("____F");

SchedulerRR::SchedulerRR(float timeslice, float duration): T(timeslice), D(duration), U(0), jobID(0), taskID(0){}

float SchedulerRR::getUtilization()
{
    return U;
}

int SchedulerRR::enqueueJob(Job& j)
{

    if (j.getPriority() > MAXPRLEVEL)
    {
        ready[MAXPRLEVEL].push_back(j);
        return 1;
    }
    else
    {
        ready[j.getPriority()].push_back(j);
        return 0;
    }
}

int SchedulerRR::popJob(Job &j)
{
    for(int i=MAXPRLEVEL; i>=0; i--)
    {
        if(!ready[i].empty())
        {
            j = ready[i].front();
            ready[i].pop_front();
            return 1;
        }
    }
    return 0;
}

bool SchedulerRR::readyempty()
{
    for(int i=MAXPRLEVEL; i>=0; i--)
    {
        if(!ready[i].empty())
            return 0;
    }
    return 1;
}

bool SchedulerRR::checkdeadline()
{
    for(int i=MAXPRLEVEL; i>=0; i--)
    {
        if(!ready[i].empty())
        {
            list<Job>::iterator it;
            it = ready[i].begin();
            while(it != ready[i].end())
            {

                if ((*it).getDeadline() != 0 && ( (*it).getDeadline() <= proc.getClock() ) )
                {

                    proc.print(READYE,(*it).getTID(),(*it).getDeadline(),"",true);
                    proc.print(TEXTOVER,(*it).getTID(),(*it).getDeadline(),failed);
                    it = ready[i].erase(it);
                }
                else
                    it++;
            }
        }
    }
    return 1;
}




int SchedulerRR::loadTask(Task t)
{
    //Se il task non è valido, termino e segnalo al chiamante
    if(!t.isValid())
        return 1;

    if (U == 1)
        return 2;

    Job j;

    /*
    Stampo le etichette sulle righe di kiwi (solo se la funzione non è stata chiamata dal
    metodo per caricare i task periodici)
    */
//    if(!periodic)
//    {
//        //taskLabel(jobID,t.size());

//        taskID++;
//    }

    /*
    Per ogni job del task: imposto l'id univoco, lo accodo nella coda waiting e stampo le deadline sull'output.
    La coda waiting è una coda a priorità che utilizza un vettore dinamico di Job come struttura dati.
    L'operazione di push effettua l'inserimento dei Job utilizzando l'operatore > della classe Job per effettuare il test
    di prioritaà tra i vari Job
    */
    for (int i = 0; i < t.size(); i++)
    {
        j = t.getJob(i);
        j.setTID(taskID);
        //j.setID(jobID++);

        waiting.push(j);

        if(j.getDeadline() != 0)
        {
            stringstream ss;
            ss << "d" << j.getTID() << "," << j.getID();
            proc.print(DEADLINE,j.getTID(),j.getDeadline(),ss.str());
            proc.setMaxDeadline(j.getDeadline());
        }
    }
    jobID++;//??
    taskID++;
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



    /*
    Assegno alla durata massima di esecuzione il massimo tra la durata attuale e il periodo del task ripetuto
    REPETITION volte
    */
    //D = max(D,t.getPeriod()*REPETITION);

//    stringstream ss;
//    ss << "EOP" << taskID;

    /*
    "Clono" i job del mio task tante volte quante ne stanno nella durata totale della simulazione (simulando il loro
    ripetersi) e li inserisco nella coda dei processi in attesa chiamando il metodo loadTask per task non periodici
    */

    vector<Job> newJobs;
    Job j = t.getJob(0);
    int r = j.getReleaseTime(), e = j.getExecTime(), d = j.getDeadline();
    int p = t.getPeriod(), pr = j.getPriority();
    float dead = p;

    if (d>0 && d<p)
        dead = d;

    for (float i = r; i < D; i+=p)
    {
        Job nw(i,e,i+dead,pr);
        newJobs.push_back(nw);
    }

    Task newTask(newJobs);

    loadTask(newTask);

    U += u;
//        jobID-=t.size()+1;

        //proc.print(VLINE,-1,t.getPeriod()+q,ss.str());


    //taskLabel(true,jobID,t.size());

//    jobID+=t.size()+1;

    return 0;
}


int SchedulerRR::schedule()
{
    Job  r,j,*currentJob = NULL;
    int sliceEl = 0;
    int end = -1;


    //Se non ci sono job nella coda dei job in attesa, termino
    if (waiting.empty())
        return 1;

    do
    {



        //Fine della timeslice o processorre idle
        if(sliceEl == 0)
        {
            checkdeadline();

            //Controllo se ci sono processi READY e li inserisco in un vettore temporaneo
            while(!waiting.empty() && (r = waiting.top()).getReleaseTime() <= proc.getClock())
            {
                int tid = r.getTID(), rel = r.getReleaseTime();
                stringstream ss;
                ss << "r" << tid << "," << r.getID();
                proc.print(ARROWUP,tid,rel,ss.str());
                proc.print(READYB,tid,rel);
                proc.print(START,tid,rel);

                enqueueJob(r);
                waiting.pop();
            }

            /*
            Se il processore non è idle significa che è terminato il timeslice o che il job ha terminato in anticipo la
            la sua esecuzione, quindi forzo il preempt e se il job corrente non ha terminato la sua esecuzione lo riaccodo
            */
            if(!proc.idle())
            {
                proc.preempt();

                if(!end)
                    enqueueJob(*currentJob);

                currentJob = NULL;
            }


            /*
            Se ci sono processi READY in attesa di essere eseguiti li estraggo uno alla volta dalla lista e controllo
            se hanno mancato la deadline segnalandolo finchè non ne trovo uno che possa essere
            eseguito o finchè la lista non è vuota. Se tutti hanno mancato la deadline imposto a NULL il job corrente
            e imposto sliceEl a zero indicando che il processore è libero altrimenti imposto il job corrente con quello
            estratto dalla lista
            */


            if(popJob(j))
            {
                sliceEl = T;
                currentJob = &j;
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

    }while(!waiting.empty() || !readyempty() || !proc.idle());

    //Stampo su file tutto l'output generato
    proc.filePrint();

    return 0;
}
