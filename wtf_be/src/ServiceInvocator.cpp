#include "ServiceInvocator.hpp"

#include "ServiceRegistry.hpp"

#include "toolbox/StringUtils.hpp"
#include "toolbox/Logger.hpp"

#include <iostream>
#include "LibLoader.hpp"
#include <boost/property_tree/json_parser.hpp>
#include "toolbox/ExecutionContext.hpp"

#include "BackendConfiguration.hpp"
#include "ServiceConfiguration.hpp"

using namespace WTF;
using namespace std;

////////////////////////////////////////////////////////////////////////

ServiceInvocator::ServiceInvocator()
{
	// Get the config
	std::string filename = toolbox::ExecutionContext::instance().getDirCfg() + "entrypoints.001.json";
	boost::property_tree::ptree pt;
	boost::property_tree::read_json(filename, pt);
	_be_config = configuration::BackendConfiguration::load(pt);

	// Load the libraries
	std::set<std::string >::const_iterator it;
	for(it  = _be_config.getLibraries().begin();
		it != _be_config.getLibraries().end();
		++it)
	{
		LibLoader loader(new LibLoaderObject());
		loader->init(it->c_str());
		_loadedLibsList.insert(loader);
	}

	// register handlers
	
}

////////////////////////////////////////////////////////////////////////

std::shared_ptr<Service> ServiceInvocator::resolveUrl(const std::string& url)
{
	// Resolve url to service name.
	// Url unknown => default service if defined
	const configuration::ServiceConfiguration* config = & _be_config.getDefaultHandler();
	
	std::map<std::string, configuration::ServiceConfiguration>::const_iterator it = _be_config.getHandlers().find(url);
	if (it != _be_config.getHandlers().end())
	{
		MDW_LOG_DEBUG("Found a handler for url [" << url << "]");
		config = & it->second;
	}
	else
	{
		
		MDW_LOG_DEBUG("Using default handler for url [" << url << "]");
	}
	
	// Get service from name
	std::shared_ptr<Service> service = ServiceRegistry::instance().getService(config->getServiceName());
	if (service.get() != NULL)
		service->getContext().getStaticParameters() = config->getStaticParameters();
	
	return service;
} 
 
////////////////////////////////////////////////////////////////////////

bool ServiceInvocator::invoke(const Query& iQuery, Reply& ioReply)
{

	std::vector<std::string> url_tokens = toolbox::split(iQuery._url, '/');
	
	std::string url = "";
	U16 idx = 0;
	while (url.empty() && ! idx < url_tokens.size())	
	{
		url = url_tokens[idx];
		++idx;
	};

    // local copy to protect hot load.
	// Get service is thread safe.
	std::shared_ptr<Service> service = resolveUrl(url);
    if (service.get() == NULL)
    {
		MDW_LOG_WARNING("No service registered for url ["<< url <<"]");
        ioReply.answerstring = toolbox::MakeDataPtr("Unknown Service");
		return false;
	}
	
	// invoke	
	MDW_LOG_DEBUG("Service invocation with params " << iQuery._url_args.size() << " " << iQuery._parsed_post_data.size() );
    return service->invoke(	iQuery._url, 
							iQuery._url_args, 
							iQuery._parsed_post_data,
							ioReply.answerstring);
}

void ServiceInvocator::_getInvalidResponse(string& response)
{
    response = "Some error in your data ";
}

