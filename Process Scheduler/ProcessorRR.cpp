#include "ProcessorRR.h"
ProcessorRR::ProcessorRR(Scheduler* psch, int time) :Processor(psch)
{
	TimeSlice = time;
}
void ProcessorRR::ScheduleAlgo()
{
	if (State == BUSY)
	{
		return;
	}
	Process* Pr;
	RDY.dequeue(Pr);
	RUN = Pr;
}
int ProcessorRR::getExpTime()
{
	return 0;
}
void ProcessorRR:: MovetoRDY(Process* P)
{
	RDY.enqueue(P);
	ExpTime += P->get_CT();
}
void  ProcessorRR::MovetoRun(Process* P)
{
	RUN = P;
	State = BUSY;
}
void  ProcessorRR::MovetoBLK(Process* P)
{
	//pSch->
	ExpTime -= P->get_CT();
}
void  ProcessorRR::Terminate(Process* P)
{
	//pSch->
	ExpTime -= P->get_CT();
}