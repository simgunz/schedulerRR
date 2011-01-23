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

#include "job.h"

#include <iostream> //Cancellami
#include <sstream>


Job::Job(float R, float D, float EX): r(R), d(D), ex(EX)
{
    id = -1;
    el = -1;
}

bool Job::operator<(const Job &j) const{
    return (r > j.r);
}

bool Job::operator>(const Job &j) const{
    return (r < j.r);
}

int Job::getID()
{
    return id;
}

float Job::getReleaseTime(){
    return r;
}

float Job::getDeadLine()
{
    return d;
}

float Job::getExecTime()
{
    return ex;
}

float Job::getElapsedTime()
{
    return el;
}
