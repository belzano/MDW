#pragma once

#include "LibLoader.hpp"
#include <list>
#include <string>


namespace uhf {
namespace core {
	
/////////////////////////////////////////////////////////////////////
	
class LibraryManager
{
public:
    constexpr static const char* TypeName = "uhf::core::LibraryManager";

    LibraryManager();

    virtual void initialize(const std::list<std::string>&);
    virtual void activate();
    virtual void deactivate();

private:
    std::list<std::string>  m_libraries;
    std::list<LibLoader>    m_loadedLibsList;
};

}
}
