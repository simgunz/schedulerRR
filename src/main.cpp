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
#include <string>
#include <vector>

//Durata in nanosecondi
//Step processore 1 nanosecondo (1GHz)

#define TIMESLICE 3
#define DURATION 250

void loadCheck(int loaded,string name);
void utiliz(SchedulerRR &rr);

int main (int argc, char *argv[])
{
    int loaded,input;
    float timeslice=TIMESLICE;
    float duration=DURATION;

    vector<string> tasks;
    vector<string> ptasks;

//    cout << "Choose test (0 - 6)" << endl << ">>";
//    cin >> input;
//    cout << endl << "Timeslice" << endl << ">>";
//    cin >> timeslice;
//    cout << endl << "Timeslice" << endl << ">>";
//    cin >> duration;

//    switch(input)
//    {
//    case 0:
//        {
//            ptasks.push_back("TP1");
//            ptasks.push_back("TP2");
//            break;
//        }
//    case 1:
//        {
//            tasks.push_back("T1");
//            tasks.push_back("T2");
//            break;
//        }
//    }

    //Carico i nomi dei file che rappresentano task aperiodici/sporadici
    tasks.push_back("T1");
    tasks.push_back("T2");

    //Carico i nomi dei file che rappresentano task periodici
    ptasks.push_back("TP1");
    ptasks.push_back("TP2");
    ptasks.push_back("TP3");

    SchedulerRR rr(timeslice,duration);

    for (unsigned int i=0; i<ptasks.size(); i++)
    {
        loaded = rr.loadTask(PeriodicTask(ptasks[i]));
        loadCheck(loaded,ptasks[i]);
        utiliz(rr);
    }

    for (unsigned int i=0; i<tasks.size(); i++)
    {
        loaded = rr.loadTask(Task(tasks[i]));
        loadCheck(loaded,tasks[i]);
    }

    rr.schedule();

    return 0;
}


void loadCheck(int loaded, string name)
{
    cout << "Task "<< name;
    switch(loaded)
    {
    case 0:
        cout << " inserito correttamente" << endl;break;
    case 1:
        cout << " non valido" << endl;break;
    case 2:
        cout << " non inserito, sistema sovraccarico" << endl;break;
    }
}

void utiliz(SchedulerRR &rr)
{
    cout << "Carico del processore: " << rr.getUtilization()*100 << "%" << endl;
}
