#include "main.h"
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
            SPF_RUN(tasks, TASK_NUM);
            algorithm_end_print();
            break;
        case a_RR:
            RR(tasks);
            break;
        case a_HRRN:
            HRRN_RUN(tasks, TASK_NUM);
            algorithm_end_print();
            break;
    }
    print_summerize(tasks);
    system("pause");
    return 0;
}
