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



//=========================================================
// HRRN 优先级计算 + 链表排序（响应比从大到小）
//=========================================================
void calpriority(TASKQueue* ready_queue, int sys_done_time)
{
    // ---------- 1. 计算响应比 ----------
    TASK_s* p = ready_queue->firstProg->next;
    while (p) {
        p->waiting_time = sys_done_time - p->dqzztime;
        p->priority = (p->waiting_time + p->serve_time) / (float)p->serve_time;
        p = p->next;
    }

    // ---------- 2. 单链表插入排序 ----------
    TASK_s* sorted = nullptr;
    TASK_s* cur = ready_queue->firstProg->next;

    while (cur) {
        TASK_s* next = cur->next;

        // 插入开头或作为最大响应比节点
        if (sorted == nullptr || cur->priority > sorted->priority) {
            cur->next = sorted;
            sorted = cur;
        }
        else {
            // 找到插入点（从大到小）
            TASK_s* s = sorted;
            while (s->next && s->next->priority >= cur->priority) {
                s = s->next;
            }
            cur->next = s->next;
            s->next = cur;
        }

        cur = next;
    }

    // ---------- 3. 挂回 ready_queue ----------
    ready_queue->firstProg->next = sorted;

    // ---------- 4. 重新更新尾指针 LastProg ----------
    TASK_s* t = sorted;
    while (t && t->next) t = t->next;
    ready_queue->LastProg = t;
}



//=========================================================
// HRRN 调度核心循环
//=========================================================
void HRRN_RUN(TASK_s* task_list, int num)
{
    static int sys_start_time = 0;
    static int sys_done_time = 0;
    static int pronum = 1;
    static int last_pronum = 0;
    static TASK_s* temp = nullptr;

    int index = 0;
    int time = 0;

    // 保证按到达时间排序
    sortWithEnterTime(task_list);

    // 创建队列
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

        // ------------------ 更新 HRRN 优先级 + 排序 ------------------
        calpriority(ready_queue_, sys_done_time);

        // ------------------ 若当前无执行进程 → 拉取队首 ------------------
        if (last_pronum != pronum && ready_queue_->firstProg->next != nullptr)
        {
            temp = PullQueue(ready_queue_);
            temp->start_time = get_time();
            temp->waiting_time = temp->start_time - temp->dqzztime;

            std::cout << "正在执行进程：" << temp->name << std::endl;
            last_pronum = pronum;
        }

        // ------------------ 判断执行是否完成 ------------------
        if (temp != nullptr)
        {
            temp->running_time = time - temp->start_time;

            if (temp->running_time >= temp->serve_time)
            {
                temp->done_time = sys_done_time;

                std::cout << "结束时间：" << temp->done_time << std::endl;

                pronum++;
                temp = nullptr;
            }
        }
    }
}
