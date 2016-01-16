#pragma once

#include "Macros.hpp"
#include "Types.hpp"
#include "ScopedChrono.hpp"

#include <deque>
#include <memory>
#include <ostream>
#include <sstream>


namespace toolbox
{

class Logger 
{
	public:

	typedef enum
	{
		Debug,
		Stat,
		Perf,
		Info,
		Warning,
		Error,
		Fatal
	} 
	LogType;

	//Format
	// TS - PID - TID - LVL - FUNCT_TOKEN - MSG
	std::ostream& log(LogType);
	
	// TODO make per thread unique instance
	static std::shared_ptr<Logger> instance();
	
private:

	//U64 m_pid;
	//U64 m_tid;

};

	class ScopedContext
	{
	public:
		// ctor push in context
		ScopedContext(const std::string&);
	
		// dtor pop context
		~ScopedContext();
		
		static std::string currentContext();

		// TODO make per thread unique instance
		static std::deque<std::string>& getContext();	
		
	private:

		MDW_DEBUG_ONLY(ScopedChrono _sectionChrono;)
	};
	
}

#define MDW_LOGGER_CONTENT(xxx) BUILD_MODULE << toolbox::ScopedContext::currentContext() << " " << BUILD_FILENAME << " " << xxx << std::endl

#ifdef MDW_DEBUG
#define MDW_LOG_DEBUG(xxx) 		toolbox::Logger::instance()->log(toolbox::Logger::Debug) 	<< MDW_LOGGER_CONTENT(xxx);
#else
#define MDW_LOG_DEBUG(xxx) 
#endif 

#define MDW_LOG_STAT(xxx)  		toolbox::Logger::instance()->log(toolbox::Logger::Stat)		<< MDW_LOGGER_CONTENT(xxx);
#define MDW_LOG_PERF(xxx)  		toolbox::Logger::instance()->log(toolbox::Logger::Perf)		<< MDW_LOGGER_CONTENT(xxx);
#define MDW_LOG_INFO(xxx) 		toolbox::Logger::instance()->log(toolbox::Logger::Info) 	<< MDW_LOGGER_CONTENT(xxx);
#define MDW_LOG_WARNING(xxx) 	toolbox::Logger::instance()->log(toolbox::Logger::Warning) 	<< MDW_LOGGER_CONTENT(xxx);
#define MDW_LOG_ERROR(xxx) 		toolbox::Logger::instance()->log(toolbox::Logger::Error) 	<< MDW_LOGGER_CONTENT(xxx);
#define MDW_LOG_FATAL(xxx)		toolbox::Logger::instance()->log(toolbox::Logger::Fatal) 	<< MDW_LOGGER_CONTENT(xxx);


#define MDW_LOG_CONTEXT(xxx) \
std::stringstream COMBINE(context, _LINE_); \
COMBINE(context, _LINE_) << xxx; \
toolbox::ScopedContext COMBINE(scopeLoggingObj,__LINE__)( COMBINE(context, _LINE_).str());

#define MDW_LOG_SCOPE_CHRONO(xxx) \
std::stringstream COMBINE(context, _LINE_); \
COMBINE(context, _LINE_) << xxx; \
toolbox::ScopedChrono COMBINE(scopeLoggingObj,__LINE__)( COMBINE(context, _LINE_).str());

