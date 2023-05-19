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
	int IOD;
	int RunTime;
	LinkedQueue<mypair<int,int>>IOqueue;
	Process* LChildptr;
	Process* RChildptr;
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
	void set_Lchild(Process* c);
	void set_Rchild(Process* c);
	Process* get_Lchild();
	Process* get_Rchild();
	bool request_IO();
	friend ostream& operator << (ostream& out, Process& c);
	bool operator==(int id);
	void increment_run_time();
	bool isDone();
	int get_IOD();
	void increment_IOD();
	void set_processor(Processor* P);
	Processor* get_processor();
	bool IsChild();
	int get_current_IOD();
	int get_current_IOR();
	void RemoveCurrentIOpair();
};
#endif
