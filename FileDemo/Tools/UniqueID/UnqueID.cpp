#include "UniqueID.h"


using std::deque;
using std::cout;
using std::endl;

UniqueID::UniqueID(int initialCount , int incrementIn, bool randomize )
{
	random = randomize;

	totalCount = 0;
	used = 0;
	remaining = totalCount - used;

	if(initialCount <= 0 )
		inc = 100;
	else
		inc = initialCount;

	addValues();
	setIncrement( incrementIn );
	

}

void UniqueID::printList(){

	cout << "  UniqueID Class:" << endl;
	cout << "    @Total Count: " << totalCount << endl;
	cout << "    @Used Count:" << used << endl;
	cout << "    @Remaining Count:" << remaining << endl;
	cout << "    @Value List Size:" << valueList.size() << endl;
	cout << "    @Printing Values..." << endl;
	


	for( deque<int>::iterator i = valueList.begin() ; i != valueList.end() ; ++i )
		cout <<  "     #Value in list : " << (*i) << endl;

}

void UniqueID::addValues(){

	for(int i = totalCount; i < totalCount + inc ; ++i ){
		valueList.push_back(i);
	}

	if(random){
		std::random_shuffle(valueList.begin(), valueList.end() ); 
	}

	totalCount += inc;
	remaining += inc;

}

int UniqueID::pop_ID(){

	if(valueList.size() > 0 ){
		int front = valueList.front();
		valueList.pop_front();
		++used;
		--remaining;

		if(remaining < (inc / 2 ) )
			addValues();

		return front;
	} 

		cout << "Probable serious Error!!!" << endl;
		return -1;

}

void UniqueID::setIncrement(int incrementIn ){
	if(incrementIn < MINIMUM_INCREMENT )
		incrementIn= MINIMUM_INCREMENT;

	inc = incrementIn;
}