#include "StdAfx.h"

#include "Scheduler.h"
#include "LockManager.h"

#include <iterator>
#include <algorithm>
#include <cassert>

using namespace std;
using namespace boost;

typedef list<TranManager::Operation> OpLst;

//////////////////////////////////////////////////////////////////////////
//Schedule the transactions by the lock
OpLst ScheduleOperations(const OpLst& ls, LockManager& lm)
{
	OpLst ret = ls;
	BOOST_FOREACH(TranManager::Operation op, ret)
	{
		auto tid = op.m0;
		auto itemid = op.m4;
		auto type = (int)op.m1;//0 read 1 write 2 delete
		auto filename = op.m3;

		assert (type != -1);
		LockCondition lc;
		if (type != 2)
			lc = lm.Lock(tid, itemid, type, filename);
		else
			lc = lm.Lock(filename);

		if (lc.first == true)//get the lock
			continue;
		else {
			std::vector<int> result = *lc.second;
			if (result.size() > 1)//dead lock
			/*
			select the id from the ids which is the youngest one as the victim.
			if the type is process, just delete the rest of this 'transaction'
			if the type is transaction, just delete the whole transaction
			*/
			{
				break;
			}
			else//no dead lock
			/*Just move all current trans operations down the the last operation of the 
			current lock owner trans.
			*/
			{
				break;
			}
		}
	}
	return ret;
}
//////////////////////////////////////////////////////////////////////////

Scheduler::Scheduler(void){}

void Scheduler::ScheduleTransactions(Operations Transactions)
{
	OpLst ls;
	LockManager lm;
	copy(Transactions.begin(), Transactions.end(), back_inserter(ls));

	while (ls != ScheduleOperations(ls, lm))
	{}
}

Scheduler::~Scheduler(void)
{

}

Operations Scheduler::GetCommitedOutput()
{
	return Operations();
}
