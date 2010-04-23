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
		if (li.type == READ_TYPE && li.owners.find(tid) != li.owners.end() && type == READ_TYPE){// RL | self-owned | Want to read
			lc.get == true;
			lc.owners = li.owners;
			return lc;
		}
		else if (li.type == READ_TYPE && li.owners.find(tid) != li.owners.end() && type == WRITE_TYPE){// RL | self-owned | Want to write
			if (li.owners.size() == 1){//only me owns this read lock
				li.type = WRITE_TYPE;
				locks[lockId] = li;//Upgrade current RL to WL

				lc.get = true;
				lc.owners = li.owners;
				return lc;
			}
			else{//Others also sharing this lock
				;
			}
		}
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
