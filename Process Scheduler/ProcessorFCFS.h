#pragma once
#include "Processor.h"
class ProcessorFCFS :
    public Processor
{
    LinkedQueue<Process*>Ready;
public:
    ProcessorFCFS(Scheduler* psch);
	void MovetoRDY(Process* P);
	void ScheduleAlgo();
	void MovetoBLK(Process* P);
	void Terminate(Process* P);
	bool MovetoRun(Process* P);
};

