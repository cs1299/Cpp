#include <iostream>
#include "main.h"
#include "SPF.h"
#include <Windows.h>
using namespace std;
<<<<<<< Updated upstream
int main() {
    //cout << "Hello, World!" << endl;
    SetConsoleOutputCP(CP_UTF8);//输出中文方法2
    SPF_RUN(tasks,10);
    //system("pause");
=======

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
>>>>>>> Stashed changes
    return 0;
}
