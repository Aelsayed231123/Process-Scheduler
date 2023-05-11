#include "ProcessorFCFS.h"
#include"Scheduler.h"
#include<iostream>
using namespace std;
ProcessorFCFS::ProcessorFCFS(Scheduler* psch): Processor(psch)
{
}
void ProcessorFCFS::MovetoRDY(Process* P)
{
	Ready.InsertEnd(P);
	ExpTime += P->get_CT();
	if (P == RUN)
	{
		RUN = nullptr;
		pSch->decrement_num_run();
		BusyTime = 0;
		State = IDLE;
	}
}
void ProcessorFCFS::ScheduleAlgo()
{
	if (isBusy())
	{
		if (RUN->isDone())
		{
			pSch->Terminate(RemoveRun());
			fromRDY_to_run();
		}
		else
		{
			RUN->increment_run_time();
			BusyTime++;
		}
		return;
	}
	fromRDY_to_run();
}
Process* ProcessorFCFS::RemoveRun()
{
	ExpTime -= RUN->get_CT();
	Process* temp = RUN;
	RUN = nullptr;
	pSch->decrement_num_run();
	BusyTime = 0;
	State = IDLE;
	return temp;
}
bool ProcessorFCFS::Kill(int id)
{
	if (Ready.isEmpty())
	{
		return false;
	}
	Process* p = nullptr;
	p=Ready.SearchbyID(id);
	if (p)
	{
		pSch->TerminateKilled(p);
		return true;
	}
	return false;
}
void ProcessorFCFS::print_RDY()
{
	cout << "[FCFS] :  ";
	Ready.PrintList();
}
int ProcessorFCFS::get_countrdy()
{
	return Ready.get_count();
}
ostream& operator << (ostream& out, ProcessorFCFS& c)
{
	out << " [FCFS]: " << c.get_countrdy() << "  RDY : ";
	c.print_RDY();
	return out;
}
bool ProcessorFCFS::fromRDY_to_run()
{
	Process* Pr;
	Pr = Ready.GetFirst()->getItem();
	if (Pr)
	{
		RUN = Pr;
		Pr->increment_run_time();
		pSch->increment_num_run();
		BusyTime = 1;
		State = BUSY;
		return true;
	}
	else
		return false;
}