#include <iostream>
#include "main.h"
#include "SPF.h"
#include <Windows.h>
using namespace std;
int main() {
    //cout << "Hello, World!" << endl;
    SetConsoleOutputCP(CP_UTF8);//输出中文方法2
    SPF_RUN(tasks,10);
    system("pause");
    return 0;
}
