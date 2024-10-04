/*
Permission is hereby granted for the copying, distribution,
modification and use of this program and associated documentation
for recreational purposes, provided that all references to the
authors are retained.  However, permission is not and will not be
granted for the sale or promotional use of this program or program
documentation, or for use in any situation in which profit may be
considered an objective, since it is the desire of the authors to
respect the copyrights of the originators of the game.
 
This software and source code are distributed on an
"AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, either express
or implied.
*/

#include "crewdialog.h"
#include "colors.h"

void printDialog(enum CREW m, char *c)
{
    clprintf("%s", clrbrblue);
    if(m == CAPTAIN) clprintf("Captain");
    else if(m == SPOCK) clprintf("Mr. Spock");
    else if(m == UHURA) clprintf("Lt. Uhura");
    else if(m == SCOTTY) clprintf("Engineer Scott");
    else if(m == BONES) clprintf("Bones");
    else if(m == CHEKOV) clprintf("Ensign Chekov");
    else if(m == SULU) clprintf("Helsman Sulu");

    clprintf("%s", clrdefault);
    clprintf(": %s\n", c);
} // printDialog
