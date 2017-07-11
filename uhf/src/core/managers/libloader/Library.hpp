#pragma once

#include <memory>
#include "uhf/IObject.hpp"

namespace uhf
{

	class LibLoaderObject : public uhf::IObject
	{
	public:

		LibLoaderObject();
		~LibLoaderObject();
    
		bool init(const std::string& libfile);

	private:

		bool invoke_void(const std::string& functionName);
		void * _lib_handle;
	};

	typedef std::shared_ptr<LibLoaderObject> Library;

} // namespace uhf ends

