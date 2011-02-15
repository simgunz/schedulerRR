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

#define TIMESLICE 2

void loadCheck(int loaded,string name);
void utiliz(SchedulerRR &rr);

int main (int argc, char *argv[])
{
    int loaded ;
    int input = 0;

    cout << "Choose (0 -10)\n\n>>";
    cin >> input;

    switch(input)
    {
    case 0:{
        SchedulerRR rr0(2,1000);
        Task t1a("T1");
        loaded = rr0.loadTask(t1a);
        loadCheck(loaded,t1a.getName());
        rr0.schedule();
        break;
    }
    case 1:{
        SchedulerRR rr1(3,1000);
        Task t1b("T1");
        loaded = rr1.loadTask(t1b);
        loadCheck(loaded,t1b.getName());
        rr1.schedule();
        break;
    }
    case 2:{
        SchedulerRR rr2(2,1000);
        Task t1pr("T1PR");
        loaded = rr2.loadTask(t1pr);
        loadCheck(loaded,t1pr.getName());
        rr2.schedule();
        break;
    }
    }

    //Variazione della timeslice con un singolo task sporadico

    //Task composto di 3 job senza priorità (Testare con timeslice 2 e 3)
    /*
    Task t("T1");
    loaded = rr.loadTask(t);
    loadCheck(loaded,t.getName());
    */

    //Task composto di 3 job di cui i primi due con priorità 1 (Testare con timeslice 2)
    /*
    Task t("T1PR");
    loaded = rr.loadTask(t);
    loadCheck(loaded,t.getName());
    */


    //Variazione della priorità dei singoli job

    //Task composto di 3 job senza priorità (Testare con timeslice 3)
    /*
    Task t("T2");
    loaded = rr.loadTask(t);
    loadCheck(loaded,t.getName());
    */

    //Task composto di 3 job con priorità crescenti in funzione della criticità (Testare con timeslice 3)
    /*
    Task t("T2PR");
    loaded = rr.loadTask(t);
    loadCheck(loaded,t.getName());
    */


    //Variazione della timeslice con due task periodici

    //Due task periodici senza priorità (Testare con timeslice 2 e 3)
    /*
    PeriodicTask pta("PT3A",170);
    loaded = rr.loadTask(pta);
    loadCheck(loaded,pta.getName());
    utiliz(rr);

    PeriodicTask ptb("PT3B",120);
    loaded = rr.loadTask(ptb);
    loadCheck(loaded,ptb.getName());
    utiliz(rr);
    */


    //Variazione della priorità dei task

    //Due task periodici senza priorità, il job 2 del task 2 ha priorità 1 (Testare con timeslice 3)
    /*
    PeriodicTask pta("PT4A",170);
    loaded = rr.loadTask(pta);
    loadCheck(loaded,pta.getName());
    utiliz(rr);

    PeriodicTask ptb("PT4B",113);
    loaded = rr.loadTask(ptb);
    loadCheck(loaded,ptb.getName());
    utiliz(rr);
    */

    //Due task periodici: il primo senza senza priorità, il secondo con priorità 1,
    //il job 2 del task 2 ha priorità 1 (che quindi diventa 11 sommandola alla priorità del task) (Testare con timeslice 3)
    /*
    PeriodicTask pta("PT4A",170);
    loaded = rr.loadTask(pta);
    loadCheck(loaded,pta.getName());
    utiliz(rr);

    PeriodicTask ptb("PT4B",113,1);
    loaded = rr.loadTask(ptb);
    loadCheck(loaded,ptb.getName());
    utiliz(rr);
    */

    //rr.schedule();

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
