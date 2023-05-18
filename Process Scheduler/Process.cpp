#include<iostream>
#include<cstdlib>
#include "Process.h"
Process::Process(int id, int arrT, int cpuT, int n, mypair<int,int>* P) :pID(id), AT(arrT), CT(cpuT), N(n)
{
	RT = -1;
	TT = -1;
	TRT = -1;
	WT = -1;
	RunTime = 0;
	IOD = 0;
	Childptr = nullptr;
	Pr = nullptr;
	Child = false;
	for (int i = 0; i < N; i++)
	{
		IOqueue.enqueue(P[i]);
	}
}
void Process::set_RT(int readyT)
{
	if(RT==-1)
	RT = readyT - AT;
}
void Process::set_TT(int terT)
{
	TT = terT;
	TRT = TT - AT;
	WT = TRT - CT;
}
int Process::get_ID()
{
	return pID;
}
int Process::get_AT()
{
	return AT;
}
int Process::get_RT()
{
	return RT;
}
int Process::get_CT()
{
	return CT;
}
int Process::get_TT()
{
	return TT;
}
int Process::get_TRT()
{
	return TRT;
}
int Process::get_WT()
{
	return WT;
}
void Process::set_child(Process* c)
{
	Childptr = c;
}
bool Process::request_IO(int time)
{
	int t = time - RT;
	bool request = false;
	mypair<int,int>curIO;
	if (IOqueue.peek(curIO))
	{
		if (curIO.first == t)
			request = true;
	}
	return request;
}
ostream& operator << (ostream& out, Process& c)
{
	out << c.pID;
	return out;
}
bool Process:: operator==(int id)
{
	return(id == pID);
}
void Process::increment_run_time()
{
	RunTime++;
}
int  Process::getRunTime()
{
	return RunTime;
}
bool Process::isDone()
{
	return(RunTime == CT);
}
int Process::get_remaining_time()
{
	return(CT - RunTime);
}
Process* Process::get_child()
{
	return Childptr;
}
void Process::set_processor(Processor* P)
{
	Pr = P;
}
Processor* Process::get_processor()
{
	return Pr;
}
bool  Process::IsChild()
{
	return Child;
}
int Process::get_IOD()
{
	return IOD;
}