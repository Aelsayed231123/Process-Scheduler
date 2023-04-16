#ifndef PROCESS
#define PROCESS


#include"LinkedQueue.h"
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
	LinkedQueue<mypair<int>>IOqueue;
	Process* Parptr;
	Process* Childptr;
public:
	Process(int id, int arrT, int cpuT, int n, mypair<int>* P);
	void set_RT(int runT);
	void set_TT(int terT);
	int get_ID();
	int get_AT();
	int get_RT();
	int get_CT();
	int get_TT();
	int get_TRT();
	int get_WT();
	bool CreateChild(int p);
	void set_child(Process* c);
	bool request_IO(int time);
};
#endif
