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
	int num_FCFS, num_RR, num_SJF, RTF, MaxW, STL, ForkProb, num_processes, num_processors, num_run, num_blk, num_terminate,num_forked,num_killed;
	LinkedQueue<mypair<int,int>> sigKILL;
	Process**process_ptr;
	Processor**Processor_ptr;
	LinkedQueue<Process*>NEW;
	LinkedQueue<Process*>BLKlist;
	LinkedQueue<Process*>Terminated;
	int TimeStep;
	int currentIOtime;
	
public:
	Scheduler();
	void Simulate();
	void Schedule();
	void LoadInputs();
	void movetoBLK(Processor*Pr);
	void Terminate(Process* P);
	void TerminateKilled(Process* P);
	void movetoRDY(Process*P,Processor* Pr);
	int get_time_step();
	void Print_Processors_Ready();
	void Print_Processes_inRun();
	void Print_Processes_trem();
	void Print_Processes_blk();
	bool MigrateRRSJF(Processor* Pr);
	bool MigrateFCFSRR(Processor* Pr);
	void WorkSteal();
	int get_num_run();
	int get_num_blk();
	int get_num_terminate();
	int get_RTF();
	int get_MaxW();
	void increment_num_run();
	void decrement_num_run();
	void generate_outfile();
	Processor* get_shortest();
	void forK_a_child(Process* P);
	int get_fork_probability();
	Processor* get_shortest_FCFS();
	Processor* get_shortest_SJF();
	Processor* get_shortest_RR();
	Processor* get_longest();
	void from_run_to_blk(Process*P);
	void from_blk_to_rdy();
	void sig_kill();

};
#endif
