#pragma once

#include <string>

namespace logger
{
	class Scope
	{
	public:
		// ctor push in stack
		Scope(const std::string&);
	
		// dtor pop stack
		~Scope();
	};
	
}

