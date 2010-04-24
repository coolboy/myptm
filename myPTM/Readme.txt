Input and output:
 
 1. Round robin read from transaction and process files, one line at a time.
 2. Random read from files, omit the one in which all transactions have been 
    read. Allow user to specify the seed. The number of lines is also 
    randomly generated.(between 1 and 10)

Implementation feature:
 
  This project is implemented using C/C++ under Visual Studio 2010.
  We use a nested vector to represent the transactions and the operations
  in each transaction. Several libraries(fusion, variant,xpressive,etc.) 
  from Boost are used.  Input is parsed using regular expression.   
   
Implemented Features:
 
  2-phase locking scheme(lock table and waiting list).
   
How to run:

  Option1:
    open vs2010, specify the input parameters, then F5 
  Option2:
    open command line, cd to the project directory, then 
    type:  myPTM 10 1 5 inputfile1 inputfile2 inputfile3...
    
  Note: The first parameter is the seed, the second is whether
    read files in round robin or random, the third parameter currently
    not used.  The subsequent parameters are input transaction
    and process files.

Thanks!
Yong and Yang  
