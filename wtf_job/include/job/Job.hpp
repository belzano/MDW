 #pragma once


#include "toolbox/StorageCell.hpp"
#include "job/Types.hpp"
#include <memory>


namespace job
{

class Job 
{
	public:
		Job(JobId id, std::shared_ptr<toolbox::StorageCell> storage)
		{
			_key = id;
			_storage = storage;
		}
	
		JobId getKey() const;
		
		std::shared_ptr<toolbox::StorageCell> getStorage();
		
	private:	
		std::shared_ptr<toolbox::StorageCell> _storage;
		JobId _key;
};

typedef std::shared_ptr<job::Job> JobPtr;

}
