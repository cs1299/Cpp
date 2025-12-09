//
// Created by 28339 on 2025/12/9.
//

#ifndef J_DEV_CONFIG_H
#define J_DEV_CONFIG_H

typedef struct TASK_s
{
    char name[20];             //进程名称 (输入)
    int  arrivetime;           //到达时间 (输入)
    int  serve_time;           //服务时间 (输入)
    int  priority;             //优先级
    int  start_time;           //开始时间
    int  done_time;            //结束时间
    int  running_time;         //已运行时间
    TASK_s* next;
};

extern TASK_s tasks[10];

#endif //J_DEV_CONFIG_H
