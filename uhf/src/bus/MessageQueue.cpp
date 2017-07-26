
#include "MessageQueue.hpp"

#include "toolbox/Logger.hpp"
#include "toolbox/Base64.hpp"

#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <sys/types.h>
#include <unistd.h>

#define MAX_MSG_SIZE 255
#define MAX_MSG_COUNT 100


namespace uhf {
namespace bus {
	
////////////////////////////////////////////////////////////////////

MessageQueue::MessageQueue(const std::string& name)
	: _name(name)
	, _maxMsgSize(MAX_MSG_SIZE)
	, _maxQueueSize(MAX_MSG_COUNT)
{

}
 	
////////////////////////////////////////////////////////////////////
	
DataPtr MessageQueue::tryDequeue()
{
	// In reader process open queue for reading:
	mqd_t queue = mq_open(_name.c_str(), 
							O_RDONLY | O_NONBLOCK);
	 
	// Size of buffer *must be greater than the mq_msgsize attribute of the queue.
	DataPtr message(new toolbox::Data(_maxMsgSize + 1));
	char* rcvbuf = message->data();
	mqd_t ret = mq_receive( queue, rcvbuf, _maxMsgSize+1, NULL);
	
	// switch iret
	if (ret == (mqd_t) - 1)
		return DataPtr(nullptr);
	
	return message;
}
		
////////////////////////////////////////////////////////////////////
	
bool MessageQueue::queue(DataPtr message)
{
	if (message.get() == nullptr)
		return false;
	
	const char* data = message->data();
		
	//Fill mq_attr struct (doc):
	struct mq_attr attr;  
	attr.mq_flags = 0;  
	attr.mq_maxmsg = _maxQueueSize;
	attr.mq_msgsize = _maxMsgSize;  
	attr.mq_curmsgs = 0;  
	
	//In writer process open queue for writing:
	mqd_t queue = mq_open(_name.c_str(),
						  O_CREAT|O_WRONLY|O_NONBLOCK, 0644, &attr);

	// And send some text. 
	//Length of the text must be lesser than mq_msgsize attribute of the queue (doc):
	int ret = mq_send(queue, data, strlen(data) + 1, 1);
	if (ret == EAGAIN)
		return false;
		
	return true;
}

////////////////////////////////////////////////////////////////////
	
}
}

	/*
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
* */
