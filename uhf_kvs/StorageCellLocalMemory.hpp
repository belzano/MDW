#pragma once

#include <map>
#include "toolbox/StorageCell.hpp"

namespace toolbox
{

class StorageCellLocalMemory : public StorageCell
{
	public:
		StorageCellLocalMemory();
		virtual ~StorageCellLocalMemory(){}
		
		virtual bool dataExists(const DataKey & hashkey);
        virtual bool dataSet(const DataKey & hashkey, DataPtr) ;     
        virtual DataPtr dataGet(const DataKey & hashkey)  ;

        std::map<DataKey, DataPtr> 			_data;
};

}
