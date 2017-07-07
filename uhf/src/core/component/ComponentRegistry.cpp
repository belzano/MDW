#include "uhf/core/component/ComponentRegistry.hpp"

////////////////////////////////////////////////////////////

namespace uhf {
namespace component {
	
ComponentRegistry::ComponentRegistry()
{

}

//---------------------------------------------------------

ComponentRegistry::~ComponentRegistry()
{

}	
	
//---------------------------------------------------------
void ComponentRegistry::registerComponentInstance(const std::string& componentName, IComponentPtr component)
{
    m_components.insert({componentName, component});
}

//---------------------------------------------------------
IComponentPtr ComponentRegistry::getComponentInstance(const std::string& componentTypeName)
{
    auto findIt = m_components.find(componentTypeName);
    if (findIt == m_components.end())
      return IComponentPtr(nullptr);

    return findIt->second;
}

//---------------------------------------------------------
void ComponentRegistry::getComponents(std::list<IComponentPtr>& components)
{
    for(auto pair : m_components)
	components.push_back(pair.second);
}


}
}
