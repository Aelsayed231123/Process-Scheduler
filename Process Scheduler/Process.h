#pragma once
#ifndef PROCESS
#define PROCESS
#include"LinkedQueue.h"
#include"PriorityQueue.h"
#include"Processor.h"
class Process
{
	int pID;
	int AT;
	int RT;
	int CT;
	int TT;
	int TRT;
	int WT;
	int N;
	int RunTime;
	LinkedQueue<mypair<int,int>>IOqueue;
	Process* Childptr;
	Processor* Pr;
public:
	Process(int id, int arrT=0, int cpuT=0, int n=0, mypair<int,int>* P=nullptr);
	void set_RT(int runT);
	void set_TT(int terT);
	int get_ID();
	int get_AT();
	int get_RT();
	int get_CT();
	int get_TT();
	int get_TRT();
	int get_WT();
	int getRunTime();
	int get_remaining_time();
	bool Child;
	void set_child(Process* c);
	Process* get_child();
	bool request_IO(int time);
	friend ostream& operator << (ostream& out, Process& c);
	bool operator==(int id);
	void increment_run_time();
	bool isDone();
	void set_processor(Processor* P);
	Processor* get_processor();
	bool IsChild();
};
#endif
