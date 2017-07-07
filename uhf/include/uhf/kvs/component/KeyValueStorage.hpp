#pragma once

#include "toolbox/Types.hpp"
#include "uhf/IComponent.hpp"

namespace uhf {
namespace component {
namespace kvs {

	typedef toolbox::DataKey DataKey;
	typedef toolbox::DataPtr DataPtr;
	typedef toolbox::Data Data;

	class KeyValueStorage : public uhf::IComponent
	{
		public:
			KeyValueStorage() {}
			virtual ~KeyValueStorage(){}
			
			virtual bool dataExists(const DataKey & hashkey) = 0;
			virtual bool dataSet(const DataKey & hashkey, const DataPtr) = 0;     
			virtual DataPtr dataGet(const DataKey & hashkey) = 0;
	};

	typedef std::shared_ptr<KeyValueStorage> KeyValueStoragePtr;

}
}
}


