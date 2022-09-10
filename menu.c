/***********************************************************************
 * menu.c
 * main menu functions
 * Ver III
 * ********************************************************************/

#include "menu.h"

#include "emptybuff.h"
#include "winnot.h"
#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <sys/stat.h>
#include <errno.h>

/* Select option from menu */
void option(struct audWav wave)
{
    char mazeT[] = 
       "    __  __  __  ______ __  __  __________  ______  __  __\n"
       "   / / / / / / /     / | |/ / / __  __  / /     / / / / /\n"
       "  / / / / / / / __  /  |   / / / / / / / / __  / / /_/ /\n"
       " / /_/ /_/ / / / / /   |  / / / / / / / / / / / / ___  \\\n"
       "/_________/ /_/ /_/    |_/ /_/ /_/ /_/ /_/ /_/ /_/   \\__\\\n"
       "===============Use WASD keys to Navigate==================\n";
    char opt[4][MAXL] = {"Create Sample", "Option", "About", "Exit"};
    _Bool valid = 1;
    
    while(valid)
    {
        int sel = select(mazeT, 4, opt);
        switch(yesNo("Are you sure? [y/N]: "))
        {
            case 1:
                switch(sel)
                {
                    case 0:
                        makWav(wave);
                        break;
                    case 1:
                        wave = config(wave);
                        break;
                    case 2:
                        about();
                        break;
                    default:
                        valid = 0;
                        closing(wave);
                        break;
                }
                break;
            default:
                break;    
        }
    }
}

void about(void)
{
    system((WINN)?"cls":"clear");
    textFold("'WavMak' is a program that allow users to design and "
    "create waveform and exported as short samples that can be used in "
    "DAWs, samplers and music-trackers. Using a method of FM synthesis "
    "where sine waves are added together (the superposition of all "
    "waves) to create any kind of wave function possible.\n\n"
            "\t+========+\n"
            "\t+Tutorial+\n"
            "\t+========+\n\n"
    "How to Create a Sample?\n"
    "-----------------------\n"
    "1. Select 'Create Sample' from main menu\n"
    "2. Give your file a appropriate Name, this will be saved in "
    "whatever file location you have selected it to.\n"
    "3. Choose what foundational note or frequency you’d like the "
    "sample to be in (A = 440, C = 261.63)\n"
    "4. Enter a Volume (this will be a value between 1 and 0).\n"
    "\tNow comes the most important part. Entering the sine wave inform"
    " that will dictate your wave shape.\n"
    "5. First Enter the Number of Harmonics (or sine waves) that will "
    "comprise your waveform.\n"
    "6. than you will asked to enter the Amplitude (between 1 and -1) "
    "and Harmonic (1 to infinite) for each sine wave. For example, to "
    "enter a wave with a amplitude of 0.5 and harmonic of 3 – you’d "
    "enter: \n\n"
    "Enter amplitude & harmonic (?h?): 0.5h3\n\n"
    "7. you than will be asked if all the information above is correct,"
    " if so enter 'Y' and your file will be created and once "
    "complete... DONE! You’ve now created your first sample. "
    "Congrats!!!\n\n"
    "How to change/choose file directory?\n"
    "------------------------------------\n"
    "If you want to change where your samples are exported. Then you "
    "will need to change to sample directory. This can be done by:\n"
    "1. Select 'Option' from main menu\n"
    "2. Then select 'File Location'\n"
    "3. Now you have many ways to create a directory\n"
    "\tYou can enter a single Directory e.g.\n"
    "Enter File Location Directory: sample\n"
    "\tIf you want to a specific directory than you can use '\\'\n"
    "Enter File Location Directory: test\\sample\n"
    "\tIf you want a specific location within your Drive\n"
    "Enter File Location Directory: C:\\Users\\NAME\\Desktop\\sample");
    pause("Press Enter to Return to Menu...");
}

/* To fold long text around itself so as to be more readable to user */
void textFold(char text[])
{
    int ch = 0, sc = 0;
    while(text[ch] != '\0')
    {
        printf("%c", text[ch]);
        if(text[ch] == '\n')
        {
            sc = 0;
        }
        if(sc == 65)
        {
            if(text[ch] != ' ')
            {
                while(text[ch] != ' ')
                {
                    ch++;
                    printf("%c", text[ch]);
                }
                ch++;
            }
            printf("\n");
            sc = 0;
        }
        else
        {
            sc++;
            ch++;
        }
    }
    printf("\n\n");
}

struct audWav Initial(void)
{
    struct audWav wave = {"RIFF", 0, "WAVE", "fmt ", 16, 1, 1, 44100, 0,
                                            0, 16, "data", 0, "", ""};
    wave.byteRate = wave.sampleRate * wave.channelNum * 
                                                     (wave.fmtSize / 8);
    wave.blockAlign = wave.channelNum * (wave.fmtSize / 8);
    _Bool def = yesNo("Would you like to set up WavMak to previous "
    "configurations? if no than WavMake will be set to default "
    "settings\n [y/N]: ");
    
    FILE *fConfig;
    switch(def)
    {
        case 1:
            if((fConfig = fopen("wakmak.config", "r")) == NULL)
            {
                printf("Could not open File to read to...");
                exit(1);
            }
            fscanf(fConfig, "%d\n%d\n%s", &wave.channelNum, 
                                       &wave.sampleRate, wave.location);
            if(mkdir(wave.location) == -1)
            {
                switch(errno)
                {
                    case EACCES:
                        pause("Permission to create directory not "
                                                             "allowed");
                        break;
                    case ENAMETOOLONG:
                        pause("pathname is too long");
                        break;
                    default:
                        break;
                }
            }
            break;
        default:
            break;
    }
    return wave;
}

void closing(struct audWav wave)
{
    FILE* fConfig;
    switch(yesNo("Would you like to save current settings? [y/N]: "))
    {
        case 1:
            if((fConfig = fopen("wakmak.config", "w")) == NULL)
            {
                printf("Could not open File to write to...");
                exit(2);
            }
            fprintf(fConfig, "%d\n%d\n%s", wave.channelNum, 
                                        wave.sampleRate, wave.location);
            break;
        default:
            break;
    }
}
