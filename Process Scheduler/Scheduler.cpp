#include "Scheduler.h"
#include"pair.h"
#include<fstream>
#include<string>
#include"ProcessorFCFS.h"
#include"ProcessorSJF.h"
#include"ProcessorRR.h"
#include"UI.h"
#include<iostream>
#include<Process.h>
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
	num_forked = 0;
	num_killed = 0;
	currentIOtime = 0;
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
//		u.choose_mode();
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
//Called Each STL time ( Time step % STL == 0 )
//No forked processes
void Scheduler::WorkSteal()
{
	Processor* Longest = get_longest();
	Processor* Shortest = get_shortest();
	float Steallimit = (Longest->getExpTime() - Shortest->getExpTime()) / float(Longest->getExpTime());
	while (Steallimit > 0.4)
	{
		Longest->
		Process* Stolen;
		Stolen = Longest->RemoveFromRDY();
		if (Stolen != nullptr)
		{
			if (Stolen->IsChild())
			{
				continue;
			}
			Shortest->MovetoRDY(Stolen);
		}
		else
		{
			break;
		}
		Steallimit = (Longest->getExpTime() - Shortest->getExpTime()) / float(Longest->getExpTime());
	}
}
void Scheduler::movetoBLK(Processor* Pr)
{
	BLKlist.enqueue(Pr->RemoveRun());
	num_blk++;
}
void Scheduler::Terminate(Process* P)
{
	if (P->get_child())
	{
		P->get_child()->get_processor()->TerminateChild(P->get_child()->get_ID());
	}
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
int Scheduler::get_RTF()
{
	return RTF;
}
int Scheduler::get_MaxW()
{
	return MaxW;
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
void Scheduler::generate_outfile()
{
	ofstream out_file;
	out_file.open("outfile.txt");
	Process* ptr=nullptr;
	out_file << "TT" << "       " << "PID" << "       " << "AT" << "       "<<"CT"<<"       "<<"IO_D"<<"               "<<"WT"<<"       "<<"RT"<<"         "<<"TRT"<<endl;
	int total_WT = 0;
	int total_RT = 0;
	int total_TRT = 0;
	while (!Terminated.isEmpty())
	{
		Terminated.dequeue(ptr);
		total_WT += ptr->get_WT();
		total_RT += ptr->get_RT();
		total_TRT += ptr->get_TRT();
			out_file << ptr->get_TT() << "       " << ptr->get_ID() << "       " << ptr->get_AT() << "       " << ptr->get_CT() << "       " << ptr->get_IOD() << "       " << ptr->get_WT() << "       " << ptr->get_RT() << "       " << ptr->get_TRT() << endl;
	}
	out_file << "Processes: " << num_processes << endl;
	out_file << "Avg WT = " << total_WT / num_processes << "         " << "Avg RT = " << total_RT / num_processes << "         " << "Avg TRT = " << total_TRT / num_processes << endl;
	out_file << "Migration % :" << "          " << "RTF = " << RTF << "  ,  " << " MAX W = " << MaxW << endl;
	out_file << " Work Steal = " << STL << "%" << endl;
	out_file << " Forked Process = " << (num_forked / num_processes) * 100 << "%" << endl;
	out_file << "Killed Process = " << (num_killed / num_processes) * 100 << " %" << endl << endl;
	out_file << "Processors : " << num_processors<<" { " << num_FCFS << " FCFS , " << num_SJF << " SJF ," << num_RR << " RR }" << endl;
	out_file << "Prpcessor Load :" << endl;
	for (int i = 0;i < num_processors;i++)
	{
		out_file << "P" << i + 1 << " = " << (Processor_ptr[i]->getTotalBusyTime() / total_TRT) * 100 << " %      ,      ";
	}
	out_file << endl << "Processors Utiliz " << endl;
	int total_utlization = 0;
	for (int i = 0;i < num_processors;i++)
	{
		total_utlization += (Processor_ptr[i]->getTotalBusyTime() / (Processor_ptr[i]->getTotalBusyTime() + Processor_ptr[i]->getIdealTime())) * 100;
		out_file << "P" << i + 1 << " = " << (Processor_ptr[i]->getTotalBusyTime() / (Processor_ptr[i]->getTotalBusyTime() + Processor_ptr[i]->getIdealTime())) * 100 << " %      ,      ";
	}
	out_file << "AVG Utlization = " << total_utlization / num_processors << endl;
}
Processor* Scheduler::get_shortest()
{
	if (num_RR + num_SJF + num_FCFS == 0)
		return nullptr;
	int shortest_duration = Processor_ptr[0]->getExpTime();
	Processor* shortest = Processor_ptr[0];
	for (int i = 1;i < num_processors;i++)
	{
		if (Processor_ptr[i]->getExpTime() < shortest_duration)
		{
			shortest_duration = Processor_ptr[i]->getExpTime();
			shortest = Processor_ptr[i];
		}

	}
	return shortest;
}
void Scheduler:: forK_a_child(Process* P)
{
	int new_id = num_processes + P->get_ID();
	Process* child = new Process(new_id, TimeStep, P->get_remaining_time());
	P->set_child(child);
	get_shortest_FCFS()->MovetoRDY(P);
	P->set_processor(get_shortest_FCFS());
	num_forked++;
}
int Scheduler::get_fork_probability()
{
	return ForkProb;
}
Processor* Scheduler::get_shortest_FCFS()
{
	Processor* shortestFCFS = Processor_ptr[num_SJF + num_RR];
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
Processor* Scheduler::get_shortest_RR()
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
Processor* Scheduler::get_longest()
{
	if (num_RR + num_SJF + num_FCFS == 0)
		return nullptr;
	Processor* Longest = Processor_ptr[0];
	for (int i = 1;i < num_RR + num_SJF + num_FCFS; i++)
	{
		if (Processor_ptr[i]->getExpTime() > Longest->getExpTime())
			Longest = Processor_ptr[i];
	}
	return Longest;
}
void Scheduler::from_run_to_blk(Process* P)
{
	BLKlist.enqueue(P);
	if (BLKlist.isEmpty())
	{
		currentIOtime = 1;
	}
}
void Scheduler:: from_blk_to_rdy(Process* P)
{

}
