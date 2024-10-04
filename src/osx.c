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

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#ifndef WINDOWS
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>
#endif

void randomize(void) {
	srand((int)time(NULL));
}

#ifndef WINDOWS
int max(int a, int b) {
	if (a > b) return a;
	return b;
}

int min(int a, int b) {
	if (a < b) return a;
	return b;
}

int getch(void) {
    char chbuf[1];
    struct termios oldstate, newstate;
    fflush(stdout);
	tcgetattr(0, &oldstate);
	newstate = oldstate;
	newstate.c_lflag &= ~ICANON;
	newstate.c_lflag &= ~ECHO;
	tcsetattr(0, TCSANOW,  &newstate);
	read(0, &chbuf, 1);
	tcsetattr(0, TCSANOW, &oldstate);
        return chbuf[0];
}
#endif
