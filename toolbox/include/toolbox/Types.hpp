#pragma once

#include <string>
#include <vector>
#include <map>
#include <memory>

#include <istream>


// 1 byte
typedef  int8_t 	S8;
typedef	uint8_t 	U8;
// 2 bytes
typedef  int16_t 	S16;
typedef uint16_t 	U16;
// 4 bytes
typedef  int32_t 	S32;
typedef uint32_t 	U32;
// 8 bytes
typedef  int64_t 	S64;
typedef uint64_t 	U64;


namespace toolbox
{
	typedef std::string PropertyGroup;	
	typedef std::string PropertyKey;
	typedef std::string PropertyValue;
	
	typedef std::string DataGroup;
	typedef std::string DataKey;
	
	typedef std::vector<char> Data;
	typedef std::shared_ptr< Data > DataPtr;
	
	DataPtr MakeDataPtr(const char*);
	DataPtr MakeDataPtr(const char*, int len);	
	
	DataPtr MakeDataPtrFromFile(const std::string& fullFilename);
	
	class DataPtrStreamWrapper : public std::basic_streambuf<char, std::char_traits<char> > 
	{
		public:
		DataPtrStreamWrapper(DataPtr &vec) 
		{
			setg(vec->data(), vec->data(), vec->data() + vec->size());
		}
	};

}






