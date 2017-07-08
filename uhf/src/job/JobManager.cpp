
#include "uhf/job/JobManager.hpp"
#include "uhf/job/Job.hpp"

#include "uhf/kvs/component/KeyValueStorage.hpp"
#include "toolbox/Logger.hpp"
#include "toolbox/Base64.hpp"

#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <sys/types.h>
#include <unistd.h>

#define MAX_QUEUE_MSG_SIZE 64

using uhf::kvs::component::KeyValueStorage;
using uhf::kvs::component::KeyValueStoragePtr;

namespace job
{

////////////////////////////////////////////////////////////////////
	
JobId JobManager::createJobId()
{       
	// Stream in hex mode
    std::stringstream stream;
    stream << std::hex ;
     
    // get the timestamp
	stream << clock();
    // get process ID by calling getpid(), the return value of which is an integer.
 	stream << getpid();
	// get thread ID by calling pthread_self(), the return value of which is an opaque type called pthread_t 
	stream << pthread_self();
  
  
	JobId theJobId(stream.str());    
    return theJobId;
} 
 
////////////////////////////////////////////////////////////////////
	
Job JobManager::create()
{
	const JobId jobId = createJobId();
    MDW_LOG_DEBUG("Generated JobId ["<< jobId << "]");
    
	std::string cellPath = _job_storage + jobId + "/";
	//StorageCell* storagePtr = new StorageCellFileSystem(cellPath);
	//std::shared_ptr<StorageCell> storage((StorageCell*) new StorageCellFileSystem(cellPath));
	return Job(jobId, KeyValueStoragePtr(nullptr));
}
		
////////////////////////////////////////////////////////////////////
/*	
Job JobManager::get(const JobId& jobId)
{
	// TODO chek if not already existing
	std::string cellPath = _job_storage + jobId + "/";
	std::shared_ptr<StorageCell> storage((StorageCell*) new StorageCellFileSystem(cellPath));
	return Job(jobId, storage);
}	
*/
////////////////////////////////////////////////////////////////////
	
JobPtr JobManager::get(const JobId& jobId)
{
	// TODO chek if not already existing
	std::string cellPath = _job_storage + jobId + "/";
	//std::shared_ptr<StorageCell> storage((StorageCell*) new StorageCellFileSystem(cellPath));
	return JobPtr( new Job(jobId, KeyValueStoragePtr(nullptr)));
}	
		
////////////////////////////////////////////////////////////////////
	
JobPtr JobManager::tryDequeue()
{
	// In reader process open queue for reading:
	mqd_t queue = mq_open(_queue_name.c_str(), O_RDONLY | O_NONBLOCK);
	 
	// Size of buffer *must be greater than the mq_msgsize attribute of the queue.
	char rcvbuf[MAX_QUEUE_MSG_SIZE+1];
	mqd_t ret = mq_receive( queue, rcvbuf, MAX_QUEUE_MSG_SIZE+1, NULL);
	
	// switch iret
	if (ret == (mqd_t) -1)
		return JobPtr(nullptr);
	
	JobId theJobId = std::string(rcvbuf);
    MDW_LOG_DEBUG("Dequeued JobId ["<< theJobId << "]");
    	
	return get(theJobId);
}
		
////////////////////////////////////////////////////////////////////
	
bool JobManager::queue(const Job& iJob)
{
	if (iJob.getKey() == "")
		return false;
	
	const char* msg = iJob.getKey().c_str();
		
	//Fill mq_attr struct (doc):
	struct mq_attr attr;  
	attr.mq_flags = 0;  
	attr.mq_maxmsg = 100;  // max 100 items in queue
	attr.mq_msgsize = MAX_QUEUE_MSG_SIZE;  
	attr.mq_curmsgs = 0;  
	
	//In writer process open queue for writing:
	mqd_t queue = mq_open(  _queue_name.c_str(),
							O_CREAT|O_WRONLY|O_NONBLOCK, 0644, &attr);

	// And send some text. 
	//Length of the text must be lesser than mq_msgsize attribute of the queue (doc):
	int ret = mq_send(queue, msg, strlen(msg)+1, 1);
	if (ret == EAGAIN)
		return false;
		
    MDW_LOG_DEBUG("Queued JobId ["<< iJob.getKey() << "]");
    	
	return true;
}

////////////////////////////////////////////////////////////////////
	
}
