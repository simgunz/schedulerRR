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

#ifndef JOB_H
#define JOB_H

using namespace std;


enum JobState{
        START,
        STOP,
        DEADLINE,
        EXECB,
        EXECE,
        READYB,
        READYE,
        VLINE = 12,
        TEXTOVER = 13
};


class Job
{
public:
    Job();
    Job(float R, float D, float E,int P=0);
    bool operator>(const Job &j) const;  //Utilizzato per confrontare i release time
    bool operator<(const Job &j) const;  //Utilizzato per confrontare le deadline
    int getID() const;
    int getPriority() const;
    float getReleaseTime() const;
    float getDeadline() const;
    float getExecTime() const;
    float getElapsedTime() const;
    void setID(int ID);
    void incElapsedTime(float EL);
    bool isValid(float p = 0);

private:
    int id;     //Job ID
    int p;      //Priority
    float r;    //Release time
    float d;    //Deadline
    float e;    //Execution time
    float el;   //Elapsed time
};

#endif // JOB_H
