#include"UI.h"
UI::UI(Scheduler*p)
{
	Psch=p;
}
void UI::LoadInterface()
{
	cout<<"Current TIMESTEP : "<<Psch->get_time_step()<<"\n";
	cout<<"----------------------------------     READY PROCESSORS       ---------------------------------------------"<<"\n";
	Psch->Print_Processors_Ready();
	cout<<"\n";
	cout<<"-------------------------------------------------     BLK PROCESSES      ------------------------------------"<<"\n";
	cout<<Psch->get_num_blk()<<"  BLK: ";
	Psch->Print_Processes_blk();
	cout<<"\n";
	cout<<"-------------------------------------------      RUN PROCESSES      ---------------------------------------"<<"\n";
	cout<<Psch->get_num_run()<<"  RUN: ";
	Psch->Print_Processes_inRun();
	cout<<"\n";
	cout<<"--------------------------------------      TRM PROCESSES      -------------------------------------------------------------------"<<"\n";
	cout<<Psch->get_num_terminate()<<" TRM: ";
	Psch->Print_Processes_trem();
	cout<<endl;
	cout<<"---------------------------------------------------------------------------------------------------------------------------"<<"\n";
}
