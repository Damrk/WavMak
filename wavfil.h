/***********************************************************************
 * wavfil.h
 * Constants and functions involved in the creation and manipulation of 
 the wave file.
 * Version I
 * ********************************************************************/
#ifndef WAVFIL_H
#define WAVFIL_H

#include <stdio.h>

#define AMPMAX 32767
#define MAXL 100
#define HARM 100

struct audWav {
    char riffId[5];
    int riffSize;
    char format[5];
    char fmtId[5];
    int fmtSize;
    int audioFormat;
    int channelNum; /* 1 = Mono or 2 = Stereo */
    int sampleRate;
    int byteRate;
    int blockAlign;
    int bitsPerSample;
    char dataId[5];
    int dataSize;
    char location[MAXL];
    char fileName[MAXL];
};

struct sinHarm {
    double amplitude[2];
    unsigned int harmonic[2];
};

struct prop {
    _Bool note;
    _Bool same;
    double volume;
    int tperiod;
    int num[2];
};

/* Function */
void makWav(struct audWav wave);
void inputHarmSin(struct prop *waveProp, struct sinHarm harm[], 
                                                    struct audWav wave);
FILE *fileConstruct(char name[], struct audWav wave);
void waveContent(struct audWav wave);
struct audWav inputFileName(struct audWav wave, char fileLocation[]);
_Bool inputNote(void);
double inputVolume(void);
int inputNumHarm(void);
void inputSin(struct sinHarm harm[], int num, int chan);
int inputDuration(void);
_Bool inputSame(struct audWav wave);
void createWave(struct audWav wave, struct sinHarm harm[], 
                                     FILE *Wfile, struct prop waveProp);
void finishWave(struct audWav wave, int audioStart, fpos_t refp, 
                                                           FILE *Wfile);
#endif
