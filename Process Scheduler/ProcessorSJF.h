#ifndef PROCESSORSJF_H
#define PROCESSORRSJF_H
#include"Process.h"
#include "Processor.h"

class ProcessorSJF : public Processor
{
	PriorityQueue<Process*>Ready;
	bool fromRDY_to_run();
public:
	ProcessorSJF(Scheduler* pS);
	void MovetoRDY(Process* P);
	void ScheduleAlgo();
	Process* RemoveRun();
	void print_RDY();
	int get_countrdy();
	void print_process_inRun();
};
#endif
