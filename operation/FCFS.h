//先来先服务调度算法
#ifndef _FCFS_
#define _FCFS_

#include"structure.h"
#include<queue>
#include<vector>
#include<iomanip>

class FCFS;

class FCFS {
public:
    FCFS(process pro[100], int n): length(n), time(1), AWTT(0) {
        for(int i = 0; i < n; ++i) all_process.push_back(pro[i]);
    }
    void run_process(); //运行进程
    bool is_finished(); //进程是否全部做完
    void add_process(); //将已到达的进程加入等待队列
    void print_data(const process &pro); //输出进程信息
private:
    //进程数量
    int length;
    //储存所有进程
    std::vector<process> all_process;
    //等待队列
    std::queue<process> wait_queue;
    //现在的运行时间
    int time;
    //总的带权运行时间
    double AWTT;
};

inline bool
FCFS::is_finished()
{
    for(process i : all_process)
        if(i.pcb.state != 3) return false;
    return true;
}

inline void
FCFS::add_process()
{
    //如果进程已到达，则加入等待队列
    for(process i : all_process) {
        if(i.pcb.state == 2 && i.pcb.arrive_time <= time) {
            all_process[i.pcb.number].pcb.state = 0;
            wait_queue.push(i);
        }
    }
}

inline void
FCFS::print_data(const process &pro)
{
    if(pro.pcb.state == 1) {
        cout<<"in "<<time<<" ms"<<endl;
        cout<<"process "<<pro.pcb.number<<" started"<<endl;
        cout<<"--------------"<<endl;
    }
    else if(pro.pcb.state == 3) {
        int runtime = time - pro.pcb.arrive_time;
        AWTT += runtime / pro.pcb.require_runtime;
        cout<<"in "<<time<<" ms"<<endl;
        cout<<"process "<<pro.pcb.number<<" finished"<<endl;
        cout<<"turnaround time is "<<runtime<<endl;
        cout<<"weighted turnaround time is "<<runtime / pro.pcb.require_runtime<<endl;
        cout<<"--------------"<<endl;
    }
}

inline void
FCFS::run_process()
{
    //当有进程没有做完时继续循环
    while(!is_finished()) {
        add_process();
        //当队列不为空时取队首进程
        if(!wait_queue.empty()) {
            process tmp = wait_queue.front();
            wait_queue.pop();
            all_process[tmp.pcb.number].pcb.state = 1;
            print_data(all_process[tmp.pcb.number]);
            time += tmp.pcb.require_runtime;
            //定义进程的运行状态为运行完成
            all_process[tmp.pcb.number].pcb.state = 3;
            print_data(all_process[tmp.pcb.number]);
        } else {    //当队列为空时时间自动增长
            time++;
        }
    }
    cout<<"all processes finished"<<endl;
    cout<<"average weighted turnsround time is :"<<setprecision(2)<<AWTT / length<<endl;
}

#endif  //_FCFS_