#include "ProcessorFCFS.h"
#include"Scheduler.h"
ProcessorFCFS::ProcessorFCFS(Scheduler* psch): Processor(psch)
{
}
void ProcessorFCFS::MovetoRDY(Process* P)
{
	Ready.enqueue(P);
	ExpTime += P->get_CT();
}
void ProcessorFCFS::ScheduleAlgo()
{
	if (isBusy())
	{
		return;
	}
	Process* Pr;
	Ready.dequeue(Pr);
	MovetoRun(Pr);
}
void ProcessorFCFS::MovetoBLK(Process* P)
{
	pSch->movetoBLK(P);
	ExpTime -= P->get_CT();
	RUN = nullptr;
	State = IDLE;
}
void ProcessorFCFS::Terminate(Process* P)
{
	pSch->Terminate(P);
	ExpTime -= P->get_CT();
	RUN = nullptr;
	State = IDLE;
}
bool  ProcessorFCFS::MovetoRun(Process* P)
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