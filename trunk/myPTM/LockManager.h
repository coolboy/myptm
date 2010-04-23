#pragma once

#include <map>

#include "Transaction.h"

typedef std::vector<TIDS> LockCycles;

class LockCondition
{
public:
	LockCondition():get(false) {}

	bool get; //get it?
	TIDS owners; //Current owners
	LockCycles deadlock_ids; //the current deadlock ids
};

class LockInfo
{
public:
	TIDS owners; //Current owners
	int itemId;
	int type; // 0-read 1-write
	std::string	fileName;

	//tid, need upgrade to WL?
	std::map<int, bool> waitingQueue;
};

class LockManager
{
public:
	typedef std::map<int, LockInfo> ItemLocks;
	typedef std::map<int, std::string> FileLocks;

public:
	LockManager(void);
	~LockManager(void);

	//lock the item and return the trans ids in the cycle if detect a dead lock
	// type: 0-read 1-write -1-error
	LockCondition Lock (int tid, int itemid, int type, const std::string&	fileName);

	//lock the whole file  and return the trans ids in the cycle if detect a dead lock
	LockCondition Lock (const std::string&	fileName);

	//Reinit the class
	void clear(){;}

	//Free all the locks that owned by tid
	void FreeLock(int tid){;}

private:
	//lockId = tid + itemid << 10 + type << 20, lock
	ItemLocks	itemLocks;
	//file lock : tid, fileName
	FileLocks fileLocks;
};

class DeadLockDetector
{
public:

public:
	DeadLockDetector(void){}
	~DeadLockDetector(void){}

	LockCycles Detect(const LockManager::ItemLocks& ils, const LockManager::FileLocks& fls){
		return LockCycles();
	}
};
