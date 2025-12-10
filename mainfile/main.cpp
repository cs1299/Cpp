#include <iostream>
#include "main.h"
#include "SPF.h"
#include <Windows.h>
#include "config.h"
#include "FCFS.h"
#include "RR.h"

using namespace std;

int main()
{
    // FCFS(tasks);
    RR(tasks);
    print_summerize(tasks);
    return 0;
}
