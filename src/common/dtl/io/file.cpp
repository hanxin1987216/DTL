/***************************************************************************************************
File.cpp:	
	C++ Foundation Library header files
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	This file contain the declaration of classes:

Author:
	韩欣 (han.xin@datatom.com)

Creating Time:
	2012-1-10
***************************************************************************************************/

#include "../prec.h"

#include "../mono_base/uglify.h"

#include "../lang/string.h"
#include "../sys/exception.h"

#include "comdef.h"
#include "basefile.h"
#include "path.h"


#include "file.h"


#ifndef __WINDOWS__
	#include <sys/stat.h>
	#include <unistd.h>
#endif


// public virtual 
bool 
File::exists (void) const
{
	if (_needLoad) {
		const_cast<File*>(this)->loadFileAttrs ();
	}

	FileAttributes attrs = _data->attrs;
	return (attrs == INVALID_FILE ? false : (attrs & DIRECTORY) != 0 ? false : true);
}



//// public virtual 
String 
File::getName (void) const
{
	return Path::getFileName (this->_fullPath);
}


// public
void 
File::remove (void)
{
	int ret=unlink(this->_fullPath.getCStr ());
	
	if(ret != 0) {
		THROW (strerror(errno));
	}
	else
		_needLoad = true; // Mark this as true to reload its attributes.
}

// public
void 
File::setReadonly (bool readonly)
{
	int attr = (int) getFileAttrs ();

	if (readonly == true)
		attr |= READONLY;
	else
		attr &= ~READONLY;

	setFileAttrs (attr);
}


// public
void 
File::rename (const String& newName)
{
	if (newName.isEmpty ())
		THROW ("IDS_EMPTY_NEW_NAME");
	
	String tempName = newName;
	if (tempName.trim ().isEmpty () || 
		Path::isValidPath (tempName) == false)
		THROW ("IDS_ILLEGAL_PATH");

	FileAttributes attrs = BaseFile::getFileAttrs (newName);
	if (attrs != INVALID_FILE) {
		String errMsg;		
		THROW (errMsg);
	}
	
	if (::MoveFile (_fullPath.getCStr (), newName.getCStr ()) == FALSE)
		THROW ("move file error");		

	_fullPath = Path::makeFullPath (newName);
	_needLoad = true;
}

void
File::create (void)
{
	void* ret = ::CreateFile (_fullPath.getCStr (),
							   GENERIC_WRITE | GENERIC_READ, 
							   0,
							   0,
							   CREATE_NEW,
							   FILE_ATTRIBUTE_NORMAL,
							   0);
	if(ret == INVALID_HANDLE_VALUE) {
		THROW_ID ("create file failed", ::GetLastError ());
	}
	
	::CloseHandle (ret);
	_needLoad = true;
}


// public 
void
File::copy (const String& newFileName, bool failIfExists)
{
	if (::CopyFile (_fullPath.getCStr (), 
					newFileName.getCStr (), 
					failIfExists) == FALSE) 
		THROW_ID ("copy file failed", ::GetLastError ());
}

// public 
int64 
File::truncate (const int64& newLength)
{
	if (exists () == false)
		return 0;
		
	if (getLength () <= newLength)
		return getLength ();
		
	void* file  = ::CreateFile (_fullPath.getCStr (), 
					  			 GENERIC_READ | GENERIC_WRITE, 
					  			 0, 
					  			 0,
					  			 OPEN_EXISTING,
					  			 0,
					  			 0);
					  
	if (file == INVALID_HANDLE_VALUE) {
		THROW_ID ("create file failed", ::GetLastError ());		
	}	
	
	int lowLength = (int) (newLength & 0xFFFFFFFF);
	int hiLength= (int) (newLength >> 32);
	lowLength = ::SetFilePointer (file, 
								  lowLength, // Low-order 32 bits length
								  TO_LONG_PTR(&hiLength),  // high-order 32 bits length
								  FILE_BEGIN);
	if ((unsigned)lowLength == INVALID_SET_FILE_POINTER) {
		::CloseHandle (file);
		THROW_ID("SetFilePointer failed", ::GetLastError ());
	}
	int64 realLength = (lowLength | ((int64)hiLength << 32));
	
	if (::SetEndOfFile (file) == FALSE) {		
		::CloseHandle (file);
		THROW_ID ("SetEndOfFile failed", ::GetLastError ());
	}
	
	::CloseHandle (file);
	_needLoad = true;
	return realLength;
}