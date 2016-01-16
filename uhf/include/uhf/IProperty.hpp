#pragma once

#include <string>
#include "toolbox/Types.hpp"

namespace  uhf {
	
	class IProperty
	{
		public:
		
			// ctor
			IProperty();
			// dtor
			virtual ~IProperty();

	};
	
	typedef std::shared_ptr<IProperty> IPropertyPtr;
}

