#include "Processor.h"
Processor::Processor(Scheduler* psch)
{
	pSch = psch;
}
int Processor:: getExpTime()
{
	return ExpectedTime;
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

