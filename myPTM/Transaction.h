#pragma once

#include "TranManager.h"

class Transaction
{
public:
	Transaction(void);
	~Transaction(void);

	bool doOne (const TranManager::Operation& oper);

	Operations getCommitedResults();
};

