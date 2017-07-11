#include "LibraryManager.hpp"


////////////////////////////////////////////////////////////

namespace uhf {
namespace core {

    LibraryManager::LibraryManager()
    {

    }

    ////////////////////////////////////////////////////////////

    void LibraryManager::initialize(const std::list<std::string>& libraries)
    {
		m_libraries = libraries;
    }

    ////////////////////////////////////////////////////////////

    void LibraryManager::activate()
    {
		// Loading dynamic libraries
		//WTF_LOG_INFO("Process::initialize loading dynamic libraries [" << m_libraries.size() << "]");
		std::list<std::string >::const_iterator it;
		for(it  = m_libraries.begin(); it != m_libraries.end(); ++it)
		{
			Library loader(new LibLoaderObject());
			loader->init(it->c_str());
			m_loadedLibsList.push_back(loader);
		}				
    }

    ////////////////////////////////////////////////////////////

    void LibraryManager::deactivate()
    {
		m_loadedLibsList.clear();
    }

    ////////////////////////////////////////////////////////////

    std::list<Library> LibraryManager::getLoadedLibraries() const 
    { 
		return m_loadedLibsList;
	}
}
}
