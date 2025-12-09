//
// Created by 28339 on 2025/12/9.
//

#ifndef J_DEV_CONFIG_H
#define J_DEV_CONFIG_H
#include <queue>
#include <set>
#include <malloc.h>
#define TASK_NUM 10
typedef enum
{
    TASK_READY,//就绪态
    TASK_RUNNING,//运行态
    TASK_WAIT,//阻塞态
} task_status_t;

typedef struct TASK_s
{
    task_status_t status;    //进程状态
    char name[20];             //进程名称 (输入)
    int  arrivetime;           //到达时间 (输入)
    int  serve_time;           //服务时间 (输入)
    int  priority;             //优先级
    int  copyRunning_time;     //用于时间片轮转
    float zztime;              //记录该进程的周转时间（后期复制用）
    float dqzztime;            //记录该进程的带权周转时间（后期复制用）
    int  start_time;           //开始时间
    int  done_time;            //结束时间
    int  running_time;         //已运行时间
    TASK_s* next=nullptr;
}TASK_s;

typedef struct  {
    TASK_s* firstProg;
    TASK_s* LastProg;
    int size;
} TASKQueue;
extern TASK_s tasks[10];
void sortWithEnterTime(TASK_s* task_list);
TASK_s* PullQueue(TASKQueue* queue);
void EnterQueue(TASKQueue* queue,TASK_s* task);
void TaskQueueInit(TASKQueue* queue);
int get_time(void);

#endif //J_DEV_CONFIG_H
