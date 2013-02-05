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

#ifndef __DTL_SYS_LIBRARY_H__
#define __DTL_SYS_LIBRARY_H__

#if PRAGMA_ONCE
#	pragma once
#endif

/**
 * A class to operate system operation on current CFL runtime.
 */
class DTL_DLLEXPORT Library
{
public:
	
	/**
	 * Loads the specified shared library.
	 *
	 * @param libName 	The library name to the shared library.
	 * @return The address to store the shared library.
	 * @throw ArgumentException If libName is empty.
	 * @throw Exception If the library does not exist or cannot find. 
	 */	
	static void* load (const String& libName);
	
	/**
	 * Close the specified shared library.
	 *
	 * @param handle 	The address of the shared library.
	 * @throw ArgumentException If handle is null.
	 * @throw Exception If failed to unload the shared library.
	 */
	static void unload (void* handle);
	
	/**
	 * Loads a symbol from a shared library.
	 *
	 * @param handle 		The address of the shared library.
	 * @param symbolName 	The symbol name to load.
	 * @throw Exception If handle is null or symbolName is empty.
	 * @throw Exception If the symbol doesn't exist.
	 * @return The address of the symbol.
	 */
	static void* loadSymbol (void* handle, const String& symbolName);
		
}; // End class Library	
		
#endif // __DTL_SYS_LIBRARY_H__
