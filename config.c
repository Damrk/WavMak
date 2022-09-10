/***********************************************************************
 * config.c
 * configuration options for .wav file
 * Ver III
 * ********************************************************************/

#include "config.h"
#include "winnot.h"
#include "emptybuff.h"
#include "wavfil.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

struct audWav config(struct audWav wave)
{
    system((WINN)?"cls":"clear");
    char opt[4][MAXL] = {"File Location", "Sample Rate", 
                                    "Channel Number", "Return to Menu"};
    _Bool valid = 1;
    while(valid)
    {
        int sel = select("Options\n=======\n",4, opt);
        switch(sel)
        {
            case 0:
                wave = chanFileLoc(wave);
                waveContent(wave);
                break;
            case 1:
                wave.sampleRate = chanSampleR(wave);
                waveContent(wave);
                break;
            case 2:
                wave.channelNum = chanChanNum(wave);
                waveContent(wave);
                break;
            default:
                valid = 0;
                break;
        }
    }
    return wave;
}

/* Change file Directory and/or create directory */
struct audWav chanFileLoc(struct audWav wave)
{
    char loc[MAXL] = "";
    _Bool loop = 1;
    _Bool answer;
    system((WINN)?"cls":"clear");
    while(loop)
    {
        printf("Enter File Location Directory [Enter '#' to exit]: ");
        scanf("%[^\n]", loc);
        emptyBuffer();
        if(strcmp(loc, "#") == 0)
        {
            loop = 0;
        }
        else if(strcmp(loc, "") == 0)
        {
            strcpy(wave.location, "");
            loop = 0;
        }
        else
        {
            if(mkdir(loc) == -1)
            {
                switch(errno)
                {
                    case EACCES:
                        printf("%s ", wave.location);
                        pause("Permission to create directory not "
                                                             "allowed");
                        break;
                    case EEXIST:
                        printf("%s ", wave.location);
                        answer = yesNo("pathname already exists. Do you"
                                   " want files to save here? [y/N]: ");
                        switch(answer)
                        {
                            case 1:
                                loop = 0;
                                break;
                            default:
                                break;
                        }
                        break;
                    case ENAMETOOLONG:
                        printf("%s ", wave.location);
                        pause("pathname is too long");
                        break;
                    default:
                        pause("Error - unknown");
                        break;
                }
            }
            else
            {
                printf("%s ", wave.location);
                pause("Directory successfully created");
                loop = 0;
            }
            strcpy(wave.location, loc);
        }
    }
    return wave;
}
int chanSampleR(struct audWav wave)
{
    char opt[][MAXL] = {"44100 Hz", "48000 Hz", "88200 Hz", "96000 Hz", 
                                                 "192000 Hz", "Return"};
    int Hz;
    int sel = select("Channel\n=======\n", 6, opt);
    switch(sel)
    {
        case 0:
            Hz = 44100;
            break;
        case 1:
            Hz = 48000;
            break;
        case 2:
            Hz = 88200;
            break;
        case 3:
            Hz = 96000;
            break;
        case 4:
            Hz = 192000;
            break;
        default:
            Hz = wave.sampleRate;
            break;
    }
    return Hz;
}
int chanChanNum(struct audWav wave)
{
    int num;
    char opt[][MAXL] = {"One", "Two", "Return"};
    int sel = select((wave.channelNum==2?"Currently: Stereo\nChannel "
    "Number\n==============\n":"Currently: Mono\nChannel Number\n======"
                                                 "========\n"), 3, opt);
    switch(sel)
    {
        case 0:
            num = 1;
            break;
        case 1:
            num = 2;
            break;
        default:
            num = wave.channelNum;
            break;
    }
    return num;
}

