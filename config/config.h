//
// Created by 28339 on 2025/12/9.
//

#ifndef J_DEV_CONFIG_H
#define J_DEV_CONFIG_H
#include <queue>
#include <set>

typedef enum
{
    TASK_READY,   //就绪态
    TASK_RUNNING, //运行态
    TASK_WAIT,    //阻塞态
} task_status_t;

typedef struct TASK_s
{
    task_status_t status = TASK_WAIT;    //进程状态
    char name[20];             //进程名称 (输入)
    int  arrivetime;           //到达时间 (输入)
    int  serve_time;           //服务时间 (输入)
    float  priority;           //优先级
    int  copyRunning_time;     //用于时间片轮转
    float zztime;              //记录该进程的周转时间（后期复制用）
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
#define UNIT_TIME   0.005f   //单位时间 s
#define TIME_SLICE  5        //时间片时长为几个单位时间,使用时间片轮转时有效

TASK_s tasks[TASK_NUM] =
{
    {.name = "P1", .arrivetime = 5, .serve_time = 20},
    {.name = "P2", .arrivetime = 17, .serve_time = 10},
    {.name = "P3", .arrivetime = 25, .serve_time = 15},
    {.name = "P4", .arrivetime = 33, .serve_time = 30},
    {.name = "P5", .arrivetime = 45, .serve_time = 20},
    {.name = "P6", .arrivetime = 50, .serve_time = 15},
    {.name = "P7", .arrivetime = 60, .serve_time = 5},
    {.name = "P8", .arrivetime = 68, .serve_time = 10},
    {.name = "P9", .arrivetime = 80, .serve_time = 25},
    {.name = "P10", .arrivetime = 100, .serve_time = 40},
};
/*---USER_DEFINE_END---------------------------------------------------------------*/

void sortWithEnterTime(TASK_s* task_list);
TASK_s* PullQueue(TASKQueue* queue);
void EnterQueue(TASKQueue* queue,TASK_s* task);
void TaskQueueInit(TASKQueue* queue);
int get_time(void);

#endif //J_DEV_CONFIG_H
