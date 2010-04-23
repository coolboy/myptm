#include "StdAfx.h"

#include "Scheduler.h"
#include "LockManager.h"

#undef max

using namespace std;
using namespace boost;

typedef list<TranManager::Operation> OpLst;

//////////////////////////////////////////////////////////////////////////

//Get trans by id
OpLst GetTransactionsById(const OpLst& ls, int tid)
{
	OpLst ret;
	for_each(ls.begin(), ls.end(), [&ret, &tid] (const TranManager::Operation& op)  {
		if (op.m0 == tid)
			ret.push_back(op);
	}
	);
	return ret;
}

//remove trans by id
void RemoveTransactionById( OpLst& ls, OpLst::iterator beg, OpLst::iterator end, int tid)
{
	for (auto iter = beg; iter != end; iter++){
		if (iter->m0 == tid)
			ls.erase(iter);
	}
}

//Move the trans with id outside
OpLst TakeTransactionsById(const OpLst& ls, int tid)
{
	OpLst ret = ls;
	for (auto iter = ret.begin(); iter != ret.end(); iter++){
		if (iter->m0 == tid){
			ret.push_back(*iter);
			ret.erase(iter);
		}
	}
	return ret;
}

//Get Last Trans Position
OpLst::const_iterator GetLastPositionById(const OpLst& ls, int tid)
{
	auto ret = ls.end();

	for (auto iter = ls.begin(); iter != ls.end(); iter++){
		if (iter->m0 == tid){
			ret = iter;
		}
	}

	return ret;
}

OpLst::const_iterator GetLastPositionById(const OpLst& ls, const TIDS& tids)
{
	auto ret = ls.end();

	for (auto iter = ls.begin(); iter != ls.end(); iter++){
		if (tids.find(iter->m0) != tids.end()){
			ret = iter;
		}
	}

	return ret;
}

//Get age of the transaction till end
int GetAge(OpLst::const_iterator beg, OpLst::const_iterator end, int tid)
{
	int ret = 0;
	for_each(beg, end, [&](TranManager::Operation op){
		if (op.m0 == tid)
			++ret;
	});
	return ret;
}

//Schedule the transactions by the lock
OpLst ScheduleOperations(const OpLst& ls, LockManager& lm)
{
	OpLst ret = ls;
	for (auto iter = ret.begin(); iter != ret.end(); ++iter)
	{
		TranManager::Operation op = *iter;
		auto tid = op.m0;
		auto itemid = op.m4;
		auto type = (int)op.m1;//0 read 1 write 2 delete
		auto filename = op.m3;
		auto mode = op.m2;// 1 transaction 0 proc

		assert (type != -1);
		LockCondition lc;
		if (type == 0 || type == 1)
			lc = lm.Lock(tid, itemid, type, filename);
		else if (type == 2)
			lc = lm.Lock(filename);

		if (lc.deadlock_ids.empty())
			continue;

		if (lc.get == true)//get the lock
			continue;
		else {
			if (!lc.deadlock_ids.empty())//dead lock
			/* select the id from the ids which is the youngest one as the victim.
			if the mode is process(0), just delete the rest of this 'transaction'
			if the mode is transaction(1), just delete the whole transaction
			*/{
				TIDS& result = lc.deadlock_ids;
				int youngestId = -1;
				int currentYoungestAge = std::numeric_limits<int>::max();
				for_each(result.begin(), result.end(), [&](int tid){
					int age = GetAge(ret.begin(), iter, tid);
					if (age < currentYoungestAge)	{
						currentYoungestAge = age;
						youngestId = tid;
					}
				});

				assert (youngestId != -1);

				if (mode == 1)
					RemoveTransactionById(ret, ret.begin(), ret.end(), youngestId);
				else if (mode == 0)
					RemoveTransactionById(ret, iter, ret.end(), youngestId);
				else
					assert (0);
				
				break;
			}
			else if (!lc.owners.empty())//no dead lock
			/*Just move all current trans operations down the the last operation of the 
			current lock owner trans.
			*/{
				auto currentBlockedTrans = TakeTransactionsById(ret, tid);
				auto rid = lc	.owners;
				auto lastPosOfRid = GetLastPositionById(ret, rid);
				ret.splice(lastPosOfRid, currentBlockedTrans);
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

	while (ls != ScheduleOperations(ls, lm)){}
}

Scheduler::~Scheduler(void)
{

}

Operations Scheduler::GetCommitedOutput()
{
	return Operations();
}
