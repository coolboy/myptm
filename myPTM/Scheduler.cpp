#include "StdAfx.h"
#include "Scheduler.h"

using namespace std;
using namespace boost;

Scheduler::Scheduler(void)
{
   
}

void Scheduler::ScheduleTransactions(Operations Transactions)
{
	//Lock table
	//class transaction
}

Scheduler::~Scheduler(void)
{

}

Operations Scheduler::GetCommitedOutput()
{
	return Operations();
}
