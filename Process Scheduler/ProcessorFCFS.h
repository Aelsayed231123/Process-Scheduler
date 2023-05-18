#pragma once
#include "Processor.h"
#include"LinkedList.h"
class ProcessorFCFS :
    public Processor
{
    LinkedList<Process*>Ready;
	bool fromRDY_to_run();
public:
    ProcessorFCFS(Scheduler* psch);
	void MovetoRDY(Process* P);
	void ScheduleAlgo();
	 Process* RemoveRun();
	bool Kill(int id);
	void print_RDY();
	void CheckMigration();
	int get_countrdy();
	bool Fork(int fp);
};

