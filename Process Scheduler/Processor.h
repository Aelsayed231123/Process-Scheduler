#ifndef PROCESSOR_H
#define PROCESSOR_H
#include"Process.h"
enum CPUState{IDLE,BUSY};
class Scheduler;
class Processor
{
protected:
	Scheduler* pSch;
	enum CPUState State;
	float pLoad, pUtil;
	Process* RUN;
public:
	Processor::Processor(Scheduler* psch)
{
	pSch = psch;
	State = IDLE;
	pLoad = -1;
	pUtil = -1;
	RUN = nullptr;
}
	virtual void ScheduleAlgo() = 0;
	virtual int getExpTime() = 0;
	virtual void MovetoRDY(Process* P) = 0;
	
	Process* getRUN()
{
	return RUN;
}
float getpLoad()
{
	return pLoad;
}
float getpUtil()
{
	return pUtil;
}
};
#endif
