#include "logger/Scope.hpp"
#include "ThreadContext.hpp"
#include <iostream>
using namespace logger;

///////////////////////////////////////

Scope::Scope(const std::string& iToken)
{
	// ctor push in context and create a scoped chrono	
	logger::ThreadContext::ThreadInstance().getStack().push_back(iToken);
}

Scope::~Scope()
{
	// dtor pop context and log the scoped chrono
	logger::ThreadContext::ThreadInstance().getStack().pop_back();
}
