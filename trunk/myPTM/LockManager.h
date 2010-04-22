#pragma once

#include <boost/optional.hpp>

// first: get it?
// second: the deadlock ids
typedef std::pair<bool, boost::optional<std::vector<int>>> LockCondition;

class LockManager
{
public:
	LockManager(void);
	~LockManager(void);

	//lock the item and return the trans ids in the cycle if detect a dead lock
	LockCondition Lock (int tid, int itemid, const std::string&	fileName);

	//lock the whole file  and return the trans ids in the cycle if detect a dead lock
	LockCondition Lock (const std::string&	fileName);
};

