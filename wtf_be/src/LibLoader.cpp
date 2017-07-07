#include <string.h>
#include <iostream>

#include "LibLoader.hpp"

#include <dlfcn.h>
#include <cstdio>

#include "toolbox/Logger.hpp"

using namespace WTF;


LibLoaderObject::LibLoaderObject()
{	
   _lib_handle = NULL;
}

////////////////////////////////////////////////////////////////////////

LibLoaderObject::~LibLoaderObject()
{
/*	if (_lib_handle == NULL)
		return;
		
	// notify lib is about to be unloaded	
	//invoke_void("unload");
	
	// close lib
	dlclose(_lib_handle);*/
}

////////////////////////////////////////////////////////////////////////

bool LibLoaderObject::init(const char* libfile)
{
	MDW_LOG_CONTEXT("Library loading [" << libfile << "] ");
	
	MDW_LOG_DEBUG("Library dynamic loading [" << libfile <<  "] : started ");
	
   _lib_handle = dlopen(libfile, RTLD_LAZY);
   if (!_lib_handle) 
   {
      fprintf(stderr, "%s\n", dlerror());
      return false;
   }
   
	MDW_LOG_DEBUG("Library dynamic loading [" << libfile <<  "] : completed ");
	return true;
}

////////////////////////////////////////////////////////////////////////

bool LibLoaderObject::invoke_void(const char* functionName)
{
	if (NULL == _lib_handle)
		return false;
	
    typedef bool (* VoidFunctionPtr)();
	
	void *gptr = dlsym(_lib_handle, functionName);
	VoidFunctionPtr fptr = reinterpret_cast<VoidFunctionPtr>(reinterpret_cast<long>(gptr)) ;
	
	char *error = dlerror();
	if (error != NULL)  
	{
		fprintf(stderr, "%s\n", error);
		return false;
	}

	// Let's invoke!
	fprintf(stderr, "Invoking %s() \n", functionName);	
	return (*fptr)();
}



