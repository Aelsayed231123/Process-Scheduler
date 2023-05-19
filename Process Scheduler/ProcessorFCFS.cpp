#include "ProcessorFCFS.h"
#include"Scheduler.h"
#include"Process.h"
#include<iostream>
using namespace std;
ProcessorFCFS::ProcessorFCFS(Scheduler* psch) : Processor(psch)
{
}
void ProcessorFCFS::MovetoRDY(Process* P)
{
	Ready.InsertEnd(P);
	ExpTime += P->get_CT();
	if (P == RUN)
	{
		RUN = nullptr;
		pSch->decrement_num_run();
		BusyTime = 0;
		State = IDLE;
	}
}
void ProcessorFCFS::ScheduleAlgo()
{
	if (isBusy())
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
			else if (isBusy() && Fork(pSch->get_fork_probability()))
			{
				pSch->forK_a_child(RUN);
			}
			if (RUN != nullptr && ((pSch->get_time_step() - RUN->get_AT() - RUN->getRunTime()) > pSch->get_MaxW()) && !(RUN->IsChild()))
			{
				CheckMigration();
			}
			if (isBusy())
			{
				RUN->increment_run_time();
				BusyTime++;
				ExpTime--;
			}
		}
		TotalBusyTime++;
		return;
	}
	fromRDY_to_run();
	CheckMigration();
}
//Not Applicable for Forked Processes
void ProcessorFCFS::CheckMigration()
{
	while (RUN != nullptr && ((pSch->get_time_step() - RUN->get_AT() - RUN->getRunTime()) > pSch->get_MaxW()) && !(RUN->IsChild()))
	{
		if (pSch->MigrateFCFSRR(this))
			fromRDY_to_run();
		else
			break;
	}
}
Process* ProcessorFCFS::RemoveFromRDY()
{
	if (Ready.isEmpty())
	{
		return nullptr;
	}
	else
	{
		Process* First = (Ready.RemoveFirst())->getItem();
		ExpTime -= First->get_CT();
		return First;
	}
}
Process* ProcessorFCFS::RemoveRun()
{
	ExpTime -= (RUN->get_CT()-BusyTime);
	Process* temp = RUN;
	RUN = nullptr;
	pSch->decrement_num_run();
	BusyTime = 0;
	State = IDLE;
	return temp;
}
bool ProcessorFCFS::Kill(int id)
{
	if (RUN)
	{
		if (RUN->get_ID() == id)
		{
			pSch->TerminateKilled(RemoveRun());
				return true;
		}
	}
	if (Ready.isEmpty())
	{
		return false;
	}
	Process* p = nullptr;
	p = Ready.SearchbyID(id);
	if (p)
	{
		pSch->TerminateKilled(p);
		return true;
	}
	return false;
}
void ProcessorFCFS::print_RDY()
{
	cout << "[FCFS] :  ";
	Ready.PrintList();
}
int ProcessorFCFS::get_countrdy()
{
	return Ready.get_count();
}
ostream& operator << (ostream& out, ProcessorFCFS& c)
{
	out << " [FCFS]: " << c.get_countrdy() << "  RDY : ";
	c.print_RDY();
	return out;
}
bool ProcessorFCFS::fromRDY_to_run()
{
	Process* Pr;
	Pr = Ready.GetFirst()->getItem();
	if (Pr)
	{
		RUN = Pr;
		Pr->increment_run_time();
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
bool ProcessorFCFS::Fork(int fp)
{
	if (RUN->get_Lchild()&&RUN->get_Rchild())
		return false;
	bool Create = false;
	float r = ((double)rand() / (RAND_MAX)) * 100;
	if (r <= fp)
	{
		Create = true;
	}
	return Create;
}
bool ProcessorFCFS::TerminateChild(int id)
{
	if (RUN)
	{
		if (RUN->get_ID() == id)
		{
			pSch->Terminate(RemoveRun());
			fromRDY_to_run();
			return true;
		}
	}
	else
	{
		Process* P = nullptr;
		P = Ready.SearchbyID(id);
		if (P)
		{
			pSch->Terminate(P);
			return true;
		}
	}
	return false;
}
void ProcessorFCFS::print_process_inRun()
{
	if (RUN)
		cout << *RUN;
}
Process* ProcessorFCFS:: get_first()
{
	Process* first = Ready.getHead();
	return first;
}