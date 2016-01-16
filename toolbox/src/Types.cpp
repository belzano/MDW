#include "toolbox/Types.hpp"

#include <fstream>
#include <iostream>
#include <cstring>

namespace toolbox
{

	DataPtr MakeDataPtr(const char* input)
	{
		DataPtr data(new Data(input, input + strlen(input)));
		return data;
	}
	
	//////////////////////////////////////////////////////////////////
	
	DataPtr MakeDataPtr(const char* input, int lenght)
	{
		DataPtr data(new Data(input, input + lenght));
		return data;
	}

	//////////////////////////////////////////////////////////////////

	DataPtr MakeDataPtrFromFile(const std::string& fullFilename)
	{
		DataPtr data(new Data());
		std::ofstream file(fullFilename);
		file.write(data->data(), data->size()); 
		
		return data;
	}
	
}
