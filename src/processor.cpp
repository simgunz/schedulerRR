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

#include <iostream>
#include <string>


Processor::Processor(string outputFile)
{
    output.open(outputFile.c_str());

    output << "DECIMAL_DIGITS 1" << endl;
    output << "DURATION 50" << endl;
    output << "PALETTE Rainbow" << endl;
    output << "ZOOM_X 4" << endl << endl;

    currentJob = NULL;
    clock = 0.0;
}

Processor::~Processor()
{
    output.close();
    //cout << "Chiuso\n";
}

int Processor::execute(Job *j)
{
    if(j != NULL)
    {
        preempt();
        currentJob = j;
        print(EXECB,currentJob->getID());
    }
    if(currentJob != NULL)
        currentJob->incrementElapsed(STEP);

    clock+=STEP;

    if (currentJob != NULL && currentJob->getElapsedTime() == currentJob->getExecTime())
    {
        print(STOP,currentJob->getID());
        print(READYE,currentJob->getID());
        preempt();
        return 1;
    }
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

bool Processor::idle()
{
    return (currentJob == NULL);
}

void Processor::print(JobState state, int jobID, float time)
{
    string out = "";
    stringstream sout(out);
    if(time == -1)
        time = clock;
    sout << time << " " << state << " " << jobID << endl;
    out = sout.str();
    output << out;
    output.flush();
}

float Processor::getClock(){
    return clock;
}
