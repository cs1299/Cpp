//
// Created by 47764 on 2025/12/10.
//

#include "HRRN.h"

//=========================================================
// 进程到达 → 加入队尾
//=========================================================
void CreateQueueWithPriority(TASKQueue* ready_queue, TASK_s* task)
{
    task->next = nullptr;

    // 队列为空
    if (ready_queue->firstProg->next == nullptr) {
        ready_queue->firstProg->next = task;
        ready_queue->LastProg = task;
    }
    else {
        // 插入到队尾
        ready_queue->LastProg->next = task;
        ready_queue->LastProg = task;
    }

    ready_queue->size++;
}


void calpriority(TASKQueue* ready_queue, int sys_done_time)
{
    TASK_s* p = ready_queue->firstProg->next;
    while (p) {
        p->waiting_time = sys_done_time - p->dqzztime;
        p->priority = (p->waiting_time + p->serve_time) / (float)p->serve_time;
        p = p->next;
    }

    TASK_s* sorted = nullptr;
    TASK_s* cur = ready_queue->firstProg->next;

    while (cur) {
        TASK_s* next = cur->next;

        if (sorted == nullptr || cur->priority > sorted->priority) {
            cur->next = sorted;
            sorted = cur;
        }
        else {
            TASK_s* s = sorted;
            while (s->next && s->next->priority >= cur->priority) {
                s = s->next;
            }
            cur->next = s->next;
            s->next = cur;
        }

        cur = next;
    }

    ready_queue->firstProg->next = sorted;

    TASK_s* t = sorted;
    while (t && t->next) t = t->next;
    ready_queue->LastProg = t;
}

void HRRN_RUN(TASK_s* task_list, int num)
{
    algorithm_start_print(a_HRRN);
    static int sys_start_time = 0;
    static int sys_done_time = 0;
    static int pronum = 1;
    static int last_pronum = 0;
    static TASK_s* temp = nullptr;

    int index = 0;
    int time = 0;

    sortWithEnterTime(task_list);

    TASKQueue* ready_queue_ = (TASKQueue*)malloc(sizeof(TASKQueue));
    if (!ready_queue_) {
        std::cout << "分配就绪队列头结点空间失败！" << std::endl;
        exit(1);
    }
    TaskQueueInit(ready_queue_);

    sys_start_time = get_time();

    while (pronum <= num)
    {
        time = get_time();
        sys_done_time = time - sys_start_time;

        // ------------------ 进程到达判断 ------------------
        if (index < num && sys_done_time >= task_list[index].arrivetime) {
            CreateQueueWithPriority(ready_queue_, &task_list[index]);
            task_list[index].dqzztime = sys_done_time;
            index++;
        }

        calpriority(ready_queue_, sys_done_time);

        if (last_pronum != pronum && ready_queue_->firstProg->next != nullptr)
        {
            temp = PullQueue(ready_queue_);
            temp->start_time = get_time();
            temp->waiting_time = temp->start_time - temp->dqzztime;
            task_start_print(*temp,sys_done_time);
            last_pronum = pronum;
        }

        if (temp != nullptr)
        {
            temp->running_time = time - temp->start_time;

            if (temp->running_time >= temp->serve_time)
            {
                temp->done_time = sys_done_time;
                pronum++;
                temp = nullptr;
            }
        }
    }
}
