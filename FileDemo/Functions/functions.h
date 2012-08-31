#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include "../Tools/UniqueID/UniqueID.h"
#include "../Tools/FileStream/FileStream.h"

#include <list>
#include <vector>
#include <iterator>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <memory>
#include <fstream>

using std::string;
#define STRING_SIZE 36


enum main_loop_options{ INVALID = - 1 , QUIT = 0 , SHOW_OPTIONS, FILESTREAM_DEMO_ONE , FILESTREAM_DEMO_TWO , FILESTREAM_DEMO_THREE  , FILESTREAM_DEMO_FOUR , FILESTREAM_DEMO_FIVE  , FILESTREAM_DEMO_SIX  , MAIN_LOOP_OPTIONS_END };
extern string main_loop_names[];
enum filestream_demo_one_options{   FD1_INVALID = -1,  FD1_QUIT = 0 , FD1_SHOW_OPTIONS, FD1_SAVEFILE , 
									FD1_LOADFILE ,  FD1_END };
enum filestream_demo_two_options{   FD2_INVALID = -1,  FD2_QUIT = 0 , FD2_SHOW_OPTIONS, FD2_SAVEFILE , 
									FD2_LOADFILE , FD2_LOADINVALIDFILE ,  FD2_END };
extern string filestream_demo_one_names[];
//enum functions_demo_one_options{   FD1_INVALID = -1,  FD1_QUIT = 0 , FD1_SHOW_OPTIONS,   FD1_PRINT ,  FD1_END };
//extern string functions_demo_one_names[];

int get_user_input();
string get_input_string();
void print_list_options(  string names[] ,  int end = 0 , string menuName = "MENU:" , int start = 0  );
string convertInt(int number);

//void function_demo_one();
void filestream_demo_one();
void filestream_demo_two();
void filestream_demo_three();
void filestream_demo_four();
void filestream_demo_five();
void filestream_demo_six();



namespace UniversalPrinterNS{
	
	template <class T>
	class Print
	{
	public:
		void operator()(T & t){ std::cout << "Printing: " << (t) << endl ; }
		void operator()(T *&t){ std::cout << "Printing Pointer: " << (*t) << endl ; }
		void operator()(std::shared_ptr<T> & t){ std::cout << "Printing Shared Pointer: " << (*t) << " Use Count: " << t.use_count() << endl ; }
	};

	template <class T>
	class PrintCount
	{	
	private:
		int count;
	public:
		PrintCount() { count = 0; }
		void operator()(T & t){ std::cout << "Printing value at: " << ++count << ": " << (t) << endl ; }
		void operator()(T *& t){ std::cout << "Printing Pointer Value at :" << ++count << ": " << (*t) << endl ; }
	};


}

namespace UniversalDeleterNS{

	template <class T>
		class Deleter
		{	
		private:
			bool print;
		public:	
			Deleter(bool printValue = false ) : print(printValue) {}
			void operator()(T *& t){  if( t != 0 ) { if(print) std::cout << "Deleting " << *t << std::endl; delete t; t = 0; } }
		};

}




#endif
