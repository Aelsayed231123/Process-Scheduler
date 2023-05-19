#include "ProcessorRR.h"
#include"Scheduler.h"
#include"Process.h"
#include<iostream>
using namespace std;
ProcessorRR::ProcessorRR(Scheduler* psch, int time) :Processor(psch)
{
	TimeSlice = time;
}
void ProcessorRR::ScheduleAlgo()
{
	if (State == BUSY)
	{
		if (RUN->isDone())
		{
			pSch->Terminate(RemoveRun());
			fromRDY_to_run();
			CheckMigration();
		}
		else if (isBusy())
		{
			if (RUN->request_IO())
			{
				pSch->from_run_to_blk(RemoveRun());
				fromRDY_to_run();
				CheckMigration();
			}
			else if (isBusy() && (BusyTime == TimeSlice))
			{
				Process* R = RemoveRun();
				MovetoRDY(R);
				fromRDY_to_run();
				CheckMigration();
			}
			else if (RUN != nullptr && (RUN->get_remaining_time() < pSch->get_RTF()) && !(RUN->IsChild()))
			{
				CheckMigration();
			}
			if (isBusy())
			{
				RUN->increment_run_time();
				BusyTime++;
				ExpTime--;
			}
			TotalBusyTime++;
			return;
		}
	}
	fromRDY_to_run();
	CheckMigration();
}
void ProcessorRR::CheckMigration()
{
	while (RUN != nullptr && (RUN->get_remaining_time() < pSch->get_RTF()) && !(RUN->IsChild()))
	{
		if (pSch->MigrateRRSJF(this))
			fromRDY_to_run();
		else
			break;
	}
}
Process* ProcessorRR::RemoveFromRDY()
{
	if (RDY.isEmpty())
	{
		return nullptr;
	}
	else
	{
		Process* First;
		RDY.dequeue(First);
		ExpTime -= First->get_CT();
		return First;
	}
}
int ProcessorRR::getExpTime()
{
	return ExpTime;
}
void ProcessorRR::MovetoRDY(Process* P)
{
	RDY.enqueue(P);
	ExpTime += P->get_CT();
	if (P == RUN)
	{
		RUN = nullptr;
		BusyTime = 0;
		pSch->decrement_num_run();
		State = IDLE;
	}
}
Process* ProcessorRR::RemoveRun()
{
	ExpTime -= (RUN->get_CT() - BusyTime);
	Process* temp = RUN;
	RUN = nullptr;
	pSch->decrement_num_run();
	BusyTime = 0;
	State = IDLE;
	return temp;
}
void ProcessorRR::print_RDY()
{
	cout << "[RR] :  ";
	RDY.print();
}
int ProcessorRR::get_countrdy()
{
	return RDY.get_count();
}
ostream& operator << (ostream& out, ProcessorRR& c)
{
	out << " [RR]: " << c.get_countrdy() << "  RDY : ";
	c.print_RDY();
	return out;
}
bool ProcessorRR::fromRDY_to_run()
{
	Process* Pr;
	if (RDY.dequeue(Pr))
	{
		RUN = Pr;
		BusyTime = 1;
		pSch->increment_num_run();
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
void ProcessorRR::print_process_inRun()
{
	if (RUN)
		cout << *RUN;
}
Process* ProcessorRR::get_first()
{
	Process* first;
	RDY.peek(first);
	return first;
}