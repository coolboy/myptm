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
		li.latest_owner = tid;
		li.fileName = fileName;
		li.itemId = itemid;
		li.type = type;

		locks[lockId] = li;

		lc.get = true;
		lc.latest_owner = tid;
		return lc;
	}
	else{//lock on this item exist, 4 types: R/W SELF/OTHERS
		li = locks[lockId];
		if (li.type == 0 && li.latest_owner == tid){// R SELF
			if (type == 0){
			}
			else if (type == 1){
				li.type = 1;
				locks[lockId] = li;//Upgrade RL to WL
			}
			lc.get = true;
			lc.latest_owner = tid;
			return lc;
		}
		else if (li.type == 1 && li.latest_owner == tid){// W SELF
			lc.get = true;
			lc.latest_owner = tid;
			return lc;
		}
		else if (li.type == 0 && li.latest_owner != tid){// R OTHERS
			if (type == 0){}
			else if (type == 1){}

			lc.get = false;
			lc.latest_owner = li.latest_owner;
		}
		else if (li.type == 1 && li.latest_owner != tid){// W OTHERS

		}
	}
	return lc;
}

LockCondition LockManager::Lock( const std::string& fileName )
{
	LockCondition lc;
	return lc;
}
