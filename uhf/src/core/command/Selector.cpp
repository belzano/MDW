
#include "uhf/core/command/Selector.hpp"

#include "toolbox/Logger.hpp"

#include "uhf/core/component/ComponentRegistry.hpp"
#include "uhf/core/aspects/IActivable.hpp"
#include "uhf/core/property/Activable.hpp"

////////////////////////////////////////////////////////////

namespace uhf {
namespace command {
	
    Selector::Selector()
	{

    }	

    ////////////////////////////////////////////////////////////

    Selector::~Selector()
    {

    }	

    ////////////////////////////////////////////////////////////

	void Selector::filter(IPropertyPtr iCriteria, 
						  std::list<uhf::IComponentPtr>& components,
						  std::list<uhf::IComponentPtr>& result)
	{
		for (auto comp : components) 
		{
			if (comp->hasProperty(iCriteria))
			{
				result.push_back(comp);
			}

		}
	}

    
}
}
