/***************************************************************************************************
FileOutputStream.h
 	Copyright (c) Datatom Co., Ltd.(2012 - 2013), All rights reserved.

Purpose:
	FileOnputStream块
	
Auther:
	严支能 (yan.zhineng@datatom.com)
	
Created Time:
	2012-3-1
***************************************************************************************************/

#include "../prec.h"
#include <assert.h>

#include "../mono_base/uglify.h"
#include "../lang/string.h"
#include "comdef.h"
#include "file.h"

#include "../sys/exception.h"

#include "fileoutputstream.h"

//
// 检查文件句柄
//
#define CHECK_CLOSED() \
	do { \
		if (_handle == INVALID_HANDLE_VALUE) { \
			String msg; \
			msg.format(_T("File %s Has Closed"), _fileName.getCStr()); \
			THROW (msg); \
		} \
	} while (false)


// public ctor
FileOutputStream::FileOutputStream(const File& file, 
								   FileMode mode,
								   FileShare share /*= READ_WRITE_SHARE */)
	: _fileName (file.getFullName ())
	, _handle (INVALID_HANDLE_VALUE)
{
	open (mode, share);
}

// public ctor
FileOutputStream::FileOutputStream (const String& fileName, 
									FileMode mode,
									FileShare share /*= READ_WRITE_SHARE*/)
	: _fileName (fileName)
	, _handle (INVALID_HANDLE_VALUE)
{
	if (fileName.isEmpty ())
		THROW (_T("The file name is empty."));

	open (mode, share);
}

// public virtual 
void 
FileOutputStream::write (int b)
{	
#ifndef __IS_BIG_ENDIAN__
	write (reinterpret_cast<const unsigned char*> (&b), 1);
#else
	// convert to littlen endian to write.
	b = b << 24;
	write (reinterpret_cast<const unsigned char*> (&b), 1);
#endif
}

// public virtual
void 
FileOutputStream::write (const unsigned char* bytes, size_t len)
{
	CHECK_CLOSED ();
	
	if (bytes == 0)
		THROW (_T("IDS_NULL_ARGUMENT"));

	if (len == 0)
		return; // Ignore it.

	unsigned int dwWritten = 0;
	while (true) {
		int result = ::WriteFile (_handle, bytes, (unsigned) len, TO_DWORD_PTR(&dwWritten), 0);
		
		if (!result) {
			String error;
			int lasterr = ::GetLastError ();
			error.format (_T("Write File %s Error, %s!"), _fileName.getCStr (), strerror (lasterr));
			THROW_ID (error, lasterr);
		}
		
		if (dwWritten == len) {
			break;
		}
		else {
			len -= dwWritten;
			bytes += dwWritten;
		}
	}
}

// public virtual 
int64 
FileOutputStream::seek (int64 offset, SeekOrigin origin)
{
	CHECK_CLOSED ();

	unsigned method = convertSeekOrigin (origin);
	
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
			error.format (_T("SetFilePointer File %s Error, %s!"), _fileName.getCStr (), strerror (lasterr));
			THROW_ID (error, lasterr);
	}
	
	return (offset | ((int64)hiOffset << 32));
}

// public virtual
void 
FileOutputStream::flush (void)
{
	CHECK_CLOSED ();

	if (::FlushFileBuffers (_handle) == FALSE) {
		String error;
		int lasterr = ::GetLastError ();
		error.format (_T("Flush File %s Error, %s!"), _fileName.getCStr (), strerror (lasterr));
		THROW_ID (error, lasterr);
	}
}

// public virtual 
void 
FileOutputStream::close (void) NO_THROW
{
	if (_handle != INVALID_HANDLE_VALUE) {
		try {
			flush (); // Flush the internal buffer before close it.
		}
		catch (...) {
			assert (false);
		}

		::CloseHandle (_handle);
		_handle = INVALID_HANDLE_VALUE;
	}
}

// protected virtual
void 
FileOutputStream::open (FileMode mode, FileShare share)
{
	if (_handle != INVALID_HANDLE_VALUE)
		THROW (_T("the file has opend"));

	void* ret = ::CreateFile (_fileName.getCStr (),
							   GENERIC_WRITE, 
							   convertFileShare (share),
							   0,
							   convertFileMode (mode),
							   FILE_ATTRIBUTE_NORMAL,
							   0);

	if(ret == INVALID_HANDLE_VALUE) {
		String error;
		int lasterr = ::GetLastError ();
		error.format (_T("Create File %s Error, %s!"), _fileName.getCStr (), strerror (lasterr));
		THROW_ID (error, lasterr);
	}

	_handle = ret;
	if (mode == APPEND_MODE) {
		try {
			seek (0, END_ORIGIN); // The Win32 don't provide appending mode directly.
		}
		catch (...) {
			::CloseHandle (ret);
			throw;
		}
	}
}



void
FileOutputStream::setEndOfFile(int64 endOFFile) const
{
	int lowLength = (int) (endOFFile & 0xFFFFFFFF);
	int hiLength= (int) (endOFFile >> 32);
	lowLength = ::SetFilePointer (_handle, 
								  lowLength, // Low-order 32 bits length
								  TO_LONG_PTR(&hiLength),  // high-order 32 bits length
								  FILE_BEGIN);
	if ((unsigned)lowLength == INVALID_SET_FILE_POINTER) {
		THROW_ID("SetFilePointer failed", ::GetLastError ());
	}
	int64 realLength = (lowLength | ((int64)hiLength << 32));
	
	if (::SetEndOfFile (_handle) == FALSE) {		
		//::CloseHandle (file);
		THROW_ID ("SetEndOfFile failed", ::GetLastError ());
	}
}
// public 
int64 
FileOutputStream::getCurrentOffset (void) const
{
	// Get current file pointer position
	int offset_hi = 0;
	unsigned int offset_low = ::SetFilePointer (_handle, 0, TO_LONG_PTR (&offset_hi), FILE_CURRENT);

	return (offset_low | ((int64)offset_hi << 32));
}