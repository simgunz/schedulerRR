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


SchedulerRR::SchedulerRR(float timeslice, float duration): T(timeslice), D(duration), U(0), taskID(0) {}

/*
 Permette di inserire il job di priorità N nella corrispondente coda di priorità N.
 Se la priorità del job è superiore al massimo livello di priorità ammesso dallo Scheduler il job
 viene inserito nella coda di priorità massima
*/
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

/*
 Estrae il job in cima alla prima lista più prioritaria non vuota
 Ritorna 1 se l'estrazione è andata a buon fine o 0 se tutte le liste sono vuote
*/
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

//Controlla se tutte le liste sono vuote
bool SchedulerRR::readyempty()
{
    for(int i=MAXPRLEVEL; i>=0; i--)
    {
        if(!ready[i].empty())
            return 0;
    }
    return 1;
}


//Scansiona tutte le liste ed elimino tutti i job che hanno mancato la deadline
bool SchedulerRR::checkdeadline()
{
    for(int i=MAXPRLEVEL; i>=0; i--)
    {
        list<Job>::iterator it;
        it = ready[i].begin();
        while(it != ready[i].end())
        {
            if ((*it).getDeadline() != 0 && ( (*it).getDeadline() <= proc.getClock() ) )
            {

                proc.print(READYE,(*it).getTID(),(*it).getDeadline(),"",true);
                proc.print(TEXTOVER,(*it).getTID(),(*it).getDeadline(),"____F");
                bl[(*it).getTID()]=0;
                it = ready[i].erase(it);
            }
            else
                it++;
        }

    }
    return 1;
}


int SchedulerRR::loadTask(Task t)
{
    Job j;

    //Se il task non è valido o se l'utilizzazione del processore è 1, termino e segnalo al chiamante
    if(!t.isValid())
        return 1;

    if (U == 1)
        return 2;

    /*
    Per ogni job del task: imposto l'id del task a cui appartiene, lo accodo nella coda waiting e stampo le deadline sull'output.
    La coda waiting è una coda a priorità che utilizza un vettore dinamico di Job come struttura dati.
    L'operazione di push effettua l'inserimento dei Job utilizzando l'operatore > della classe Job per effettuare il test
    di priorità tra i vari Job. Un job è più prioritario se il suo release time è minore.
    */
    for (int i = 0; i < t.size(); i++)
    {
        j = t.getJob(i);
        j.setTID(taskID);

        waiting.push(j);

        //Stampo le deadline
        if(j.getDeadline() != 0)
        {
            stringstream ss;
            ss << "d" << j.getTID() << "," << j.getID();
            proc.print(DEADLINE,j.getTID(),j.getDeadline(),ss.str());
            proc.setMaxDeadline(j.getDeadline());
        }
    }
    taskID++;
    return 0;
}


int SchedulerRR::loadTask(PeriodicTask t)
{
    Job j;

    //Se il task non è valido, termino e segnalo al chiamante
    if(!t.isValid())
        return 1;

    float u = t.getExecTime() / t.getPeriod();

    //Se inserendo il task sforo l'utilizzazione massima del processore, non lo inserisco e segnalo al chiamante
    if (u + U > 1)
        return 2;

    /*
    "Clono" i job del mio task tante volte quante ne stanno nella durata totale della simulazione (simulando il loro
    ripetersi) e li inserisco nella coda dei processi in attesa chiamando il metodo loadTask per task non periodici
    */

    vector<Job> newJobs;
    j = t.getJob(0);
    int r = j.getReleaseTime(), e = j.getExecTime(), d = j.getDeadline();
    int p = t.getPeriod(), pr = j.getPriority();

    if(d == 0)
        d = p;

    for (float i = r; i < D; i+=p)
    {
        Job nw(i,e,i+d,pr);
        newJobs.push_back(nw);
    }

    Task newTask(newJobs);

    loadTask(newTask);

    //Incremento l'utilizzazione del processore
    U += u;

    return 0;
}


int SchedulerRR::schedule()
{
    Job  r,j,*currentJob = NULL;
    int sliceEl = 0;
    int end = -1;
    int tid,rel;

    list<Job> blocked;

    //Se non ci sono job nella coda dei job in attesa, termino
    if (waiting.empty())
        return 1;

    do
    {
        /*
        Fine della timeslice o processorre idle.
        Lo scheduler si attiva solo quando sliceEl==0
        All'interno di questo if avviene la schedulazione vera e propria.
        */
        if(sliceEl == 0)
        {

            //Controllo se i job in coda hanno mancato la deadline
            checkdeadline();

            for (int i=0; i<blocked.size();i++)
            {
                r = blocked.front();
                blocked.pop_front();
                tid = r.getTID();
                rel = r.getReleaseTime();

                if(bl[tid]==0)
                {
                    proc.print(READYB,tid,proc.getClock());
                    proc.print(START,tid,proc.getClock());
                    enqueueJob(r);
                    bl[tid]=1;
                }
                else
                    blocked.push_back(r);
            }

            //Controllo se ci sono stati rilasciati nuovi job, li accoda nell'opportuna coda dei job ready e stampo
            while(!waiting.empty() && (r = waiting.top()).getReleaseTime() <= proc.getClock())
            {
                tid = r.getTID();
                rel = r.getReleaseTime();

                stringstream ss;
                ss << "r" << tid << "," << r.getID();
                proc.print(ARROWUP,tid,rel,ss.str());

                if(bl[tid]==0)
                {
                    proc.print(READYB,tid,rel);
                    proc.print(START,tid,rel);
                    enqueueJob(r);
                    bl[tid]=1;
                }
                else
                {
                    blocked.push_back(r);
                }

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


            //Estraggo il job in testa alla coda opportuna e lo imposto come job corrente, se la coda è vuota non faccio niente
            if(popJob(j) && (j.getDeadline()==0 || proc.getClock() < j.getDeadline()))
            {
                sliceEl = T;
                currentJob = &j;
            }

        }

        //Eseguo un passo del processore e decremento il tempo di slice corrente solo se il processore non è idle (currentJob = NULL)
        end = proc.execute(currentJob);

        if (currentJob != NULL)
            sliceEl--;

        //Se il processo termina prima della fine della timeslice mi preparo a schedulare un nuovo job
        if(end)
        {
            sliceEl = 0;
            bl[currentJob->getTID()]=0;
            currentJob = NULL;
        }

    }while(!waiting.empty() || !readyempty() || !proc.idle() || !blocked.empty());

    //Stampo su file tutto l'output generato
    proc.filePrint();

    return 0;
}
