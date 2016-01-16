#pragma once

#include "toolbox/Types.hpp"

namespace toolbox
{

class StorageCell
{
	public:
		StorageCell() {}
		virtual ~StorageCell(){}
		
		virtual bool dataExists(const DataKey & hashkey) = 0;
        virtual bool dataSet(const DataKey & hashkey, const DataPtr) = 0;     
        virtual DataPtr dataGet(const DataKey & hashkey) = 0;
};

typedef std::shared_ptr<StorageCell> StorageCellPtr;

}


