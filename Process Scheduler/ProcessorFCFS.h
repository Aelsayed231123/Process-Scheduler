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
	void MovetoBLK(Process* P);
	void Terminate(Process* P);
	bool MovetoRun(Process* P);
	bool Kill(int id);
};

