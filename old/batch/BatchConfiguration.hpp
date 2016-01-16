#pragma once

#include <map>
#include <set>
#include <list>
#include <string>

#include "wtf/toolbox/Types.hpp"
#include "wtf/toolbox/PtreeHelper.hpp"
#include "wtf/toolbox/ObjectModelHelpers.hpp"

namespace WTF
{

namespace configuration
{
	/////////////////////////////////////////////////////////////////////

	class BatchConfiguration : public toolbox::PtreeDocument<BatchConfiguration>
	{
		
	public:
	
		template <class K>
		static void registerConversions(toolbox::PtreeDocumentConversions<K>& /*registry*/)
		{		
			
		}
	};
	
	}

}
