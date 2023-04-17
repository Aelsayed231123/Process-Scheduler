#include "Processor.h"
Processor::Processor(Scheduler* psch)
{
	pSch = psch;
	State = IDLE;
	pLoad = -1;
	pUtil = -1;
	RUN = nullptr;
	ExpTime = 0;
}
Process* Processor::getRUN()
{
	return RUN;
}
float Processor::getpLoad()
{
	return pLoad;
}
float Processor::getpUtil()
{
	return pUtil;
}
int Processor::getExpTime()
{
	return ExpTime;
}
bool Processor::isBusy()
{
	return(State == BUSY);
}
