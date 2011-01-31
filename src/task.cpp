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

#include <sstream>
#include <fstream>


Task::Task(const string &fileName, float priority) : pr(priority)
{
    ifstream file(fileName.c_str());
    string data;

    getline(file,data);
    getline(file,data);

    while (!file.eof())
    {
        getline(file,data);
        if (!data.empty())
            jobs.push_back(makeJob(data));
    }
}

Task::Task(const vector<Job> &newjobs, float priority) : pr(priority)
{
    jobs = newjobs;
}

Job Task::makeJob(const string& data)
{
    stringstream ss(data);
    float token;
    float r=-1,e=0,d=0;
    int p=0;

    if ( ss >> token )
       r = token;
    if ( ss >> token )
       e = token;
    if ( ss >> token )
       d = token;
    if ( ss >> token )
       p = token;

    return Job(r,d,e,p + pr*10);
}

Job Task::getJob(int i) const{
    return jobs[i];
}

int Task::size(){
    return jobs.size();
}

bool Task::isValid(float p)
{
    bool valid = true;
    for (int i = 0; i < size(); i++)
    {
        valid = valid && jobs[i].isValid(p);
    }
    return valid;
}
