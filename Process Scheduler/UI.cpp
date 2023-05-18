#include"UI.h"
#include<fstream>
enum mode
{
	step_by_step,
	interaactive,
	silent
};
UI::UI(Scheduler*p)
{
	Psch=p;
	mode_chosen = 3;
}
void UI::LoadInterface()
{
	if (mode_chosen != silent)
	{
		cout << "Current TIMESTEP : " << Psch->get_time_step() << "\n";
		cout << "-------------------------------------------------  READY PROCESSORS   -----------------------------------" << "\n";
		Psch->Print_Processors_Ready();
		cout << "\n";
		cout << "-------------------------------------------------  BLK PROCESSES     -----------------------------------" << "\n";
		cout << Psch->get_num_blk() << "  BLK: ";
		Psch->Print_Processes_blk();
		cout << "\n";
		cout << "-------------------------------------------------  RUN PROCESSES     -----------------------------------" << "\n";
		cout << Psch->get_num_run() << "  RUN: ";
		Psch->Print_Processes_inRun();
		cout << "\n";
		cout << "-------------------------------------------------  TRM PROCESSES     -----------------------------------" << "\n";
		cout << Psch->get_num_terminate() << " TRM: ";
		Psch->Print_Processes_trem();
		cout << endl;
		cout << "----------------------------------------------------------------------------------------------------------" << "\n";
		if (mode_chosen == interaactive)
		{
			int x;
			cout << "ENTER ANY CHAR TO MOVE TO NEXT TIME STEP " << "\n";
			cin >> x;
		}
	}
}
void UI::choose_mode()
{
	if (mode_chosen == 3)
	{
		cout << "FOR STEP BY STEP MODE ENTER 0 " << "\n";
		cout << "FOR INTERACTIVE MODE ENTER 1 " << "\n";
		cout << "FOR SILENT MODE ENTER 2 " << "\n";
		cin >> mode_chosen;
	}
}
