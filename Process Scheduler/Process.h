#ifndef PROCESS
#define PROCESS


#include"LinkedQueue.h"
#include"PriorityQueue.h"

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
	LinkedQueue<mypair<int,int>>IOqueue;
	Process* Parptr;
	Process* Childptr;
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
	bool CreateChild(int p);
	void set_child(Process* c);
	bool request_IO(int time);
	friend ostream& operator << (ostream& out, Process& c);
	bool operator==(int id);
};
#endif
