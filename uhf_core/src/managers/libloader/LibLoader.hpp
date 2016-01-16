#pragma once

#include <memory>

namespace uhf
{

	class LibLoaderObject
	{
	public:

		LibLoaderObject();
		~LibLoaderObject();
    
		bool init(const std::string& libfile);

	private:

		bool invoke_void(const std::string& functionName);
		void * _lib_handle;
	};

	typedef std::shared_ptr<LibLoaderObject> LibLoader;

} // namespace uhf ends

