#ifndef _UNIQUEID_H_
#define _UNIQUEID_H_

#include <deque>
#include <algorithm>
#include <iostream>

class UniqueID{

public:	
	UniqueID(int initialCount = 100 , int incrementIn = 100 , bool randomize = false );
	int pop_ID();
	void setIncrement(int incrementIn );
	void printList();

private:
	int inc;
	int used;
	int remaining;
	int totalCount;	
	bool random;
	void addValues();
	std::deque<int>valueList;
	enum OPTIONS{ MINIMUM_INCREMENT = 5 };

};

#endif