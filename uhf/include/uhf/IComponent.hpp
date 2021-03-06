#pragma once

#include <string>
#include <list>
#include "toolbox/Types.hpp"
#include "toolbox/Typename.hpp"
//#include "toolbox/utils/Registry.hpp"

#include "uhf/IObject.hpp"
#include "uhf/IProperty.hpp"
#include "uhf/IComponentConfiguration.hpp"

namespace  uhf {

    class IComponentRegistry;
      
    typedef std::string ComponentTypeName;  
      
    class IComponent : public IObject
    {
    public:
		IComponent();
		virtual ~IComponent();

		template <class T>
		static ComponentTypeName getTypename() {
		    return type_name<T>();
		}
		
		virtual ComponentTypeName getTypename() {
		    return type_name<decltype(*this)>();
		}

		template<class T>
		bool isA() const { 
			std::shared_ptr<T> ptr = std::dynamic_pointer_cast<T>(this);
			return ptr != nullptr;
		}

	// Initialization
	public:
		bool initialize(std::shared_ptr<IComponent> iThis,
		                std::shared_ptr<IComponentRegistry> registry, 
		                std::list<IPropertyPtr> properties,
		                std::list<IObjectPtr> dependencies,
		                IComponentConfigurationPtr config);
		bool isInitialized() const { return m_isInitialized; }
	protected:
		virtual void onInitialize() {}

	private: 
		bool m_isInitialized;
		
	// Component registry
    protected:
		std::shared_ptr<IComponentRegistry> getComponentRegistry() { return m_componentRegistry;}
		std::shared_ptr<IComponentRegistry> m_componentRegistry;
	
	// Properties
    public:	
		template <class T>
		bool hasProperty() { return hasProperty(IProperty::getTypename<T>());}
		bool hasProperty(const std::string& iTypeName);
		bool hasProperty(const IPropertyPtr iProperty);

		template <class T>
		IPropertyPtr getProperty() { return getProperty(IProperty::getTypename<T>());}
		IPropertyPtr getProperty(const std::string& iTypeName);	
		IPropertyPtr getProperty(const IPropertyPtr iProperty);

		std::list<IPropertyPtr> getProperties() { return m_properties;}

    private:
		std::list<IPropertyPtr> m_properties;

	// Component configuration
    protected:
		IComponentConfigurationPtr getConfiguration() { return m_configuration;}
	private:
		IComponentConfigurationPtr m_configuration;

	// Component dependencies
		std::list<IObjectPtr> getDependencies() const { return m_dependencies;}

    private:
		std::list<IObjectPtr> m_dependencies;
    };

    typedef std::shared_ptr<IComponent> IComponentPtr;
}
