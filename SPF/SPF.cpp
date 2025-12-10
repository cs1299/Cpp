//
// Created by 47764 on 2025/12/9.
//

#include "SPF.h"
void CreateQueueWithRuntime(TASK_s* task,TASKQueue* ready_queue,int index);
void SPF_RUN(TASK_s* task_list,int num)
{
    static int pronum = 1;
    static int last_pronum=0;
    int index=0;
    static TASK_s*temp=nullptr;
    int time,sys_done_time,sys_start_time;
    sortWithEnterTime(tasks);
    TASKQueue* ready_queue_ = (TASKQueue*)malloc(sizeof(TASKQueue));;
    if (ready_queue_==nullptr)
    {
        std::cout<<"分配就绪队列头结点空间失败！"<<std::endl;
        exit(1);
    }
    TaskQueueInit(ready_queue_);
    sys_start_time=get_time();
    std::cout<<"系统开始"<<std::endl;
    while(pronum<=10)
    {
        time=get_time();
        sys_done_time=time-sys_start_time;

        if (sys_done_time>task_list[index].arrivetime && index<num)
        {
            CreateQueueWithRuntime(&task_list[index],ready_queue_,index);
            index++;
        }

        if (last_pronum!=pronum && ready_queue_->firstProg->next!=nullptr )
        {

            temp=PullQueue(ready_queue_);
            temp->start_time=get_time();
            last_pronum=pronum;
            std::cout << "正在执行进程：" << temp->name << std::endl;
        }
        if (temp!=nullptr)
        {
            temp->running_time=time - temp->start_time;
            if (temp->running_time>=temp->serve_time)
            {
                pronum++;
                temp->done_time=sys_done_time;
                std::cout << "结束时间：" << temp->done_time << std::endl;
            }
        }


    }


}

void CreateQueueWithRuntime(TASK_s* task,TASKQueue* ready_queue,int index)
{

    TASK_s*p,*q;
    p=ready_queue->firstProg->next;
    q=ready_queue->firstProg;
    while (p && index<=9)//队头插入、队末取
    {
        if (p->serve_time>task->serve_time)
        {
            task->next=p;
            q->next=task;
            break;
        }
        q=p;
        p=p->next;
        //if (index>=9)return;
    }
    if (!p)
    {
        ready_queue->LastProg->next=task;
        ready_queue->LastProg=task;
        task->next=nullptr;
    }
    ready_queue->size++;

}