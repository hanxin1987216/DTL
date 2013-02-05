/***************************************************************************************************
FileStream.cpp
 	Copyright (c) Datatom Co., Ltd.(2012 - 2013), All rights reserved.

Purpose:
	FileStream 		¿é
	
Auther:
	Áõ¼ÑÂ½ (liu.jialu@datatom.com)

Created Time:
	2012-02-04
***************************************************************************************************/
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstddef>
#include "filestream.h"
using namespace std;

#define CHECK_CLOSE(file)	\
	if (file == 0)	\
		return;
		
FileStream ::FileStream (const String& name, FileMode mode, FileShare share)
			:_name = name
{	
	String str;
	int style;
	style = convert(share,mode);
	_handle = open (name.getCStr(), style);
	if(_handle == -1){
		char *mesg = strerror(errno);              
		printf("Mesg:%s\n",mesg);
	}
}

FileStream::FileStream (const File& file, FileShare share)
{
	_name = file.getName ();
	String str;
	int style;
	style = convert(share,mode);
	_handle = open (name.getCStr(), style);
	if(_handle == -1){
		char *mesg = strerror(errno);              
		printf("Mesg:%s\n",mesg);
	}	
}

FileStream::FileStream (const String& name, FileShare share)
{
	String str;
	int style;
	style = convert(share,mode);
	_handle = open (name.getCStr(), style);
	if(_handle == -1){
		char *mesg = strerror(errno);              
		printf("Mesg:%s\n",mesg);
	}
}


int64
FileStream::getFileLength (void) const
{
	
	
	int64 tmp_cur = lseek(_handle,0,SEEK_CUR);
	int64 length = lseek(_handle,0,SEEK_END);		
	lseek(_handle,tmp_cur,SEEK_SET);                        
	return length;
}

int
FileStream::read (char* bytes, size_t len)
{
	
	
	int m = read(_handle,bytes,len-1);
	return m;
}

void
FileStream::seek (int64 offset, SeekOrigin origin)
{
	CHECK_CLOSE(_handle);
	
	int off;
	off = lseek(_handle,offset,origin);            //(long)offset 
	if(off == -1){
		perror("fail to lseek");
		
	}
}

void
FileStream::available (void) const
{
	
	
	
}

void
FileStream::write(const char* bytes, size_t len)
{
	CHECK_CLOSE(_handle);
	
	if(fwrite(_handle,bytes,len - 1) == -1){
		perror("fail to write");
		
	}
}

void
FileStream::flush (void)
{
	CHECK_CLOSE(_handle);
	
	if(fsync(_handle) == -1)
	{
		perror("fail to flush");
		exit(errno);
	}
}

void
FileStream::close (void) NO_THROW
{
	
	
	if(close(_handle) == -1){
		perror("fail to close");
		exit(1);
	}
}

void
FileStream::endOfFile (void) const
{
	
	
	lseek(_handle,0,SEEK_END);
}

String
FileStream::open (FileShare share, FileMode mode)
{
/*	String str;	
	if(READ_SHARE && CREATE_MODE){
		str = "r";
	}
	if(READ_WRITE_SHARE && CREATE_NEW_MODE){
		str = "r+";
	}
	if(WRITE_SHARE && ){
		str = "w";
	}
	if(READ_WRITE_SHARE && CREATE_NEW_MODE){
		str = "w+";
	}
	if(WRITE_SHARE && ){
		str = "a";
	}
	if(READ_WRITE_SHARE && ){
		str = "a+";
	}
	if(READ_SHARE && ){
		str = "rb";
	}
	if(READ_WRITE_SHARE && ){
		str = "rb+";
	}
	if(WRITE_SHARE && ){
		str = "wb";
	}
	if(READ_WRITE_SHARE && ){
		str = "wb+";
	}
	if(WRITE_SHARE && ){
		str = "ab";
	}
	if(READ_WRITE_SHARE && ){
		str = "qb+";
	}
	
	return str;*/
}
int
FileStream::convert (FileShare share,FileMode mode)
{
	int turn = 0;
	switch(share){
	case NONE_SHARE :
	//	trun = 
		break;
	case READ_SHARE :
		turn = O_RDNLY;
		break;
	case WRITE_SHARE :
		rutn = O_WRONLY;
		break;
	case READ_WRITE_SHARE :
		rutn = O_RDWR;
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
	

}
	
void
FileStream::checkClosed (void) const
{
	
	
}

