#pragma once

#include "uhf/kvs/component/KeyValueStorage.hpp"

namespace uhf {
namespace component {
namespace kvs {

	class EnvVar : public KeyValueStorage
	{
		public:
			EnvVar();
			virtual ~EnvVar(){}
			
			virtual bool dataExists(const DataKey & hashkey);
			virtual bool dataSet(const DataKey & hashkey, DataPtr) ;     
			virtual DataPtr dataGet(const DataKey & hashkey)  ;
	};

}
}
}
