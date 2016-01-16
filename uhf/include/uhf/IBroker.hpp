#pragma once

#include "uhf/IComponent.hpp"
#include <list>


namespace uhf {

/////////////////////////////////////////////////////////////////////

class IBroker
{
public:
    IBroker();
    virtual ~IBroker();

    virtual void getComponents(std::list<IComponentPtr>& components) = 0;
    
    template<class ComponentT>
    void registerComponent(std::shared_ptr<ComponentT> component) 
    { 
	registerComponentInstance(ComponentT::TypeName, std::dynamic_pointer_cast<IComponent>(component));
    }
    
    template<class ComponentT>
    std::shared_ptr<ComponentT> getComponentInstance() 
    { 
	IComponentPtr ptr = getComponentInstance(ComponentT::TypeName);
	std::shared_ptr<ComponentT> typed_ptr = std::dynamic_pointer_cast<ComponentT>(ptr);
	return typed_ptr;
    }
    
protected:
    virtual IComponentPtr getComponentInstance(const std::string& componentName) = 0;
    virtual void registerComponentInstance(const std::string& componentName, IComponentPtr component) = 0;
        

};
typedef std::shared_ptr<IBroker> IBrokerPtr;

///////////////////////////////////////////////////////////////////////////////////////


}
