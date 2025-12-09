//
// Created by 47764 on 2025/12/9.
//

#include "FCFS.h"
#include <stdio.h>

/**
 * @brief FCFS  先来先服务
 * @param tasks 任务数组
 */
void FCFS(TASK_s tasks[])
{
    sortWithEnterTime(tasks);    //按到达先后顺序排序
    TASKQueue ready_queue;       //创建就绪队列
    TaskQueueInit(&ready_queue); //初始化就绪队列
    printf("--------------FCFS start---------------\n");
    int i = 0;
    int init_time = get_time();  //任务调度开始时间
    while (1)
    {
        int nowtime = get_time() - init_time;
        if ((nowtime > tasks[TASK_NUM-1].arrivetime) && (ready_queue.size == 0))
        {
            //如果全部任务都到达了且就绪队列里没有任务要执行
            printf("--------------all tasks done----------------!\n");
            return;
        }
        if (tasks[i].arrivetime <= nowtime && i < TASK_NUM)
        {
            //按到达时间依次将任务放进就绪队列
            tasks[i].status = TASK_READY;
            EnterQueue(&ready_queue, &tasks[i]);
            i++;
        }
        if (ready_queue.size != 0)
        {
            //当就绪队列不为空
            if (ready_queue.firstProg->next->status == TASK_READY)
            {
                //刚开始执行某任务
                ready_queue.firstProg->next->status = TASK_RUNNING;
                ready_queue.firstProg->next->start_time = nowtime;
                printf("%s   %d\n",ready_queue.firstProg->next->name,ready_queue.firstProg->next->start_time);
            }
            else if (ready_queue.firstProg->next->status == TASK_RUNNING)
            {
                ready_queue.firstProg->next->running_time = nowtime - ready_queue.firstProg->next->start_time;
                if (ready_queue.firstProg->next->running_time >= ready_queue.firstProg->next->serve_time)
                {
                    //如果运行时长等于设定的服务时长
                    //任务执行完成
                    ready_queue.firstProg->next->done_time = nowtime;
                    PullQueue(&ready_queue);
                }
            }
        }
    }
}

