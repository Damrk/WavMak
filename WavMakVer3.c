/***********************************************************************
 * WavMak.c
 * WavMak is a sample maker that will create wav files that can be used 
 by music trackers
 * Ver III
 * ********************************************************************/

#include "menu.h"

int main(void)
{
    struct audWav wave = Initial();
    option(wave);
    return 0;
}


