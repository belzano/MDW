#pragma once

#include "uhf/kvs/component/KeyValueStorage.hpp"
#include <map>

namespace uhf {
namespace kvs {
namespace component {	

	class LocalMemory : public KeyValueStorage
	{
		public:
			LocalMemory();
			virtual ~LocalMemory(){}
			
			virtual bool dataExists(const DataKey & hashkey);
			virtual bool dataSet(const DataKey & hashkey, DataPtr) ;     
			virtual DataPtr dataGet(const DataKey & hashkey)  ;

			std::map<DataKey, DataPtr> _data;
	};
}
}
}
