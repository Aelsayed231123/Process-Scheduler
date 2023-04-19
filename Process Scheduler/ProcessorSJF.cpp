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
		BusyTime = 0;
		State = IDLE;
	}
}
void ProcessorSJF::ScheduleAlgo()
{
	if (isBusy())
	{
		BusyTime++;
		return;
	}
	Process* Pr;
	Ready.dequeue(Pr);
	if (Pr)
	{
		RUN = Pr;
		BusyTime = 1;
		State = BUSY;
	}
}
Process*  ProcessorSJF::RemoveRun()
{
	ExpTime -= RUN->get_CT();
	Process* temp = RUN;
	RUN = nullptr;
	BusyTime = 0;
	State = IDLE;
	return temp;
}
void ProcessorSJF::print_RDY()
{
	Ready.print();
}
int ProcessorSJF::get_countrdy()
{
	return Ready.get_count();
}
ostream& operator << (ostream& out, ProcessorSJF& c)
{
	out << " [SJF]: " << c.get_countrdy() << "  RDY : ";
	c.print_RDY();
	return out;
}