/***************************************************************************************************
FileInputStream.cpp
 	Copyright (c) Datatom Co., Ltd.(2012 - 2013), All rights reserved.

Purpose:
	FileInputStream块
	
Auther:
	严支能 (yan.zhineng@datatom.com)

Created Time:
	2012-02-28
***************************************************************************************************/

#include "../prec.h"
#include <assert.h>

#include "../mono_base/uglify.h"
#include "../lang/string.h"
#include "comdef.h"
#include "file.h"
#include "../lang/string.h"
#include "../sys/exception.h"
#include "fileinputstream.h"

//
// 检查文件句柄
//
#define CHECK_CLOSED() \
	do { \
		if (_handle == INVALID_HANDLE_VALUE) { \
			String msg; \
			msg.format(_T("File %s Has Closed"), _name.getCStr()); \
			THROW (msg); \
		} \
	} while (false)


// public ctor
FileInputStream::FileInputStream (const File& file, FileShare share /*= READ_WRITE_SHARE */)
	: _name (file.getFullName ())
	, _handle (INVALID_HANDLE_VALUE)
	, _hasRead (0)
{
	open (share);
}

// public ctor
FileInputStream::FileInputStream (const String& name, FileShare share /*= READ_WRITE_SHARE*/)
	: _name (name)
	, _handle (INVALID_HANDLE_VALUE)
	, _hasRead (0)
{
	if (name.isEmpty ())
		THROW (_T("The file name is empty."));

	open (share);
}


// public virtual 
int 
FileInputStream::read (void) 
{
	int data;
	int bytes = read ((unsigned char*) &data, 1);
	
	if (bytes < 0)
		return -1;
	else {
#ifdef __IS_BIG_ENDIAN__
		data = data >> 24;	
#endif
		return (data & 0xFF);
	}
}

// public virtual
int
FileInputStream::read (unsigned char* bytes, int len)
{
	CHECK_CLOSED ();
	
	if (bytes == 0)
		THROW (_T("The buffer into which the data is read is null."));

	if (len == 0)
		return 0;

	int64 avLen = available ();
	if (avLen <= 0)
		return -1; // Have reached the file end.

	if ((int64) len > avLen)
		len = (int) avLen;

	unsigned int n;
	int result = ::ReadFile (_handle, bytes, (unsigned int) len, TO_DWORD_PTR(&n), NULL);
	
	if (result == FALSE) {
		String error;
		int lasterr = ::GetLastError ();
		error.format (_T("Read File %s Error, %s!"), _name.getCStr (), strerror (lasterr));
		THROW_ID (error, lasterr);
	}

	_hasRead += n;
	return n;
}

// public virtual 
int64 
FileInputStream::seek (int64 offset, SeekOrigin origin)
{	
	CHECK_CLOSED ();

	unsigned method = convertSeekOrigin (origin);

	// Move the file pointer to expected position
	int hiOffset = (int) (offset >> 32);
	offset = ::SetFilePointer (_handle, 
									 (int) (offset & 0xFFFFFFFF), 
									 TO_LONG_PTR (&hiOffset), 
#ifdef __WINDOWS__
									 method);
#else
									(WapiSeekMethod) method);
#endif

	if(offset == INVALID_SET_FILE_POINTER) {
		String error;
		int lasterr = ::GetLastError ();
		error.format (_T("SetFilePointer File %s Error, %s!"), _name.getCStr (), strerror (lasterr));
		THROW_ID (error, lasterr);
	}
	
	int64 newOff = (offset | ((int64)hiOffset << 32));
	_hasRead = newOff; // Updates the read size

	return newOff;
}

// public virtual 
void 
FileInputStream::close (void) NO_THROW
{
	if (_handle != INVALID_HANDLE_VALUE) {
		::CloseHandle (_handle);
		
		_handle = INVALID_HANDLE_VALUE;
	}
}

// public virtual
int64
FileInputStream::available (void) const
{	
	CHECK_CLOSED ();

	int64 fileSize;
	unsigned int lowFileSize, highFileSize;

	lowFileSize = ::GetFileSize (_handle, TO_DWORD_PTR(&highFileSize));
	if (lowFileSize == INVALID_FILE_SIZE) {
		String error;
		int lasterr = ::GetLastError ();
		error.format (_T("SetFilePointer File %s Error, %s!"), _name.getCStr (), strerror (lasterr));
		THROW_ID (error, lasterr);
	}

	fileSize = ((int64)highFileSize << 32) | lowFileSize;
	return (fileSize - _hasRead);
}

// protected virtual
void 
FileInputStream::open (FileShare share)
{
	if (_handle != INVALID_HANDLE_VALUE)
		THROW (_T("The file has been opened."));

	void* ret = ::CreateFile (_name.getCStr (),
							   GENERIC_READ, 
							   convertFileShare (share),
							   0,
							   OPEN_EXISTING,
							   FILE_ATTRIBUTE_NORMAL,
							   0);

	if(ret == INVALID_HANDLE_VALUE) {
		String error;
		int lasterr = ::GetLastError ();
		error.format (_T("Create File %s Error, %s!"), _name.getCStr (), strerror (lasterr));
		THROW_ID (error, lasterr);
	}

	_handle = ret;
}
