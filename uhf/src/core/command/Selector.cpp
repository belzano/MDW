
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
			for (auto prop : comp->getProperties()) 
			{
				if (prop->getTypename() == iCriteria->getTypename())
				{
					result.push_back(comp);
					break;
				}
			}
		}
		
		MDW_LOG_INFO("Filter returned " << result.size() << " macthes");
	}

    
}
}
