/*
*  Copyright (C) 2010 Simone Gaiarin <simgunz@gmail.com>
*
*  This file is part of Foobar.
*
*  Foobar is free software: you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation, either version 3 of the License, or
*  (at your option) any later version.
*
*  Foobar is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with Foobar.  If not, see <http://www.gnu.org/licenses/>. 
*/

#include "periodictask.h"

PeriodicTask::PeriodicTask(string fileName, float period, float priority) : Task(fileName,priority)
{
    float totEx = 0;

    for (int i = 0; i < size(); i++)
    {
        totEx += getJob(i).getExecTime();
    }

    //Se i job non sono eseguibili entro il periodo il job viene assunto come non periodico
    if(totEx <= period)
        p = period;
    else
        p = 0;
}

float PeriodicTask::getPeriod()
{
    return p;
}
