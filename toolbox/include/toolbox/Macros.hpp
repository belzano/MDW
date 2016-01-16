#pragma once

#define MDW_SINGLE_ARG(...) __VA_ARGS__
#define MDW_SINGLE_ARG2(A,B) A,B
#define MDW_SINGLE_ARG3(A,B,C) A,B,C

#ifdef DEBUG 
	#define MDW_DEBUG 1
#endif

#ifdef MDW_DEBUG
	#define MDW_DEBUG_ONLY(xxx) xxx
#else
	#define MDW_DEBUG_ONLY(xxx) 
#endif

#ifdef MDW_DEBUG
	#define DEBUG_LINE for(;;false)
#else
	#define DEBUG_LINE  
#endif


#define COMBINE1(X,Y) X##Y  // helper macro
#define COMBINE2(X,Y,Z) X##Y##Z  // helper macro
#define COMBINE(X,Y) COMBINE1(X,Y)

#define ON_DLL_OPEN(id) void* loader##id __attribute__ ((section (".ctors"))) 
#define ON_LIB_OPEN static void* COMBINE(loader, __LINE__) __attribute__ ((section (".ctors"))) 

#define STATIC_ANOMYMOUS_UID(name) static void* name


#ifndef BUILD_MODULE
	#pragma message "BUILD_MODULE is not defined: defaulting to XXX"
	#define BUILD_MODULE "XXX"
#endif

#ifndef BUILD_FILENAME
	#define BUILD_FILENAME __FILE__
#endif



#define NAMESPACE_OPEN1(a) namespace a { 
#define NAMESPACE_OPEN2(a, b) namespace a { namespace b 
#define NAMESPACE_OPEN3(a, b, c) namespace a { namespace b { namespace c {

#define NAMESPACE_CLOSE1 }
#define NAMESPACE_CLOSE2 }}
#define NAMESPACE_CLOSE3 }}}

//////////////////////////////////////////////////////////////////////

#define MDW_ON_LIBRARY_LOAD(action)\
void (*loader##__FILENAME__##__LINE__/*##BaseT##ExtendedT*/)(void) __attribute__ ((section (".ctors"))) = action;

//////////////////////////////////////////////////////////////////////

#define MDW_SHARED_POINTER(type) typedef std::shared_ptr<type> type##Ptr;
#define MDW_WEAK_POINTER(type) typedef std::weak_ptr<type> type##Ptr;

