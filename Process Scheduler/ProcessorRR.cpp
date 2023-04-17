#include "ProcessorRR.h"
#include"Scheduler.h"
ProcessorRR::ProcessorRR(Scheduler* psch, int time) :Processor(psch)
{
	TimeSlice = time;
}
void ProcessorRR::ScheduleAlgo()
{
	if (State == BUSY || RDY.isEmpty())
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
void  ProcessorRR::MovetoBLK(Process* P)
{
	pSch->movetoBLK(P);
	ExpTime -= P->get_CT();
	RUN = nullptr;
	State = IDLE;
	
}
void  ProcessorRR::Terminate(Process* P)
{
	pSch->Terminate(P);
	ExpTime -= P->get_CT();
	RUN = nullptr;
	State = IDLE;
}
bool  ProcessorRR::MovetoRun(Process* P)
{
	if (State == IDLE)
	{
		RUN = P;
		State = BUSY;
		P->set_RT(pSch->get_time_step());
			return true;
	}
	return false;
}