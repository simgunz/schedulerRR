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

#include "processor.h"

#include <fstream>
#include <algorithm>


Processor::Processor() : clock(0), currentJob(NULL), maxdeadline(0)
{
    initParam << "DECIMAL_DIGITS 1" << endl;
    initParam << "PALETTE Rainbow" << endl;
    initParam << "ZOOM_X 5" << endl;
    initParam << "ZOOM_Y 20" << endl;
}

float Processor::getClock() const{
    return clock;
}


int Processor::execute(Job *j)
{
    //Se il metodo è chiamato senza parametri eseguo un passo "idle" di processore
    //Se il metodo è chiamato con un parametro, prelevo il job corrente e lo sostituisco con il nuovo job se questo è diverso
    //segnalandolo sull'output
    if(j != NULL)
    {
        if (j != currentJob)
        {
            preempt();
            currentJob = j;
            print(EXECB,currentJob->getID());
        }
    }

    //Incremento il tempo trascorso di esecuzione al job
    if(currentJob != NULL)
        currentJob->incElapsedTime(STEP);


    clock+=STEP;

    //Se il job ha teminato la sua esecuzione lo prelevo, lo segnalo su output e lo segnalo al chiamante
    if (currentJob != NULL && currentJob->getElapsedTime() == currentJob->getExecTime())
    {
        print(READYE,currentJob->getID());
        print(STOP,currentJob->getID());
        preempt();
        return 1;
    }

    return 0;
}

//Libera il processore e segnala la preemption
void Processor::preempt()
{
    if (currentJob != NULL)
    {
        print(EXECE,currentJob->getID());
        currentJob = NULL;
    }
}

bool Processor::idle() const
{
    return (currentJob == NULL);
}

void Processor::setMaxDeadline(float deadline)
{
    if (deadline > maxdeadline)
        maxdeadline = deadline;
}

/*
La mappa out è composta da una chiave che corrisponde al tempo in cui avviene l'evento e un valore stringa
che contiene tutti gli eventi avvenuti in quel tempo. Il tutto è in un formato leggibile da kiwi.
Tramite la mappa è possibile fare un output non ordinato, l'ordinazione sarà successiva.
Il metodo è chiamabile con più o meno parametri in base al tipo di evento da segnalare

*/
void Processor::print(JobState state, int jobID, float time, string text, bool reverse)
{
    string outStr = "";
    stringstream sout(outStr);
    if(time == -1)
        time = clock;
    sout << time << " " << state << " ";
    if(jobID != -1)
        sout << jobID << " ";
    sout << text << endl;
    outStr = sout.str();
    if(!reverse)
        out[time] += outStr;
    else
        out[time] = outStr + out[time];
}

//Stampa l'output su file ordinatamente e in formato leggibile da kiwi
void Processor::filePrint()
{
    initParam << endl;

    ofstream output("output.ktr");

    output << initParam.str();

    for (int i = 0; i <= max(clock,maxdeadline); i++)
    {
        output << out[i];
    }

    output.flush();
    output.close();
}

void Processor::rowLabel(int line, string label)
{
    initParam << "LINE_NAME " << line << " " << label << endl;
}
