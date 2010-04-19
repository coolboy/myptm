#pragma once
#include "TranManager.h"

class Scheduler
{

public:
	Scheduler(void);
	Operations ScheduleTransactions(Operations Transactions);
	~Scheduler(void);
};

