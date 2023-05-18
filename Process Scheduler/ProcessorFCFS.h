#ifndef PROCESSORFCFS_H
#define PROCESSORFCFS_H
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
	int get_countrdy();
	bool Fork(int fp);
	bool TerminateChild(int id);
	void print_process_inRun();
};
#endif
