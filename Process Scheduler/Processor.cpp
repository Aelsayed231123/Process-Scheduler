#include "Processor.h"
#include<iostream>
using namespace std;
Processor::Processor(Scheduler* psch)
{
	pSch = psch;
	State = IDLE;
	pLoad = -1;
	pUtil = -1;
	RUN = nullptr;
	ExpTime = 0;
	BusyTime = 0;
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
	return (State==BUSY);
}
void Processor::print_process_inRun()
{
	if (RUN)
		cout << *RUN << " , ";
}
bool Processor:: Busymorethan1()
{
	return(BusyTime > 1);
}