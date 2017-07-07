
#include "kvs/component/EnvVar.hpp"
#include "toolbox/Logger.hpp"

#include <fstream>
#include <iostream>
#include <iterator>

namespace uhf {
namespace component {
namespace kvs {

	EnvVar::EnvVar()
	{}

	//////////////////////////////////////////////////////////////////
	
	bool EnvVar::dataExists(const DataKey & hashkey)
	{
		const char* envVar = ::getenv(hashkey.c_str());
		return (envVar != NULL);	
	}

	//////////////////////////////////////////////////////////////////
	
	bool EnvVar::dataSet(const DataKey & hashkey, DataPtr iData)
	{ 
		::setenv(hashkey.c_str(), iData->data(), iData->size());
		return true;
	}     

	//////////////////////////////////////////////////////////////////
	
	DataPtr EnvVar::dataGet(const DataKey & hashkey)
	{
		const char* envVar = ::getenv(hashkey.c_str());
		if (envVar != NULL){
			//MDW_LOG_DEBUG("Read var " << hashkey << ":" << envVar);
			return toolbox::MakeDataPtr(envVar);
		}
		return DataPtr((Data*)NULL);
	}   

	//////////////////////////////////////////////////////////////////
			
}
}
}
