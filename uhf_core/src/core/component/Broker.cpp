#include "uhf/core/component/Broker.hpp"

////////////////////////////////////////////////////////////

namespace uhf {
namespace core {
namespace component {
	
Broker::Broker()
{

}

//---------------------------------------------------------

Broker::~Broker()
{

}	
	
//---------------------------------------------------------
void Broker::registerComponentInstance(const std::string& componentName, IComponentPtr component)
{
    m_components.insert({componentName, component});
}

//---------------------------------------------------------
IComponentPtr Broker::getComponentInstance(const std::string& componentTypeName)
{
    auto findIt = m_components.find(componentTypeName);
    if (findIt == m_components.end())
      return IComponentPtr(nullptr);

    return findIt->second;
}

//---------------------------------------------------------
void Broker::getComponents(std::list<IComponentPtr>& components)
{
    for(auto pair : m_components)
	components.push_back(pair.second);
}


}
}
}
