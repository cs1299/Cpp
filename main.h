#ifndef MAIN_H
#define MAIN_H
#include <iostream>

typedef enum
{
    TASK_READY,//就绪态
    TASK_RUNNING,//运行态
    TASK_WAIT,//阻塞态
} task_status_t;


typedef struct
{
    /* data */
} task_t;

#endif // MAIN_H