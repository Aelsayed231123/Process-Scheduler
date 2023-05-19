#include "ProcessorSJF.h"
#include"Scheduler.h"
#include"Process.h"
ProcessorSJF::ProcessorSJF(Scheduler* pS) :Processor(pS)
{
}
void ProcessorSJF::MovetoRDY(Process* P)
{
	Ready.enqueue(P, P->get_CT());
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
		else if (isBusy())
		{
			if (RUN->request_IO())
			{
				pSch->from_run_to_blk(RemoveRun());
				fromRDY_to_run();
			}
			if (isBusy())
			{
				RUN->increment_run_time();
				BusyTime++;
				ExpTime--;
			}
			TotalBusyTime++;
		}
		return;
	}
	fromRDY_to_run();
}
Process* ProcessorSJF::RemoveFromRDY()
{
	if (Ready.isEmpty())
	{
		return nullptr;
	}
	else
	{
		Process* First;
		Ready.dequeue(First);
		ExpTime -= First->get_CT();
		return First;
	}
}
Process* ProcessorSJF::RemoveRun()
{
	ExpTime -= (RUN->get_CT() - BusyTime);
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
		Pr->set_RT(pSch->get_time_step());
		return true;
	}
	else
	{
		IdealTime++;
		return false;
	}
}
void ProcessorSJF::print_process_inRun()
{
	if (RUN)
		cout << *RUN;
}
Process* ProcessorSJF::get_first()
{
	Process* first = nullptr;
	Ready.peek(first);
	return first;
}