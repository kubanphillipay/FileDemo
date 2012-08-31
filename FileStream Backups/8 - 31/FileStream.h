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
		friend FileStream & operator<<(FileStream & fs , const std::vector<T*> & in );
		template< class T >
		friend FileStream & operator>>(FileStream & fs , std::vector<T*> & out );	

		template< class T >
		friend FileStream & operator<<(FileStream & fs , const std::vector<std::shared_ptr<T>> & in );
		template< class T >
		friend FileStream & operator>>(FileStream & fs , std::vector<std::shared_ptr<T>> & out );	

		template< class T >
		friend FileStream & operator<<=(FileStream & fs , const std::vector<T> & in );
		template< class T >
		friend FileStream & operator>>=(FileStream & fs , std::vector<T> & out );

		
		template< class T >
		friend FileStream & operator<<(FileStream & fs , const T* const & in );
		template< class T >
		friend FileStream & operator>>(FileStream & fs , T* & out );

	/*
		template< class T >
		friend FileStream & operator<<(FileStream & fs , const std::shared_ptr<T> & in );
		template< class T >
		friend FileStream & operator>>(FileStream & fs , std::shared_ptr<T> & out );*/
		
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
	
/*
template<typename T> 
struct remove_pointer 
{ 
    typedef T type; 
}; 
 
template<typename T> 
struct remove_pointer<T*> 
{ 
    typedef typename remove_pointer<T>::type type; 
}; 

typename remove_pointer<T>::type type; 

*/



	template<typename T> 
	struct remove_pointer 
	{ 
		typedef T type; 
	}; 
 
	template<typename T> 
	struct remove_pointer<T*> 
	{ 
		typedef T type; 
	}; 
	//typedef typename remove_pointer<T>::type type; 

	template <class T>
	class WritePtr
	{
		private:
			FileStream & fs;
		public:
			WritePtr(FileStream & fsIn ) : fs(fsIn) { }
			//void operator()( T t){ fs << *t;  std::cout << "WritePtr, Writing: " << *t << " to file" <<endl; }
			void operator()( T t){ fs << *t; }
	};
	
	template <class T>
	class WriteValue
	{
		private:
			FileStream & fs;
		public:
			WriteValue(FileStream & fsIn ) : fs(fsIn) { }
			void operator()(const T & t){ fs << t; }
			void operator()( T*const & t){ fs << *t; }
			void operator()(const std::shared_ptr<T> & t){ fs << *t; std::cout << "Writing Shared Pointer: " << *t << std::endl; }
			//void operator()(const T & t){ std::cout << "STL Writing Value: " << t << std::endl;  }
	};


	template <class T>
	class WriteAValue
	{
		private:
			FileStream & fs;
		public:
			WriteAValue(FileStream & fsIn ) : fs(fsIn) { }
			void operator()(T*const & t){ fs << *t; }			
			
	};



	/*
	template <class T>
	class ReadPtr
	{
		private:
			FileStream & fs;
		public:
			ReadPtr(FileStream & fsIn ) : fs(fsIn) { }
			T operator()(){ fs >> *t; }
	};*/

	template <class T>
	class ReadPtrS
	{
		private:
			FileStream & fs;
		public:
			ReadPtrS(FileStream & fsIn ) : fs(fsIn) { }
			T operator()(){
				typedef typename remove_pointer<T>::type type; 
				T t = new type();
				fs >> *t;
				return t;
			}
	};


	template <class T>
	class ReadPtr
	{
		private:
			FileStream & fs;
		public:
			ReadPtr(FileStream & fsIn ) : fs(fsIn) { }
			T* operator()(){			
				T* t = new T();
				fs >> *t;
				return t;
			}
	};


	template <class T>
	class ReadValue
	{
		private:
			FileStream & fs;
		public:
			ReadValue(FileStream & fsIn ) : fs(fsIn) { }
			T & operator()(T & t){ fs >> t; return t; }
			T* & operator()(T* & t ){ t = new T(); fs >> *t;  return t; } //std::cout << "Reading Pointer: " << *t << std::endl; return t; }
			std::shared_ptr<T> & operator()(std::shared_ptr<T> & t){ t.reset(new T() ); fs >> *t;  return t; } //std::cout << "Reading Shared Pointer: " << *t << "Use Count: = " << t.use_count() << std::endl; return t; }
	};
	/*
	template <class T>
	class ReadValues
	{
		private:
			FileStream & fs;
		public:
			ReadValues(FileStream & fsIn ) : fs(fsIn) { }
			//void operator()( T & t){ fs >> t; std::cout << "Read value " << t << " into Memory?" << std::endl; }
			T operator()( ){ T t; fs >> t; return t; }
	};*/

	

template< class T >
FileStream & operator<<(FileStream & fs , const std::vector<T> & in ){
	
	if(fs.isOpen()&& fs.isOpenForWriting()){

		//std::cout << "Writing Vector to File (not implemented yet)" << std::endl;
		int checkType = FileStream::STL_VECTOR_TYPE;
		int size = in.size();
		fs.file.write(reinterpret_cast<const char * >(&checkType) , sizeof(int) );		
		fs.file.write(reinterpret_cast<const char * >(&size) , sizeof(int) );		

		for_each(in.begin() , in.end() , WriteValue<T>(fs) );

		/*
		int checkType = FileStream::BOOL_TYPE;
		bool boolValue = in;
		fs.file.write(reinterpret_cast<const char * >(&checkType) , sizeof(int) );		
		fs.file.write(reinterpret_cast< char * >(&boolValue) , sizeof(bool) );*/
	} else {
		throw FileStream::badfile();		
	}	
	return fs;


}

template< class T >
FileStream & operator>>(FileStream & fs , std::vector<T> & out ){
	out.clear();

	if(fs.isOpen() && fs.isOpenForReading() ){
		int checkType;
		int size = 0;
		ReadValue<T> read(fs);
		fs.file.read(reinterpret_cast< char * >(&checkType) , sizeof(int) );
		fs.file.read(reinterpret_cast< char * >(&size) , sizeof(int) );

		if(checkType == FileStream::STL_VECTOR_TYPE ){

			//std::cout << "STL Vector Accomplished" << std::endl;
			//std::cout << "Size: " << size << std::endl;

			for(int i = 0 ; i < size ; ++i ){	
				T t;
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
FileStream & operator<<(FileStream & fs , const std::vector<T*> & in ){
	std::cout << "In vector overload Pointer << Method" << std::endl;

	if(fs.isOpen()&& fs.isOpenForWriting()){

		int checkType = FileStream::STL_VECTOR_TYPE;
		int size = in.size();
		fs.file.write(reinterpret_cast<const char * >(&checkType) , sizeof(int) );		
		fs.file.write(reinterpret_cast<const char * >(&size) , sizeof(int) );	

		//for_each(in.begin() , in.end() , WritePtr<T*>(fs) );		
		for_each(in.begin() , in.end() , WriteValue<T>(fs) );		

	} else {
		throw FileStream::badfile();		
	}	
	return fs;



}

template< class T >
FileStream & operator>>(FileStream & fs , std::vector<T*> & out ){
	//std::cout << "In vector overload Pointer >> Method" << std::endl;

	if(fs.isOpen() && fs.isOpenForReading() ){
		int checkType;
		int size = 0;
		//ReadPtr<T> read(fs);
		ReadValue<T> read(fs);
		fs.file.read(reinterpret_cast< char * >(&checkType) , sizeof(int) );
		fs.file.read(reinterpret_cast< char * >(&size) , sizeof(int) );

		if(checkType == FileStream::STL_VECTOR_TYPE ){			

			for(int i = 0 ; i < size ; ++i ){						
				T* t; 
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
FileStream & operator<<(FileStream & fs , const std::vector<std::shared_ptr<T>> & in ){
	std::cout << "In overload Write  Shared Pointer << Method" << std::endl;

	if(fs.isOpen()&& fs.isOpenForWriting()){

		int checkType = FileStream::STL_VECTOR_TYPE;
		int size = in.size();
		fs.file.write(reinterpret_cast<const char * >(&checkType) , sizeof(int) );		
		fs.file.write(reinterpret_cast<const char * >(&size) , sizeof(int) );	

		//for_each(in.begin() , in.end() , WriteValue<std::shared_ptr<T>>(fs) );		
		for_each(in.begin() , in.end() , WriteValue<T>(fs) );		
	} else {
		throw FileStream::badfile();		
	}	
	return fs;

}
template< class T >
FileStream & operator>>(FileStream & fs , std::vector<std::shared_ptr<T>> & out ){
	std::cout << "In overload Load Shared Pointer << Method" << std::endl;

	if(fs.isOpen() && fs.isOpenForReading() ){
		int checkType;
		int size = 0;
		ReadValue<T> read(fs);
		fs.file.read(reinterpret_cast< char * >(&checkType) , sizeof(int) );
		fs.file.read(reinterpret_cast< char * >(&size) , sizeof(int) );

		if(checkType == FileStream::STL_VECTOR_TYPE ){			

			for(int i = 0 ; i < size ; ++i ){						
				shared_ptr<T> t;
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



//======== TEMPORARY =============


template< class T >
FileStream & operator<<=(FileStream & fs , const std::vector<T> & in ){
	std::cout << "In vector<T> <<= method" << std::endl;
		
	if(fs.isOpen()&& fs.isOpenForWriting()){
		
		int checkType = FileStream::STL_VECTOR_TYPE;
		int size = in.size();
		fs.file.write(reinterpret_cast<const char * >(&checkType) , sizeof(int) );		
		fs.file.write(reinterpret_cast<const char * >(&size) , sizeof(int) );		

		for_each(in.begin() , in.end() , WriteValue<T>(fs) );

	} else {
		throw FileStream::badfile();		
	}	
	return fs;


}

template< class T >
FileStream & operator>>=(FileStream & fs , std::vector<T> & out ){
	
	std::cout << "In vector<T> >>= Method" << std::endl;
	
	out.clear();

	if(fs.isOpen() && fs.isOpenForReading() ){
		int checkType;
		int size = 0;
		ReadValue<T> read(fs);
		fs.file.read(reinterpret_cast< char * >(&checkType) , sizeof(int) );
		fs.file.read(reinterpret_cast< char * >(&size) , sizeof(int) );

		if(checkType == FileStream::STL_VECTOR_TYPE ){

			

			for(int i = 0 ; i < size ; ++i ){	
				T t;
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

//======== TEMPORARY =============


		template< class T >
		FileStream & operator<<(FileStream & fs , const T* const & in ){
			std::cout << "    In overloaded write pointer template" << endl;
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
			std::cout << "    In overloaded read pointer template" << endl;
			//T* t = new T;
			T t;
			try{
				fs >> t;
			}
			catch(...)	{
				throw;
			}
			out = new T(t);
			return fs;
		}







}


#endif