/***********************************************************************
 * emptybuff.h
 * emptybuff header file
 * Version I
 * ********************************************************************/
#ifndef EMPTYBUFF_H
#define EMPTYBUFF_H
#include "wavfil.h"

void emptyBuffer(void);
void pause(char prompt[]);
_Bool yesNo(char prompt[]);
int select(char title[], int optNum, char optName[][MAXL]);

#endif
