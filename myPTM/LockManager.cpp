#include "StdAfx.h"

#include "LockManager.h"

#define READ_TYPE 0
#define WRITE_TYPE 1

LockManager::LockManager(void){}

LockManager::~LockManager(void){}

LockCondition LockManager::Lock( int tid, int itemid, int type, const std::string& fileName )
{
	int lockId = tid + (itemid << 10) + (type << 20);

	LockCondition lc; //the return lock 
	LockInfo& li = itemLocks[lockId]; //lock info
	DeadLockDetector detector;//4 dead lock

	if (itemLocks.find(lockId) == itemLocks.end()){//no one lock it, get the lock
		li.owners.insert(tid);
		li.fileName = fileName;
		li.itemId = itemid;
		li.type = type;

		lc.get = true;
		lc.owners.insert(tid);
		return lc;
	}
	else{//lock on this item exist, 4 types: R/W SELF/OTHERS
		li = itemLocks[lockId];
		if (li.type == READ_TYPE && li.owners.find(tid) != li.owners.end() && type == READ_TYPE){// RL | self-owned | Want to read
			lc.get = true;
			lc.owners = li.owners;
			return lc;
		}
		else if (li.type == READ_TYPE && li.owners.find(tid) != li.owners.end() && type == WRITE_TYPE){// RL | self-owned | Want to write
			if (li.owners.size() == 1){//only me owns this read lock
				li.type = WRITE_TYPE;//Upgrade RL 2 WL

				lc.get = true;
				lc.owners = li.owners;
				return lc;
			}
			else{//Others also sharing this lock
				li.waitingQueue[tid] = true;// insert current requesting tid to queue with the req to up RL 2 WL

				lc.get = false;
				lc.owners = li.owners;
				lc.deadlock_ids = detector.Detect(itemLocks, fileLocks);
				return lc;
			}
		}
		else if (li.type == WRITE_TYPE && li.owners.find(tid) != li.owners.end() && type == READ_TYPE){// WL | self-owned | Want to read
			lc.get = true;
			lc.owners = li.owners;
			return lc;
		}
		else if (li.type == WRITE_TYPE && li.owners.find(tid) != li.owners.end() && type == WRITE_TYPE){// WL | self-owned | Want to write
			lc.get = true;
			lc.owners = li.owners;
			return lc;
		}
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
