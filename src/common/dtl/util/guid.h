/***************************************************************************************************
guid.h:	
	Copyright (c) Datatom Software, Inc.(2012)

Purpose:
	This file contain the declaration of classes:
	Guid: Represents a globally unique indentifier.

Author:
	韩欣 (han.xin@datatom.com)

Creating Time:
	2012-3-9  	
***************************************************************************************************/

#ifndef __DTL_UTIL_GUID_H__
#define __DTL_UTIL_GUID_H__

#if PRAGMA_ONCE
#	pragma once
#endif

#ifdef __LINUX__
#include <uuid/uuid.h>
#endif // __WINDOWS__

#if defined(__AIX__) || defined(__HPPA__) || defined(__SOLARIS__)
	typedef unsigned char uuid_t[16];
#endif

/**
 * This class represents globally unique indentifier.
 */
class DTL_DLLEXPORT Guid
{
public: 
	Guid ();
	Guid (const String& guid);

#ifdef __WINDOWS__
	Guid (const GUID& guid);
#else
	Guid (const uuid_t& guid);
#endif // __WINDOWS__

	~Guid();

#ifdef __WINDOWS__	
	const GUID& getGuid () const
	{
		return _guid;
	}
#else
	const uuid_t& getGuid () const
	{
		return _guid;
	}
#endif // __WINDOWS__

	Guid& operator= (const String& guid);
	
	Guid& operator= (const Guid& guid);

#ifdef __WINDOWS__
	Guid& operator= (const GUID& guid);
#else
	Guid& operator= (const uuid_t& guid);
#endif // __WINDOWS__

	bool operator== (const Guid& guid);

#ifdef __WINDOWS__
	bool operator== (const GUID& guid);
#else
	bool operator== (const uuid_t& guid);
#endif // __WINDOWS__

	String toString () const;
	
	/**
	 * 所有平台统一使用 {AAA-BBB-CCC-DDD} 格式（大写字母）
	 */
	String toStdString () const;

protected:
	Guid& assign (const String& guid);
		
#ifdef __WINDOWS__
	Guid& assign (const GUID& guid);
#else
	Guid& assign (const uuid_t& guid);
#endif // __WINDOWS__

private:
#ifdef __WINDOWS__
	GUID _guid;
#else
	uuid_t _guid;
#endif // __WINDOWS__

}; // End class Guid


#endif // __DTL_UTIL_GUID_H__
