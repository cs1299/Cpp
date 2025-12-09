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
void SortWithEnterTime(TASK_s tasks[], int size)
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
    SortWithEnterTime(tasks, task_num);
    TASKQueue ready_queue;
    TaskQueueInit(&ready_queue);
    printf("FCFS开始运行");
    int i = 0;
    int last_size = ready_queue.size;
    int init_time = get_time();
    while (1)
    {
<<<<<<< Updated upstream
=======
<<<<<<< Updated upstream
=======
>>>>>>> Stashed changes
        if (tasks[i].arrivetime<= get_time() - init_time)
        {
            //按到达时间依次将任务放进就绪队列
            last_size = ready_queue.size;
            EnterQueue(&ready_queue, &tasks[i]);
<<<<<<< Updated upstream
=======
            tasks[i].status = TASK_READY;
>>>>>>> Stashed changes
            i++;
        }
        if (ready_queue.size != 0)
        {
            //当就绪队列不为空
<<<<<<< Updated upstream
            //运行任务
            ready_queue.firstProg->running_time
        }
=======
            if (ready_queue.firstProg->status == TASK_READY)
            {

                ready_queue.firstProg->status = TASK_RUNNING;
                ready_queue.firstProg->start_time = get_time() - init_time;
                printf("%s\t%d",ready_queue.firstProg->name,ready_queue.firstProg->start_time);

            }
            else if (ready_queue.firstProg->status == TASK_RUNNING)
            {
                if (ready_queue.firstProg->running_time == ready_queue.firstProg->serve_time)
                {
                    //如果运行时长等于设定的服务时长

                }
            }
        }
>>>>>>> Stashed changes
>>>>>>> Stashed changes

    }
}

