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

#include "processor.h"

#include <iostream>
#include <string>
//#include <sstring>



Processor::Processor(char *outputFile)
{
    output.open(outputFile);
    clock = 0.3;
}

Processor::~Processor()
{
    output.close();
    cout << "chiuso";
}

void Processor::execute(Job *j = NULL)
{
//    if (j!=NULL)
//    {
//        print(EXECB,j.getID());
//        t++;
//        print(EXECE,j.getID());
//    }
//    else
//        t++;
}

void Processor::print(JobState state, int jobID)
{
    string out = "";
    stringstream sout(out);
    sout << clock << " " << state << " " << jobID << endl;
    out = sout.str();
    output << out;
    output.flush();
}
