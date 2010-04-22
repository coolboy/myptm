#include "StdAfx.h"
#include "Scheduler.h"

#include <iterator>
#include <algorithm>

using namespace std;
using namespace boost;

typedef list<TranManager::Operation> OpLst;

Scheduler::Scheduler(void)
{
   
}

void Scheduler::ScheduleTransactions(Operations Transactions)
{
	OpLst ls;
	copy(Transactions.begin(), Transactions.end(), back_inserter(ls));
}

Scheduler::~Scheduler(void)
{

}

Operations Scheduler::GetCommitedOutput()
{
	return Operations();
}
