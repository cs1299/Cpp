//
// Created by 28339 on 2025/12/9.
//

#include "config.h"
#include <string.h>
#include <time.h>
#include <malloc.h>
#include <stdio.h>

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

// void EnterQueue(TASKQueue* queue,TASK_s* task)//加入进程
// {
//     queue->LastProg->next =(TASK_s*)malloc(sizeof(TASK_s));
//     queue->LastProg = queue->LastProg->next;
//     memcpy(queue->LastProg->name, task->name, sizeof(task->name));
//     queue->LastProg->priority = task->priority;
//     queue->LastProg->running_time = task->running_time;
//     queue->LastProg->copyRunning_time = task->copyRunning_time;
//     queue->LastProg->arrivetime = task->arrivetime;
//     queue->LastProg->serve_time = task->serve_time;
//     queue->LastProg->status = task->status;
//     queue->LastProg->next = nullptr;
//     queue->size++;
// }

void EnterQueue(TASKQueue* queue,TASK_s* task)//加入进程
{
    task->status = TASK_READY;
    queue->LastProg->next =task;
    queue->LastProg = queue->LastProg->next;
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

/**
 * @brief sortWithEnterTime 按到达顺序排序
 * @param task_list 要排序的任务数组
 */
void sortWithEnterTime(TASK_s* task_list)
{
    TASK_s temp;
    for (int i = 0; i < TASK_NUM - 1 - i; i++)
    {
        int swapped = 0;
        for (int j = 0; j < TASK_NUM - 1; j++)
        {
            if (tasks[j].arrivetime > tasks[j + 1].arrivetime)
            {
                temp = tasks[j];
                tasks[j] = tasks[j + 1];
                tasks[j + 1] = temp;
                swapped = 1;
            }
        }
        if (swapped == 0)break;
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

/**
 * @brief get_time 获取时间
 * @return int 程序运行单位时间
 */
int get_time(void)
{
    clock_t t;
    t = clock();
    int time = ((double)t / CLOCKS_PER_SEC) / UNIT_TIME;
    return time;
}

/**
 * @brief get_average_turnaround_time 获取平均周转时间
 * @param task 任务数组
 * @return float 平均周转时间
 */
float get_average_turnaround_time(TASK_s task[])
{
    float average_turnaround_time = 0;
    for (int i = 0; i < TASK_NUM; i++)
    {
        average_turnaround_time += task[i].done_time - task[i].arrivetime;
    }
    average_turnaround_time = average_turnaround_time / (float)TASK_NUM;
    return average_turnaround_time;
}

/**
 * @brief algorithm_start_print 调度算法开始时打印
 * @param a 选择的调度算法
 */
void algorithm_start_print(algorithm_choose a)
{
    switch (a)
    {
        case a_FCFS:
            printf("/**--------FCFS--------**/\n");
            break;
        case a_SPF:
            printf("/**--------SPF---------**/\n");
            break;
        case a_RR:
            printf("/**---------RR---------**/\n");
            break;
        case a_HRRN:
            printf("/**--------HRRN--------**/\n");
            break;
    }
    printf("/* task_name \t time\t*/\n");
}

/**
 * @brief task_start_print 任务开始执行时打印
 * @param task 任务
 * @param time 任务开始运行时间
 */
void task_start_print(TASK_s task, int time)
{
    printf("/* %s \t\t  %d\t*/\n",task.name, time);
}

/**
 * @brief algorithm_end_print 调度算法执行完成后打印
 */
void algorithm_end_print(void)
{
    printf("/**---all task done----**/\n");
}

/**
 * @brief print_summerize 打印总结
 * @param task 任务数组
 */
void print_summerize(TASK_s task[])
{
    printf("/**-----------------------------SUMMERIZE------------------------------**/\n");
    printf("/*   task name \t\tarrive time\tstart time\tend time\t*/\n");
    for (int i = 0; i < TASK_NUM; i++)
    {
        printf("/*   %s \t\t%d\t\t%d\t\t%d\t\t*/\n", task[i].name, task[i].arrivetime, task[i].start_time, task[i].done_time);
    }
    printf("/*   average turnaround time = %.2f                                    */\n", get_average_turnaround_time(task));
    printf("/**--------------------------------------------------------------------**/\n");
}
