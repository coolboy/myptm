#include "StdAfx.h"

#include "LockManager.h"

LockManager::LockManager(void){}

LockManager::~LockManager(void){}

LockCondition LockManager::Lock( int tid, int itemid, int type, const std::string& fileName )
{
	int lockId = tid + (itemid << 10) + (type << 20);

	LockCondition lc; //the return lock 
	LockInfo li; //lock info

	if (locks.find(lockId) == locks.end()){//no one lock it, get the lock
		li.owners.insert(tid);
		li.fileName = fileName;
		li.itemId = itemid;
		li.type = type;

		locks[lockId] = li;

		lc.get = true;
		lc.owners.insert(tid);
		return lc;
	}
	else{//lock on this item exist, 4 types: R/W SELF/OTHERS
		li = locks[lockId];
		//if (li.type == 0 && li.owners == tid){// R SELF
		//}
		//else if (li.type == 1 && li.owners == tid){// W SELF
		//}
		//else if (li.type == 0 && li.owners != tid){// R OTHERS
		//}
		//else if (li.type == 1 && li.owners != tid){// W OTHERS
		//}
	}
	return lc;
}

LockCondition LockManager::Lock( const std::string& fileName )
{
	LockCondition lc;
	return lc;
}
