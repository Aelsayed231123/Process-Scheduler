#include<iostream>
#include"Scheduler.h"
using namespace std;
class UI
{
private :
	Scheduler*Psch;
public:
	UI(Scheduler*p);
	void LoadInterface();
};
