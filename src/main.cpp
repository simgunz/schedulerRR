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

#define TIMESLICE 1
#define DURATION 250

void loadCheck(int loaded,string name);
void utiliz(SchedulerRR &rr);

int main (int argc, char *argv[])
{
    int loaded ;
    //int input,
    int timeslice=TIMESLICE;

    Task *t = NULL;
    PeriodicTask *pt = NULL;
    vector<string> tasks;
    vector<string> ptasks;

    //tasks.push_back("T1");
    //tasks.push_back("T2");

    ptasks.push_back("TP1");
    ptasks.push_back("TP2");
    //ptasks.push_back("TP3");

    SchedulerRR rr(timeslice,DURATION);

    for (int i=0; i<ptasks.size(); i++)
    {
        pt = new PeriodicTask(ptasks[i]);
        loaded = rr.loadTask(*pt);
        loadCheck(loaded,ptasks[i]);
        utiliz(rr);
    }

    for (int i=0; i<tasks.size(); i++)
    {
        t = new Task(tasks[i]);
        loaded = rr.loadTask(*t);
        loadCheck(loaded,tasks[i]);
    }

    rr.schedule();

////////////////////////DISTRUTTORE


//    cout << "Choose test (0 - 6)" << endl << ">>";
//    cin >> input;
//    cout << endl << "Timeslice" << endl << ">>";
//    cin >> timeslice;

//    switch(input)
//    {
//        //Testare con timeslice 2 e 3
//    case 0:{
//        SchedulerRR rr0(timeslice,DURATION);
//        Task t1a("T1");
//        loaded = rr0.loadTask(t1a);
//        loadCheck(loaded,t1a.getName());
//        rr0.schedule();
//        break;
//        }
//        //Testare con timeslice 2
//    case 1:{
//        SchedulerRR rr1(timeslice,DURATION);
//        Task t1pr("T1PR");
//        loaded = rr1.loadTask(t1pr);
//        loadCheck(loaded,t1pr.getName());
//        rr1.schedule();
//        break;
//        }
//    case 2:{
//            //Testare con timeslice 3
//            SchedulerRR rr2(timeslice,DURATION);
//            Task t2a("T2");
//            loaded = rr2.loadTask(t2a);
//            loadCheck(loaded,t2a.getName());
//            rr2.schedule();
//            break;
//        }
//    case 3:{
//            //Testare con timeslice 3
//            SchedulerRR rr3(timeslice,DURATION);
//            Task t2b("T2PR");
//            loaded = rr3.loadTask(t2b);
//            loadCheck(loaded,t2b.getName());
//            rr3.schedule();
//            break;
//        }
//    case 4:{
//            //Testare con timeslice 2 e 3
//            SchedulerRR rr4(timeslice,DURATION);
//            PeriodicTask pt3a("PT3A",170);
//            loaded = rr4.loadTask(pt3a);
//            loadCheck(loaded,pt3a.getName());
//            utiliz(rr4);
//            PeriodicTask pt3b("PT3B",120);
//            loaded = rr4.loadTask(pt3b);
//            loadCheck(loaded,pt3b.getName());
//            utiliz(rr4);
//            rr4.schedule();
//            break;
//        }
//    case 5:{
//            //Testare con timeslice 3
//            SchedulerRR rr5(timeslice,DURATION);
//            PeriodicTask pt4a("PT4A",170);
//            loaded = rr5.loadTask(pt4a);
//            loadCheck(loaded,pt4a.getName());
//            utiliz(rr5);
//            PeriodicTask pt4b("PT4B",113);
//            loaded = rr5.loadTask(pt4b);
//            loadCheck(loaded,pt4b.getName());
//            utiliz(rr5);
//            rr5.schedule();
//            break;
//        }
//    case 6:{
//            //Testare con timeslice 3
//            SchedulerRR rr6(timeslice,DURATION);
//            PeriodicTask pt5a("PT4A",170);
//            loaded = rr6.loadTask(pt5a);
//            loadCheck(loaded,pt5a.getName());
//            utiliz(rr6);
//            PeriodicTask pt5b("PT4B",113,1);
//            loaded = rr6.loadTask(pt5b);
//            loadCheck(loaded,pt5b.getName());
//            utiliz(rr6);
//            rr6.schedule();
//            break;
//        }
//    }

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
