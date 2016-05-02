
#include "toolbox/entity/Factory.hpp"
#include "toolbox/Logger.hpp"

namespace toolbox {
namespace entity {
  
    /////////////////////////////////////////////////////////////////////////////////

    Factory& Factory::instance()
    {
		static Factory instance;
		return instance;
    }
 
    /////////////////////////////////////////////////////////////////////////////////

    void Factory::registration(const Key& key, MakerPtr& maker)
    {			
		typename MakerRegistry::iterator it;
		it = _makers.find(key);
		if (it != _makers.end())
		{
			// Warning: overriding existing service
		}
		_makers[key] = maker;
		MDW_LOG_INFO("Registered maker for entity ["<< key << "] " );	
    }

 
    /////////////////////////////////////////////////////////////////////////////////

	bool Factory::isRegistered(const Key& key) const
	{
		typename MakerRegistry::const_iterator it = _makers.find(key);
		return it != _makers.end();
	}

    /////////////////////////////////////////////////////////////////////////////////

    std::shared_ptr<Entity> Factory::do_make(Key const& key)
    {
		typename MakerRegistry::const_iterator it;
		it = _makers.find(key);
		if (it == _makers.end())
		{
			MDW_LOG_ERROR("Unable to make entity with typename ["<< key << "]");
			return std::shared_ptr<Entity>(nullptr); 
		}	
		
		//MDW_LOG_DEBUG("Service found ["<< key << "]");
		return it->second->make();
	}

      
}
}
