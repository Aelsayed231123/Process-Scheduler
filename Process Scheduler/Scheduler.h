#include"pair.h"
//#include"LinkedQueue.h"
#include<iostream>
#include"process.h"
using namespace std;
class Scheduler
{
private:
	int num_FCFS,num_RR,num_SJF,RTF,MaxW,STL,ForkProb,num_processes;
	LinkedQueue<mypair<int,int>> sigKILL;
	Process**process_ptr;
public:
	Scheduler();
	void LoadInputs();
};
