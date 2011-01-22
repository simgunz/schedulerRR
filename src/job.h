/*
 * Copyright (C) 2010 Simone Gaiarin <simgunz@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#ifndef JOB_H
#define JOB_H

using namespace std;

#include <string>


enum JobState{
        START,
        STOP,
        DEADLINE,
        EXECB,
        EXECE,
};


class Job
{
public:
    Job(string data);
    bool operator<(const Job &j) const;  //Used for comparing release time
    int getID();
    float getReleaseTime();
    float getDeadLine();
    float getExecTime();
    float getElapsedTime();

private:

    void init(std::string data);
    int id;     //Job ID
    float r;    //Release time
    float d;    //Deadline
    float ex;    //Execution time
    float el;   //Elapsed time
};

#endif // JOB_H
