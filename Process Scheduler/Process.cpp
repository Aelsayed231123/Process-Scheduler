#include<iostream>
#include<cstdlib>
#include "Process.h"
Process::Process(int id, int arrT, int cpuT, int n, mypair<int, int>* P) :pID(id), AT(arrT), CT(cpuT), N(n)
{
	RT = -1;
	TT = -1;
	TRT = -1;
	WT = -1;
	RunTime = 0;
	IOD = 0;
	LChildptr = nullptr;
	RChildptr = nullptr;
	Pr = nullptr;
	Child = false;
	for (int i = 0; i < N; i++)
	{
		IOqueue.enqueue(P[i]);
	}
}
void Process::set_RT(int readyT)
{
	if (RT == -1)
		RT = readyT - AT;
}
void Process::set_TT(int terT)
{
	TT = terT;
	TRT = TT - AT;
	if (TRT < 0)
		TRT = 0;
	WT = TRT - CT;
	if (WT < 0)
		WT = 0;
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
void Process::set_Lchild(Process* c)
{
	LChildptr = c;
}
void Process::set_Rchild(Process* c)
{
	RChildptr = c;
}
bool Process::request_IO()
{
	bool request = false;
	mypair<int, int>curIO;
	if (!IOqueue.isEmpty())
	{
		if (IOqueue.peek(curIO))
		{
			if (curIO.first == RunTime)
				request = true;
		}
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
	return(RunTime >= CT);
}
int Process::get_remaining_time()
{
	return(CT - RunTime);
}
Process* Process::get_Lchild()
{
	return LChildptr;
}
Process* Process::get_Rchild()
{
	return RChildptr;
}
void Process::set_processor(Processor* P)
{
	Pr = P;
}
Processor* Process::get_processor()
{
	return Pr;
}
bool Process::IsChild()
{
	return Child;
}
int Process::get_current_IOD()
{
	mypair<int, int>IOpair;
	if (!IOqueue.isEmpty())
	{
		IOqueue.peek(IOpair);
		return IOpair.second;
	}
	else return -1;
}
int Process::get_current_IOR()
{
	mypair<int, int>IOpair;
	if (!IOqueue.isEmpty())
	{
		IOqueue.peek(IOpair);
		return IOpair.first;
	}
	else
		return -1;
}
int Process::get_IOD()
{
	return IOD;
}
void Process::RemoveCurrentIOpair()
{
	mypair<int, int>IOpair;
	IOqueue.dequeue(IOpair);
}
void Process::increment_IOD()
{
	IOD++;
}