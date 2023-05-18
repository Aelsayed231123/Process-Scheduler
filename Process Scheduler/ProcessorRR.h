#ifndef PROCESSORRR_H
#define PROCESSORRR_H
#include "Processor.h"
#include"LinkedQueue.h"
#include"Process.h"
class ProcessorRR :
	public Processor
{
private:
	LinkedQueue<Process*> RDY;
	int TimeSlice;
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
	void print_process_inRun();
};
#endif