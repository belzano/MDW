#pragma once

#include <memory>

namespace  WTF
{

	class LibLoaderObject
	{
	public:

		LibLoaderObject();
		~LibLoaderObject();
    
		bool init(const char* libfile);

	private:

		bool invoke_void(const char* functionName);

		void * _lib_handle;
	};

	typedef std::shared_ptr<LibLoaderObject> LibLoader;

} // namespace WTF ends

