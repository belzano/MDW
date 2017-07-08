
#include "kvs/component/LocalMemory.hpp"

#include <fstream>
#include <iostream>
#include <iterator>

namespace uhf {
namespace kvs {
namespace component {	

	LocalMemory::LocalMemory()
	{}

	bool LocalMemory::dataExists(const DataKey & hashkey)
	{
		return (_data.find(hashkey) != _data.end());
	}

	bool LocalMemory::dataSet(const DataKey & hashkey, DataPtr iData)
	{ 
		_data[hashkey] = iData;
		return true;	
	}     

	DataPtr LocalMemory::dataGet(const DataKey & hashkey)
	{
		std::map<DataKey, DataPtr>::iterator it = _data.find(hashkey);
		if (it == _data.end())
			return DataPtr((Data*)NULL);

		return it->second;
	}   
			
}
}
}
