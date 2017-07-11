#pragma once

#include "Library.hpp"
#include <list>
#include <string>


namespace uhf {
namespace core {
	
/////////////////////////////////////////////////////////////////////
	
class LibraryManager
{
public:
    LibraryManager();

    virtual void initialize(const std::list<std::string>&);
    virtual void activate();
    virtual void deactivate();
    
    std::list<Library> getLoadedLibraries() const ;

private:
    std::list<std::string>  m_libraries;
    std::list<Library>      m_loadedLibsList;
};

}
}
