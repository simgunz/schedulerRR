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

void loadCheck(int loaded,int utilization);

int main (int argc, char *argv[])
{
    Processor proc;
    SchedulerRR rr(3,1000);
    int loaded;

    PeriodicTask pt1("PT1",120);
    PeriodicTask pt2("PT1",10);
    PeriodicTask pt3("PT3",10);


    loaded = rr.loadTask(pt2);
    loadCheck(loaded,rr.getUtilization());
    loaded = rr.loadTask(pt1);
    loadCheck(loaded,rr.getUtilization());
    loaded = rr.loadTask(pt3);
    loadCheck(loaded,rr.getUtilization());

    rr.schedule();

    return 0;
}

void loadCheck(int loaded,int utilization)
{
    if (loaded)
        cout << "Task not loaded, system overload" << endl;
    else
        cout << "Processor utilization: " << utilization << "%" << endl;
}
