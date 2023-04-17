#include "ProcessorSJF.h"
ProcessorSJF::ProcessorSJF(Scheduler* pS):Processor(pS)
{

}
void ProcessorSJF::MovetoRDY(Process* P)
{
	Ready.enqueue(P,P->get_CT());
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
void ProcessorSJF::MovetoRun(Process* P)
{
	RUN = P;
	State = BUSY;
}
void ProcessorSJF::MovetoBLK(Process* P)
{

}
void ProcessorSJF::Terminate(Process* P)
{

}