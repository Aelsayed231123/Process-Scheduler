#pragma once
#include"Process.h"
#include "Processor.h"
class ProcessorSJF : public Processor
{
	PriorityQueue<Process*>Ready;
public:
	ProcessorSJF(Scheduler* pS);
	void MovetoRDY(Process* P);
	void ScheduleAlgo();
	Process* MovetoBLK();
	void Terminate(Process* P);
	bool MovetoRun(Process* P);
};

