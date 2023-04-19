#pragma once
#include "Processor.h"
#include"LinkedList.h"
class ProcessorFCFS :
    public Processor
{
    LinkedList<Process*>Ready;
public:
    ProcessorFCFS(Scheduler* psch);
	void MovetoRDY(Process* P);
	void ScheduleAlgo();
	 Process* RemoveRun();
	bool Kill(int id);
	void print_RDY();
	int get_countrdy();
};

