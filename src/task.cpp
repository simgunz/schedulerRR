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

#include "task.h"

#include <string>
#include <iostream>
#include <fstream>


Task::Task(char* fileName)
{
    ifstream file(fileName);
    string data;

    getline(file,data);
    getline(file,data);

    while (!file.eof())
    {
        getline(file,data);

        jobs.push_back(Job(data));

        //cout << "R=" << jobs.front().getReleaseTime() << endl;
    }
    size = jobs.size();
}

