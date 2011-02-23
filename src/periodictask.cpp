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

#include "periodictask.h"

#include <fstream>
#include <sstream>

PeriodicTask::PeriodicTask(string &fileName) : Task(fileName), p(0), e(0)
{
    ifstream file(fileName.c_str());
    string data;
    float token;
    getline(file,data);
    getline(file,data);
    stringstream ss(data);
    if ( ss >> token )
        if ( ss >> token )
            p = token;
    file.close();

    e = getJob(0).getExecTime();
}

float PeriodicTask::getPeriod() const
{
    return p;
}

float PeriodicTask::getExecTime() const
{
    return e;
}

bool PeriodicTask::isValid()
{
    return ((p > 0) && (e <= p) && (size() == 1) && Task::isValid());
}
