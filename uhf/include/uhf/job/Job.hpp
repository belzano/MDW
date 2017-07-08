 #pragma once


#include "uhf/kvs/component/KeyValueStorage.hpp"
#include "uhf/job/Types.hpp"
#include <memory>


namespace job
{

class Job 
{
	public:
		Job(JobId id, uhf::kvs::component::KeyValueStoragePtr storage)
		{
			_key = id;
			_storage = storage;
		}
	
		JobId getKey() const;
		
		uhf::kvs::component::KeyValueStoragePtr getStorage();
		
	private:	
		uhf::kvs::component::KeyValueStoragePtr _storage;
		JobId _key;
};

typedef std::shared_ptr<job::Job> JobPtr;

}
