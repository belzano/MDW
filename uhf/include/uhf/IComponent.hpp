#pragma once

#include <string>
#include "toolbox/Types.hpp"
#include "toolbox/Typename.hpp"
//#include "toolbox/utils/Registry.hpp"

#include "uhf/IProperty.hpp"
#include "uhf/IComponentConfiguration.hpp"

namespace  uhf {

    class IComponentRegistry;
      
    typedef std::string ComponentTypeName;  
      
    class IComponent
    {
    public:

		// ctor
		IComponent();

		// Initialization
		void setComponentRegistry(std::shared_ptr<IComponentRegistry>);
		virtual void initialize(IComponentConfigurationPtr) {}
		
		void initialize();
		
		// Activation
		void activate();
		void deactivate();
		// dtor
		virtual ~IComponent();

		template <class T>
		static ComponentTypeName getTypename() {
		    return type_name<T>();
		}
		
		virtual ComponentTypeName getTypename() {
		    return type_name<decltype(*this)>();
		}

    protected:	
		virtual void onInitialize();
		virtual void onActivate();
		virtual void onDeactivate();

		std::shared_ptr<IComponentRegistry> getComponentRegistry() { return m_componentRegistry;}
		std::shared_ptr<IComponentRegistry> m_componentRegistry;
/*
    public:		
		template <class T>
		bool hasProperty()				{ return getProperty(T::TypeName).get() != nullptr;}
		bool hasProperty(const std::string& iTypeName)	{ return getProperty(iTypeName).get() != nullptr;}

		template <class T>
		IPropertyPtr getProperty()			{ return m_properties.get(T::TypeName);}
		IPropertyPtr getProperty(const std::string& iTypeName) { return m_properties.get(iTypeName);}		

    private:
		toolbox::TypeNameRegistry<IProperty> m_properties;
*/
    };

    typedef std::shared_ptr<IComponent> IComponentPtr;
    


}
