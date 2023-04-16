#include "Processor.h"
Processor::Processor(Scheduler* psch)
{
	pSch = psch;
}
int Processor:: getExpTime()
{
	return ExpectedTime;
}
Processor* Processor::getRUN()
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

