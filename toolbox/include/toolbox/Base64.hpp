#pragma once

#include "toolbox/Types.hpp"


namespace toolbox
{
	namespace base64
	{
		toolbox::DataPtr base64( const toolbox::DataPtr binaryData );

		toolbox::DataPtr unbase64(const toolbox::DataPtr ascii);

	} // namespace base64
}

