#pragma once

#include <string>
#include <memory>
#include "toolbox/Image.hpp"

#include "uhf/kvs/component/KeyValueStorage.hpp"
#include "toolbox/PtreeHelper.hpp"
#include "toolbox/ObjectModelHelpers.hpp"

#include "mme/QueryDetails.hpp"


namespace API
{
	
	/////////////////////////////////////////////////////////////////
		
	class Query
	{
		typedef uhf::kvs::component::KeyValueStoragePtr KeyValueStoragePtr;
	public:

		Query(KeyValueStoragePtr& storageCell);

		void setInput(const std::string& iFileName);
		void setInput(toolbox::Image::DataPtr );
		
		int process();
		
		const toolbox::Image::DataPtr  getOutput( toolbox::Image::SerializationFormat = toolbox::Image::svg, 
												  toolbox::Image::Resolution = toolbox::Image::sameAsInput) const;
  
		MAKE_ATTRIBUTE(Requestor, 	Requestor)
		MAKE_ATTRIBUTE(InputDetails, InputDetails)
		MAKE_ATTRIBUTE(Events, 		Events)
		MAKE_ATTRIBUTE(State, 		State)
		
		void toStorage() const;
		void fromStorage();
		
	private:
		
		const toolbox::Image::DataPtr getInput() const;
		void setOutput(toolbox::Image::DataPtr );	
		
		KeyValueStoragePtr _storage;		
	};
}
