#include<iostream>
#include"FCFS.h"
#include"SPF.h"
#include"FPF.h"
#include"RR.h"
using namespace std;

process processes[100];

void run_fcfs(); //先来先服务
void run_spf(); //短进程优先
void run_fpf(); //高优先级优先
void run_rr(); //时间片轮转

int main()
{
    int run_method;
    cout<<"请选择调度算法:"<<endl;
    cout<<"1:先来先服务"<<endl;
    cout<<"2:短进程优先"<<endl;
    cout<<"3:高优先级优先"<<endl;
    cout<<"4:时间片轮转"<<endl;
    cin>>run_method;
    switch (run_method) {
    case 1:
        run_fcfs();
        break;
    case 2:
        run_spf();
        break;
    case 3:
        run_fpf();
        break;
    case 4:
        run_rr();
        break;
    }
    return 0;
}

void run_fcfs()
{
    int number, at, rt, rank;
    cout<<"请输入进程数量:"<<endl;
    cin>>number;
    cout<<"请输入各个进程的"<<endl;
    cout<<"到达时间 运行时间"<<endl;
    for(int i = 0; i < number; ++i) {
        cin>>at>>rt;
        processes[i].pcb.number = i;
        processes[i].pcb.arrive_time = at;
        processes[i].pcb.require_runtime = rt;
        processes[i].pcb.state = 2;
    }
    FCFS *program = new FCFS(processes, number);
    program->run_process();
}

void run_spf()
{
    int number, at, rt, rank;
    cout<<"请输入进程数量:"<<endl;
    cin>>number;
    cout<<"请输入各个进程的"<<endl;
    cout<<"到达时间 运行时间"<<endl;
    for(int i = 0; i < number; ++i) {
        cin>>at>>rt;
        processes[i].pcb.number = i;
        processes[i].pcb.arrive_time = at;
        processes[i].pcb.require_runtime = rt;
        processes[i].pcb.state = 2;
    }
    SPF *program = new SPF(processes, number);
    program->run_process();
}

void run_fpf()
{
    int number, at, rt, weight, rank;
    cout<<"请输入进程数量:"<<endl;
    cin>>number;
    cout<<"请输入各个进程的"<<endl;
    cout<<"到达时间 运行时间 权重"<<endl;
    for(int i = 0; i < number; ++i) {
        cin>>at>>rt>>weight;
        processes[i].pcb.number = i;
        processes[i].pcb.arrive_time = at;
        processes[i].pcb.require_runtime = rt;
        processes[i].pcb.rank = weight;
        processes[i].pcb.state = 2;
    }
    FPF *program = new FPF(processes, number);
    program->run_process();
}

void run_rr()
{
    int number, at, rt, weight;
    cout<<"请输入进程数量:"<<endl;
    cin>>number;
    cout<<"请输入各个进程的"<<endl;
    cout<<"到达时间 运行时间"<<endl;
    for(int i = 0; i < number; ++i) {
        cin>>at>>rt;
        processes[i].pcb.number = i;
        processes[i].pcb.arrive_time = at;
        processes[i].pcb.require_runtime = rt;
        processes[i].pcb.state = 2;
    }
    RR *program = new RR(processes, number);
    program->run_process();
}