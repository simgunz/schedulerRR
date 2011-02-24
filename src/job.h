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

class Job
{
public:
    Job() { e = -1;}                                     //Costruttore senza parametri, usato per dichiarare variabili non inizializzate
    Job(float R, float E, float D,int PR=0,int ID=0);     //Costruttore con parametri, utilizzato per creare il job
    bool operator>(const Job &j) const;                  //Operatore utilizzato per confrontare i release time di due job
    inline int getID() const { return id; }              //Restituisce l'ID del job
    inline int getTID() const { return tid; }            //Restituisce l'ID del task a cui appartiene il job
    inline int getPriority() const { return pr; }         //Restituisce la priorità del job
    inline float getReleaseTime() const { return r; }    //Restituisce il release time del job
    inline float getExecTime() const { return e; }       //Restituisce il tempo di esecuzione del job
    inline float getDeadline() const { return d; }       //Restituisce la deadline del job
    inline float getElapsedTime() const { return el; }   //Restituisce il tempo in cui il job è già stato processato
    inline void setID(int ID) { id = ID; }               //Imposta l'ID del job
    inline void setTID(int TID) { tid = TID; }           //Imposta l'ID del task a cui appartiene il job
    inline void incElapsedTime(float EL) { el += EL; }   //Incrementa il tempo in cui il job è già stato processato
    bool isValid();                                      //Controlla che il job sia valido, ovvero che i paramentri siano ben definiti

private:
    int id;     //Job ID
    int tid;    //Task ID
    int pr;      //Priority
    float r;    //Release time
    float e;    //Execution time
    float d;    //Relative deadline
    float el;   //Elapsed time
};

#endif // JOB_H
