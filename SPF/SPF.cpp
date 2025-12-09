//
// Created by 47764 on 2025/12/9.
//

#include "SPF.h"
void SPF_SOFT(TASK_s* task_list,int num,TASKQueue* ready_queue);
void SPF_RUN(TASK_s* task_list,int num)
{
    static int systick=0;
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
    //CreateQueueWithRuntime(&task_list[0],ready_queue_);
    sys_start_time=get_time();

    while(pronum<=10)
    {
        time=get_time();
        sys_done_time=time-sys_start_time;
        std::cout<<"系统时间片："<<sys_done_time<<" 当前时间："<<time<<std::endl;
        if (sys_done_time>task_list[index].arrivetime && index<num)
        {
            CreateQueueWithRuntime(&task_list[index],ready_queue_);
            index++;
        }

        if (last_pronum!=pronum && ready_queue_->firstProg->next!=nullptr || index==10 )
        {
            temp=PullQueue(ready_queue_);
            temp->start_time=get_time();
            last_pronum=pronum;
            std::cout << std::endl << "正在执行进程：" << temp->name << std::endl;
        }
        if (temp!=nullptr)
        {
            temp->done_time=time - temp->start_time;
            if (temp->done_time>=temp->serve_time && index>pronum)
            {
                pronum++;
            }
        }


    }


}
void SPF_SOFT(TASK_s* task_list,int num,TASKQueue* ready_queue)
{
    TaskQueueInit(ready_queue);
    for (int i=1;i<num;i++)
    {
        CreateQueueWithRuntime(&task_list[i],ready_queue);
    }

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