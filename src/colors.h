
#ifndef COLORS_H
#define COLORS_H

// ANSI escape codes for color
extern const char *clrblack;
extern const char *clrred;
extern const char *clrgreen;
extern const char *clryellow;
extern const char *clrblue;
extern const char *clrpurple;
extern const char *clrcyan;
extern const char *clrwhite;

extern const char *clrbrblack;
extern const char *clrbrred;
extern const char *clrbrgreen;
extern const char *clrbryellow;
extern const char *clrbrblue;
extern const char *clrbrpurple;
extern const char *clrbrcyan;
extern const char *clrbrwhite;

extern const char *clrreset;
extern const char *clrdefault;

void SetSRScanColor(char);
void ShowLRScanColors(int);
void SetColor(const char*);
void DefaultGameColor(void);
void ResetTerminalColor(void);
void clprintf(const char*, ...);

#endif
