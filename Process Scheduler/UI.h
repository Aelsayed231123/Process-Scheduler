#include<iostream>
#include"Scheduler.h"
using namespace std;
class UI
{
private :
	Scheduler*Psch;
	int mode_chosen;
public:
	UI(Scheduler*p);
	void LoadInterface();
	void choose_mode();
};
