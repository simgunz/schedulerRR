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
//#include <sstring>



Processor::Processor(string outputFile)
{
    output.open(outputFile.c_str());
    clock = 0.0;
}

Processor::~Processor()
{
    output.close();
    cout << "chiuso\n";
}

void Processor::execute(Job &j,float T)
{
//    if (j!=NULL)
//    {
        print(EXECB,j.getID());
        clock+=T;
        cout << "Clock=" << clock << endl;
        print(EXECE,j.getID());
        j.incrementElapsed(T);
//    }
//    else
//        t++;
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
