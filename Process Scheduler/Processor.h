#pragma once
#include "Scheduler.h"
enum CPUState{IDLE,BUSY};
class Processor
{
private:
	Scheduler* pSch;
	enum CPUState State;
	float pLoad, pUtil;
	int ExpectedTime;
	Processor* RUN;
public:
	Processor(Scheduler* psch);
	virtual void ScheduleAlgo() = 0;
	int getExpTime();
	Processor* getRUN();
	float getpLoad();
	float getpUtil();
};

