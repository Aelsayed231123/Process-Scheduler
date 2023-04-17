#include "ProcessorSJF.h"
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
	if (isBusy())
	{
		return;
	}
	Process* Pr;
	Ready.dequeue(Pr);
	MovetoRun(Pr);
}