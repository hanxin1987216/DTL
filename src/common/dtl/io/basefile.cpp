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

extern void _wapi_time_t_to_filetime (time_t timeval, WapiFileTime *filetime);

#ifndef __WINDOWS__
	#include <sys/stat.h>
	#include <unistd.h>
#endif

#include "basefile.h"


// public ctor
BaseFile::BaseFile (const String &fullPath)
	: _data (0)
	, _needLoad (true)
	, _fullPath (fullPath)
{
}

// public copy ctor
BaseFile::BaseFile (const BaseFile& file)
	: _data (0)
	, _needLoad (true)
	, _fullPath (file._fullPath)
{
	if (file._data != 0) {
		_data = new FileData ();
		
		::memcpy (_data, file._data, sizeof (FileData));
		_needLoad = false;
	}
}


// public assignment ctor
BaseFile& 
BaseFile::operator= (const BaseFile& file)
{	
	if (&file == this)
		return *this;
		
	_fullPath = file._fullPath;

	if (_data != 0) {
		delete _data;
		_data = 0;
		_needLoad = true;
	}

	if (file._data != 0) {
		_data = new  FileData ();
		::memcpy (_data, file._data, sizeof (FileData));
		_needLoad = false;
	}

	return (*this);
}


// public dtor
BaseFile::~BaseFile (void)
{
	if (_data != 0) {
		delete _data;
		_data = 0;
	}
}



// public
int64 
BaseFile::getLastModified (void) const
{	
	if (_needLoad)
		const_cast<BaseFile*>(this)->loadFileAttrs ();

	return _data->lastModifiedTime;
}


// public
int64 
BaseFile::getCreationTime (void) const
{	
	if (_needLoad)
		const_cast<BaseFile*>(this)->loadFileAttrs ();

	return _data->creationTime;
}



// public
int64 
BaseFile::getLastAccess (void) const
{	
	if (_needLoad)
		const_cast<BaseFile*>(this)->loadFileAttrs ();

	return _data->lastAccessTime;
}


// public
FileAttributes 
BaseFile::getFileAttrs (void) const
{

	if (_needLoad)
		const_cast<BaseFile*>(this)->loadFileAttrs ();

	return _data->attrs;
}

// public
void 
BaseFile::setFileAttrs (int attrs)
{	
	int result = SetFileAttributes (_fullPath.getCStr (), (unsigned) attrs);
	if (result == false)
		THROW_ID (strerror(errno), errno);

	_needLoad = true;
}



// protected
void 
BaseFile::setFileAttrs (const WapiFindData& fdata)
{
	if (_data == 0)
		_data = new FileData ();
			
	FileData* stat = _data;
			
	stat->attrs = (FileAttributes) fdata.dwFileAttributes;
	fileTimeToTime (&stat->creationTime, (&fdata.ftCreationTime));
	fileTimeToTime (&stat->lastAccessTime, (&fdata.ftLastAccessTime));
	fileTimeToTime (&stat->lastModifiedTime, (&fdata.ftLastWriteTime));
	stat->length = ((int64)fdata.nFileSizeHigh << 32) | fdata.nFileSizeLow;	
		
	_needLoad = false;
}


void
BaseFile::loadFileAttrs ()
{
	// TODO: here just implements win32
	WIN32_FILE_ATTRIBUTE_DATA data;

	if (_data == 0)
		_data = new FileData ();

	FileData* stat = _data;

	int result = ::GetFileAttributesEx (_fullPath.getCStr (), 
										GetFileExInfoStandard, 									  						
										&data);
	if (result) {
		stat->attrs = (FileAttributes) data.dwFileAttributes;

		fileTimeToTime (&stat->creationTime, (&data.ftCreationTime));
		fileTimeToTime (&stat->lastAccessTime, (&data.ftLastAccessTime));
		fileTimeToTime (&stat->lastModifiedTime, (&data.ftLastWriteTime));

		stat->length = ((int64)data.nFileSizeHigh << 32) | data.nFileSizeLow;

		_needLoad = false;
	} else {
		unsigned int lastErr = ::GetLastError ();
		if (lastErr == ERROR_FILE_NOT_FOUND || lastErr == ERROR_PATH_NOT_FOUND) {
			::memset (stat, 0, sizeof (FileData));
			stat->attrs = INVALID_FILE;
		}
		else {
			THROW ("error");
		}
	}
}



bool
BaseFile::isFile (const String& path)
{
	if (path.isEmpty ())
		THROW_ID ("IDS_ISFILE_PARAM_NULL", 2);
	
	FileAttributes attrs = loadFileAttributes (path.getCStr ());

	return (attrs == INVALID_FILE ? false : (attrs & DIRECTORY) != 0 ? false : true);
}


// public static 
bool 
BaseFile::isDirectory (const String& path)
{	
	FileAttributes attrs = loadFileAttributes (path.getCStr ());
	return (attrs == INVALID_FILE ? false : (attrs & DIRECTORY) != 0 ? true: false);
}


// public static 
int64 
BaseFile::getLastModified (const String& path)
{	
	// TODO: here just implements win32
	WapiFileAttributesData data;

	int result = GetFileAttributesEx (path.getCStr (), 
										  GetFileExInfoStandard, 
										  &data);
	int64 lastModifiedTime = 0;

	if (result) {
		fileTimeToTime (&lastModifiedTime, (&data.ftLastWriteTime));
	} 
	else {
		THROW_ID (strerror(errno), errno);
	}

	return lastModifiedTime;
}


// public static 
int64 
BaseFile::getCreationTime (const String& path)
{
	
	WapiFileAttributesData data;

	int result = ::GetFileAttributesEx (path.getCStr (), 
										  GetFileExInfoStandard, 
										  &data);
	int64 creationTime = 0;

	if (result) {
		fileTimeToTime (&creationTime, (&data.ftCreationTime));
	} 
	else {
		THROW_ID (strerror(errno), errno);
	}

	return creationTime;
}



// public static 
int64 
BaseFile::getLastAccess (const String& path)
{
		
	WapiFileAttributesData data;

	int result = ::GetFileAttributesEx (path.getCStr (), 
										  GetFileExInfoStandard, 
										  &data);
	int64 lastAccessTime = 0;

	if (result) {
		fileTimeToTime (&lastAccessTime, (&data.ftLastAccessTime));
	} 
	else {
		THROW_ID (strerror(errno), errno);
	}

	return lastAccessTime;
}


// public static 
FileAttributes 
BaseFile::getFileAttrs (const String& path)
{	
	return loadFileAttributes (path.getCStr ());
}

