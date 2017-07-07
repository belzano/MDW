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
			
	DataPtr MakeDataPtr(const std::string& input)
	{
		return MakeDataPtr(input.c_str(), input.size() + 1);
	}	

	//////////////////////////////////////////////////////////////////

	DataPtr MakeDataPtrFromFile(const std::string& fullFilename)
	{
		DataPtr data(new Data());
		std::ofstream file(fullFilename);
		file.write(data->data(), data->size()); 
		
		return data;
	}
		
	//////////////////////////////////////////////////////////////////
			
	std::string toString(const DataPtr& input)
	{
		return std::string(input->data(), input->size());
	}

}
