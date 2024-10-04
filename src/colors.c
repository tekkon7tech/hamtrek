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
#include <stdarg.h>
#include "colors.h"

// ANSI escape codes for color
const char *clrblack = "\033[30m";
const char *clrred = "\033[31m";
const char *clrgreen = "\033[32m";
const char *clryellow = "\033[33m";
const char *clrblue = "\033[34m";
const char *clrpurple = "\033[35m";
const char *clrcyan = "\033[36m";
const char *clrwhite = "\033[37m";

const char *clrbrblack = "\033[90m";
const char *clrbrred = "\033[91m";
const char *clrbrgreen = "\033[92m";
const char *clrbryellow = "\033[93m";
const char *clrbrblue = "\033[94m";
const char *clrbrpurple = "\033[95m";
const char *clrbrcyan = "\033[96m";
const char *clrbrwhite = "\033[97m";

const char *clrreset = "\033[0m"; // Reset
const char *clrdefault = "\033[96m"; // bright cyan

void clprintf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}

void SetSRScanColor(char c)
{
    if(c == 'E') printf("%s", clrcyan);
    else if(c == 'B') printf("%s", clrbrcyan);
    else if(c == 'P') printf("%s", clrbrblue);
    else if(c == 'S') printf("%s", clrbrred);
    else if(c == 'C') printf("%s", clrred);
    else if(c == 'K') printf("%s", clrred);
    else if(c == 'R') printf("%s", clrgreen);
    else if(c == '*') printf("%s", clrbryellow);
    else printf("%s", clrbrblue);
} // SetSRScanColor

void ShowLRScanColors(int galaxy)
{
    int thousands = galaxy / 1000;
    int hundreds = (galaxy / 100) % 10;
    int tens = (galaxy / 10) % 10;
    int digits = galaxy % 10;
    
    clprintf(" %s", clrbrblue);
    if(thousands > 0) clprintf("%s%d%s", clrbrpurple, thousands, clrbrblue); else clprintf(" ");
    if(hundreds > 0) clprintf("%s%d%s", clrbrred, hundreds, clrbrblue); else clprintf(".");
    if(tens > 0) clprintf("%s%d%s", clrbrcyan, tens, clrbrblue); else clprintf(".");
    if(digits > 0) clprintf("%s%d%s", clrbryellow, digits, clrbrblue); else clprintf(".");
    clprintf("%s", clrdefault);
} // ShowLRScanColors

void SetColor(const char *c) { printf("%s", c); } // SetColor
void DefaultGameColor(void) { printf("%s", clrbrcyan); } // DefaultGameColor
void ResetTerminalColor(void) { printf("%s", clrreset); } // ResetTerminalColor

/*
\e[0;30m 	Black
\e[0;31m 	Red
\e[0;32m 	Green
\e[0;33m 	Yellow
\e[0;34m 	Blue
\e[0;35m 	Purple
\e[0;36m 	Cyan
\e[0;37m 	White

High Intensity
\e[0;90m 	Black
\e[0;91m 	Red
\e[0;92m 	Green
\e[0;93m 	Yellow
\e[0;94m 	Blue
\e[0;95m 	Purple
\e[0;96m 	Cyan
\e[0;97m 	White

Background
Value 	Color
\e[40m 	Black
\e[41m 	Red
\e[42m 	Green
\e[43m 	Yellow
\e[44m 	Blue
\e[45m 	Purple
\e[46m 	Cyan
\e[47m 	White

High Intensity backgrounds
Value 	Color
\e[0;100m 	Black
\e[0;101m 	Red
\e[0;102m 	Green
\e[0;103m 	Yellow
\e[0;104m 	Blue
\e[0;105m 	Purple
\e[0;106m 	Cyan
\e[0;107m 	White
// */
