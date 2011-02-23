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

#ifndef TASK_H
#define TASK_H

using namespace std;

#include "job.h"

#include <string>
#include <vector>

class Task
{
public:
    Task(string &fileName);                                     //Costruttore che prende il valori da file
    Task(const vector<Job> &newjobs, float priority = 0);       //Costruttore che prende un vettore di job
    Job getJob(int i) const;                                    //Restituisce l'i-esimo job del task
    int size();                                                 //Restituisce il numero di job nel task
    virtual bool isValid();                                     //Controlla che ogni job sia valido e che il task non sia vuoto

private:
    Job makeJob(const string &data,int JobID);                  //Crea un nuovo job dalla stringa di dati
    vector<Job> jobs;                                           //Vettore dinamico dei job
    float pr;                                                   //Priorità del task
};

#endif // TASK_H
