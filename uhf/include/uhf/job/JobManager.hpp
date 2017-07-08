#pragma once

#include "uhf/job/Types.hpp"
#include "uhf/job/Job.hpp"

#include <memory>

namespace job
{

class JobManager
{
	public:
	
		JobManager( const std::string& queue_name,
					const std::string& job_storage)
		{
			_queue_name = queue_name;
			_job_storage = job_storage;
		}
	
		Job create();
		JobPtr get(const JobId& iId);
		
		JobPtr tryDequeue();
		bool queue(const Job& iJob);
	
	private:
		
		JobId createJobId();
	
		std::string _queue_name;
		std::string _job_storage;
};

}
