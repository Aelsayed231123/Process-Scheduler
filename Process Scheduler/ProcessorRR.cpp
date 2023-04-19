#include "ProcessorRR.h"
#include"Scheduler.h"
#include<iostream>
using namespace std;
ProcessorRR::ProcessorRR(Scheduler* psch, int time) :Processor(psch)
{
	TimeSlice = time;
}
void ProcessorRR::ScheduleAlgo()
{
	if (State == BUSY)
	{
		BusyTime++;
		return;
	}
	Process* Pr;
	RDY.dequeue(Pr);
	if (Pr)
	{
		RUN = Pr;
		BusyTime = 1;
		State = BUSY;
	}
}
int ProcessorRR::getExpTime()
{
	return ExpTime;
}
void ProcessorRR:: MovetoRDY(Process* P)
{
	RDY.enqueue(P);
	ExpTime += P->get_CT();
	if (P == RUN)
	{
		RUN = nullptr;
		BusyTime = 0;
		State = IDLE;
	}
}
Process*  ProcessorRR::RemoveRun()
{
	ExpTime -= RUN->get_CT();
	Process* temp = RUN;
	RUN = nullptr;
	BusyTime = 0;
	State = IDLE;
	return temp;
}
void ProcessorRR::print_RDY()
{
	RDY.print();
}
int ProcessorRR::get_countrdy()
{
	return RDY.get_count();
}
ostream& operator << (ostream& out, ProcessorRR& c)
{
	out << " [RR]: " << c.get_countrdy() << "  RDY : ";
	c.print_RDY();
	return out;
}