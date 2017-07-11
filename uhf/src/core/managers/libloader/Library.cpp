#include <string.h>
#include <iostream>

#include "Library.hpp"

#include <dlfcn.h>
#include <cstdio>

#include "toolbox/Logger.hpp"

using namespace uhf;


LibLoaderObject::LibLoaderObject()
{	
   _lib_handle = NULL;
}

////////////////////////////////////////////////////////////////////////

LibLoaderObject::~LibLoaderObject()
{
	MDW_LOG_INFO("Unloading library");

	if (_lib_handle == NULL)
		return;
		
	// notify lib is about to be unloaded	
	//invoke_void("unload");
	
	// close lib
	dlclose(_lib_handle);
}

////////////////////////////////////////////////////////////////////////

bool LibLoaderObject::init(const std::string& libfile)
{
	MDW_LOG_CONTEXT("dlopen");
	
	MDW_LOG_DEBUG("Library dynamic loading [" << libfile <<  "]");
	
   _lib_handle = dlopen(libfile.c_str(), RTLD_LAZY);
   if (!_lib_handle) 
   {
      MDW_LOG_ERROR("Failure "<< dlerror() <<" at dlopen() when attempting to load [" << libfile <<  "]");
      return false;
   }
   
   return true;
}

////////////////////////////////////////////////////////////////////////

bool LibLoaderObject::invoke_void(const std::string& functionName)
{
	if (NULL == _lib_handle)
		return false;
	
    typedef bool (* VoidFunctionPtr)();
	
	void *gptr = dlsym(_lib_handle, functionName.c_str());
	VoidFunctionPtr fptr = reinterpret_cast<VoidFunctionPtr>(reinterpret_cast<long>(gptr)) ;
	
	char *error = dlerror();
	if (error != NULL)  
	{
		MDW_LOG_ERROR("Failure "<< error <<" at dlopen() when attempting to invoke [" << functionName <<  "]");	
		return false;
	}

	// Let's invoke!
	MDW_LOG_DEBUG("Invoking [" << functionName <<  "]");
	fprintf(stderr, "Invoking %s() \n", functionName.c_str());	
	return (*fptr)();
}



