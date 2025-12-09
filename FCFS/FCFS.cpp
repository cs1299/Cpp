//
// Created by 47764 on 2025/12/9.
//

#include "FCFS.h"
#include <stdio.h>
#include "config.h"

/**
 *
 * @param tasks 任务数组
 */
void FCFS(TASK_s tasks[])
{
    int task_num = sizeof(tasks)/sizeof(*tasks);
    sortWithEnterTime(tasks);
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
            tasks[i].status = TASK_READY;
            i++;
        }
        if (ready_queue.size != 0)
        {
            //当就绪队列不为空
            //运行任务
            // ready_queue.firstProg->running_time
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
    }
}

