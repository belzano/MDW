#pragma once

#include <string>
#include <memory>
#include <map>

namespace toolbox {

	namespace Registry
	{
		typedef std::string Key;
	}

	// Registry
	template <class BaseT>
	class BaseRegistry
	{
		public:
			std::shared_ptr<BaseT> get(const Registry::Key& key)
			{
				typename std::map<std::string, std::shared_ptr<BaseT> >::const_iterator it;
				it = _registered_objects.find(key);
				if (it == _registered_objects.end())
				{
					//MDW_LOG_DEBUG("Service not found ["<< key << "]");
					return std::shared_ptr<BaseT>((BaseT*)nullptr); 
				}	
				
				//MDW_LOG_DEBUG("Service found ["<< key << "]");
				return it->second;
			}

			void registration(const Registry::Key& key, 
							  std::shared_ptr<BaseT> theInstance)
			{			
				typename std::map<std::string, std::shared_ptr<BaseT> >::iterator it;
				it = _registered_objects.find(key);
				if (it != _registered_objects.end())
				{
					// Warning: overriding existing service
				}
				_registered_objects[key] = theInstance;
				//WTF_LOG_INFO("Service registration ["<< key << "] " );	
			}					

		private:
			std::map<Registry::Key, std::shared_ptr<BaseT > > _registered_objects;
	};
	
	// Registry with singleton 
	template <class BaseT>
	class SimpleRegistry : public BaseRegistry<BaseT>
	{
		public:		
			static SimpleRegistry<BaseT>& instance();
	};
	
	// Type name Registry
	template <class BaseT>
	class TypeNameRegistry : public BaseRegistry<BaseT>
	{
	public:
		template <class ExtendedT>
		std::shared_ptr<ExtendedT> getFromTypeName()
		{
			return get(ExtendedT::TypeName);
		}
		
		template <class ExtendedT>
		void registration(std::shared_ptr<ExtendedT> iInstance)
		{			
			Registry::Key registrationKey(ExtendedT::TypeName);
			std::shared_ptr<BaseT> downcastedInstance = std::dynamic_pointer_cast<BaseT>(iInstance);
			BaseRegistry<BaseT>::registration(registrationKey, downcastedInstance);
		}
	};

} 

// Macro to force registry singleton in cpp
#define WTF_REGISTRY_INSTANCIATION(BaseT)				\
namespace toolbox{							\
	template <> 							\
	SimpleRegistry<BaseT>& SimpleRegistry<BaseT>::instance()	\
	{								\
		static SimpleRegistry<BaseT> instance;			\
		return instance;					\
	}\
}


// Named object registration helpers
//////////////////////////////////////////////////////

namespace toolbox {	

	template <class BaseT, class ExtendedT>
	struct NamedObject
	{
		static std::string Name();
	};

	//////////////////////////////////////////////////////////////////////

	template<class BaseT, class ExtendedT>
	void registerNamedObject()
	{
		std::string theKey ( NamedObject<BaseT, ExtendedT>::Name() );
		SimpleRegistry< BaseT >::instance().registration(
			theKey, 
			std::shared_ptr<BaseT>((BaseT*) new ExtendedT() )
		);
	}
}

//////////////////////////////////////////////////////////////////////

#define WTF_REGISTRY_DO_REGISTRATION(BaseT, ExtendedT, key)\
namespace toolbox{\
	template<>\
	struct NamedObject< BaseT, ExtendedT>\
	{\
		static std::string Name() { return std::string("" #key "" );}\
	};\
}\
void (*loader##__FILENAME__##__LINE__/*##BaseT##ExtendedT*/)(void) __attribute__ ((section (".ctors"))) \
			= toolbox::registerNamedObject<BaseT, ExtendedT>;

//////////////////////////////////////////////////////////////////////

#define WTF_REGISTRY_DO_REGISTRATION_AUTO(BaseT, ExtendedT)\
WTF_REGISTRY_DO_REGISTRATION(BaseT, ExtendedT, "" #BaseT "#" #ExtendedT "")
