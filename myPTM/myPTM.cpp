// myIQO.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <boost/assign.hpp>

#include "TranManager.h"

using namespace std;

string ReadAll(const char* fileName){
	string inFileBuf;
	ifstream ifs(fileName);

	if (!ifs){
		return inFileBuf;
	}

	ifs.unsetf(ios::skipws);//unset skip space

	copy(istream_iterator<char>(ifs), istream_iterator<char>(), back_inserter(inFileBuf));

	return inFileBuf;
}

vector<string> ReadLines(const char* fileName)
{
   FILE *fp = fopen(fileName,"r");
   vector<string> lines;
   if(!fp)
   {
	   return lines;
   }
   char *line; /* space to read a line into */      
   int instr_count = 0;
   while ( fgets(line, sizeof line, fp) != NULL ) /* read each line */      
   {         
	  lines.push_back(string(line));
   }
	return lines;	

}

vector<string> ReadLines1(const char* fileName)
{

   vector<string> lines;

   ifstream ifs(fileName);

   string line; /* space to read a line into */      
		
   while ( getline(ifs, line, '\n') ) /* read each line */      
	{         
		lines.push_back(string(line));
	}
	return lines;	

}


int main(int argc, char** argv)
{
	int i;
	unsigned int mySeed;
	int RoundRobin;
	int lines;

	std::vector<const char*> filePathes;  //the files starts at the third input parameters
	typedef vector<string> StrVec;
	std::vector<StrVec> FileLinesList;

	if (argc < 5){
		cerr<<"Not enough parameters!\n";
		return 1;
	}

	mySeed = atoi(argv[1]);
	RoundRobin = atoi(argv[2]);
	lines = atoi(argv[3]);
	argc -= 3;

	i = 4;

	while(argc-- > 1)
	{
		vector<string> lines;
		filePathes.push_back(argv[i]);  
		lines = ReadLines1(argv[i]);
		FileLinesList.push_back(lines);
		i++;
	}

	srand(mySeed);

	if(RoundRobin)
	  TranManager TransactionManager = TranManager(FileLinesList);
	else
	{
	  lines = rand() % 10 + 1; //allow to read 1 - 10 lines once
	  TranManager TransactionManager = TranManager(FileLinesList,lines);
	}

	return 0;
}
