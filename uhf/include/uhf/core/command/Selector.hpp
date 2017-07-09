#pragma once

#include <memory>

#include "uhf/IComponent.hpp"
#include "uhf/IProperty.hpp"
#include "uhf/IComponentRegistry.hpp"



namespace uhf {
namespace command {
		
	/////////////////////////////////////////////////////////////////////
		
	class Selector
	{
	public:
		Selector();
		~Selector();

		void filter(IPropertyPtr iCriteria, 
					std::list<uhf::IComponentPtr>& components,
					std::list<uhf::IComponentPtr>& result);

	};
}
}
