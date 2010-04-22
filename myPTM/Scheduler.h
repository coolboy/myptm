#pragma once

#include "TranManager.h"
#include "Transaction.h"

typedef std::map<int, Transaction> TranSet;

class Scheduler
{
public:
	Scheduler(void);
	~Scheduler(void);

	void ScheduleTransactions(Operations Transactions);

	Operations GetCommitedOutput();

private:
	TranSet trans;
};

