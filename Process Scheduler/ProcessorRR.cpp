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
	if (will_overheat() && state != OVERHEATED)
	{
		Processor* ptr = RUN;
		pSch->movetoRDY(ptr);
		RUN = nullptr;
		while (!Ready.isEmpty())
		{
			ptr = RemoveFromRDY();
			pSch->movetoRDY(ptr);
		}
		stopping_time--;
		if (stopping_time == 0)
		{
			state = IDLE;
		}

	}
	else if (State == BUSY)
	{

		if (RUN->isDone())
		{
			pSch->Terminate(RemoveRun());
			fromRDY_to_run();
			CheckMigration();
		}
		else if (BusyTime == TimeSlice)
		{
			Process* R= RemoveRun();
			MovetoRDY(R);
			fromRDY_to_run();
			CheckMigration();
		}
		else if (RUN != nullptr && (RUN->get_remaining_time() < pSch->get_RTF()))
		{
			CheckMigration();
		}
		else
		{
			RUN->increment_run_time();
			BusyTime++;
		}
		return;
	}
	else if (!isBusy())
	{
		fromRDY_to_run();
		CheckMigration();
	}
}
void ProcessorRR::CheckMigration()
{
	while (RUN != nullptr && (RUN->get_remaining_time() < pSch->get_RTF()))
	{
		pSch->MigrateRRSJF(RemoveRun());
		fromRDY_to_run();
	}
}
int ProcessorRR::getExpTime()
{
	return ExpTime;
}
void ProcessorRR:: MovetoRDY(Process* P)
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
Process*  ProcessorRR::RemoveRun()
{
	ExpTime -= RUN->get_CT();
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
		return true;
	}
	else
	{
		return false;
		IdealTime++;
	}
}
void ProcessorRR::print_process_inRun()
{
	if (RUN)
		cout << *RUN;
}