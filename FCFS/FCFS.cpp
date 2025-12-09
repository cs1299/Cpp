//
// Created by 47764 on 2025/12/9.
//

#include "FCFS.h"
#include <stdio.h>
#include "config.h"

/**
 * @brief sortWithEnterTime 按到达顺序排序
 * @param tasks 要排序的任务数组
 * @param size 任务个数
 */
void sortWithEnterTime(TASK_s tasks[], int size)
{
    TASK_s temp;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size - 1; j++)
        {
            if (tasks[j].arrivetime > tasks[j + 1].arrivetime)
            {
                temp = tasks[j];
                tasks[j] = tasks[j + 1];
                tasks[j + 1] = temp;
            }
        }
    }
}

/**
 *
 * @param tasks 任务数组
 */
void FCFS(TASK_s tasks[])
{
    int task_num = sizeof(tasks)/sizeof(*tasks);
    sortWithEnterTime(tasks, task_num);
    TASKQueue ready_queue;
    TaskQueueInit(&ready_queue);
    printf("FCFS开始运行");
    int i = 0;
    int last_size = ready_queue.size;
    int init_time = get_time();
    while (1)
    {
        if (tasks[i].arrivetime<= get_time() - init_time)
        {
            //按到达时间依次将任务放进就绪队列
            last_size = ready_queue.size;
            EnterQueue(&ready_queue, &tasks[i]);
            i++;
        }
        if (ready_queue.size != 0)
        {
            //当就绪队列不为空
            //运行任务
            ready_queue.firstProg->running_time
        }

    }
}

