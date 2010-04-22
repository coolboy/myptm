#include "StdAfx.h"
#include "LockManager.h"


LockManager::LockManager(void)
{
}


LockManager::~LockManager(void)
{
}

LockCondition LockManager::Lock( int tid, int itemid, int type, const std::string& fileName )
{
	return LockCondition();
}

LockCondition LockManager::Lock( const std::string& fileName )
{
	return LockCondition();
}
