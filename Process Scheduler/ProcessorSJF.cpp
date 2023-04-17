#include "ProcessorSJF.h"
#include"Scheduler.h"
ProcessorSJF::ProcessorSJF(Scheduler* pS):Processor(pS)
{
}
void ProcessorSJF::MovetoRDY(Process* P)
{
	Ready.enqueue(P,P->get_CT());
	ExpTime += P->get_CT();
}
void ProcessorSJF::ScheduleAlgo()
{
	if (isBusy() || Ready.isEmpty())
	{
		return;
	}
	Process* Pr;
	Ready.dequeue(Pr);
	MovetoRun(Pr);
}
void  ProcessorSJF::MovetoBLK(Process* P)
{
	pSch->movetoBLK(P);
	ExpTime -= P->get_CT();
	RUN = nullptr;
	State = IDLE;
}
void  ProcessorSJF::Terminate(Process* P)
{
	pSch->Terminate(P);
	ExpTime -= P->get_CT();
	RUN = nullptr;
	State = IDLE;
}