//
// Created by 47764 on 2025/12/9.
//

#include "SPF.h"
void SPF_RUN(TASK_s* task_list,int num)
{
    int time,done_time;
    sortWithEnterTime(tasks);
    TASKQueue* ready_queue = (TASKQueue*)malloc(sizeof(TASKQueue));;
    if (ready_queue==nullptr)
    {
        std::cout<<"分配就绪队列头结点空间失败！"<<std::endl;
        exit(1);
    }

    TaskQueueInit(ready_queue);

}

void CreateQueueWithRuntime(TASK_s* task,TASKQueue* ready_queue)
{
    TASK_s*p,*q;
    p=ready_queue->firstProg->next;
    q=ready_queue->firstProg;
    while (p)//队头插入、队末取
    {
        if (p->serve_time>task->serve_time)
        {
            task->next=p;
            q->next=task;
        }
        q=p;
        p=p->next;
    }
    if (!p)
    {
        q->next=task;
        task->next=nullptr;
    }
    ready_queue->size++;
}