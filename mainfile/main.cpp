#include <iostream>
#include "main.h"
#include "SPF.h"
#include <Windows.h>

using namespace std;

int main()
{
    int choice;
    printf("/**---------------MENU---------------**/");
    printf("/* type number to choose algorithm:   */\n");
    printf("/*  1.FCFS                            */\n");
    printf("/*  2.SPF                             */\n");
    printf("/*  3.RR                              */\n");
    printf("/*  4.HRRN                            */\n");
    printf("/**----------------------------------**/\n");
    printf("Enter your choice:");
    scanf("%d",&choice);
    switch(choice)
    {
        case a_FCFS:
            FCFS(tasks);
            break;
        case a_SPF:

            break;
        case a_RR:
            RR(tasks);
            break;
        case a_HRRN:

            break;
    }
    print_summerize(tasks);
    return 0;
}
