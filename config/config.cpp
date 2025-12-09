//
// Created by 28339 on 2025/12/9.
//

#include "config.h"
#include <string.h>
TASK_s tasks[10] =
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

void TaskQueueInit(TASKQueue* queue)
{
    if (queue == NULL)
    {
        return;
    }
    queue->LastProg = new TASK_s;
    queue->firstProg = queue->LastProg;
    queue->LastProg->next=nullptr;
    queue->size = 0;
}

void EnterQueue(TASKQueue* queue,TASK_s* task)//加入进程
{
    queue->LastProg->next =(TASK_s*)malloc(sizeof(TASK_s));
    queue->LastProg = queue->LastProg->next;
    memcpy(queue->LastProg->name, task->name, sizeof(task->name));
    queue->LastProg->priority = task->priority;
    queue->LastProg->running_time = task->running_time;
    queue->LastProg->copyRunning_time = task->copyRunning_time;
    queue->LastProg->next = nullptr;
    queue->size++;
}
TASK_s* PullQueue(TASKQueue* queue)//取出进程
{
    if (queue->size == 0)
    {
        return nullptr;
    }

    TASK_s* temp = queue->firstProg->next;
    queue->firstProg->next = temp->next;
    queue->size--;
    if (queue->size == 0)
    {
        queue->LastProg = queue->firstProg;
    }
    return temp;
}

void sortWithEnterTime(TASK_s* task_list)
{
    TASK_s temp;
    for (int i = 0; i < 10; i++)
    {
        for (int t= i+1;t<10;t++)
        {
            if (task_list[i].arrivetime > task_list[t].arrivetime)
            {
                temp = task_list[i];
                task_list[i] = task_list[t];
                task_list[t] = temp;
            }
        }
    }
}

void CopyProgram(TASK_s *pro1,TASK_s *pro2) {
    memcpy(pro1->name,pro2->name,sizeof(pro2->name));
    pro1->arrivetime=pro2->arrivetime;
    pro1->running_time=pro2->running_time;
    pro1->priority=pro2->priority;
    pro1->start_time=pro2->start_time;
    pro1->done_time=pro2->done_time;
    pro1->zztime=pro2->zztime;
    pro1->dqzztime=pro2->dqzztime;
}
