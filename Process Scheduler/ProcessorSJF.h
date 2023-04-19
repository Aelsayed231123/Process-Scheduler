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
	Process* RemoveRun();
	void print_RDY();
	int get_countrdy();
};

