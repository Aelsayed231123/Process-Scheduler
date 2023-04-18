#include "Scheduler.h"
#include"pair.h"
#include<fstream>
#include<string>
#include"ProcessorFCFS.h"
#include"ProcessorSJF.h"
#include"ProcessorRR.h"
Scheduler::Scheduler()
{
	process_ptr=nullptr;
	Processor_ptr = nullptr;
	num_FCFS=0;
	num_RR=0;
	num_SJF=0;
	RTF=0;
	MaxW=0;
	STL=0;
	ForkProb=0;
	num_processes=0;
	TimeStep = 1;
	TerminatedSize = 0;
}
void Scheduler::Simulate()
{
	while (TerminatedSize < num_processes)
	{

		Schedule();
		int Random = (rand() % (100 - 1 + 1)) + 1;
		for (int i = 0;i < num_FCFS + num_RR + num_SJF;i++)
		{
			if(Processor_ptr[i]->isBusy())
			{
				if (Random >= 1 && Random <= 15)
				{
					movetoBLK(Processor_ptr[i]);
					//clear run of processor
				}
				else if (Random >= 20 && Random <= 30)
				{
					Processor_ptr[i]->MovetoRDY(Processor_ptr[i]->getRUN());
					//clear run of processor

				}
				else if (Random >= 50 && Random <= 60)
				{
					Terminate(Processor_ptr[i]->getRUN());
					//clear run of processor
				}
			}
			else{
			break;
			}
		}
		TimeStep++;
		
	}
}
void Scheduler::Schedule()
{
	/// <summary>
		/// for(int i=0;i<num_FCFS+num_RR+num_SJF;i++)
		/// {
		///		Process* P
		///		New.peak(P)
		///		if(p.get_AT()==TimeStep)
		///		{
		///		ProcessorList[i]->MovetoRDY(P);
		///		New.dequeue(p);
		///		}
		///		else
		///		{
		/// break;
		/// }
		/// 
		/// }
		/// for(int i=0;i<num_FCFS+num_RR+num_SJF;i++)
		/// {
		///		ProcessorList[i]->ScheduleAlgo();
		/// }
		/// 
		/// </summary>
}
void Scheduler::LoadInputs()
{
	ifstream finput("f1.txt",ios::in);
	finput>>num_FCFS>>num_SJF>>num_RR;
	int time_slice;
	finput>>time_slice;
	Processor_ptr = new Processor*[num_FCFS + num_FCFS + num_RR];
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
	finput>>RTF>>MaxW>>STL>>ForkProb>>num_processes;
	int loop_count=num_processes;
	process_ptr=new Process*[num_processes];
	int index=0;
	int Arrival_time,ID,CPU_time,n;
	mypair<int,int>arr[100];
	while(loop_count)
	{
		finput>>Arrival_time>>ID>>CPU_time>>n;
		for(int i=0;i<n;i++)
		{
			finput.ignore(100,'(');
			finput>>arr[i].first;
			finput.ignore(100,',');
			finput>>arr[i].second;
		}
			Process*ptr=new Process(ID,Arrival_time,CPU_time,n,arr);
			process_ptr[index]=ptr;
		//////////intantaie process with constructor,setting pairs
		finput.ignore(10000000000,'\n');
		index++;
		loop_count--;
	}
	while(!finput.eof())
	{
		mypair<int,int>sig;
		finput>>sig.first>>sig.second;
		sigKILL.enqueue(sig);
		finput.ignore(100000000,'\n');
	}
}
void Scheduler::movetoBLK(Processor* Pr)
{
	BLKlist.enqueue(Pr->MovetoBLK());
}
void Scheduler::Terminate(Process* P)
{
	P->set_TT(TimeStep);
	Terminated.enqueue(P);
	TerminatedSize++;
}
void Scheduler::movetoRDY(Process* p,Processor* pu)
{
	pu->MovetoRDY(p);
}
int Scheduler::get_time_step()
{
	return TimeStep;
}