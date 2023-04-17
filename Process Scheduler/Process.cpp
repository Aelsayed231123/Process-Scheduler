#include<iostream>
#include<cstdlib>
#include "Process.h"
Process::Process(int id, int arrT, int cpuT, int n, mypair<int,int>* P) :pID(id), AT(arrT), CT(cpuT), N(n)
{
	RT = -1;
	TT = -1;
	TRT = -1;
	WT = -1;
	Parptr = nullptr;
	Childptr = nullptr;
	for (int i = 0; i < N; i++)
	{
		IOqueue.enqueue(P[i]);
	}
}
void Process::set_RT(int readyT)
{
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
bool Process::CreateChild(int fp)
{
	bool Create = false;
	srand((unsigned)time(NULL));
	float r = ((double)rand() / (RAND_MAX));
	if (r >= fp)
	{
		Create = true;
	}
	return Create;
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
