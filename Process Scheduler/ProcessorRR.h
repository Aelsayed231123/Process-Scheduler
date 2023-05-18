#pragma once
#include "Processor.h"
#include"LinkedQueue.h"
#include"Process.h"
class ProcessorRR :
	public Processor
{
private:
	LinkedQueue<Process*> RDY;
	int TimeSlice;
	int RunTime;
	bool fromRDY_to_run();
public:
	ProcessorRR(Scheduler* psch, int time);
	void MovetoRDY(Process* P);
	Process* RemoveFromRDY();
	void ScheduleAlgo();
	int getExpTime();
	Process* RemoveRun();
	void print_RDY();
	void CheckMigration();
	int get_countrdy();
};
