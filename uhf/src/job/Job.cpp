
#include "uhf/job/Job.hpp"

#include <fstream>
#include <iostream>
#include <iterator>

namespace job
{

JobId Job::getKey() const
{
	return _key;
}
	
//////////////////////////////////////////////////////////////


uhf::kvs::component::KeyValueStoragePtr Job::getStorage()
{
	return _storage;
}
	
}
