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


Job::Job(float R, float E, float D, int P,int ID): id(ID), tid(-1), p(P), r(R), e(E), d(D), el(0) {}

bool Job::operator>(const Job &j) const
{ return (r > j.r); }

bool Job::isValid()
{
    bool valid = (r >= 0);                              //Il release time deve essere maggiore di zero
    valid = valid && (e > 0);                           //Il tempo di esecuzione deve essere maggiore di zero
    valid = valid && (d >= 0);                          //La deadline deve essere non negativa
    valid = valid && (p >= 0);                          //La priorità deve essere maggiore di zero
    return valid;
}
