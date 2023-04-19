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
	int num_FCFS, num_RR, num_SJF, RTF, MaxW, STL, ForkProb, num_processes, num_processors, num_run, num_blk, num_terminate;
	LinkedQueue<mypair<int,int>> sigKILL;
	Process**process_ptr;
	Processor**Processor_ptr;
	LinkedQueue<Process*>NEW;
	LinkedQueue<Process*>BLKlist;
	LinkedQueue<Process*>Terminated;
	int TimeStep;
	
public:
	Scheduler();
	void Simulate();
	void Schedule(int& ind);
	void LoadInputs();
	void movetoBLK(Processor*Pr);
	void Terminate(Processor* Pr);
	void movetoRDY(Process*P,Processor* Pr);
	int get_time_step();
	void Print_Processors_Ready();
	void Print_Processes_inRun();
	void Print_Processes_trem();
	void Print_Processes_blk();
	int get_num_run();
	int get_num_blk();
	int get_num_terminate();
};
#endif
