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
			return typeid(*this).name();
		    //return type_name<decltype(*this)>();
		}
		
		virtual bool equals(std::shared_ptr<IProperty> other) const = 0; 
		
		virtual bool checkConsistency(std::shared_ptr<uhf::IComponent>) const { return true; }

		virtual std::ostream& toStream(std::ostream& stream) const ;

	};
	
	typedef std::shared_ptr<IProperty> IPropertyPtr;
	
}

