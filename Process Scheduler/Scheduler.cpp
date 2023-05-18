#include "Scheduler.h"
#include"pair.h"
#include<fstream>
#include<string>
#include"ProcessorFCFS.h"
#include"ProcessorSJF.h"
#include"ProcessorRR.h"
#include"UI.h"
Scheduler::Scheduler()
{
	process_ptr = nullptr;
	Processor_ptr = nullptr;
	num_FCFS = 0;
	num_RR = 0;
	num_SJF = 0;
	RTF = 0;
	MaxW = 0;
	STL = 0;
	ForkProb = 0;
	num_processes = 0;
	TimeStep = 1;
	num_processors = 0;
	num_run = 0;
	num_blk = 0;
	num_terminate = 0;
}
//void Scheduler::Simulate()
//{
//	LoadInputs();
//		UI u(this);
//		int i = 0;
//	while (num_terminate < num_processes)
//	{
//		Schedule(i);
//		int Random = (rand() % (100 - 1 + 1)) + 1;
//		for (int i = 0; i < num_processors; i++)
//		{
//			if ((Processor_ptr[i]->Busymorethan1())&&Processor_ptr[i]->isBusy())
//			{
//				if (Random >= 1 && Random <= 15)
//				{
//					movetoBLK(Processor_ptr[i]);
//					//clear run of processor
//				}
//				else if (Random >= 20 && Random <= 30)
//				{
//					Processor_ptr[i]->MovetoRDY(Processor_ptr[i]->getRUN());
//					//clear run of processor
//
//				}
//				else if (Random >= 50 && Random <= 60)
//				{
//					Terminate(Processor_ptr[i]);
//					//clear run of processor
//				}
//			}
//			if (!BLKlist.isEmpty())
//			{
//				if (Random < 10)
//				{
//					Process* P;
//					BLKlist.dequeue(P);
//					num_blk--;
//					Processor_ptr[i]->MovetoRDY(P);
//				}
//			}
//			Random = (rand() % (100 - 1 + 1)) + 1;
//		}
//		Random = (rand() % (100 - 1 + 1)) + 1;
//		for (int i = num_RR + num_SJF; i < num_processors; i++)
//		{
//			if (Processor_ptr[i]->Kill(Random))
//			{
//				break;
//			}
//		}
//		u.LoadInterface();
//		TimeStep++;
//	}
//}
void Scheduler::Schedule(int& ind)
{
	Process* P;
	NEW.peek(P);
	if (P)
	{
		while (P&&(P->get_AT() == TimeStep))
		{
			Processor_ptr[ind]->MovetoRDY(P);
			ind++;
			NEW.dequeue(P);
			NEW.peek(P);
		}
	}
			if (ind ==num_processors)
				ind = 0;
	for (int i = 0; i < num_processors; i++)
	{
		Processor_ptr[i]->ScheduleAlgo();
	}

}
void Scheduler::LoadInputs()
{
	ifstream finput("f1.txt", ios::in);
	finput >> num_FCFS >> num_SJF >> num_RR;
	int time_slice;
	finput >> time_slice;
	num_processors = num_FCFS + num_SJF + num_RR;
	Processor_ptr = new Processor * [num_processors];
	int i = 0;
	for (; i < num_RR; i++)
	{
		Processor_ptr[i] = new ProcessorRR(this, time_slice);
	}
	for (; i < num_SJF + num_RR; i++)
	{
		Processor_ptr[i] = new ProcessorSJF(this);
	}
	for (; i < num_SJF + num_RR + num_FCFS; i++)
	{
		Processor_ptr[i] = new ProcessorFCFS(this);
	}

	////////////////////////////creating rr processors with timesclice as par in constructor
	finput >> RTF >> MaxW >> STL >> ForkProb >> num_processes;
	int loop_count = num_processes;
	int Arrival_time, ID, CPU_time, n;
	mypair<int, int>arr[100];
	while (loop_count)
	{
		finput >> Arrival_time >> ID >> CPU_time >> n;
		for (int i = 0; i < n; i++)
		{
			finput.ignore(100, '(');
			finput >> arr[i].first;
			finput.ignore(100, ',');
			finput >> arr[i].second;
		}
		Process* ptr = new Process(ID, Arrival_time, CPU_time, n, arr);
		NEW.enqueue(ptr);
		//////////intantaie process with constructor,setting pairs
		finput.ignore(10000000000, '\n');
		loop_count--;
	}
	while (!finput.eof())
	{
		mypair<int, int>sig;
		finput >> sig.first >> sig.second;
		sigKILL.enqueue(sig);
		finput.ignore(100000000, '\n');
	}
}
bool Scheduler::MigrateRRSJF(Process* P)
{
	Processor* Shortest = get_shortest_SJF();
	if (Shortest == nullptr)
		return false;
	Shortest->MovetoRDY(P);
	return true;
}
bool Scheduler::MigrateFCFSRR(Process* P)
{
	Processor* Shortest = get_shortest_RR();
	if (Shortest == nullptr)
		return false;
	Shortest->MovetoRDY(P);
	return true;
}
void Scheduler::movetoBLK(Processor* Pr)
{
	BLKlist.enqueue(Pr->RemoveRun());
	num_blk++;
}
void Scheduler::Terminate(Process* P)
{
	P->set_TT(TimeStep);
	Terminated.enqueue(P);
	num_terminate++;
}
void Scheduler::movetoRDY(Process* p, Processor* pu)
{
	pu->MovetoRDY(p);
}
int Scheduler::get_time_step()
{
	return TimeStep;
}
void Scheduler::Print_Processors_Ready()
{
	for (int i = 0; i < num_processors; i++)
	{
		cout << "Processor " << i + 1;
		Processor_ptr[i]->print_RDY();
		cout << "\n";
	}
}
void Scheduler::Print_Processes_inRun()
{
	for (int i = 0; i < num_processors; i++)
	{

		Processor_ptr[i]->print_process_inRun();
		cout << "(P" << i + 1 << ") ,";
	}
}
void Scheduler::Print_Processes_trem()
{
	Terminated.print();
}
void Scheduler::Print_Processes_blk()
{
	BLKlist.print();
}
int Scheduler::get_num_run()
{
	return num_run;
}
int Scheduler::get_num_blk()
{
	return num_blk;
}
int Scheduler::get_num_terminate()
{
	return num_terminate;
}
void Scheduler::increment_num_run()
{
	num_run++;
}
void Scheduler::decrement_num_run()
{
	num_run--;
}
void Scheduler::TerminateKilled(Process* P)
{
	Terminated.enqueue(P);
	num_terminate++;
}
void Scheduler:: forK_a_child(Process* P)
{
	int new_id = num_processes + P->get_ID();
	Process* child = new Process(new_id, TimeStep, P->get_remaining_time());
	P->set_child(child);
	get_shortest_FCFS()->MovetoRDY(P);
}
int Scheduler::get_fork_probability()
{
	return ForkProb;
}
Processor* Scheduler::get_shortest_FCFS()
{
	Processor* shortestFCFS = Processor_ptr[num_SJF + num_RR + 1];
	for (int i = num_SJF + num_RR + 1; i < num_SJF + num_RR + num_FCFS; i++)
	{
		if (Processor_ptr[i]->getExpTime() < shortestFCFS->getExpTime())
			shortestFCFS = Processor_ptr[i];
	}
	return shortestFCFS;
}
Processor* Scheduler::get_shortest_SJF()
{
	if (num_RR == 0)
		return nullptr;
	Processor* ShortestSJF = Processor_ptr[num_RR];
	for (int i = num_RR + 1;i < num_RR + num_SJF; i++)
	{
		if (Processor_ptr[i]->getExpTime() < ShortestSJF->getExpTime())
			ShortestSJF = Processor_ptr[i];
	}
	return ShortestSJF;
}
Processor* Scheduler::get_shortest_SJF()
{
	if (num_SJF == 0)
		return nullptr;
	Processor* ShortestRR = Processor_ptr[0];
	for (int i = 1;i < num_RR; i++)
	{
		if (Processor_ptr[i]->getExpTime() < ShortestRR->getExpTime())
			ShortestRR = Processor_ptr[i];
	}
	return ShortestRR;
}