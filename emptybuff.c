/***********************************************************************
 * emptybuff.c
 * Function for the purpose of emptying buffer + command effiency
 * Version I
 * ********************************************************************/

#include "emptybuff.h"
#include "winnot.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

void emptyBuffer(void)
{
    while(getchar() != '\n')
    {
        ;
    }
}

void pause(char prompt[])
{
    printf(prompt);
    emptyBuffer();
}

_Bool yesNo(char prompt[])
{
    char choose;
    _Bool loop = 1;
    _Bool answer;
    while(loop)
    {
        printf("%s", prompt);
        while(!scanf("%c", &choose))
        {
            emptyBuffer();
            printf("Incorrect input");
        }
        switch(choose)
        {
            case 'y':
            case 'Y':
                answer = 1;
                loop = 0;
                break;
            case 'n':
            case 'N':
                answer = 0;
                loop = 0;
                break;
            default:
                break;
        }
        emptyBuffer();
    }
    return answer;
}

int select(char title[], int optNum, char optName[][MAXL])
{
    char arrow[optNum];
    arrow[0] = '>';
    for(int i = 1; i < optNum; i++)
    {
        arrow[i] = ' ';
    }
    
    _Bool valid = 1;
    char input;
    char temp;
    int search = 0;
    while(valid)
    {
        system((WINN)?"cls":"clear");
        printf("%s", title);
        for(int i = 0; i < optNum; i++)
        {
            printf("%c %s\n", arrow[i], optName[i]);
        }
        input = getch();
        switch(input)
        {
            case 'w':
            case 'W':
                temp = arrow[0];
                for(int i = 0; i < optNum; i++)
                {
                    arrow[i] = arrow[i+1];
                }
                arrow[optNum-1] = temp;
                break;
            case 's':
            case 'S':
                temp = arrow[optNum-1];
                for(int i = optNum - 1; i > 0; i--)
                {
                    arrow[i] = arrow[i - 1];
                }
                arrow[0] = temp;
                break;
            case 13:
                while(arrow[search] != '>')
                {
                    search++;
                }
                return search;
                break;
            default:
                break;
        }
    }
    return -1;
}
