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


//Nuovo tipo di dato che può assumere i valori necessari a descrivere gli stati di kiwi
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
    Job();                                      //Costruttore senza parametri, usato per dichiarare variabili non inizializzate
    Job(float R, float D, float E,int P=0);     //Costruttore con parametri, utilizzato per creare il job
    bool operator>(const Job &j) const;         //Operatore utilizzato per confrontare i release time di due job
    bool operator<(const Job &j) const;         //Operatore utilizzato per confrontare le deadline di due job
    int getID() const;                          //Restituisce l'ID del job
    int getPriority() const;                    //Restituisce la priorità del job
    float getReleaseTime() const;               //Restituisce il release time del job
    float getDeadline() const;                  //Restituisce la deadline del job
    float getExecTime() const;                  //Restituisce il tempo di esecuzione del job
    float getElapsedTime() const;               //Restituisce il tempo in cui il job è già stato processato
    void setID(int ID);                         //Imposta l'ID del job
    void incElapsedTime(float EL);              //Incrementa il tempo in cui il job è già stato processato
    bool isValid(float period    = 0);          //Controlla che il job sia valido, ovvero che i paramentri siano ben definiti

private:
    int id;     //Job ID
    int p;      //Priority
    float r;    //Release time
    float d;    //Deadline
    float e;    //Execution time
    float el;   //Elapsed time
};

#endif // JOB_H
