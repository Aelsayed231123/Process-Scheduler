#include"pair.h"
//#include"LinkedQueue.h"
#ifndef SCHEDULER_H
#define SCHEDULER_H
#include"ProcessorRR.h"
#include"Process.h"
#include<iostream>
using namespace std;
class Scheduler
{
private:
	int num_FCFS,num_RR,num_SJF,RTF,MaxW,STL,ForkProb,num_processes;
	LinkedQueue<mypair<int,int>> sigKILL;
	Process**process_ptr;
	ProcessorRR**processor_RR_ptr;
	LinkedQueue<Process*>BLKlist;
	LinkedQueue<Process*>Terminated;
	int TimeStep;
	int TerminatedSize;
	
public:
	Scheduler();
	void Simulate();
	void Schedule();
	void LoadInputs();
	void movetoBLK(Process*P);
	void Terminate(Process* P);
};
#endif
