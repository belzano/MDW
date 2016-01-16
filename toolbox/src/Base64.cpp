#include "toolbox/Base64.hpp"

#include "Base64Impl.hpp"
#include <iterator>

using namespace toolbox;

///////////////////////////////////////////////////////////////////////

DataPtr toolbox::base64::base64( const DataPtr binaryData)
{
	int resLen = 0;
	char* res = Base64Impl::base64( (const void*) binaryData.get(), binaryData->size(), &resLen);
	
	DataPtr result = toolbox::MakeDataPtr(res, resLen);
		
	free(res);				
	return result;
}

///////////////////////////////////////////////////////////////////////

DataPtr toolbox::base64::unbase64( const DataPtr ascii)
{
	int resLen = 0;
	unsigned char* res = Base64Impl::unbase64( (const char*) ascii.get(), ascii->size(), &resLen);
	
	DataPtr result = toolbox::MakeDataPtr((char*)res, resLen);
	
	free(res);	
	return result;
}
	
