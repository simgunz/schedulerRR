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

#ifndef PROCESSOR_H
#define PROCESSOR_H

using namespace std;

#include "job.h"
//#include "schedulerRR.h"

#include <fstream>
#include <sstream>



class Processor
{
public:
    Processor(char *outputFile);
    ~Processor();
    //friend SchedulerRR::SchedulerRR(Processor proc)
    void execute(Job *j);
    void print(JobState state, int jobID);

private:
    float clock;
    ofstream output;
};

#endif // PROCESSOR_H
