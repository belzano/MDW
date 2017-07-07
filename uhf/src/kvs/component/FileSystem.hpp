#pragma once

#include "uhf/kvs/component/KeyValueStorage.hpp"

namespace uhf {
namespace component {
namespace kvs {

	class FileSystem : public KeyValueStorage
	{
		public:
			FileSystem(){}
			FileSystem(const std::string& rootPath);
			virtual ~FileSystem(){}
			
			virtual bool dataExists(const DataKey & hashkey) ;
			virtual bool dataSet(const DataKey & hashkey, DataPtr) ;     
			virtual DataPtr dataGet(const DataKey & hashkey) ;
			
		private:
			std::string _rootPath;
	};
}
}
}
