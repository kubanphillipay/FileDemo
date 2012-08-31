#include "functions.h"


using std::list;
using std::string;

using std::cout;
using std::cin;
using std::endl;
using std::shared_ptr;
using std::weak_ptr;
using std::ofstream;
using std::ifstream;
using FileNS::FileStream;
//using UniversalPrinterNS::Print;
//using UniversalPrinterNS::PrintCount;

using std::vector;

string main_loop_names[] = {  "QUIT" ,   "SHOW_OPTIONS", "FILESTREAM_DEMO_ONE" , "FILESTREAM_DEMO_TWO" , "FILESTREAM_DEMO_THREE" , "FILESTREAM_DEMO_FOUR" , "FILESTREAM_DEMO_FIVE"  , "FILESTREAM_DEMO_SIX"  };
string filestream_demo_one_names[] = { "QUIT" , "SHOW_OPTIONS" , "SAVE_FILE" , "LOAD_FILE" };
string filestream_demo_two_names[] = { "QUIT" , "SHOW_OPTIONS" , "SAVE_FILE" , "LOAD_FILE" , "LOAD_INVALID_FILE" };
	

int get_user_input()
{
    string input_string;
    bool debug = false;
    int size;
    char parse_string[STRING_SIZE];
    int return_value;
    getline(cin, input_string, '\n');
    size = input_string.length();

    if(debug) printf("Input String = %s\n Size = %d" , input_string.c_str() , size );

    if( size > STRING_SIZE - 1 ){
        strncpy( parse_string,  input_string.c_str() , STRING_SIZE - 1 );
        parse_string[STRING_SIZE - 1] = '\0';
    }else
        strcpy( parse_string , input_string.c_str() );

    if(debug) printf("Output String = %s\n" , &parse_string );

    int i = 0;
    while(parse_string[i] >= 48 && parse_string[i] <= 57){
        i++;
    }

    if( i == 0)
        return_value = INVALID;
    else
        return_value = atoi(parse_string);

    if( ( parse_string[0] == 'q' || parse_string[0] == 'Q' )&&
        ( parse_string[1] == 'u' || parse_string[1] == 'U' )&&
        ( parse_string[2] == 'i' || parse_string[2] == 'I' )&&
        ( parse_string[3] == 't' || parse_string[3] == 'T' ) )
            return_value = 0;

    if(debug) printf("Return value = %d\n" , return_value );
    return return_value;

}

string get_input_string(){
	string input_string;
	string return_string;
	getline(cin, input_string, '\n');
    int size = input_string.size();

    if(size > STRING_SIZE-1)
        cout << "Warning! String size should be less than " << STRING_SIZE - 1 << endl;
	
	return_string = input_string.substr(0 , STRING_SIZE - 1 );
	return return_string;

}
	 
void print_list_options(  string names[] , int end , string menuName , int start  ){	
int loop_l;
cout << endl << menuName << endl;
for( loop_l = start ; loop_l < end ; ++loop_l )
	cout << "(" << loop_l << ") " << names[loop_l] << endl; 
}

string convertInt(int number)
{
   std::stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}

// ================================ END SHELL CRITICAL =============================

/*
//void function_demo_one()
void filestream_demo_one()
{
	//UniqueID uniqueID( 10 , 5 , true );
	int input = SHOW_OPTIONS;
	//print_list_options(function_demo_one_names , FD1_END , "Function Demo One Options:" );

	do{
		cout << endl;

		switch(input){
			case FD1_QUIT:
				cout << "Quitting"<< endl;
				get_user_input() ;
				break;	
			case FD1_SHOW_OPTIONS:
				print_list_options(function_demo_one_names , FD1_END , "Function Demo One" );
				break;			
			case  FD1_PRINT:		
			{
				std::cout << "In PFD1_Print: " << std::endl;	

				std::cout << "Printing random junk" << std::endl;	
				std::cout << "More junk..." << std::endl;	
				
				UniqueID randomider(5 , 10  ,true);
				UniqueID ider(100, 100  );

				//int i;
				std:: cout << "RandomIDer" << std::endl;
				for(int i = 0 ; i < 20 ; ++i )
					std::cout << "Get random ID: " << randomider.pop_ID() << std::endl;


				std::cout << std::endl << "IncrementalIDer" << std::endl;
				for(int i = 0 ; i < 20 ; ++i )
					std::cout << "Get ID: " << ider.pop_ID() << std::endl;

			}
			break;
			case FD1_END:
				cout << "Invalid Option" << endl;
				break;		
		}

		cout << "Function Demo One" << endl << "Enter Selection: ";
		input = get_user_input();		

	}while( input != QUIT );
	cout << "Returning to MainMenu..." << endl;


}*/




//void function_demo_one()
void filestream_demo_one()
{

	int input = SHOW_OPTIONS;
	string demo_name = "File Stream Demo One";

	do{
		cout << endl;

		switch(input){
			case FD1_QUIT:
				cout << "Quitting"<< endl;
				get_user_input() ;
				break;	
			case FD1_SHOW_OPTIONS:
				cout << "This is a demo of the filestream class" << endl;
				cout << "In this demo several integers, strings, and float values are written to a filename given by the user.  Load the file to see the saved values" << endl;

				print_list_options(filestream_demo_one_names , FD1_END , demo_name );
				break;			
			case  FD1_SAVEFILE:		
			{
				
				cout << "Type the file name to save to:" << endl;
				string input = get_input_string();				
				FileStream fs(input , FileStream::WRITE_ONLY);				
				
				int intValue1 = 43;
				int intValue2 = 463;
				int intValue3 = 3;
				string stringValue1 = "This is a test string";
				string stringValue2 = "This is another test string";
				string stringValue3 = "One more string";
				float floatValue1 = float(94.32);
				float floatValue2 = float(42.1);
				float floatValue3 = float(592.43);
									
	
				try{
					cout << "Writing " << intValue1 << " to file " << input << endl;
					fs << intValue1;
					cout << "Writing " << intValue2 << " to file " << input << endl;
					fs << intValue2;
					cout << "Writing " << intValue3 << " to file " << input << endl;
					fs << intValue3;

					cout << "Writing " << stringValue1 << " to file " << input << endl;
					fs << stringValue1;
					cout << "Writing " << stringValue2 << " to file " << input << endl;
					fs << stringValue2;
					cout << "Writing " << stringValue3 << " to file " << input << endl;
					fs << stringValue3;

					cout << "Writing " << floatValue1 << " to file " << input << endl;
					fs << floatValue1;
					cout << "Writing " << floatValue2 << " to file " << input << endl;
					fs << floatValue2;
					cout << "Writing " << floatValue3 << " to file " << input << endl;
					fs << floatValue3;

				} 
				catch(FileStream::badfile & bf )
				{
					cout << bf.what() << endl;
				}
				

			}
			break;
			case  FD1_LOADFILE:		
			{
				
				cout << "Type the file name to load from:" << endl;
				string input = get_input_string();				
				FileStream fs(input , FileStream::READ_ONLY);				
				
				int intValue1;
				int intValue2;
				int intValue3;
				string stringValue1;
				string stringValue2;
				string stringValue3;
				float floatValue1;
				float floatValue2;
				float floatValue3;
									
	
				try{
					fs >> intValue1;
					cout << "Reading " << intValue1 << " from file " << input << endl;
					fs >> intValue2;
					cout << "Reading " << intValue2 << " from file " << input << endl;
					fs >> intValue3;
					cout << "Reading " << intValue3 << " from file " << input << endl;
					
					fs >> stringValue1;
					cout << "Reading " << stringValue1 << " from file " << input << endl;
					fs >> stringValue2;
					cout << "Reading " << stringValue2 << " from file " << input << endl;
					fs >> stringValue3;
					cout << "Reading " << stringValue3 << " from file " << input << endl;
					
					fs >> floatValue1;
					cout << "Reading " << floatValue1 << " from file " << input << endl;
					fs >> floatValue2;
					cout << "Reading " << floatValue2 << " from file " << input << endl;
					fs >> floatValue3;
					cout << "Reading " << floatValue3 << " from file " << input << endl;
					

				} 
				catch(FileStream::badfile & bf )
				{
					cout << bf.what() << endl;
				}
				catch(FileStream::baddata & bd )
				{
					cout << bd.what() << endl;						
				}

			}
			break;
			case FD1_END:
				cout << "Invalid Option" << endl;
				break;		
		}

		cout << demo_name << endl << "Enter Selection: ";
		input = get_user_input();		

	}while( input != QUIT );
	cout << "Returning to MainMenu..." << endl;


}


void filestream_demo_two()
{

	int input = SHOW_OPTIONS;
	string demo_name = "File Stream Demo Two";

	do{
		cout << endl;

		switch(input){
			case FD1_QUIT:
				cout << "Quitting"<< endl;
				get_user_input() ;
				break;	
			case FD1_SHOW_OPTIONS:
				cout << "This is a demo of the filestream class" << endl;
				cout << "In this demo a vector of integers, strings, and doubles is written to a file" << endl;

				print_list_options(filestream_demo_one_names , FD1_END , demo_name );
				break;			
			case  FD1_SAVEFILE:		
			{
				using UniversalPrinterNS::PrintCount;

				PrintCount<int> printIntVector;
				PrintCount<string> printStringVector;
				PrintCount<double> printDoubleVector;


				cout << "Type the file name to save to:" << endl;
				string input = get_input_string();				
				FileStream fs(input , FileStream::WRITE_ONLY);					

				vector<int> myVectorInt;
				myVectorInt.push_back(429);
				myVectorInt.push_back(90);
				myVectorInt.push_back(43);
				myVectorInt.push_back(634);
				myVectorInt.push_back(53);

				vector<string> myVectorString;
				myVectorString.push_back("Demo String");
				myVectorString.push_back("Another Demo String");
				myVectorString.push_back("Writing More Strings");
				myVectorString.push_back("");
				myVectorString.push_back("String #5");

				vector<double> myVectorDouble;
				myVectorDouble.push_back(429.576);
				myVectorDouble.push_back(95.3);
				myVectorDouble.push_back(0.932);
				myVectorDouble.push_back(593.53);
				myVectorDouble.push_back(043.432);
	
				try{
					cout << "Writing MyIntVector to file " << input << endl;
					for_each(myVectorInt.begin() , myVectorInt.end() , printIntVector );
					fs << myVectorInt;

					cout << "Writing MyStringVector to file " << input << endl;
					for_each(myVectorString.begin() , myVectorString.end() , printStringVector );
					fs << myVectorString;

					cout << "Writing MyDoubleVector to file " << input << endl;
					for_each(myVectorDouble.begin() , myVectorDouble.end() , printDoubleVector );
					fs << myVectorDouble;


				} 
				catch(FileStream::badfile & bf )
				{
					cout << bf.what() << endl;
				}
				

			}
			break;
			case  FD1_LOADFILE:		
			{
				
				cout << "Type the file name to load from:" << endl;
				string input = get_input_string();				
				FileStream fs(input , FileStream::READ_ONLY);					

				using UniversalPrinterNS::PrintCount;
				PrintCount<int> printIntVector;
				PrintCount<string> printStringVector;
				PrintCount<double> printDoubleVector;			

				vector<int> myVectorInt;
				vector<string> myVectorString;
				vector<double> myVectorDouble;											
	
				try{
					cout << "Reading MyIntVector from file " << input << endl;
					fs >> myVectorInt;
					for_each(myVectorInt.begin() , myVectorInt.end() , printIntVector );
					

					cout << "Reading MyStringVector from file " << input << endl;
					fs >> myVectorString;
					for_each(myVectorString.begin() , myVectorString.end() , printStringVector );
					

					cout << "Reading MyDoubleVector from file " << input << endl;
					fs >> myVectorDouble;
					for_each(myVectorDouble.begin() , myVectorDouble.end() , printDoubleVector );
					

				} 
				catch(FileStream::badfile & bf )
				{
					cout << bf.what() << endl;
				}
				catch(FileStream::baddata & bd )
				{
					cout << bd.what() << endl;						
				}

			}
			break;
			case FD1_END:
				cout << "Invalid Option" << endl;
				break;		
		}

		cout << demo_name << endl << "Enter Selection: ";
		input = get_user_input();		

	}while( input != QUIT );
	cout << "Returning to MainMenu..." << endl;


}



void filestream_demo_three(){
	
	int input = SHOW_OPTIONS;
	string demo_name = "File Stream Demo Three";

	do{
		cout << endl;

		switch(input){
			case FD2_QUIT:
				cout << "Quitting"<< endl;
				get_user_input() ;
				break;	
			case FD2_SHOW_OPTIONS:
				cout << "This is a demo of the filestream class" << endl;
				cout << "Write and load pointers to variables to a file.  Can check"
					" exception handling with invalid option" << endl;

				print_list_options(filestream_demo_two_names , FD2_END , demo_name );
				break;			
			case  FD2_SAVEFILE:		
			{
				cout << "Type the file name to save to:" << endl;
				string input = get_input_string();				
				FileStream fs(input , FileStream::WRITE_ONLY);					
	
				int* intValue1 = new int(532);
				int* intValue2 = new int(239);
				int* intValue3 = new int(4);
				string* stringValue1 = new string("Demo String One");
				string* stringValue2 = new string("Another Demo String");
				string* stringValue3 = new string("Yet Another String");
				double* doubleValue1 = new double(492.3);
				double* doubleValue2 = new double(3092.4);
				double* doubleValue3 = new double(953.32);
									
	
				try{
					cout << "Writing " << *intValue1 << " to file " << input << endl;
					fs << intValue1;
					cout << "Writing " << *intValue2 << " to file " << input << endl;
					fs << intValue2;
					cout << "Writing " << *intValue3 << " to file " << input << endl;
					fs << intValue3;

					cout << "Writing " << *stringValue1 << " to file " << input << endl;
					fs << stringValue1;
					cout << "Writing " << *stringValue2 << " to file " << input << endl;
					fs << stringValue2;
					cout << "Writing " << *stringValue3 << " to file " << input << endl;
					fs << stringValue3;

					cout << "Writing " << *doubleValue1 << " to file " << input << endl;
					fs << doubleValue1;
					cout << "Writing " << *doubleValue2 << " to file " << input << endl;
					fs << doubleValue2;
					cout << "Writing " << *doubleValue3 << " to file " << input << endl;
					fs << doubleValue3;
					

				} 
				catch(FileStream::badfile & bf )
				{
					cout << bf.what() << endl;
				}
				catch(FileStream::baddata & bd )
				{
					cout << bd.what() << endl;						
				}
				
				delete intValue1;
				delete intValue2;
				delete intValue3;
				delete stringValue1;
				delete stringValue2;
				delete stringValue3;
				delete doubleValue1;
				delete doubleValue2;
				delete doubleValue3;


			}
			break;
			case  FD2_LOADFILE:		
			{
				
				cout << "Type the file name to load from:" << endl;
				string input = get_input_string();				
				FileStream fs(input , FileStream::READ_ONLY);					

				int* intValue1 = 0;
				int* intValue2 = 0;
				int* intValue3 = 0;
				string* stringValue1 = 0;
				string* stringValue2 = 0;
				string* stringValue3 = 0;
				double* doubleValue1 = 0;
				double* doubleValue2 = 0;
				double* doubleValue3 = 0;
									
		
				try{
				
					fs >> intValue1;
					cout << "Reading " << *intValue1 << " from file " << input << endl;
					fs >> intValue2;
					cout << "Reading " << *intValue2 << " from file " << input << endl;
					fs >> intValue3;
					cout << "Reading " << *intValue3 << " from file " << input << endl;
					
					fs >> stringValue1;
					cout << "Reading " << *stringValue1 << " from file " << input << endl;
					
					//change these two lines to check error checking functionallity
					fs >> stringValue2;
					//fs >> intValue2;
					cout << "Reading " << *stringValue2 << " from file " << input << endl;
					fs >> stringValue3;
					cout << "Reading " << *stringValue3 << " from file " << input << endl;
					
					fs >> doubleValue1;
					cout << "Reading " << *doubleValue1 << " from file " << input << endl;
					fs >> doubleValue2;
					cout << "Reading " << *doubleValue2 << " from file " << input << endl;
					fs >> doubleValue3;
					cout << "Reading " << *doubleValue3 << " from file " << input << endl;
					


				} 
				catch(FileStream::badfile & bf )
				{
					std::cout << "in funciton demo" << endl;
					cout << bf.what() << endl;
				}
				catch(FileStream::baddata & bd )
				{
					std::cout << "in funciton demo" << endl;
					cout << bd.what() << endl;						
				}
				if(intValue1){
					delete intValue1;
					cout << "Deleting IntValue1" << endl;
				}
				if(intValue2){
					delete intValue2;
					cout << "Deleting IntValue2" << endl;
				}
				if(intValue3){
					delete intValue3;
					cout << "Deleting IntValue3" << endl;
				}
				if(stringValue1){
					delete stringValue1;
					cout << "Deleting stringValue1" << endl;
				}
				if(stringValue2){
					delete stringValue2;
					cout << "Deleting stringValue2" << endl;
				}
				if(stringValue3){
					delete stringValue3;
					cout << "Deleting stringValue3" << endl;
				}
				if(doubleValue1){
					delete doubleValue1;
					cout << "Deleting doubleValue1" << endl;
				}
				if(doubleValue2){
					delete doubleValue2;
					cout << "Deleting doubleValue2" << endl;
				}
				if(doubleValue3){
					delete doubleValue3;
					cout << "Deleting doubleValue3" << endl;
				}
			}
			break;
			case  FD2_LOADINVALIDFILE:		
			{
				
				cout << "Type the file name to load from:" << endl;
				string input = get_input_string();				
				FileStream fs(input , FileStream::READ_ONLY);					

				int* intValue1 = 0;
				int* intValue2 = 0;
				int* intValue3 = 0;
				string* stringValue1 = 0;
				string* stringValue2 = 0;
				string* stringValue3 = 0;
				double* doubleValue1 = 0;
				double* doubleValue2 = 0;
				double* doubleValue3 = 0;
									
		
				try{
				
					fs >> intValue1;
					cout << "Reading " << *intValue1 << " from file " << input << endl;
					fs >> intValue2;
					cout << "Reading " << *intValue2 << " from file " << input << endl;
					fs >> intValue3;
					cout << "Reading " << *intValue3 << " from file " << input << endl;
					
					fs >> stringValue1;
					cout << "Reading " << *stringValue1 << " from file " << input << endl;
					
					//change these two lines to check error checking functionallity
					//fs >> stringValue2;
					fs >> intValue2;
					cout << "Reading " << *stringValue2 << " from file " << input << endl;
					fs >> stringValue3;
					cout << "Reading " << *stringValue3 << " from file " << input << endl;
					
					fs >> doubleValue1;
					cout << "Reading " << *doubleValue1 << " from file " << input << endl;
					fs >> doubleValue2;
					cout << "Reading " << *doubleValue2 << " from file " << input << endl;
					fs >> doubleValue3;
					cout << "Reading " << *doubleValue3 << " from file " << input << endl;
					


				} 
				catch(FileStream::badfile & bf )
				{
					std::cout << "in funciton demo" << endl;
					cout << bf.what() << endl;
				}
				catch(FileStream::baddata & bd )
				{
					std::cout << "in funciton demo" << endl;
					cout << bd.what() << endl;						
				}
				if(intValue1){
					delete intValue1;
					cout << "Deleting IntValue1" << endl;
				}
				if(intValue2){
					delete intValue2;
					cout << "Deleting IntValue2" << endl;
				}
				if(intValue3){
					delete intValue3;
					cout << "Deleting IntValue3" << endl;
				}
				if(stringValue1){
					delete stringValue1;
					cout << "Deleting stringValue1" << endl;
				}
				if(stringValue2){
					delete stringValue2;
					cout << "Deleting stringValue2" << endl;
				}
				if(stringValue3){
					delete stringValue3;
					cout << "Deleting stringValue3" << endl;
				}
				if(doubleValue1){
					delete doubleValue1;
					cout << "Deleting doubleValue1" << endl;
				}
				if(doubleValue2){
					delete doubleValue2;
					cout << "Deleting doubleValue2" << endl;
				}
				if(doubleValue3){
					delete doubleValue3;
					cout << "Deleting doubleValue3" << endl;
				}
			}
			break;

			case FD2_END:
				cout << "Invalid Option" << endl;
				break;		
		}

		cout << demo_name << endl << "Enter Selection: ";
		input = get_user_input();		

	}while( input != QUIT );
	cout << "Returning to MainMenu..." << endl;


}


void filestream_demo_four(){
	
	int input = SHOW_OPTIONS;
	string demo_name = "File Stream Demo Four";

	do{
		cout << endl;

		switch(input){
			case FD2_QUIT:
				cout << "Quitting"<< endl;
				get_user_input() ;
				break;	
			case FD2_SHOW_OPTIONS:
				cout << "This is a demo of the filestream class" << endl;
				cout << "Write and load a vector of pointers to a file. Can check exception handling with"
					" invalid option" << endl;

				print_list_options(filestream_demo_two_names , FD2_END , demo_name );
				break;			
			case  FD2_SAVEFILE:		
			{
				

				cout << "Type the file name to save to:" << endl;
				string input = get_input_string();				
				FileStream fs(input , FileStream::WRITE_ONLY);					
	

				vector<int *> myVectorIntPtr;
				myVectorIntPtr.push_back(new int(893));
				myVectorIntPtr.push_back(new int(643));
				myVectorIntPtr.push_back(new int(63));
				myVectorIntPtr.push_back(new int(123));
				myVectorIntPtr.push_back(new int(433));
				
				vector<string *> myVectorStringPtr;
				myVectorStringPtr.push_back(new string("Demo One"));
				myVectorStringPtr.push_back(new string("Demo Two"));
				myVectorStringPtr.push_back(new string("Demo Three"));
				myVectorStringPtr.push_back(new string("Demo Four"));
				myVectorStringPtr.push_back(new string("Demo Five"));

				vector<double *> myVectorDoublePtr;
				myVectorDoublePtr.push_back(new double(93.53));
				myVectorDoublePtr.push_back(new double(9535.0));
				myVectorDoublePtr.push_back(new double(24.0));
				myVectorDoublePtr.push_back(new double(0.042));
				myVectorDoublePtr.push_back(new double(84.494));

				try{
					cout << "Writing MyIntVectorPtr to file " << input << endl;
					fs << myVectorIntPtr;
					for_each(myVectorIntPtr.begin() , myVectorIntPtr.end() , UniversalPrinterNS::Print<int>() );

					cout << "Writing MyStringVectorPtr to file " << input << endl;
					fs << myVectorStringPtr;
					for_each(myVectorStringPtr.begin() , myVectorStringPtr.end() , UniversalPrinterNS::Print<string>() );

					cout << "Writing MyDoubleVectorPtr to file " << input << endl;
					fs << myVectorDoublePtr;
					for_each(myVectorDoublePtr.begin() , myVectorDoublePtr.end() , UniversalPrinterNS::Print<double>() );


				} 
				catch(FileStream::badfile & bf )
				{
					cout << bf.what() << endl;
				}
				
				UniversalDeleterNS::Deleter<int> deleteInt(true);
				while( !myVectorIntPtr.empty() ){
					deleteInt(myVectorIntPtr.back() );
					myVectorIntPtr.pop_back();
				}

				UniversalDeleterNS::Deleter<string> deleteString(true);
				while( !myVectorStringPtr.empty() ){
					deleteString(myVectorStringPtr.back() );
					myVectorStringPtr.pop_back();
				}

				/*
				UniversalDeleterNS::Deleter<double> deleteDouble(true);
				while( !myVectorDoublePtr.empty() ){
					deleteDouble(myVectorDoublePtr.back() );
					myVectorDoublePtr.pop_back();
				}*/
				for_each( myVectorDoublePtr.begin() , myVectorDoublePtr.end() , UniversalDeleterNS::Deleter<double>(true) );
				myVectorDoublePtr.clear();


			}
			break;
			case  FD2_LOADFILE:		
			{
				
				cout << "Type the file name to load from:" << endl;
				string input = get_input_string();				
				FileStream fs(input , FileStream::READ_ONLY);					

				vector<int *> myVectorIntPtr;
				vector<string *> myVectorStringPtr;
				vector<double *> myVectorDoublePtr;

		
				try{
					cout << "Reading MyIntVectorPtr from file " << input << endl;
					fs >> myVectorIntPtr;
					for_each(myVectorIntPtr.begin() , myVectorIntPtr.end() , UniversalPrinterNS::Print<int>() );

					cout << "Reading MyStringVectorPtr from file " << input << endl;
					fs >> myVectorStringPtr;
					for_each(myVectorStringPtr.begin() , myVectorStringPtr.end() , UniversalPrinterNS::Print<string>() );

					cout << "Reading MyDoubleVectorPtr from file " << input << endl;
					fs >> myVectorDoublePtr;
					for_each(myVectorDoublePtr.begin() , myVectorDoublePtr.end() , UniversalPrinterNS::Print<double>() );

				} 
				catch(FileStream::badfile & bf )
				{
					cout << bf.what() << endl;
				}
				catch(FileStream::baddata & bd )
				{
					cout << bd.what() << endl;						
				}

				for_each( myVectorIntPtr.begin() , myVectorIntPtr.end() , UniversalDeleterNS::Deleter<int>(true) );
				myVectorIntPtr.clear();
				for_each( myVectorStringPtr.begin() , myVectorStringPtr.end() , UniversalDeleterNS::Deleter<string>(true) );
				myVectorStringPtr.clear();
				for_each( myVectorDoublePtr.begin() , myVectorDoublePtr.end() , UniversalDeleterNS::Deleter<double>(true) );
				myVectorDoublePtr.clear();

			}
			break;
			case  FD2_LOADINVALIDFILE:		
			{
					cout << "Type the file name to load from:" << endl;
				string input = get_input_string();				
				FileStream fs(input , FileStream::READ_ONLY);					

				vector<int *> myVectorIntPtr;
				vector<string *> myVectorStringPtr;
				vector<double *> myVectorDoublePtr;

		
				try{
					cout << "Reading MyIntVectorPtr from file " << input << endl;
					fs >> myVectorIntPtr;
					for_each(myVectorIntPtr.begin() , myVectorIntPtr.end() , UniversalPrinterNS::Print<int>() );

					cout << "Reading MyStringVectorPtr from file " << input << endl;
					fs >> myVectorStringPtr;
					for_each(myVectorStringPtr.begin() , myVectorStringPtr.end() , UniversalPrinterNS::Print<string>() );

					cout << "Reading MyIntVectorPtr (Should be invalid) from file " << input << endl;
					fs >> myVectorIntPtr;
					for_each(myVectorIntPtr.begin() , myVectorIntPtr.end() , UniversalPrinterNS::Print<int>() );

				} 
				catch(FileStream::badfile & bf )
				{
					cout << bf.what() << endl;
				}
				catch(FileStream::baddata & bd )
				{
					cout << bd.what() << endl;						
				}

				for_each( myVectorIntPtr.begin() , myVectorIntPtr.end() , UniversalDeleterNS::Deleter<int>(true) );
				myVectorIntPtr.clear();
				for_each( myVectorStringPtr.begin() , myVectorStringPtr.end() , UniversalDeleterNS::Deleter<string>(true) );
				myVectorStringPtr.clear();
				for_each( myVectorDoublePtr.begin() , myVectorDoublePtr.end() , UniversalDeleterNS::Deleter<double>(true) );
				myVectorDoublePtr.clear();



			}
			break;
			case FD2_END:
				cout << "Invalid Option" << endl;
				break;		
		}

		cout << demo_name << endl << "Enter Selection: ";
		input = get_user_input();		

	}while( input != QUIT );
	cout << "Returning to MainMenu..." << endl;


}






void filestream_demo_five(){
	
	int input = SHOW_OPTIONS;
	string demo_name = "File Stream Demo Five";

	do{
		cout << endl;

		switch(input){
			case FD2_QUIT:
				cout << "Quitting"<< endl;
				get_user_input() ;
				break;	
			case FD2_SHOW_OPTIONS:
				cout << "This is a demo of the filestream class" << endl;
				cout << "Write and load shared pointers to a file.  Test exception handldign" 
					"with invalid option" << endl;

				print_list_options(filestream_demo_two_names , FD2_END , demo_name );
				break;			
			case  FD2_SAVEFILE:		
			{
				

				cout << "Type the file name to save to:" << endl;
				string input = get_input_string();				
				FileStream fs(input , FileStream::WRITE_ONLY);					
	
				shared_ptr<int> myIntSharedPtr1(new int(5943));
				shared_ptr<int> myIntSharedPtr2(new int(346));
				shared_ptr<int> myIntSharedPtr3(new int(753));
				shared_ptr<int> myIntSharedPtr4(new int(3));
				shared_ptr<int> myIntSharedPtr5(new int(653));
		
				shared_ptr<string> myStringSharedPtr1(new string("Demo String One"));
				shared_ptr<string> myStringSharedPtr2(new string("Demo String Two"));
				shared_ptr<string> myStringSharedPtr3(new string("Demo String Three"));
				shared_ptr<string> myStringSharedPtr4(new string("Demo String Four"));
				shared_ptr<string> myStringSharedPtr5(new string("Demo String Five"));

				shared_ptr<double> myDoubleSharedPtr1(new double(53.943));
				shared_ptr<double> myDoubleSharedPtr2(new double(8356.5));
				shared_ptr<double> myDoubleSharedPtr3(new double(42.4));
				shared_ptr<double> myDoubleSharedPtr4(new double(752.24));
				shared_ptr<double> myDoubleSharedPtr5(new double(86.35));


				try{
					fs <<  myIntSharedPtr1;
					cout << "Writing " << * myIntSharedPtr1 << " to file " << input << endl;
					fs <<  myIntSharedPtr2;
					cout << "Writing " << * myIntSharedPtr2 << " to file " << input << endl;
					fs <<  myIntSharedPtr3;
					cout << "Writing " << * myIntSharedPtr3 << " to file " << input << endl;
					fs <<  myIntSharedPtr4;
					cout << "Writing " << * myIntSharedPtr4 << " to file " << input << endl;
					fs <<  myIntSharedPtr5;
					cout << "Writing " << * myIntSharedPtr5 << " to file " << input << endl;


					fs <<  myStringSharedPtr1;
					cout << "Writing " << * myStringSharedPtr1 << " to file " << input << endl;
					fs <<  myStringSharedPtr2;
					cout << "Writing " << * myStringSharedPtr2 << " to file " << input << endl;
					fs <<  myStringSharedPtr3;
					cout << "Writing " << * myStringSharedPtr3 << " to file " << input << endl;
					fs <<  myStringSharedPtr4;
					cout << "Writing " << * myStringSharedPtr4 << " to file " << input << endl;
					fs <<  myStringSharedPtr5;
					cout << "Writing " << * myStringSharedPtr5 << " to file " << input << endl;

					fs <<  myDoubleSharedPtr1;
					cout << "Writing " << * myDoubleSharedPtr1 << " to file " << input << endl;
					fs <<  myDoubleSharedPtr2;
					cout << "Writing " << * myDoubleSharedPtr2 << " to file " << input << endl;
					fs <<  myDoubleSharedPtr3;
					cout << "Writing " << * myDoubleSharedPtr3 << " to file " << input << endl;
					fs <<  myDoubleSharedPtr4;
					cout << "Writing " << * myDoubleSharedPtr4 << " to file " << input << endl;
					fs <<  myDoubleSharedPtr5;
					cout << "Writing " << * myDoubleSharedPtr5 << " to file " << input << endl;


				} 
				catch(FileStream::badfile & bf )
				{
					cout << bf.what() << endl;
				}
				

			}
			break;
			case  FD2_LOADFILE:		
			{
				
				cout << "Type the file name to load from:" << endl;
				string input = get_input_string();				
				FileStream fs(input , FileStream::READ_ONLY);					

				shared_ptr<int> myIntSharedPtr1;
				shared_ptr<int> myIntSharedPtr2;
				shared_ptr<int> myIntSharedPtr3;
				shared_ptr<int> myIntSharedPtr4;
				shared_ptr<int> myIntSharedPtr5;
		
				shared_ptr<string> myStringSharedPtr1;
				shared_ptr<string> myStringSharedPtr2;
				shared_ptr<string> myStringSharedPtr3;
				shared_ptr<string> myStringSharedPtr4;
				shared_ptr<string> myStringSharedPtr5;

				shared_ptr<double> myDoubleSharedPtr1;
				shared_ptr<double> myDoubleSharedPtr2;
				shared_ptr<double> myDoubleSharedPtr3;
				shared_ptr<double> myDoubleSharedPtr4;
				shared_ptr<double> myDoubleSharedPtr5;

				try{
					fs >>  myIntSharedPtr1;
					cout << "Reading " << * myIntSharedPtr1 << " from file " << input << endl;
					fs >>  myIntSharedPtr2;
					cout << "Reading " << * myIntSharedPtr2 << " from file " << input << endl;
					fs >>  myIntSharedPtr3;
					cout << "Reading " << * myIntSharedPtr3 << " from file " << input << endl;
					fs >>  myIntSharedPtr4;
					cout << "Reading " << * myIntSharedPtr4 << " from file " << input << endl;
					fs >>  myIntSharedPtr5;
					cout << "Reading " << * myIntSharedPtr5 << " from file " << input << endl;

					fs >>  myStringSharedPtr1;
					cout << "Reading " << * myStringSharedPtr1 << " from file " << input << endl;
					fs >>  myStringSharedPtr2;
					cout << "Reading " << * myStringSharedPtr2 << " from file " << input << endl;
					fs >>  myStringSharedPtr3;
					cout << "Reading " << * myStringSharedPtr3 << " from file " << input << endl;
					fs >>  myStringSharedPtr4;
					cout << "Reading " << * myStringSharedPtr4 << " from file " << input << endl;
					fs >>  myStringSharedPtr5;
					cout << "Reading " << * myStringSharedPtr5 << " from file " << input << endl;

					fs >>  myDoubleSharedPtr1;
					cout << "Reading " << * myDoubleSharedPtr1 << " from file " << input << endl;
					fs >>  myDoubleSharedPtr2;
					cout << "Reading " << * myDoubleSharedPtr2 << " from file " << input << endl;
					fs >>  myDoubleSharedPtr3;
					cout << "Reading " << * myDoubleSharedPtr3 << " from file " << input << endl;
					fs >>  myDoubleSharedPtr4;
					cout << "Reading " << * myDoubleSharedPtr4 << " from file " << input << endl;
					fs >>  myDoubleSharedPtr5;
					cout << "Reading " << * myDoubleSharedPtr5 << " from file " << input << endl;

				} 
				catch(FileStream::badfile & bf )
				{
					cout << bf.what() << endl;
				}
				catch(FileStream::baddata & bd )
				{
					cout << bd.what() << endl;						
				}

			

			}
			break;
			case  FD2_LOADINVALIDFILE:		
			{
				cout << "Type the file name to load from:" << endl;
				string input = get_input_string();				
				FileStream fs(input , FileStream::READ_ONLY);							

				shared_ptr<int> myIntSharedPtr1;
				shared_ptr<int> myIntSharedPtr2;
				shared_ptr<int> myIntSharedPtr3;
				shared_ptr<int> myIntSharedPtr4;
				shared_ptr<int> myIntSharedPtr5;
		
				shared_ptr<string> myStringSharedPtr1;
				shared_ptr<string> myStringSharedPtr2;
				shared_ptr<string> myStringSharedPtr3;
				shared_ptr<string> myStringSharedPtr4;
				shared_ptr<string> myStringSharedPtr5;

				shared_ptr<double> myDoubleSharedPtr1;
				shared_ptr<double> myDoubleSharedPtr2;
				shared_ptr<double> myDoubleSharedPtr3;
				shared_ptr<double> myDoubleSharedPtr4;
				shared_ptr<double> myDoubleSharedPtr5;

		
				try{
					fs >>  myIntSharedPtr1;
					cout << "Reading " << * myIntSharedPtr1 << " from file " << input << endl;
					fs >>  myIntSharedPtr2;
					cout << "Reading " << * myIntSharedPtr2 << " from file " << input << endl;
					fs >>  myIntSharedPtr3;
					cout << "Reading " << * myIntSharedPtr3 << " from file " << input << endl;
					fs >>  myIntSharedPtr4;
					cout << "Reading " << * myIntSharedPtr4 << " from file " << input << endl;
					fs >>  myIntSharedPtr5;
					cout << "Reading " << * myIntSharedPtr5 << " from file " << input << endl;

					fs >>  myStringSharedPtr1;
					cout << "Reading " << * myStringSharedPtr1 << " from file " << input << endl;
					fs >>  myStringSharedPtr2;
					cout << "Reading " << * myStringSharedPtr2 << " from file " << input << endl;
					fs >>  myStringSharedPtr3;
					cout << "Reading " << * myStringSharedPtr3 << " from file " << input << endl;
					fs >>  myStringSharedPtr4;
					cout << "Reading " << * myStringSharedPtr4 << " from file " << input << endl;
					fs >>  myStringSharedPtr5;
					cout << "Reading " << * myStringSharedPtr5 << " from file " << input << endl;

					fs >>  myDoubleSharedPtr1;
					cout << "Reading " << * myDoubleSharedPtr1 << " from file " << input << endl;
					cout << "Should error out here" << endl;
					fs >>  myIntSharedPtr2;
					cout << "Reading " << * myIntSharedPtr2 << " from file " << input << endl;
					fs >>  myDoubleSharedPtr3;
					cout << "Reading " << * myDoubleSharedPtr3 << " from file " << input << endl;
					fs >>  myDoubleSharedPtr4;
					cout << "Reading " << * myDoubleSharedPtr4 << " from file " << input << endl;
					fs >>  myDoubleSharedPtr5;
					cout << "Reading " << * myDoubleSharedPtr5 << " from file " << input << endl;

				} 
				catch(FileStream::badfile & bf )
				{
					cout << bf.what() << endl;
				}
				catch(FileStream::baddata & bd )
				{
					cout << bd.what() << endl;						
				}
		


			}
			break;
			case FD2_END:
				cout << "Invalid Option" << endl;
				break;		
		}

		cout << demo_name << endl << "Enter Selection: ";
		input = get_user_input();		

	}while( input != QUIT );
	cout << "Returning to MainMenu..." << endl;


}



void filestream_demo_six(){
	
	int input = SHOW_OPTIONS;
	string demo_name = "File Stream Demo Six";

	do{
		cout << endl;

		switch(input){
			case FD2_QUIT:
				cout << "Quitting"<< endl;
				get_user_input() ;
				break;	
			case FD2_SHOW_OPTIONS:
				cout << "This is a demo of the filestream class" << endl;
				cout << "Write and load a vector of shared pointers to a file. Can check exception handling with"
					" invalid option" << endl;

				print_list_options(filestream_demo_two_names , FD2_END , demo_name );
				break;			
			case  FD2_SAVEFILE:		
			{
				

				cout << "Type the file name to save to:" << endl;
				string input = get_input_string();				
				FileStream fs(input , FileStream::WRITE_ONLY);					
	

				vector<shared_ptr<int>> myVectorIntPtr;
				myVectorIntPtr.push_back(shared_ptr<int>(new int(435)));
				myVectorIntPtr.push_back(shared_ptr<int>(new int(643)));
				myVectorIntPtr.push_back(shared_ptr<int>(new int(63)));
				myVectorIntPtr.push_back(shared_ptr<int>(new int(123)));
				myVectorIntPtr.push_back(shared_ptr<int>(new int(433)));
				
				vector<shared_ptr<string>> myVectorStringPtr;
				myVectorStringPtr.push_back(shared_ptr<string>(new string("Demo One")));
				myVectorStringPtr.push_back(shared_ptr<string>(new string("Demo Two")));
				myVectorStringPtr.push_back(shared_ptr<string>(new string("Demo Three")));
				myVectorStringPtr.push_back(shared_ptr<string>(new string("Demo Four")));
				myVectorStringPtr.push_back(shared_ptr<string>(new string("Demo Five")));

				vector<shared_ptr<double>> myVectorDoublePtr;
				myVectorDoublePtr.push_back(shared_ptr<double>(new double(93.53)));
				myVectorDoublePtr.push_back(shared_ptr<double>(new double(9535.0)));
				myVectorDoublePtr.push_back(shared_ptr<double>(new double(24.0)));
				myVectorDoublePtr.push_back(shared_ptr<double>(new double(0.042)));
				myVectorDoublePtr.push_back(shared_ptr<double>(new double(84.494)));

				try{
					cout << "Writing MyIntVectorPtr to file " << input << endl;
					fs << myVectorIntPtr;
					for_each(myVectorIntPtr.begin() , myVectorIntPtr.end() , UniversalPrinterNS::Print<int>() );

					cout << "Writing MyStringVectorPtr to file " << input << endl;
					fs << myVectorStringPtr;
					for_each(myVectorStringPtr.begin() , myVectorStringPtr.end() , UniversalPrinterNS::Print<string>() );

					cout << "Writing MyDoubleVectorPtr to file " << input << endl;
					fs << myVectorDoublePtr;
					for_each(myVectorDoublePtr.begin() , myVectorDoublePtr.end() , UniversalPrinterNS::Print<double>() );


				} 
				catch(FileStream::badfile & bf )
				{
					cout << bf.what() << endl;
				}			


			}
			break;
			case  FD2_LOADFILE:		
			{
				
				cout << "Type the file name to load from:" << endl;
				string input = get_input_string();				
				FileStream fs(input , FileStream::READ_ONLY);					

				vector<shared_ptr<int>> myVectorIntPtr;
				vector<shared_ptr<string>> myVectorStringPtr;
				vector<shared_ptr<double>> myVectorDoublePtr;

		
				try{
					cout << "Reading MyIntVectorPtr from file " << input << endl;
					fs >> myVectorIntPtr;
					for_each(myVectorIntPtr.begin() , myVectorIntPtr.end() , UniversalPrinterNS::Print<int>() );

					cout << "Reading MyStringVectorPtr from file " << input << endl;
					fs >> myVectorStringPtr;
					for_each(myVectorStringPtr.begin() , myVectorStringPtr.end() , UniversalPrinterNS::Print<string>() );

					cout << "Reading MyDoubleVectorPtr from file " << input << endl;
					fs >> myVectorDoublePtr;
					for_each(myVectorDoublePtr.begin() , myVectorDoublePtr.end() , UniversalPrinterNS::Print<double>() );

				} 
				catch(FileStream::badfile & bf )
				{
					cout << bf.what() << endl;
				}
				catch(FileStream::baddata & bd )
				{
					cout << bd.what() << endl;						
				}

			

			}
			break;
			case  FD2_LOADINVALIDFILE:		
			{
					cout << "Type the file name to load from:" << endl;
				string input = get_input_string();				
				FileStream fs(input , FileStream::READ_ONLY);					

				vector<shared_ptr<int>> myVectorIntPtr;
				vector<shared_ptr<string>> myVectorStringPtr;
				vector<shared_ptr<double>> myVectorDoublePtr;

		
				try{
					cout << "Reading MyIntVectorPtr from file " << input << endl;
					fs >> myVectorIntPtr;
					for_each(myVectorIntPtr.begin() , myVectorIntPtr.end() , UniversalPrinterNS::Print<int>() );

					cout << "Reading MyStringVectorPtr from file " << input << endl;
					fs >> myVectorStringPtr;
					for_each(myVectorStringPtr.begin() , myVectorStringPtr.end() , UniversalPrinterNS::Print<string>() );

					cout << "Reading MyIntVectorPtr (Should be invalid) from file " << input << endl;
					fs >> myVectorIntPtr;
					for_each(myVectorIntPtr.begin() , myVectorIntPtr.end() , UniversalPrinterNS::Print<int>() );

				} 
				catch(FileStream::badfile & bf )
				{
					cout << bf.what() << endl;
				}
				catch(FileStream::baddata & bd )
				{
					cout << bd.what() << endl;						
				}




			}
			break;
			case FD2_END:
				cout << "Invalid Option" << endl;
				break;		
		}

		cout << demo_name << endl << "Enter Selection: ";
		input = get_user_input();		

	}while( input != QUIT );
	cout << "Returning to MainMenu..." << endl;


}