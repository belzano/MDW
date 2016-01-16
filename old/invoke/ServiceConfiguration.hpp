#pragma once

#include <map>
#include <string>

#include <boost/property_tree/ptree.hpp>

#include "wtf/toolbox/Types.hpp"
#include "wtf/toolbox/PtreeHelper.hpp"
#include "wtf/toolbox/ObjectModelHelpers.hpp"

template<>
void ptreeToObject<std::map<std::string, std::string> >	(const boost::property_tree::ptree& iNode, std::map<std::string, std::string>& oResult);

template<> 
void objectToPtree<std::map<std::string, std::string> >	(const std::map<std::string, std::string>& oResult, boost::property_tree::ptree& iNode);

namespace WTF
{

namespace configuration
{

	class ServiceConfiguration : public toolbox::PtreeDocument<ServiceConfiguration>
	{
		typedef std::map<std::string, std::string> StaticParameters;
		WTF_ATTRIBUTE(std::string, ServiceName)
		WTF_ATTRIBUTE(StaticParameters, StaticParameters)
		
	public:
		
		template <class K>
		static void registerConversions(toolbox::PtreeDocumentConversions<K>& registry)
		{		
			WTF_REGISTER_ATTRIBUTE_TO_PTREE(K, registry, std::string, ServiceName)
			WTF_REGISTER_ATTRIBUTE_TO_PTREE(K, registry, StaticParameters, StaticParameters)
		}
	
	};
	
	}

}

