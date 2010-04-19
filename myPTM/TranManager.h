#pragma once

#include <boost/variant.hpp>
#include <boost/fusion/include/at_c.hpp>
#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/bind.hpp>
#include <boost/algorithm/string/join.hpp>
#include <boost/foreach.hpp>

class TranManager
{
public:
	typedef enum 
	{
		READ = 0,
		WRITE = 1,
		DEL = 2,
		COMMIT = 3,
		BEGIN = 4,
		ABORD = 5,
		UNKONWN = 6
	} OpType;

	typedef std::vector<std::vector<std::string>> fileList;
	//typedef OpType O		peration1;  //
	//typedef boost::fusion::vector2<OpType, int> Operation2;
	//typedef boost::fusion::vector3<OpType, std::string, int> Operation3;

	//this is the operation:  TRAN_ID, OP_TYPE, MODE, FILE_NAME, RECORD_ID, CLIENT_NAME, PHONE	
	typedef boost::fusion::vector7<int, OpType, int, std::string, int, std::string, std::string> Operation;

	//typedef std::map<int,Operation> NumberedOp;
	//typedef boost::variant<Operation1,Operation2,Operation3,Operation4> Operation;

private:

	std::vector<Operation> Transaction;

public:
	TranManager(fileList files);
	TranManager(fileList files, int lines);
	std::vector<Operation> getTrans(void);
	~TranManager(void);
};

typedef std::vector<TranManager::Operation> Operations;