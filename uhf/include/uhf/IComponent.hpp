#pragma once

#include <string>
#include "toolbox/Types.hpp"
#include "toolbox/utils/Registry.hpp"


#include "uhf/IProperty.hpp"

namespace  uhf {

    class IBroker;
      
    class IComponent
    {
    public:

	// ctor
	IComponent(std::shared_ptr<IBroker>);

	// Initialization
	void initialize();
	// Activation
	void activate();
	void deactivate();
	// dtor
	virtual ~IComponent();

    protected:	
	virtual void onInitialize();
	virtual void onActivate();
	virtual void onDeactivate();

	std::shared_ptr<IBroker> getBroker() { return m_broker;}
	std::shared_ptr<IBroker> m_broker;

    public:		
	template <class T>
	bool hasProperty()				{ return getProperty(T::TypeName).get() != nullptr;}
	bool hasProperty(const std::string& iTypeName)	{ return getProperty(iTypeName).get() != nullptr;}

	template <class T>
	IPropertyPtr getProperty()			{ return m_properties.get(T::TypeName);}
	IPropertyPtr getProperty(const std::string& iTypeName) { return m_properties.get(iTypeName);}		

    private:
	toolbox::TypeNameRegistry<IProperty> m_properties;

    };

    typedef std::shared_ptr<IComponent> IComponentPtr;
}
