//
// Created by 28339 on 2025/12/9.
//

#ifndef J_DEV_CONFIG_H
#define J_DEV_CONFIG_H
#include <queue>
#include <set>
#include <malloc.h>
#include <iostream>
#include <string.h>
#include <time.h>
#include <stdio.h>

typedef enum
{
    TASK_READY,   //就绪态
    TASK_RUNNING, //运行态
    TASK_WAIT,    //阻塞态
} task_status_t;

typedef enum
{
    a_FCFS = 1,   //先来先服务
    a_SPF,        //短进程优先
    a_RR,         //时间片轮转
    a_HRRN,       //高响应比优先调度算法
} algorithm_choose;

typedef struct TASK_s
{
    task_status_t status = TASK_WAIT;    //进程状态
    char name[20];             //进程名称 (输入)
    int  arrivetime;           //到达时间 (输入)
    int  serve_time;           //服务时间 (输入)
    float  priority;           //优先级
    float dqzztime;            //记录该进程的带权周转时间（后期复制用）
    int  start_time = -1;      //开始时间
    int  done_time;            //结束时间
    int  running_time;         //已运行时间
    int  waiting_time = 0;     //等待时间
    int  slice_time = 0;       //运行过的时间片数
    TASK_s* next=nullptr;
}TASK_s;

typedef struct
{
    TASK_s* firstProg;
    TASK_s* LastProg;
    int size;
} TASKQueue;

/*---USER_DEFINE_BEGIN-------------------------------------------------------------*/
#define TASK_NUM    10       //总任务数
#define UNIT_TIME   0.05f   //单位时间 s
#define TIME_SLICE  5        //时间片时长为几个单位时间,使用时间片轮转时有效
/*---USER_DEFINE_END---------------------------------------------------------------*/
extern TASK_s tasks[TASK_NUM];

void sortWithEnterTime(TASK_s* task_list);
TASK_s* PullQueue(TASKQueue* queue);
void EnterQueue(TASKQueue* queue,TASK_s* task);
void TaskQueueInit(TASKQueue* queue);
int get_time(void);
void algorithm_start_print(algorithm_choose a);
void task_start_print(TASK_s task, int time);
void algorithm_end_print(void);
float get_average_turnaround_time(TASK_s task[]);
void print_summerize(TASK_s task[]);

#endif //J_DEV_CONFIG_H
