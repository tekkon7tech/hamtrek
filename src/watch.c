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


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "watch.h"
#include "hamtrek.h"

void* watch_thread(void* arg)
{
    int sleeptime = 1200;
    int x = 0;

    while(TRUE)
    {
        if(!_active) return NULL;
        sleep(1);

        if(!_sleep) { _sleep = TRUE; x = 0; }
        else
        {
            x++;
            if(x >= sleeptime) { _active = FALSE; fflush(stdout); exit(0); }
        }
    }
    return NULL;
} // watch_thread
