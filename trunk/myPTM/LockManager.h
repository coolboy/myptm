#pragma once

#include <vector>

typedef std::vector<int> TIDS;

class LockCondition
{
public:
	LockCondition():get(false), latest_owner(-1){}

	bool get; //get it?
	int latest_owner; //latest owner tid
	TIDS deadlock_ids; //the current deadlock ids
};

class LockInfo
{
public:
	int latest_owner; //latest owner tid
	int itemId;
	int type; // 0-read 1-write
	std::string	fileName;

	TIDS waitingQueue;
};

class LockManager
{
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
	std::map<int, LockInfo> locks;
	//file lock : tid, fileName
	std::map<int, std::string> fileLocks;
};
