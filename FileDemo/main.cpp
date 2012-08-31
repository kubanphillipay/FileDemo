
#include <iostream>
#include <string>
#include "Functions/functions.h"


using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::list;
using std::shared_ptr;



int main()
{
	print_list_options(main_loop_names , MAIN_LOOP_OPTIONS_END  );
	
	int input = 0;		
	do{
		cout << "In Main Menu." << endl << "Enter Selection: ";
		input = get_user_input();

		switch(input){
			case QUIT:
				cout << "Press Enter to Quit"<< endl;
				get_user_input() ;
				break;	
			case SHOW_OPTIONS:
				print_list_options(main_loop_names , MAIN_LOOP_OPTIONS_END , "MAIN MENU Options:" );
				break;		
			case FILESTREAM_DEMO_ONE:
				filestream_demo_one();
				break;		
			case FILESTREAM_DEMO_TWO:
				filestream_demo_two();
				break;	
			case FILESTREAM_DEMO_THREE:
				filestream_demo_three();
				break;	
			case FILESTREAM_DEMO_FOUR:
				filestream_demo_four();
				break;	
			case FILESTREAM_DEMO_FIVE:
				filestream_demo_five();
				break;	
			case FILESTREAM_DEMO_SIX:
				filestream_demo_six();
				break;	
			case MAIN_LOOP_OPTIONS_END:
				cout << "Invalid Option" << endl;
				break;		
		}

		cout << endl;

	}while( input != QUIT );


}//end of program




