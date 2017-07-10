#pragma once

#include "toolbox/Types.hpp"
#include "uhf/IProperty.hpp"
#include "uhf/IComponent.hpp"

#include "toolbox/ptree/Types.hpp"
#include "toolbox/ptree/Conversions.hpp"

namespace uhf {	
namespace core {
namespace property {

	class UpdateEventArgs
	{
		
	};
	 
	//////////////////////////////////////////////////////////////////////////////////////
	
	class Updatable: public IProperty
	{
	public:
		virtual bool checkConsistency(uhf::IComponentPtr componentInstance) const override;
				
		virtual bool equals(IPropertyPtr other) const override;

		virtual std::ostream& toStream(std::ostream& stream) const;	
    };	

	typedef std::shared_ptr<Updatable> UpdatablePtr;

}
}
}

