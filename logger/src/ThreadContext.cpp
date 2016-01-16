#include "ThreadContext.hpp"
#include "logger/Stream.hpp"

#include <boost/thread/tss.hpp>

using namespace logger;

////////////////////////////////////////

static boost::thread_specific_ptr<ThreadContext> threadContext;

ThreadContext& ThreadContext::ThreadInstance()
{
	if( ! threadContext.get() )
	{
		// first time called by this thread
		threadContext.reset( new ThreadContext());
	}
	
	return *threadContext.get();
}

////////////////////////////////////////

ThreadContext::ThreadContext()
{
	_logStream = nullptr;
}
			
////////////////////////////////////////

Stream& ThreadContext::getLogStream()
{	
	if (_logStream == nullptr)
	{
		_logStream = new Stream();
	}
	
	return *_logStream;
}

////////////////////////////////////////
			
Stack& ThreadContext::getStack() 
{
	return _stack;
}
