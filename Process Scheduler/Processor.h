#pragma once
#include"Process.h"
#include "Scheduler.h"
enum CPUState{IDLE,BUSY};
class Processor
{
private:
	Scheduler* pSch;
	enum CPUState State;
	float pLoad, pUtil;
	int ExpectedTime;
	Process* RUN;
public:
	Processor(Scheduler* psch);
	virtual void ScheduleAlgo() = 0;
	int getExpTime();
	Process* getRUN();
	float getpLoad();
	float getpUtil();
};

