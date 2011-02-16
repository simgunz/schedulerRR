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

#ifndef PROCESSOR_H
#define PROCESSOR_H

using namespace std;

#include "job.h"

#include <string>
#include <sstream>
#include <map>

#define STEP 1

class Processor
{
public:
    Processor();                                        //Costruttore
    float getClock() const;                             //Restituisce il tempo di clock del processore
    int execute(Job *j = NULL);                         //Esegue un nuovo job o il job corrente
    void preempt();                                     //Esegue il preemption del job corrente
    bool idle() const;                                  //Verifica se il processore è nello stato di idle
    void setMaxDeadline(float deadline);                //Imposta la deadline massima
    void print(JobState state, int jobID, float time = -1, string text = "", bool reverse = false); //Stampa un nuovo stato di kiwi
    void filePrint();                                   //Stampa su file
    void rowLabel(int line,string label);               //Imposta le etichette dei job sull'output di kiwi

private:
    float clock;                    //Clock del processore
    stringstream initParam;         //Parametri per inizializzare l'output per kiwi
    Job *currentJob;                //Puntatore al job in esecuzione sul processore
    float maxdeadline;              //Deadline massima, necessaria per effettuare correttamente la stampa su file
    map<float,string> out;          //Mappa che contiene tutti gli stati di esecuzione
};

#endif // PROCESSOR_H
