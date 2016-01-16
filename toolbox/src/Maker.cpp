
#include "toolbox/Maker.hpp"
#include "toolbox/Logger.hpp"

namespace toolbox {
  
    /////////////////////////////////////////////////////////////////////////////////

    Maker& Maker::instance()
    {
	static Maker instance;
	return instance;
    }
 
    /////////////////////////////////////////////////////////////////////////////////

    void Maker::registration(const Key& key, ObjectMakerPtr& maker)
    {			
	typename ObjectMakerRegistry::iterator it;
	it = _makers.find(key);
	if (it != _makers.end())
	{
	    // Warning: overriding existing service
	}
	_makers[key] = maker;
	//WTF_LOG_INFO("Service registration ["<< key << "] " );	
    }

    /////////////////////////////////////////////////////////////////////////////////

    std::shared_ptr<Object> Maker::do_make(Key const& key)
    {
	typename ObjectMakerRegistry::const_iterator it;
	it = _makers.find(key);
	if (it == _makers.end())
	{
	    MDW_LOG_ERROR("Unable to make object with typename ["<< key << "]");
	    return std::shared_ptr<Object>(nullptr); 
	}	
	
	//MDW_LOG_DEBUG("Service found ["<< key << "]");
	return it->second->make();
    }

      
}
