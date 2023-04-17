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
public:
	ProcessorRR(Scheduler* psch, int time);
	void MovetoRDY(Process* P);
	void MovetoRun(Process* P);
	void MovetoBLK(Process* P);
	void Terminate(Process* P);
	void ScheduleAlgo();
	int getExpTime();
};
