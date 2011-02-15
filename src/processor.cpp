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

#include "processor.h"

#include <fstream>
#include <algorithm>


Processor::Processor() : clock(0), currentJob(NULL), maxdeadline(0)
{
    initParam << "DECIMAL_DIGITS 1" << endl;
    initParam << "PALETTE Rainbow" << endl;
    initParam << "ZOOM_X 5" << endl;
}

float Processor::getClock() const{
    return clock;
}

int Processor::execute(Job *j)
{
    if(j != NULL)
    {
        if (j != currentJob)
        {
            preempt();
            currentJob = j;
            print(EXECB,currentJob->getID());
        }
    }

    if(currentJob != NULL)
        currentJob->incElapsedTime(STEP);

    clock+=STEP;

    if (currentJob != NULL && currentJob->getElapsedTime() == currentJob->getExecTime())
    {
        print(READYE,currentJob->getID());
        print(STOP,currentJob->getID());
        preempt();
        return 1;
    }

//    if (currentJob != NULL && currentJob->getDeadline() == clock)
//    {
//        print(READYE,currentJob->getID());
//        string failed("_Failed");
//        print(TEXTOVER,currentJob->getID(),currentJob->getDeadline(),failed);
//        preempt();
//        return 2;
//    }

    return 0;
}

void Processor::preempt()
{
    if (currentJob != NULL)
    {
        print(EXECE,currentJob->getID());
        currentJob = NULL;
    }
}

bool Processor::idle() const
{
    return (currentJob == NULL);
}

void Processor::setMaxDeadline(float deadline)
{
    if (deadline > maxdeadline)
        maxdeadline = deadline;
}

void Processor::print(JobState state, int jobID, float time, string text, bool reverse)
{
    string outStr = "";
    stringstream sout(outStr);
    if(time == -1)
        time = clock;
    sout << time/10 << " " << state << " ";
    if(jobID != -1)
        sout << jobID << " ";
    sout << text << endl;
    outStr = sout.str();
    if(!reverse)
        out[time] += outStr;
    else
        out[time] = outStr + out[time];
}

void Processor::filePrint()
{
    initParam << endl;

    ofstream output("output.ktr");

    output << initParam.str();

    for (int i = 0; i <= max(clock,maxdeadline); i++)
    {
        output << out[i];
    }

    output.flush();
    output.close();
}

void Processor::rowLabel(int line, string label)
{
    initParam << "LINE_NAME " << line << " " << label << endl;
}
