#ifndef PROCESSOR_H
#define PROCESSOR_H
#include"Process.h"
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
public:
	Processor(Scheduler* psch);
	virtual void ScheduleAlgo() = 0;
	virtual void MovetoRDY(Process* P) = 0;
	virtual void MovetoBLK(Process* P) = 0;
	virtual void Terminate(Process* P) = 0;
	virtual bool MovetoRun(Process* P) = 0;
	int getExpTime();
	Process* getRUN();
	float getpLoad();
	float getpUtil();
	bool isBusy();
};
#endif
