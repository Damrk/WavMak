/***********************************************************************
 * WavMak.c
 * WavMak is a sample maker that will create wav files that can be used 
 by music trackers
 * CandNo: 231001
 * Ver III
 * ********************************************************************/

#include "menu.h"

int main(void)
{
    struct audWav wave = Initial();
    option(wave);
    return 0;
}


