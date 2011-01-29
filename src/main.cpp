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

using namespace std;

#include "task.h"
#include "periodictask.h"
#include "processor.h"
#include "schedulerRR.h"

#include <iostream>
#include <sstream>

#define TIMESLICE 3
#define DURATION 100

int main (int argc, char *argv[])
{

    Task t1("Task3");
    Task t("Task2");
    PeriodicTask pt("Task1",17),pt1("Task",10);

    Processor proc;
    SchedulerRR rr(proc,TIMESLICE,DURATION);
    rr.loadTask(t);
    rr.loadTask(t1);
    rr.loadTask(pt);
    //rr.loadTask(pt1);
    rr.loadTask(t);
    rr.schedule();
    return 0;
}
