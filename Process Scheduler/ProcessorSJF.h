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
	void MovetoRun(Process* P);
	void MovetoBLK(Process* P);
	void Terminate(Process* P);
};

