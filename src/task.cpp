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

#include <fstream>
#include <sstream>


Task::Task(string fileName)
{
    ifstream file(fileName.c_str());
    string data;

    getline(file,data);
    getline(file,data);

    while (!file.eof())
    {
        getline(file,data);
        if (!data.empty())
            jobs.push_back(strJob(data));
    }
}

Task::Task(vector<Job> &newjobs)
{
    jobs = newjobs;
}
Job Task::strJob(string& data)
{
    stringstream ss(data);
    float token;
    int r,ex,d=-1,p=0;
    if ( ss >> token );
       r = token;
    if ( ss >> token )
       ex = token;
    if ( ss >> token )
       d = token;
    if ( ss >> token )
       p = token;

    return Job(r,d,ex,p);
}

Job& Task::getJob(int i){
    return jobs[i];
}

int Task::size(){
    return jobs.size();
}
