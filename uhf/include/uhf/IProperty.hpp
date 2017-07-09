#pragma once

#include <string>
#include <list>
#include "toolbox/Types.hpp"
#include "toolbox/Typename.hpp"
//#include "uhf/IComponent.hpp"

namespace  uhf {
		
	class IComponent;
	typedef std::string PropertyTypeName;	
		
	class IProperty
	{
	public:		
		// ctor
		IProperty();
		// dtor
		virtual ~IProperty();
		
		template <class T>
		static PropertyTypeName getTypename() {
		    return type_name<T>();
		}
		
		virtual PropertyTypeName getTypename() {
		    return type_name<decltype(*this)>();
		}
		
		// Try to cast and hope?
		//template<class T>
		//bool isA() const { return isA(T::getTypename());} 

		
		virtual bool checkConsistency(std::shared_ptr<uhf::IComponent>) const { return true; }

	};
	
	typedef std::shared_ptr<IProperty> IPropertyPtr;
	
}

