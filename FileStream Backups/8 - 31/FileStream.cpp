#include "FileStream.h"


//using FileNS::FileStream;

using namespace FileNS;
using std::string;

FileStream::FileStream()
{
	fileIsOpen = false;
	streamName = "Test Stream";
	storedOption = INVALID_OPTION;
	mode = std::ios_base::in | std::ios_base::binary;
}

FileStream::FileStream(string fileName , OPTIONS options )
{
	fileIsOpen = false;
	fileIsOpen = init( fileName , options );
}

FileStream::~FileStream(){
	close();
}

void FileStream::printStreamName()
{
	std::cout << "Stream Name is " << streamName << std::endl;
	switch(storedOption)
	{
	case INVALID_OPTION:
		std::cout << "Invalid Option Chosen" << std::endl;
		break;
	case READ_ONLY:
		std::cout << "Read Only Option Chosen" << std::endl;
		break;
	case WRITE_ONLY:
		std::cout << "Write Only Option Chosen" << std::endl;
		break;
	default:
		std::cout << "Default Invalid Option Chosen" << std::endl;
		break;
	}
}

bool FileStream::open( string fileName  , OPTIONS options )
{
	return true;
}
		
		
bool FileStream::init(string fileName , OPTIONS options  )
{
	bool valid = true;
	mode = std::ios_base::binary;
	streamName = fileName;
	storedOption = options;

	if(fileIsOpen)
		close();

	switch(options)
	{
		case INVALID_OPTION:
			return false;
		break;
		case READ_ONLY:
			mode |= std::ios_base::in;
			break;
		case WRITE_ONLY:
			mode |= std::ios_base::out;
			break;
		default:
			return false;
	}

	file.open(streamName , mode );

	if(file.is_open() ){
		fileIsOpen = true;

	} else 
		return false;


	switch(options)
	{
		case READ_ONLY:
		{
			int readInt;
			
			file.read(reinterpret_cast< char * >(&readInt) , sizeof(int) );
			if(readInt != MAGIC_NUMBER ){
				//if( DEBUG ) std::cout << "This is not a file created by this system.  Major Error" << std::endl;
				valid = false;
			} //else 
				//if( DEBUG ) std::cout << "Valid Magic Number ";
			file.read(reinterpret_cast< char * >(&readInt) , sizeof(int) );
			if(readInt != VERSION_NUMBER ){
				std::cout << "This is a file created by an old version of this software. You may run into issues." << std::endl;
				valid = false;
			}	//else 
				//if( DEBUG ) std::cout << "Valid Version Number";

		}
		break;
		case WRITE_ONLY:
		{
			int writeInt;
			writeInt = MAGIC_NUMBER;
			file.write(reinterpret_cast< const char * >(&writeInt) , sizeof(int) );
			writeInt = VERSION_NUMBER;
			file.write(reinterpret_cast< const char * >(&writeInt) , sizeof(int) );
		}
		break;

	}


	return valid;
}

void FileStream::close(){
	if(fileIsOpen)
		file.close();

	fileIsOpen = false;
	streamName = "";
	storedOption = INVALID_OPTION;
	mode = std::ios_base::binary;

	

}

bool FileStream::writeMagicNumber(int num ){
	if(isOpen() && isOpenForWriting() ){		
		file.write(reinterpret_cast<const char * >(&num) , sizeof(int) );			
		return true;
	}
	throw FileStream::badfile();
	return false;

}

int FileStream::readMagicNumber( ){
	int returnInt = 0;
	if(isOpen() && isOpenForReading() ){		
		file.read(reinterpret_cast< char * >(&returnInt) , sizeof(int) );
		return returnInt;
	}
	
	throw FileStream::badfile();
	return returnInt;	

}


FileStream & FileNS::operator<<(FileStream & fs ,const int & in ) { // throw (std::exception) 
	if(fs.isOpen() && fs.isOpenForWriting() ){
		int checkType = FileStream::INT_TYPE;
		int intValue = in;
		fs.file.write(reinterpret_cast<const char * >(&checkType) , sizeof(int) );		
		fs.file.write(reinterpret_cast< char * >(&intValue) , sizeof(int) );
	} else {
		throw FileStream::badfile();		
	}	
	return fs;
}

FileStream & FileNS::operator>>(FileStream & fs , int & in ) {	// throw (std::exception)
	if(fs.isOpen() && fs.isOpenForReading() ){
		int checkType;
		in = 0;
		int intValue;
		fs.file.read(reinterpret_cast< char * >(&checkType) , sizeof(int) );

		if(checkType == FileStream::INT_TYPE ){
			fs.file.read(reinterpret_cast< char * >(&intValue) , sizeof(int) );
			in = intValue;
		}else{
			throw FileStream::baddata( FileStream::getTypeName(checkType)  , FileStream::getTypeName(FileStream::INT_TYPE) );		
		}
	} else {
		throw FileStream::badfile();
	}
	return fs;
}


		
FileStream & FileNS::operator<<(FileStream & fs , const float & in ) { // throw (std::exception) 
	if(fs.isOpen() && fs.isOpenForWriting()){
		int checkType = FileStream::FLOAT_TYPE;
		float floatValue = in;
		fs.file.write(reinterpret_cast<const char * >(&checkType) , sizeof(int) );		
		fs.file.write(reinterpret_cast< char * >(&floatValue) , sizeof(float) );
	} else {
		throw FileStream::badfile();	
	}	
	return fs;
}

FileStream & FileNS::operator>>(FileStream & fs ,  float & out  ) {	// throw (std::exception)
	if(fs.isOpen() && fs.isOpenForReading() ){
		int checkType;
		out = 0.0;
		float floatValue;
		fs.file.read(reinterpret_cast< char * >(&checkType) , sizeof(int) );

		if(checkType == FileStream::FLOAT_TYPE ){
			fs.file.read(reinterpret_cast< char * >(&floatValue) , sizeof(float) );
			out = floatValue;
		}else{
			throw FileStream::baddata( FileStream::getTypeName(checkType) , FileStream::getTypeName(FileStream::FLOAT_TYPE)  );			
		}
	} else {
		throw FileStream::badfile();
	}
	return fs;

}


FileStream & FileNS::operator<<(FileStream & fs ,const double & in ) { // throw (std::exception) 
	if(fs.isOpen() && fs.isOpenForWriting()){
		int checkType = FileStream::DOUBLE_TYPE;
		double doubleValue = in;
		fs.file.write(reinterpret_cast<const char * >(&checkType) , sizeof(int) );	
		fs.file.write(reinterpret_cast< char * >(&doubleValue) , sizeof(double) );
	} else {
		throw FileStream::badfile();	
	}	
	return fs;
}

FileStream & FileNS::operator>>(FileStream & fs ,  double & out  ) {	// throw (std::exception)	
	if(fs.isOpen() && fs.isOpenForReading() ){
		int checkType;
		double doubleValue;
	
		fs.file.read(reinterpret_cast< char * >(&checkType) , sizeof(int) );
		if(checkType == FileStream::DOUBLE_TYPE ){	
			fs.file.read(reinterpret_cast< char * >(&doubleValue) , sizeof(double) );		
			out = doubleValue;
		}else{
			throw FileStream::baddata( FileStream::getTypeName(checkType) ,  FileStream::getTypeName(FileStream::DOUBLE_TYPE)  );			
		}
	} else {
		throw FileStream::badfile();
	}
	return fs;

}




FileStream & FileNS::operator<<(FileStream & fs ,const string & in ) { // throw (std::exception) 
	if(fs.isOpen()&& fs.isOpenForWriting()){
		int stringSize = in.size()+1;
		int checkType = FileStream::STRING_TYPE;
		string stringValue = in;
		//std::cout << "String size is: " << stringSize << std::endl; 
		fs.file.write(reinterpret_cast<const char * >(&checkType) , sizeof(int) );	
		fs.file.write(reinterpret_cast<const char * >(&stringSize) , sizeof(int) );	
		//fs.file.write(reinterpret_cast<const char * >(&stringValue) , stringValue.size()+1 );
		fs.file.write( stringValue.c_str() , stringValue.size()+1 );
	} else {
		throw FileStream::badfile();	
	}	
	return fs;
}

FileStream & FileNS::operator>>(FileStream & fs ,  string & out  ) {	// throw (std::exception)
	//char *buff = 0;
	std::shared_ptr<char> sbuff;

	if(fs.isOpen() && fs.isOpenForReading() ){
		int checkType;
		int stringSize;		
		fs.file.read(reinterpret_cast< char * >(&checkType) , sizeof(int) );
		if(checkType == FileStream::STRING_TYPE ){
			fs.file.read(reinterpret_cast< char * >(&stringSize) , sizeof(int) );
			if(stringSize > 0 && stringSize < 1024 ){
				//std::cout << "String size is: " << stringSize << std::endl; 								
				//buff = new char[stringSize+10];
				sbuff.reset( new char[stringSize+10]);
				fs.file.read(sbuff.get() , stringSize );

				//strncpy( sbuff.get() , buff , stringSize );
				//std::cout << "Buff = : " << buff << std::endl;
				//std::cout << "SBuff = : " << *sbuff << std::endl;
				//std::cout << "SBuff = : " << sbuff.get() << std::endl;
				//out = buff;
				out = sbuff.get();
			}
		}else{
			throw FileStream::baddata( FileStream::getTypeName(checkType) ,  FileStream::getTypeName(FileStream::STRING_TYPE) );
			//if(buff != 0 )
			//delete buff;
		}
	} else {
		//std::cout << "Error File is not Open " << std::endl;
		//if(buff != 0 )
		//	delete buff;
		throw FileStream::badfile();
	}
	//if(buff != 0 )
	//	delete buff;
	return fs;

}



FileStream & FileNS::operator<<(FileStream & fs ,const bool & in ) { // throw (std::exception) 
	if(fs.isOpen()&& fs.isOpenForWriting()){
		int checkType = FileStream::BOOL_TYPE;
		bool boolValue = in;
		fs.file.write(reinterpret_cast<const char * >(&checkType) , sizeof(int) );		
		fs.file.write(reinterpret_cast< char * >(&boolValue) , sizeof(bool) );
	} else {
		throw FileStream::badfile();		
	}	
	return fs;
}

FileStream & FileNS::operator>>(FileStream & fs , bool & out ) {	// throw (std::exception)
	if(fs.isOpen() && fs.isOpenForReading() ){
		int checkType;
		bool boolValue;
		fs.file.read(reinterpret_cast< char * >(&checkType) , sizeof(int) );

		if(checkType == FileStream::BOOL_TYPE ){
			fs.file.read(reinterpret_cast< char * >(&boolValue) , sizeof(bool) );
			out = boolValue;
		}else{
			throw FileStream::baddata( FileStream::getTypeName(checkType)  , FileStream::getTypeName(FileStream::INT_TYPE) );			
		}
	} else {
		throw FileStream::badfile();
	}
	return fs;
}








/*
FileStream & FileNS::operator>>(FileStream & fs ,  string & out  ) {	// throw (std::exception)
	char *buff = 0;

	if(fs.isOpen() ){
		int checkType;
		int stringSize;		
		fs.file.read(reinterpret_cast< char * >(&checkType) , sizeof(int) );
		if(checkType == FileStream::STRING_TYPE ){
			fs.file.read(reinterpret_cast< char * >(&stringSize) , sizeof(int) );
			if(stringSize > 0 && stringSize < 1024 ){
				std::cout << "String size is: " << stringSize << std::endl; 								
				buff = new char[stringSize+10];
				fs.file.read(buff , stringSize );
				out = buff;
			}
		}else{
			throw FileStream::baddata( FileStream::getTypeName(checkType) ,  FileStream::getTypeName(FileStream::STRING_TYPE) );
			out = "";
			if(buff != 0 )
			delete buff;
		}
	} else {
		out = "";
		std::cout << "Error File is not Open " << std::endl;
		if(buff != 0 )
			delete buff;
		throw FileStream::badfile();
	}
	if(buff != 0 )
		delete buff;
	return fs;

}*/



std::string FileStream::getTypeName( int type ){
	return getTypeName(FileStream::TYPE_IDENTIFIER(type));
}

std::string FileStream::getTypeName( TYPE_IDENTIFIER type ){	
	switch(type)
	{
		case INT_TYPE:
			return "Int Type";
		case FLOAT_TYPE:
			return "Float Type";
		case DOUBLE_TYPE:
			return "Double Type";
		case STRING_TYPE:
			return "String Type";	
		case BOOL_TYPE:
			return "Bool Type";	
		case STL_VECTOR_TYPE:
			return "STL Vector Type";
	}
	return "Unknown";
}


FileStream::baddata::baddata(string expectedIn  , string receivedIn )
{
	 returnString = string("Expected ").append(expectedIn).append(" but received ").append(receivedIn).append(".");
}

/*
FileStream::badfile::badfile() {

}*/


