#include "Scheduler.h"
#include"pair.h"
#include<fstream>
#include<string>
Scheduler::Scheduler()
{
	process_ptr=nullptr;
	processor_RR_ptr=nullptr;
	num_FCFS=0;
	num_RR=0;
	num_SJF=0;
	RTF=0;
	MaxW=0;
	STL=0;
	ForkProb=0;
	num_processes=0;
}
void Scheduler::LoadInputs()
{
	ifstream finput("f1.txt",ios::in);
	finput>>num_FCFS>>num_SJF>>num_RR;
	int time_slice;
	finput>>time_slice;
	processor_RR_ptr=new ProcessorRR*[num_RR];
	for(int i=0;i<num_RR;i++)
	{
		ProcessorRR*ptr_rr=new ProcessorRR(this,time_slice);
		processor_RR_ptr[i]=ptr_rr;
	}
	////////////////////////////creating rr processors with timesclice as par in constructor
	finput>>RTF>>MaxW>>STL>>ForkProb>>num_processes;
	int loop_count=num_processes;
	process_ptr=new Process*[num_processes];
	int index=0;
	int Arrival_time,ID,CPU_time,n;
	mypair<int,int>arr[100];
	while(loop_count)
	{
		finput>>Arrival_time>>ID>>CPU_time>>n;
		for(int i=0;i<n;i++)
		{
			finput.ignore(100,'(');
			finput>>arr[i].first;
			finput.ignore(100,',');
			finput>>arr[i].second;
		}
			Process*ptr=new Process(ID,Arrival_time,CPU_time,n,arr);
			process_ptr[index]=ptr;
		//////////intantaie process with constructor,setting pairs
		finput.ignore(10000000000,'\n');
		index++;
		loop_count--;
	}
	while(!finput.eof())
	{
		mypair<int,int>sig;
		finput>>sig.first>>sig.second;
		sigKILL.enqueue(sig);
		finput.ignore(100000000,'\n');
	}
}

