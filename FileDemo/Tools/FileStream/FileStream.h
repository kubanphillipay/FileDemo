#ifndef _FILESTREAM_H_
#define _FILESTREAM_H_


#include <iostream>
#include <string>
#include <exception>
#include <memory>
#include <vector>
#include <fstream>

using std::string;
using std::fstream;

namespace FileNS{
	

	class FileStream{
	public:

		class badfile : public std::exception
		{
		public:
			//badfile();
			const char *what() { return "File not initialized properly"; }
		};

		class baddata : public std::exception
		{
		private:
			string returnString;
		public:
			baddata(string expectedIn = "Unknown" , string receivedIn  = "Unknown" );
			const char *what() { return returnString.c_str(); }
		};

		enum OPTIONS{ INVALID_OPTION , READ_ONLY  , WRITE_ONLY };	

		FileStream( );
		FileStream( string fileName  , OPTIONS options );
		~FileStream();
		bool open( string fileName  , OPTIONS options );
		void printStreamName();
		bool isOpen() { return fileIsOpen; }
		bool isOpenForReading() { if(storedOption == READ_ONLY) return true; return false; }
		bool isOpenForWriting() { if(storedOption == WRITE_ONLY) return true; return false; }
		void close();
		static std::string getTypeName( int type );
		bool writeMagicNumber(int num );
		int readMagicNumber( );

		friend FileStream & operator<<(FileStream & fs , const int & in ) ;// throw (std::exception)
		friend FileStream & operator>>(FileStream & fs , int & out ) ; // throw (std::exception)
		friend FileStream & operator<<(FileStream & fs , const std::string & in );
		friend FileStream & operator>>(FileStream & fs , std::string & out );
		friend FileStream & operator<<(FileStream & fs , const float & in );
		friend FileStream & operator>>(FileStream & fs , float & out );
		friend FileStream & operator<<(FileStream & fs , const double & in );
		friend FileStream & operator>>(FileStream & fs , double & out );
		friend FileStream & operator<<(FileStream & fs , const bool & in );
		friend FileStream & operator>>(FileStream & fs , bool & out );
		template< class T >
		friend FileStream & operator<<(FileStream & fs , const std::vector<T> & in );
		template< class T >
		friend FileStream & operator>>(FileStream & fs , std::vector<T> & out );	
		
		template< class T >
		friend FileStream & operator<<=(FileStream & fs , std::vector<T> & in );
		template< class T >
		friend FileStream & operator>>=(FileStream & fs , std::vector<T> & out );

		
		template< class T >
		friend FileStream & operator<<(FileStream & fs , const T* const & in );
		template< class T >
		friend FileStream & operator>>(FileStream & fs , T* & out );
		
	
		template< class T >
		friend FileStream & operator<<(FileStream & fs , const std::shared_ptr<T> & in );
		template< class T >
		friend FileStream & operator>>(FileStream & fs , std::shared_ptr<T> & out );
		
	private:
		enum { DEBUG = 1 };
		enum { MAGIC_NUMBER = 943259023 };
		enum { VERSION_NUMBER = 1 };
		enum TYPE_IDENTIFIER{ INT_TYPE = 32350933 , FLOAT_TYPE = 402350932 , 
			  DOUBLE_TYPE = 9032583 ,  STRING_TYPE = 30923583  , BOOL_TYPE = 8532095 ,
			  STL_VECTOR_TYPE = 309324 };
		int count;
		bool fileIsOpen;
		std::string streamName;
		std::fstream file;
		bool init(string fileName , OPTIONS options = READ_ONLY );
		OPTIONS storedOption;
		std::ios_base::openmode mode;
		static std::string getTypeName( TYPE_IDENTIFIER type );
	};



	template <class T>
	class WriteAValue
	{
		private:
			FileStream & fs;
		public:
			WriteAValue(FileStream & fsIn ) : fs(fsIn) { }
			//void operator()( const T & t ){ std::cout << "  In Write a Value" << std::endl ; fs << t; }			
			void operator()( const T & t ){ fs << t; }			
			
	};

	
	template <class T>
	class ReadAValue
	{
		private:
			FileStream & fs;
		public:
			ReadAValue(FileStream & fsIn ) : fs(fsIn) { }
			//T & operator()(T & t ){ std::cout << "  In Read a Value" << std::endl ; fs >> t; return t; }	
			T & operator()(T & t ){ fs >> t; return t; }	
	};
		



template< class T >
FileStream & operator<<(FileStream & fs , const std::vector<T> & in ){
	//std::cout << "In vector<T> <<= method" << std::endl;
		
	if(fs.isOpen()&& fs.isOpenForWriting()){
		
		int checkType = FileStream::STL_VECTOR_TYPE;
		int size = in.size();
		fs.file.write(reinterpret_cast<const char * >(&checkType) , sizeof(int) );		
		fs.file.write(reinterpret_cast<const char * >(&size) , sizeof(int) );		

		for_each(in.begin() , in.end() , WriteAValue<T>(fs) );

	} else {
		throw FileStream::badfile();		
	}	
	return fs;


}

template< class T >
FileStream & operator>>(FileStream & fs , std::vector<T> & out ){
	
	//std::cout << "In vector<T> >>= Method" << std::endl;
	
	out.clear();

	if(fs.isOpen() && fs.isOpenForReading() ){
		int checkType;
		int size = 0;
		ReadAValue<T> read(fs);
		T t;
		fs.file.read(reinterpret_cast< char * >(&checkType) , sizeof(int) );
		fs.file.read(reinterpret_cast< char * >(&size) , sizeof(int) );

		if(checkType == FileStream::STL_VECTOR_TYPE ){
			for(int i = 0 ; i < size ; ++i ){	
				out.push_back(read(t));
			}	
		}else{
			throw FileStream::baddata( FileStream::getTypeName(checkType)  , FileStream::getTypeName(FileStream::STL_VECTOR_TYPE) );			
		}
	} else {
		throw FileStream::badfile();
	}
	return fs;


}



		template< class T >
		FileStream & operator<<(FileStream & fs , const T* const & in ){
			//std::cout << "    In overloaded write pointer template" << endl;
			try{
				fs << *in;
			}
			catch(...)	{
				throw;
			}
			return fs;
		}

		template< class T >
		FileStream & operator>>(FileStream & fs , T* & out ){
			//std::cout << "    In overloaded read pointer template" << endl;
			//T* t = new T;
			T* t = new T();
			try{
				//fs >> t;
				fs >> *t;
			}
			catch(...)	{
				//
				delete t;
				throw;
			}
			//out = new T(t);
			out = t;
			return fs;
		}


		template< class T >
		FileStream & operator<<(FileStream & fs , const std::shared_ptr<T> & in ){
			//std::cout << "    In overloaded write shared pointer template" << endl;
			try{
				fs << *in;
			}
			catch(...)	{
				throw;
			}
			return fs;

		}

		template< class T >
		FileStream & operator>>(FileStream & fs , std::shared_ptr<T> & out ){
			//std::cout << "    In overloaded read shared pointer template" << endl;
			//T* t = new T;
			//shared_ptr<T> tempPtr(new T());
			out.reset(new T());
			try{
				//fs >> t;
				fs >> *out;
			}
			catch(...)	{
				out.reset();
				//
				//delete t;
				//tempPtr.reset();
				throw;
			}
			//out = new T(t);
			//out = tempPtr;
			return fs;
		}





}


#endif