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
	int ExpTime;
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
	virtual void MovetoRDY(Process* P) = 0;
	virtual void MovetoRun(Process* P) = 0;
	virtual void MovetoBLK(Process* P) = 0;
	virtual void Terminate(Process* P) = 0;
	int getExpTime();
	Process* getRUN();
	float getpLoad();
	float getpUtil();
	bool isBusy();
};
#endif
