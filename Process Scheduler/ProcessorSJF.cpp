#include "ProcessorSJF.h"
#include"Scheduler.h"
ProcessorSJF::ProcessorSJF(Scheduler* pS):Processor(pS)
{
}
void ProcessorSJF::MovetoRDY(Process* P)
{
	Ready.enqueue(P,P->get_CT());
	ExpTime += P->get_CT();
	if (P == RUN)
	{
		RUN = nullptr;
		State = IDLE;
	}
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
Process*  ProcessorSJF::MovetoBLK()
{
	ExpTime -= RUN->get_CT();
	Process* temp = RUN;
	RUN = nullptr;
	State = IDLE;
	return temp;
}
void  ProcessorSJF::Terminate(Process* P)
{
	pSch->Terminate(P);
	ExpTime -= P->get_CT();
	RUN = nullptr;
	State = IDLE;
}
bool  ProcessorSJF::MovetoRun(Process* P)
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