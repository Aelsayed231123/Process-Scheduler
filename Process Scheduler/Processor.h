#ifndef PROCESSOR_H
#define PROCESSOR_H
#include"Process.h"
enum CPUState { IDLE, BUSY };
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
	Processor(Scheduler* psch);
	virtual void ScheduleAlgo() = 0;
	virtual void MovetoRDY(Process* P) = 0;
	void MovetoBLK(Process* P);
	void Terminate(Process* P);
	bool MovetoRun(Process* P);
	int getExpTime();
	Process* getRUN();
	float getpLoad();
	float getpUtil();
	bool isBusy();
};
#endif
