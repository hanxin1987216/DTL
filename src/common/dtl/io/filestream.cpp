/***************************************************************************************************
FileStream.cpp
 	Copyright (c) Datatom Co., Ltd.(2012 - 2013), All rights reserved.

Purpose:
	FileStream 		块
	
Auther:
	刘佳陆 (liu.jialu@datatom.com)

Created Time:
	2012-02-04
***************************************************************************************************/
#include "../prec.h"
#include "../mono_base/uglify.h"

#include "../lang/string.h"
#include "../sys/exception.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "./comdef.h"


#include "./filestream.h"


#define CHECK_CLOSE(file)	\
	if (file == 0)	\
		return;
		
	
FileStream ::FileStream (const String& name, FileMode mode, FileShare share)
	: _handle (0)
	, _name()
	, _hasRead(false)
{			
	_name = name;
	int style;
	style = convert(share,mode);
	_handle = ::open (name.getCStr(), style);
	if(_handle == -1){
		THROW ("close file failed");
	}
}

/*
FileStream::FileStream (const File& file, FileShare share)
{
	_name = file.getName ();
	String str;
	int style;
	style = convert(share);
	_handle = ::open (_name.getCStr(), style);
	if(_handle == -1){
		THROW ("close file failed");
	}	
}
*/


FileStream::FileStream (const String& name, FileShare share)
{
	String str;
	int style;
	_name = name;
	style = convert(share);
	_handle = ::open (name.getCStr(), style);
	if(_handle == -1){
		THROW ("close file failed");
	}
}


int64
FileStream::getFileLength (void) const
{
	if(_handle == 0)
		return -1;
	
	int64 tmp_cur = lseek(_handle,0,SEEK_CUR);
	int64 length = lseek(_handle,0L,SEEK_END);
	lseek(_handle,tmp_cur,SEEK_SET);                        
	return length;
}

int
FileStream::read (char* bytes, size_t len)
{
	if(_handle == 0)
		return -1;
	
	int m = ::read(_handle,bytes,len - 1);
	if(m == -1){
		THROW ("close file failed");
	}
	return m;
}

void
FileStream::seek (int64 offset, SeekOrigin origin)
{
	CHECK_CLOSE(_handle);
	
	int off;
	off = lseek(_handle,offset,origin);            //(long)offset 
	if(off == -1){
		THROW ("close file failed");
	}
}

void
FileStream::available (void) const
{
	
	
	
}

int
FileStream::write(const char* bytes, size_t len)
{
	if(_handle == 0)
		return -1;
	
	int m = ::write(_handle,bytes,len);
	if(m == -1){
		THROW ("write file failed or the file is readyonly");
	}
	return m;
}

void
FileStream::flush (void)
{
	CHECK_CLOSE(_handle);
	
	if(fsync(_handle) == -1)
	{
		THROW ("close file failed");
	}
}

void
FileStream::close (void) NO_THROW
{
	CHECK_CLOSE(_handle);
	
	if(::close(_handle) == -1){
		THROW ("close file failed");
	}
	_handle = 0;
}

void
FileStream::endOfFile (void) const
{
	CHECK_CLOSE(_handle);
	
	lseek(_handle,0,SEEK_END);
}

String
FileStream::open (FileShare share, FileMode mode)
{
	return "";
}
int
FileStream::convert (FileShare share,FileMode mode)
{
	int turn = 0;
	switch(share){
	case NONE_SHARE :
		// TODO :
		break;
	case READ_SHARE :
		turn = O_RDONLY;
		break;
	case WRITE_SHARE :
		turn = O_WRONLY;
		break;
	case READ_WRITE_SHARE :
		turn = O_RDWR;
		break;
	default:
		break;	
	}
	
	switch(mode){
	case CREATE_NEW_MODE :
		turn|=O_CREAT|O_EXCL;
		break;		
	case CREATE_MODE :
		turn|=O_CREAT|O_TRUNC;
		break;
	case OPEN_MODE :
		turn|=O_CREAT|O_TRUNC;
		break;
	case OPEN_OR_CREATE_MODE :
		// TODO :
		break;
	case TRUNCATE_MODE :
		turn|=O_TRUNC;
		break;
	case APPEND_MODE :
		turn|=O_APPEND;
		break;
	default :
		break;
	}
	
	return turn;
}
