#pragma once
#include"Process.h"
#include "Processor.h"
class ProcessorSJF : public Processor
{
	PriorityQueue<Process*>Ready;
};

