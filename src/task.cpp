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


Task::Task(string &fileName) : pr(-1)
{
    /*
     Se il file non esiste il codice non viene eseguito.
     Se il file non è ben formattato vengono impostati dei valori di default al job.
     In entrambi i casi il task è invalido e il metodo isValid lo rileva.
    */
    ifstream file(fileName.c_str());
    if(!file.fail())
    {
        int jobID = 1;
        string data;
        float token;

        getline(file,data);
        getline(file,data);
        stringstream ss(data);
        if ( ss >> token )
            pr = token;
        getline(file,data);
        getline(file,data);

        while (!file.eof())
        {
            getline(file,data);
            if (!data.empty())
                jobs.push_back(makeJob(data,jobID++));
        }
    }
    file.close();
}

Task::Task(const vector<Job> &newjobs, float priority) : pr(priority)
{
    jobs = newjobs;
    for (int i=0;i < size();i++)
    {
        jobs[i].setID(i+1);
    }
}


Job Task::getJob(int i) const
{
    return jobs[i];
}

int Task::size()
{
    return jobs.size();
}

bool Task::isValid()
{
    if(size() == 0)
        return 0;

    bool valid = jobs[0].isValid();
    for (int i = 1; valid && (i < size()); i++)
    {
        valid = jobs[i].isValid() && (jobs[i].getReleaseTime() >= jobs[i-1].getReleaseTime() + jobs[i-1].getExecTime());
    }
    return valid;
}

Job Task::makeJob(const string& data,int jobID)
{
    /*
    StringStream permette di ottenere dati bene formattati, nel caso i dati siano mal formattati
    l'if non viene eseguito e se il parametro non è facoltativo il job creato non è valido
    e di conseguenze neanche il task. Si evita però di avere comportamenti anomali del programma.
    */
    stringstream ss(data);
    float token;
    float r=-1,e=0,d=0;

    if ( ss >> token )
       r = token;
    if ( ss >> token )
       e = token;
    if ( ss >> token )
       d = token;

    return Job(r,e,d,pr,jobID);
}
