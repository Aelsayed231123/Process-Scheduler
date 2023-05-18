#ifndef PROCESSOR_H
#define PROCESSOR_H
#include<iostream>
using namespace std;
class Scheduler;
class Process;
enum CPUState { IDLE, BUSY };
class Processor
{
protected:
	Scheduler* pSch;
	enum CPUState State;
	float pLoad, pUtil;
	Process* RUN;
	int ExpTime;
	int BusyTime;
	int TotalBusyTime;
	int IdealTime;
public:
	Processor(Scheduler* psch);
	virtual void ScheduleAlgo() = 0;
	virtual void MovetoRDY(Process* P) = 0;
	virtual Process* RemoveFromRDY() = 0;
	virtual Process* RemoveRun() = 0;
	int getExpTime();
	int getTotalBusyTime();
	int getIdealTime();
	Process* getRUN();
	float getpLoad();
	float getpUtil();
	bool isBusy();
	virtual void print_RDY() = 0;
	virtual void print_process_inRun() = 0;
	bool Busymorethan1();
	virtual bool Kill(int id);
	virtual bool TerminateChild(int id);

};
#endif
