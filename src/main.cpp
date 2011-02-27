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

#define TIMESLICE 2
#define DURATION 250

void loadCheck(int loaded,string name);
void utiliz(SchedulerRR &rr);
float getTimeslice();

int main (int argc, char *argv[])
{
    int loaded,input=3;
    float timeslice=TIMESLICE,duration=DURATION;

    vector<string> tasks;
    vector<string> ptasks;

    cout << "Choose test (0 - 6)" << endl << ">>";
    cin >> input;

    switch(input)
    {
    case 0:
        {
            //Testare con timeslice 2 e 3
            tasks.push_back("0/S1");
            tasks.push_back("0/S2");
            tasks.push_back("0/S3");
            timeslice = getTimeslice();
            break;
        }
    case 1:
        {
            //Testare con timeslice 2
            tasks.push_back("1/S1");
            tasks.push_back("1/S2");
            tasks.push_back("1/S3");
            timeslice = 2;
            break;
        }
    case 2:
        {
            //Testare con timeslice 2 e 3
            ptasks.push_back("2/T0");
            ptasks.push_back("2/T1");
            ptasks.push_back("2/T2");
            duration = 210;
            timeslice = getTimeslice();
            break;
        }
    case 3:
        {
            //Testare con timeslice 2
            ptasks.push_back("3/T0");
            ptasks.push_back("3/T1");
            ptasks.push_back("3/T2");
            tasks.push_back("3/A1");
            timeslice = 2;
            break;
        }
    case 4:
        {
            ptasks.push_back("4/T0");
            ptasks.push_back("4/T1");
            ptasks.push_back("4/T2");
            ptasks.push_back("4/T3");
            duration = 110;
            timeslice = 1;
            break;
        }
    case 5:
        {
            //Deferrable server, esercizio 7.4 prima parte
            tasks.push_back("5/A1");
            ptasks.push_back("5/T0");
            ptasks.push_back("5/T1");
            duration = 90;
            timeslice = 1;
            break;
        }
    }


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

float getTimeslice()
{
    float timeslice;
    cout << endl << "Timeslice" << endl << ">>";
    cin >> timeslice;
    return timeslice;
}
