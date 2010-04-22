#pragma once

#include <boost/optional.hpp>

// first: get it?
// second: 
// the current locker tid if single
// the deadlock ids if multi
typedef std::pair<bool, boost::optional<std::vector<int>>> LockCondition;

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
};

