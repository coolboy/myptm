#pragma once
#include "TranManager.h"

class Scheduler
{

public:
	Scheduler(void);
	std::vector<TranManager::Operation> ScheduleTransactions(std::vector<TranManager::Operation> Transactions);
	~Scheduler(void);
};

