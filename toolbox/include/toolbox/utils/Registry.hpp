#pragma once

#include <string>
#include <memory>
#include <map>

#include "toolbox/Typename.hpp"

namespace toolbox {

	// Registry
	template <class KeyT, class BaseT>
	class BaseRegistry
	{
		public:
			std::shared_ptr<BaseT> get(const KeyT& key) const
			{
				typename std::map<std::string, std::shared_ptr<BaseT> >::const_iterator it;
				it = _registered_objects.find(key);
				if (it == _registered_objects.end())
				{
					return std::shared_ptr<BaseT>((BaseT*)nullptr); 
				}	
				
				return it->second;
			}

			void put(const KeyT& key, 
					 std::shared_ptr<BaseT> theInstance)
			{			
				typename std::map<KeyT, std::shared_ptr<BaseT> >::iterator it;
				it = _registered_objects.find(key);
				if (it != _registered_objects.end())
				{
					// ? Warning: overriding existing instance
				}
				_registered_objects[key] = theInstance;
			}					

		private:
			std::map<KeyT, std::shared_ptr<BaseT > > _registered_objects;
	};
	
	///////////////////////////////////////////////////////////////////
	
	template <class KeyT, class BaseT, class ExtendedT>
	KeyT getTypename() 
	{
		return ::type_name<ExtendedT>();
	}
	
	///////////////////////////////////////////////////////////////////

	template <class KeyT, class BaseT>
	class TypeNameRegistry : public BaseRegistry<KeyT, BaseT>
	{
	public:
		std::shared_ptr<BaseT> get(const KeyT& key) const
		{
			return BaseRegistry<KeyT, BaseT>::get(key);
		}
		
		void put(const KeyT& key, 
			     std::shared_ptr<BaseT> instance)
		{
			BaseRegistry<KeyT, BaseT>::put(key, instance);			 
		}
		
		template <class ExtendedT>
		std::shared_ptr<ExtendedT> get() const
		{
			KeyT key = getTypename<KeyT, BaseT, ExtendedT>();
			BaseT instance = BaseRegistry<KeyT, BaseT>::get(key);
			std::shared_ptr<ExtendedT> upcastedInstance = std::dynamic_pointer_cast<ExtendedT>(instance);
			return upcastedInstance;
		}
		
		template <class ExtendedT>
		void put(std::shared_ptr<ExtendedT> iInstance)
		{			
			KeyT key = getTypename<KeyT, BaseT, ExtendedT>();
			std::shared_ptr<BaseT> downcastedInstance = std::dynamic_pointer_cast<BaseT>(iInstance);
			BaseRegistry<KeyT, BaseT>::put(key, downcastedInstance);
		}
	};

} 

