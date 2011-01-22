/*
 * Copyright (C) 2010 Simone Gaiarin <simgunz@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#include "job.h"

#include <iostream>
#include <fstream>
#include <sstream>


Job::Job(string data)
{
    init(data);
}

void Job::init (string data)
{
    stringstream ss(data);
    float token;
    if ( ss >> token );
       r = token;
    if ( ss >> token )
       d = token;
    if ( ss >> token )
       ex = token;
}

bool Job::operator<(const Job &j) const{
    return (r > j.r);
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
