//时间片轮转算法
#ifndef _RR_
#define _RR_

class RR;
#include<vector>
#include"structure.h"

class RR
{
public:
    RR(process pro[100], int n): length(n), time(1), AWTT(0) {
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
    std::vector<process> wait_queue;
    //现在的运行时间
    int time;
    //总的周转时间
    double AWTT;
};

inline bool
RR::is_finished()
{
    for(process i : all_process)
        if(i.pcb.state != 3) return false;
    return true;
}

inline void
RR::add_process()
{
    //如果进程已到达，则加入等待队列
    for(process i : all_process) {
        if(i.pcb.state == 2 && i.pcb.arrive_time <= time) {
            all_process[i.pcb.number].pcb.state = 0;
            //加入到容器的后方
            wait_queue.push_back(i);
        }
    }
}

#include<iostream>
using namespace std;
inline void
RR::print_data(const process &pro)
{
    if(pro.pcb.state == 2) {
        cout<<"in "<<time<<" ms"<<endl;
        cout<<"process "<<pro.pcb.number<<" running at "<<time<<endl;
    }
    else if(pro.pcb.state == 3) {
        int runtime = time - pro.pcb.arrive_time;
        AWTT += runtime / pro.pcb.require_runtime;
        cout<<"in "<<time<<" ms"<<endl;
        cout<<"process "<<pro.pcb.number<<" finished"<<endl;
        cout<<"turnaround time is "<<runtime<<endl;
        cout<<"weighted turnaround time is "<<runtime / pro.pcb.require_runtime<<endl;
        cout<<"--------------";
    }
}

inline void
RR::run_process()
{
    //当有进程没有做完时继续循环
    while(!is_finished()) {
        add_process();
        //如果等待队列为空则时间自增
        if(wait_queue.empty()) {
            time++;
            continue;
        }
        //取最后一个元素
        process tmp = wait_queue.back();
        wait_queue.pop_back();
        all_process[tmp.pcb.number].pcb.state = 1;
        print_data(all_process[tmp.pcb.number]);
        all_process[tmp.pcb.number].pcb.rest_runtime--;
        if(tmp.pcb.rest_runtime == 0) {
            all_process[tmp.pcb.number].pcb.state = 3;
            print_data(all_process[tmp.pcb.number]);
        } else {    //继续等
            all_process[tmp.pcb.number].pcb.state = 0;
            //插入队首排队
            wait_queue.insert(wait_queue.begin(), tmp);
        }
        time++;
    }
    cout<<"all processes finished"<<endl;
    cout<<"average weighted turnsround time is :"<<AWTT / length<<endl;
}

#endif  //_RR_