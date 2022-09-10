/***********************************************************************
 * wavfil.c
 * Implementation file for wavfil header file
 * version II
 * ********************************************************************/
#include "wavfil.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "emptybuff.h"
#include "winnot.h"

#define PI 3.14

/* Option to Create Wave File */
void makWav(struct audWav wave)
{
    char fileLocation[MAXL];
    struct sinHarm harm[HARM];
    struct prop waveProp;
    
    do
    {
        system((WINN)?"cls":"clear");
        wave = inputFileName(wave, fileLocation);
        waveProp.note = inputNote();
        waveProp.volume = inputVolume();
        waveProp.volume /= 100;
        waveProp.tperiod = inputDuration();
        waveProp.same = inputSame(wave);
        inputHarmSin(&waveProp, harm, wave);
    }while(!yesNo("Is Everything Correct? [y/N]: "));
    FILE *Wfile = fileConstruct(fileLocation, wave);
    createWave(wave, harm, Wfile, waveProp);
    waveContent(wave);       
}

/* Enter Num and Sin data */
void inputHarmSin(struct prop *waveProp, struct sinHarm harm[], 
                                                     struct audWav wave)
{
    printf(((*waveProp).same?"Enter Wave Data:\n":"Enter Wave Data: "
                                                        "channel 1\n"));
    (*waveProp).num[0] = inputNumHarm();
    inputSin(harm, (*waveProp).num[0], 1);
    if(!(*waveProp).same && wave.channelNum == 2)
    {
        printf("Enter Wave Data: Channel 2\n");
        (*waveProp).num[1] = inputNumHarm();
        inputSin(harm, (*waveProp).num[1], 2);
    }
}

/* File Construction */
FILE *fileConstruct(char name[], struct audWav wave)
{
    FILE *Wfile;
    if((Wfile = fopen(name, "wb")) == NULL)
    {
        printf("Could not open File to write to...");
        exit(1);
    }
    
    fwrite(wave.riffId, 4, 1, Wfile);
    fwrite(&wave.riffSize, 4, 1, Wfile);
    fwrite(wave.format, 4, 1, Wfile);
    
    fwrite(wave.fmtId, 4, 1, Wfile);
    fwrite(&wave.fmtSize, 4, 1, Wfile);
    fwrite(&wave.audioFormat, 2, 1, Wfile);
    fwrite(&wave.channelNum, 2, 1, Wfile);
    fwrite(&wave.sampleRate, 4, 1, Wfile);
    fwrite(&wave.byteRate, 4, 1, Wfile);
    fwrite(&wave.blockAlign, 2, 1, Wfile);
    fwrite(&wave.bitsPerSample, 2, 1, Wfile);
    
    fwrite(wave.dataId, 4, 1, Wfile);
    fwrite(&wave.dataSize, 4, 1, Wfile);
    
    return Wfile;
}

/* Displays WAVE data */
void waveContent(struct audWav wave)
{
    printf("Wave - Format\n"
           "=============\n");
    printf("riffId:        \t%s\n"
           "riffSize:      \t%d\n"
           "format:        \t%s\n\n"
           "fmtId:         \t%s\n"
           "fmtSize:       \t%d\n"
           "audioFormat:   \t%d\n"
           "channelNum:    \t%d\n"
           "sampleRate:    \t%d\n"
           "byteRate:      \t%d\n"
           "blockAlign:    \t%d\n"
           "bitsPerSample: \t%d\n\n"
           "dataId:        \t%s\n"
           "dataSize:      \t%d\n\n"
           "File Location: \t%s\n", wave.riffId, wave.riffSize, 
           wave.format, wave.fmtId, wave.fmtSize, wave.audioFormat, 
           wave.channelNum, wave.sampleRate, wave.byteRate, 
           wave.blockAlign, wave.bitsPerSample, wave.dataId, 
           wave.dataSize, wave.location);
    pause("Press enter to continue");
}

/*Input file name and combine with file location*/
struct audWav inputFileName(struct audWav wave, char fileLocation[MAXL])
{
    _Bool check = 0;
    while(!check)
    {
        printf("Enter File Name: ");
        scanf("%[a-z A-Z 0-9]", wave.fileName);
        emptyBuffer();
        if(yesNo("Are you sure? [y/N]: "))
        {
            check = 1;    
        }   
    }
    if(strcmp(wave.location,"") != 0)
    {
        sprintf(fileLocation, "%s\\%s.wav", wave.location, 
                                                         wave.fileName);
    }
    else
    {
        sprintf(fileLocation, "%s.wav", wave.fileName);
    }
    return wave;
}

 /*Enter foundamental frequency*/
_Bool inputNote(void)
{
    _Bool check = 0;
    _Bool note;
    char choice;
    while(!check)
    {
        printf("Enter note A(440) or C(261): ");
        scanf("%c", &choice);
        emptyBuffer();
        switch(choice)
        {
            case 'a':
            case 'A':
                note = 0;
                check = 1;
                break;
            case 'c':
            case 'C':
                note = 1;
                check = 1;
                break;
            default:
                printf("\nInvalid input\n");
                break;
        }   
    }
    return note;
}

/*Enter volume(amplitude) of audio wave */
double inputVolume(void)
{
    _Bool check = 0;
    double volume;
    while(!check)
    {
        printf("Enter Volume [100 - 0]: ");
        while(!scanf("%lf", &volume))
        {
            emptyBuffer();
            printf("\nInvalid input\nEnter Volume [100 - 0]: ");
        }
        if(volume <= 100 && volume >= 0)
        {
            check = 1;    
        }
        emptyBuffer();     
    }
    return volume;
}

/* Enter Number of Harmonics */
int inputNumHarm(void)
{
    int num = 0;
    _Bool check = 1;
    while(check)
    {
        printf("Enter number of Harmonics: ");
        while(!scanf("%d", &num))
        {
            emptyBuffer();
            printf("\nInvalid Input\nEnter number of Harmonics: ");
        }
        emptyBuffer();
        if(num > 0 && num <= HARM)
        {
            check = 0;
        }
        else
        {
            printf("\nInvalid Input - Out of Range (1 to %d)\n", HARM);    
        }   
    }
    return num;
}

/* Enter Amplitude and Harmonic of waves */
void inputSin(struct sinHarm harm[], int num, int chan)
{
    chan--;
    _Bool check;
    for(int i = 0; i < num; i++)
    {
        check = 0;
        while(!check)
        {
            printf("%d. Enter amplitude & harmonic [?h?]: ", i+1);
            while(!scanf("%lfh%d", &harm[i].amplitude[chan], 
                                               &harm[i].harmonic[chan]))
            {
                emptyBuffer();
                printf("\nInvalid Input\n%d. Enter amplitude & harmonic"
                                                     " [?h?]: ", i+1);
            }
            emptyBuffer();
            if(harm[i].amplitude[chan] <= 1 && 
                                          harm[i].amplitude[chan] >= -1)
            {
                check = 1;
                for(int j = 0; j < i; j++)
                {
                    if(harm[i].harmonic[chan] == harm[j].harmonic[chan])
                    {
                        printf("Harmonic already used\n");
                        check = 0;
                    }
                }
            }
            else
            {
                printf("Amplitude has to be between 1 and -1\n");
            }
        }
    }
}

/* Input duration of audio file (in time periods) */
int inputDuration(void)
{
    int tperiod;
    _Bool check = 1;
    while(check)
    {
        printf("Enter Duration (in time period[s]): ");
        while(!scanf("%d", &tperiod))
        {
            emptyBuffer();
            printf("\nInvalid Input\nEnter Duration (in relation to "
                                                      "time period): ");
        }
        if(tperiod > 0)
        {
            check = 0;
        }
        else
        {
            printf("\nInvalid Input - Out of Range\n");    
        }
        emptyBuffer();   
    }
    return tperiod;
}

/* If creating a stereo file than do you want the same or different wave 
*/
_Bool inputSame(struct audWav wave)
{
    _Bool same = 1;
    if(wave.channelNum == 2)
    {
        switch(yesNo("You are creating a stereo sample.\nWould you like"
                         " to create a wave for each channel? [y/N]: "))
        {
            case 1:
                same = 0;
                break;
            default:
                same = 1;
                break;
        }   
    }
    return same;
}

/* Write Wave Data to array than file */
void createWave(struct audWav wave, struct sinHarm harm[], FILE *Wfile, 
                                                   struct prop waveProp)
{
    int audioStart = ftell(Wfile); /* Binary size*/
    fpos_t refp; /* position in file */
    fgetpos(Wfile, &refp);

    /* Temp loop */
    double frq = (waveProp.note?261.63:440);
    double duration = (1/frq) * waveProp.tperiod;
    int long bits = duration * wave.sampleRate;
    bits++;
    int channel1[bits];
    int channel2[bits];
    for(int i = 0; i <= bits; i++)
    {
        channel1[i] = 0;
        channel2[i] = 0;
    }
    
    for(int i = 0; i < bits; i++)
    {
        for(int j = 0; j < waveProp.num[0]; j++)
        {
            channel1[i] += sin((i * 2 * PI * frq * harm[j].harmonic[0]) 
            / wave.sampleRate) * (AMPMAX * waveProp.volume * 
               harm[j].amplitude[0]); /* Sin(Time * 2 * pi * frquency)*/
            if(channel1[i] > AMPMAX)
            {
                channel1[i] = AMPMAX;
            }
            else if(channel1[i] < -AMPMAX)
            {
                channel1[i] = -AMPMAX;
            }   
        }
        printf("channeldata: %d\n", channel1[i]);
        if(!waveProp.same)
        {
            for(int j = 0; j < waveProp.num[1]; j++)
            {
                channel2[i] += sin((i * 2 * PI * frq * 
                harm[j].harmonic[1]) / wave.sampleRate) * 
                (AMPMAX * waveProp.volume * harm[j].amplitude[1]); 
                /* Sin(Time * 2 * pi * frquency)*/
                if(channel2[i] > AMPMAX)
                {
                    channel2[i] = AMPMAX;
                }
                else if(channel2[i] < -AMPMAX)
                {
                    channel2[i] = -AMPMAX;
                }    
            }
            printf("channeldata: %d\n", channel2[i]);   
        }
    }
    for(int i = 0; i < bits; i++)
    {
        fwrite(&channel1[i], 2, 1, Wfile);
        if(wave.channelNum == 2)
        {
            if(waveProp.same)
            {
                fwrite(&channel1[i], 2, 1, Wfile);   
            }
            else
            {
                fwrite(&channel2[i], 2, 1, Wfile);
            }
        }
        printf("Progress: [%.0lf/100]\n", ((double)i/bits) * 100);
    }
    finishWave(wave, audioStart, refp, Wfile);
}

/* changes dataSize and riffSize */
void finishWave(struct audWav wave, int audioStart, fpos_t refp, 
                                                            FILE *Wfile)
{
    size_t audioEnd = ftell(Wfile);
    wave.dataSize = (int)audioEnd - audioStart;
    wave.riffSize = (int)audioEnd - 8;
    
    fsetpos(Wfile, &refp);
    fseek(Wfile, -4, SEEK_CUR);
    fwrite(&wave.dataSize, 4, 1, Wfile);
    fseek(Wfile, 4, SEEK_SET);
    fwrite(&wave.riffSize, 4, 1, Wfile);
    fclose(Wfile);
    printf("%s.wav Successfully Complete!!!\n", wave.fileName);
}
