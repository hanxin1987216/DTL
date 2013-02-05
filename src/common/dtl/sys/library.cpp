/***************************************************************************************************
library.cpp:	
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	
	动态库加载、接口导出等
	
Author:
	韩欣

Creating Time:
	2012-03-10  	
***************************************************************************************************/

#include "../prec.h"
#include <stdlib.h>
#include "../lang/string.h"
#include "../sys/exception.h"


#ifndef __WINDOWS__
#include <dlfcn.h>
#endif


#include "library.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
// class Library

// public static
void* 
Library::load (const String& libName)
{	
	if (libName.isEmpty () == true)
	{
		THROW ("load LibName is empty");
	}
	
#ifdef __WINDOWS__
	unsigned int em = ::SetErrorMode (SEM_FAILCRITICALERRORS);
	
	void* hmodule = ::LoadLibrary (libName.getCStr ());
	if (hmodule == 0) 
		THROW_ID ("loadLibrary error", ::GetLastError ());
	
	::SetErrorMode (em);
	return reinterpret_cast<void*> (hmodule);	
	
#elif defined(__UNIX_LIKE__)
	void* dlib = dlopen (libName.getCStr (), RTLD_LAZY);
	if (dlib == 0) {
		String error;
		error.format ("dlopen %s failed!", libName.getCStr ());
		THROW (error);
	}
	
	return dlib;	
	
#elif defined(__MAC__)

	NSObjectFileImage image;	   
    NSObjectFileImageReturnCode dsoerr = ::NSCreateObjectFileImageFromFile (libName.getCStr(), 
    																	    &image);

	NSModule os_handle = 0;
	if (dsoerr == NSObjectFileImageSuccess) {
#if defined(NSLINKMODULE_OPTION_RETURN_ON_ERROR) && defined(NSLINKMODULE_OPTION_NONE)
        os_handle = ::NSLinkModule (image, 
        							libName.getCStr(),
								    NSLINKMODULE_OPTION_RETURN_ON_ERROR | NSLINKMODULE_OPTION_NONE);         
#else // NSLINKMODULE_OPTION_RETURN_ON_ERROR && NSLINKMODULE_OPTION_NONE
         os_handle = ::NSLinkModule (image, libName.getCStr(), FALSE);
#endif // NSLINKMODULE_OPTION_RETURN_ON_ERROR && NSLINKMODULE_OPTION_NONE
         ::NSDestroyObjectFileImage (image);
     }
     else if ((dsoerr == NSObjectFileImageFormat ||
              dsoerr == NSObjectFileImageInappropriateFile) &&
              NSAddLibrary (libName.getCStr ()) == TRUE) {
         os_handle = (NSModule)DYLD_LIBRARY_HANDLE;
     }
     
     if (os_handle == 0) {
     	NSLinkEditErrors errors;
        int errorNumber;
        const char *fileName;
        ::NSLinkEditError (&errors, &errorNumber, &fileName, 0);
        
		String error;
		error.format ("loadLibrary %s failed!", libName.getCStr ());
		THROW (error);
     }
	 
	 return reinterpret_cast<void*> (os_handle);
#else
	THROW ("not implement");
#endif // __WINDOWS__	
}

// public static
void
Library::unload (void* handle)
{	
	if (handle == 0)
	{
		THROW ("unload handle is null");
	}
		
#ifdef __WINDOWS__
	if (::FreeLibrary (reinterpret_cast<HMODULE> (handle)) == FALSE )
		THROW_ID ("freeLibrary is failed", ::GetLastError ());
		
#elif defined(__UNIX_LIKE__)
	if (dlclose (handle) != 0) {
		THROW ("dlclose error!");
	}
		
#elif defined(__MAC__)
	if (handle != DYLD_LIBRARY_HANDLE) {
    	::NSUnLinkModule (handle, FALSE);
    }
     
#else
	THROW ("not implement");
#endif // __WINDOWS__	
}

// public static 
void* 
Library::loadSymbol (void* handle, const String& symbolName)
{
	
	if (handle == 0)
		THROW ("loadSymbol handle is NULL");
	
	if (symbolName.isEmpty () == true)
		THROW ("symbolName is NULL");

#ifdef __WINDOWS__

	// TODO

#elif defined(__UNIX_LIKE__)
	void* sym = ::dlsym (handle, symbolName.getCStr ());
	if (sym == 0) {
		String error;
		error.format ("dlsym %s error!", symbolName.getCStr ());
		THROW (error);
	}

	return sym;
	
#elif defined(__MAC__)
	THROW ("not implement");
	
#else
	THROW ("not implement");
#endif // __WINDOWS__	
}
