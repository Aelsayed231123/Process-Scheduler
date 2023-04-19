#ifndef PROCESSOR_H
#define PROCESSOR_H
#include"Process.h"
#include<iostream>
using namespace std;
class Scheduler;
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
public:
	Processor(Scheduler* psch);
	virtual void ScheduleAlgo() = 0;
	virtual void MovetoRDY(Process* P) = 0;
	virtual Process* RemoveRun() = 0;
	int getExpTime();
	Process* getRUN();
	float getpLoad();
	float getpUtil();
	bool isBusy();
	virtual void print_RDY() = 0;
	void print_process_inRun();
	bool Busymorethan1();
	virtual bool Kill(int id);

};
#endif
