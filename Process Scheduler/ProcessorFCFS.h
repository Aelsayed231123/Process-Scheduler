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
	Process* MovetoBLK();
	void Terminate(Process* P);
	bool MovetoRun(Process* P);
	bool Kill(int id);
};

