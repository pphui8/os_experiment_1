#ifndef _SCTRUCTURE_
#define _SCTRUCTURE_

typedef struct PCB {
    //进程编号
    int number;
    //到达时间
    int arrive_time;
    //剩余运行时间
    int rest_runtime;
    //要求运行时间
    int require_runtime;
    //优先级
    int rank;
    //进程状态:0：等待，1：运行中，2：未到达，3：运行完成
    int state;
} PCB;

typedef struct process{
    //进程控制块
    PCB pcb;
    //进程工作内容,
    int work;
} process;

//由于输出后导致输出内容太多故不进行调用
#include<iostream>
using namespace std;
void work(int n)
{
    cout<<"进程"<<n<<"正在运行"<<endl;
}

#endif  //_SCTRUCTURE_