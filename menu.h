#ifndef MENU_H
#define MENU_H

#include "wavfil.h"


/* Prototypes */
void option(struct audWav wave);
void about(void);
void textFold(char text[]);
struct audWav Initial(void);
void closing(struct audWav wave);

#endif
