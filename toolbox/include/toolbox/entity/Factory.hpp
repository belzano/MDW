#pragma once

#include "toolbox/entity/Entity.hpp"
#include "toolbox/Typename.hpp"
#include <memory>
#include <map>

namespace toolbox {
namespace entity {
 
    /////////////////////////////////////////////////////////////////////////////////
  
    class Maker
    {
    public:
		virtual std::shared_ptr<Entity> make() = 0;
    };
  
    /////////////////////////////////////////////////////////////////////////////////
  
    template <class T>
    class MakerImpl : public Maker
    {
    public:
		virtual std::shared_ptr<Entity> make() override
		{ 
		  return std::shared_ptr<Entity>(new T());
		}
    };
    
    typedef std::shared_ptr<Maker> MakerPtr;
    
    /////////////////////////////////////////////////////////////////////////////////
    
    class Factory
    {
    public:
     
        // singleton 
		static Factory& instance();
		  
		typedef std::string Key;
		
		template <class T>
		void registration()
		{
			MakerPtr objMaker(new MakerImpl<T>());
			registration(type_name<T>(), objMaker);
		}
		
		void registration(const Key& key, MakerPtr& maker);
		bool isRegistered(const Key& key) const;

		
		template <class T>
		std::shared_ptr<T> make(const Key& key)
		{
			std::shared_ptr<Entity> ptr = do_make(key);
			return std::dynamic_pointer_cast<T>(ptr);
		}

		template <class T>
		std::shared_ptr<T> make()
		{
			return make(T::TypeName);
		}

    private:
		Factory(){}
		Factory(const Maker&);
		  
		std::shared_ptr<Entity> do_make(Key const& key);
		  
		typedef std::map<Key, MakerPtr> MakerRegistry;
		MakerRegistry _makers;
    };

}      
}

#define MDW_REGISTER_ENTITY_MAKER(type) toolbox::entity::Factory::instance().registration<type>())

