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
		BusyTime++;
		return;
	}
	Process* Pr;
	Pr = Ready.GetFirst()->getItem();
	if (Pr)
	{
		RUN = Pr;
		pSch->increment_num_run();
		BusyTime = 1;
		State = BUSY;
	}
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
	Node<Process*>* ptr = Ready.get_head();
	Process* p = nullptr;
	while (ptr)
	{
		if (ptr->getItem()->get_ID() == id)
		{
			p = ptr->getItem();
			break;
		}
		ptr = ptr->getNext();
	}
	if (p)
	{
		pSch->Terminate(this);
		return true;
	}
	return false;
}
void ProcessorFCFS::print_RDY()
{
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