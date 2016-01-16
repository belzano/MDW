#include "toolbox/Logger.hpp"

#include <iostream>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>

using namespace toolbox;


//Format
// TS - PID - TID - LVL - FUNCT_TOKEN - MSG
std::ostream& Logger::log(LogType level) 
{	 
	std::ostream& out = std::cout;
	std::string sep = " ";
	
	// TS

	boost::posix_time::ptime now = boost::posix_time::second_clock::universal_time(); 
	out << now.time_of_day();	
	out << sep;
		
	// PID
	//out << "#PID#";
	//out << sep;
	
	// TID
	//out << "#TID#";	
	//out << sep;
	
	// LEVEL	
	switch(level)
	{
		case Debug:
			out << "DEBUG";
		break;
		case Stat:
			out << "STATS";
		break;
		case Perf:
			out << "PERFS";
		break;
		case Info:
			out << "INFOS";
		break;
		case Warning:
			out << "WARNG";
		break;
		case Error:
			out << "ERROR";
		break;
		case Fatal:
			out << "FATAL";
		break;
	}
	out << sep;
		
	return out;	
}

//////////////////////////////////////

std::shared_ptr<Logger> Logger::instance()
{
	static std::shared_ptr<Logger> s_instance = std::shared_ptr<Logger>(new Logger());
	return s_instance;	
}

///////////////////////////////////////

toolbox::ScopedContext::ScopedContext(const std::string& iToken) 
						MDW_DEBUG_ONLY(:_sectionChrono(iToken)) 
{
	// ctor push in context and create a scoped chrono	
	getContext().push_back(iToken);
}

toolbox::ScopedContext::~ScopedContext()
{
	// dtor pop context and log the scoped chrono
	getContext().pop_back();
}

///////////////////////////////////////

std::deque<std::string>& toolbox::ScopedContext::getContext()
{
	static std::deque<std::string> g_context;
	return g_context;
}
		
///////////////////////////////////////

std::string toolbox::ScopedContext::currentContext()
{
	if (getContext().empty())
	{
		return std::string("");
	}
	
	std::string currentCtx(" [");

	// CONTEXT
	std::deque<std::string>::const_iterator dequeIt;
	for(dequeIt  = getContext().begin();
		dequeIt != getContext().end();
		++dequeIt)
	{
		if (dequeIt != getContext().begin())
			currentCtx += "_";
		currentCtx += *dequeIt;
	}
	currentCtx += "]";
	
	return currentCtx;	
}
