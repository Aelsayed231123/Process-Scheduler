#pragma once
#include "Scheduler.h"
#include "Process.h"
enum CPUState{IDLE,BUSY};
class Processor
{
protected:
	Scheduler* pSch;
	enum CPUState State;
	float pLoad, pUtil;
	Process* RUN;
public:
	Processor(Scheduler * psch);
	virtual void ScheduleAlgo() = 0;
	virtual int getExpTime() = 0;
	virtual void MovetoRDY(Process* P) = 0;
	Process* getRUN();
	float getpLoad();
	float getpUtil();
};

