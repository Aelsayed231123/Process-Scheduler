#include "ProcessorSJF.h"
#include"Scheduler.h"
#include"Process.h"
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
		pSch->decrement_num_run();
		BusyTime = 0;
		State = IDLE;
	}
}
void ProcessorSJF::ScheduleAlgo()
{
	if (isBusy())
	{
		if (RUN->isDone())
		{
			pSch->Terminate(RemoveRun());
			fromRDY_to_run();
		}
		else
		{
			RUN->increment_run_time();
			BusyTime++;
		}
		return;
	}
	fromRDY_to_run();
}
Process*  ProcessorSJF::RemoveRun()
{
	ExpTime -= RUN->get_CT();
	Process* temp = RUN;
	RUN = nullptr;
	pSch->decrement_num_run();
	BusyTime = 0;
	State = IDLE;
	return temp;
}
void ProcessorSJF::print_RDY()
{
	cout << "[SJF] :  ";
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
bool ProcessorSJF::fromRDY_to_run()
{
	Process* Pr;
	if (Ready.dequeue(Pr))
	{
		RUN = Pr;
		pSch->increment_num_run();
		BusyTime = 1;
		State = BUSY;
		return true;
	}
	else
	{
		return false;
		IdealTime++;
	}
}
void ProcessorSJF::print_process_inRun()
{
	if (RUN)
		cout << *RUN;
}