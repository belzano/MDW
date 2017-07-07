#pragma once

#include "Types.hpp"

namespace toolbox
{

class Image 
{
	public:

	typedef toolbox::Data Data;
	typedef toolbox::DataPtr DataPtr;
			
	typedef enum
	{
		jpeg,
		svg
	} SerializationFormat;

	typedef enum
	{
		low,
		medium,
		high,
		native,
		sameAsInput
	} Resolution;
	
};

}

