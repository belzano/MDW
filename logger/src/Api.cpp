#include "logger/Api.hpp"
#include "logger/Stream.hpp"
#include "logger/Stack.hpp"
#include "ThreadContext.hpp"

logger::Stream& logger::Api::ThreadInstance()
{
	return logger::ThreadContext::ThreadInstance().getLogStream();
}

logger::Stack& logger::Api::ThreadStack()
{
	return logger::ThreadContext::ThreadInstance().getStack();
}
