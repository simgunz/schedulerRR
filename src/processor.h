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

#include <string>
#include <sstream>
#include <map>

#define STEP 1

class Processor
{
public:
    Processor();
    float getClock() const;
    int execute(Job *j = NULL);
    void preempt();
    bool idle() const;
    void setMaxDeadline(float deadline);
    void print(JobState state, int jobID, float time = -1, string text = "", bool reverse = false);
    void filePrint();
    void rowLabel(int line,string label);

private:
    float clock;
    stringstream initParam;
    Job *currentJob;
    float maxdeadline;
    map<float,string> out;
};

#endif // PROCESSOR_H
