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
    while (1)
    {

    }
}

