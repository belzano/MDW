#pragma once

#include "toolbox/StorageCell.hpp"

namespace toolbox
{

class StorageCellFileSystem
{
	public:
		StorageCellFileSystem(const std::string& rootPath);
		virtual ~StorageCellFileSystem(){}
		
		virtual bool dataExists(const DataKey & hashkey) ;
        virtual bool dataSet(const DataKey & hashkey, DataPtr) ;     
        virtual DataPtr dataGet(const DataKey & hashkey) ;

        
    private:
		std::string _rootPath;
    
};

}
