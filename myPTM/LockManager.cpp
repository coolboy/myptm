#include "StdAfx.h"

#include "LockManager.h"

LockManager::LockManager(void){}

LockManager::~LockManager(void){}

LockCondition LockManager::Lock( int tid, int itemid, int type, const std::string& fileName )
{
	int lockId = tid + (itemid << 10) + (type << 20);

	LockCondition lc; //the return lock 
	LockInfo& ili = itemLocks[lockId]; //item lock info
	LockInfo& fli = fileLocks[fileName]; //file lock info
	DeadLockDetector detector;//for dead lock

	//for file locks only with WL
	if (!fli.owners.empty() && *fli.owners.begin() == tid /*&& type == READ_TYPE*/){//WL | self-owned | Want to read or write
		lc.get = true;
		lc.owners = fli.owners;
		return lc;
	}
	else if (!fli.owners.empty() && *fli.owners.begin() != tid && type == READ_TYPE){//WL | other-owned | Want to read
		fli.waitingQueue[tid] = false;//////////////////////////////////////////////////////////////////////////

		lc.get = false;
		lc.owners = fli.owners;
		lc.deadlock_ids = detector.Detect(itemLocks, fileLocks);
		return lc;
	}
	else if (!fli.owners.empty() && *fli.owners.begin() != tid && type == WRITE_TYPE){//WL | other-owned | Want to write
		fli.waitingQueue[tid] = true;

		lc.get = false;
		lc.owners = fli.owners;
		lc.deadlock_ids = detector.Detect(itemLocks, fileLocks);
		return lc;
	}

	//for item locks
	if (itemLocks.find(lockId) == itemLocks.end()){//no one lock it, get the lock
		ili.owners.insert(tid);
		ili.fileName = fileName;
		ili.itemId = itemid;
		ili.type = type;

		lc.get = true;
		lc.owners.insert(tid);
		return lc;
	}
	else{//lock on this item exist, 4 types: R/W SELF/OTHERS
		if (ili.type == READ_TYPE && ili.owners.find(tid) != ili.owners.end() && type == READ_TYPE){// RL | self-owned | Want to read
			lc.get = true;
			lc.owners = ili.owners;
			return lc;
		}
		else if (ili.type == READ_TYPE && ili.owners.find(tid) != ili.owners.end() && type == WRITE_TYPE){// RL | self-owned | Want to write
			if (ili.owners.size() == 1){//only me owns this read lock
				ili.type = WRITE_TYPE;//Upgrade RL 2 WL

				lc.get = true;
				lc.owners = ili.owners;
				return lc;
			}
			else{//Others also sharing this lock
				ili.waitingQueue[tid] = true;// insert current requesting tid to queue with the req to up RL 2 WL

				lc.get = false;
				lc.owners = ili.owners;
				lc.deadlock_ids = detector.Detect(itemLocks, fileLocks);
				return lc;
			}
		}
		else if (ili.type == WRITE_TYPE && ili.owners.find(tid) != ili.owners.end() && type == READ_TYPE){// WL | self-owned | Want to read
			lc.get = true;
			lc.owners = ili.owners;
			return lc;
		}
		else if (ili.type == WRITE_TYPE && ili.owners.find(tid) != ili.owners.end() && type == WRITE_TYPE){// WL | self-owned | Want to write
			lc.get = true;
			lc.owners = ili.owners;
			return lc;
		}
		else if (ili.type == READ_TYPE && ili.owners.find(tid) == ili.owners.end() && type == READ_TYPE){// RL | other-owned | Want to read
			ili.owners.insert(tid);

			lc.get = true;
			lc.owners = ili.owners;
			return lc;
		}
		else if (ili.type == READ_TYPE && ili.owners.find(tid) == ili.owners.end() && type == WRITE_TYPE){// RL | other-owned | Want to write
			ili.waitingQueue[tid] = true;

			lc.get = false;
			lc.owners = ili.owners;
			lc.deadlock_ids = detector.Detect(itemLocks, fileLocks);
			return lc;
		}
		else if (ili.type == WRITE_TYPE && ili.owners.find(tid) == ili.owners.end() && type == READ_TYPE){// WL | other-owned | Want to read
			ili.waitingQueue[tid] = false;

			lc.get = false;
			lc.owners = ili.owners;
			lc.deadlock_ids = detector.Detect(itemLocks, fileLocks);
			return lc;
		}
		else if (ili.type == WRITE_TYPE && ili.owners.find(tid) == ili.owners.end() && type == WRITE_TYPE){// WL | other-owned | Want to write
			ili.waitingQueue[tid] = true;

			lc.get = false;
			lc.owners = ili.owners;
			lc.deadlock_ids = detector.Detect(itemLocks, fileLocks);
			return lc;
		}
	}
	assert (0);

	return lc;
}

LockCondition LockManager::Lock( const std::string& fileName )
{
	LockCondition lc;
	return lc;
}

void LockManager::FreeLock( int tid )
{
	;
}

void LockManager::clear()
{
	;
}

//////////////////////////////////////////////////////////////////////////

DeadLockDetector::DeadLockDetector( void )
{

}

DeadLockDetector::~DeadLockDetector( void )
{

}

LockCycles DeadLockDetector::Detect(const LockManager::ItemLocks& ils, const LockManager::FileLocks& fls){
	return LockCycles();
}