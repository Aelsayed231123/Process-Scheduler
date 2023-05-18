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
	IdealTime = 0;
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
bool Processor:: Busymorethan1()
{
	return(BusyTime > 1);
}
 bool Processor::  Kill(int id)
{
	return false;
}
 bool Processor::TerminateChild(int id)
 {
	 return false;
 }
 int  Processor::getBusyTime()
 {
	 return BusyTime;
 }
 int Processor::getIdealTime()
 {
	 return IdealTime;
 }
 bool Processor::isOverheated()
 {
	 return (State == OVERHEATED);
 }
 void Processor::decrement_stopping_time()
 {
	 stopping_time--;
 }
 bool Processor::will_overheat()
 {
	 int prob= (rand() % (100 - 1 + 1)) + 1;
	 if (prob < 5 && prob>0 && isBusy())
	 {
		 State = OVERHEATED;
		 return true;
	 }
	 else
		 return false;
 }