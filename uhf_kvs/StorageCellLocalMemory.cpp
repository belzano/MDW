
#include "toolbox/StorageCellLocalMemory.hpp"

#include <fstream>
#include <iostream>
#include <iterator>

namespace toolbox
{

StorageCellLocalMemory::StorageCellLocalMemory()
{}

bool StorageCellLocalMemory::dataExists(const DataKey & hashkey)
{
	return (_data.find(hashkey) != _data.end());
}

bool StorageCellLocalMemory::dataSet(const DataKey & hashkey, DataPtr iData)
{ 
	_data[hashkey] = iData;
	return true;	
}     

DataPtr StorageCellLocalMemory::dataGet(const DataKey & hashkey)
{
	std::map<DataKey, DataPtr>::iterator it = _data.find(hashkey);
	if (it == _data.end())
		return DataPtr((Data*)NULL);

	return it->second;
 }   
        
}
