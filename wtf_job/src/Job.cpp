
#include "job/Job.hpp"

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

std::shared_ptr<toolbox::StorageCell> Job::getStorage()
{
	return _storage;
}
	
}
