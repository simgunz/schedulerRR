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

#ifndef PERIODICTASK_H
#define PERIODICTASK_H

#include "task.h"

class PeriodicTask : public Task
{
public:
    PeriodicTask(string &fileName);                 //Costruttore che prende il valori da file
    inline float getPeriod() const { return p; }    //Restituisce il periodo del task
    inline float getExecTime() const { return e; }  //Restituisce la il tempo di esecuzione del task
    bool isValid();                                 //Controlla che il task sia valido
private:
    float p;       //Period
    float e;       //Execution time
};

#endif // PERIODICTASK_H
