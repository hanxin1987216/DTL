/***************************************************************************************************
streamwriter.h
 	Copyright (c) Datatom Co., Ltd.(2012 - 2013), All rights reserved.

Purpose:
	streamwriter 文件的写操作
	
Auther:
	刘佳陆 (liu.jialu@datatom.com)

Created Time:
	2012-02-02
***************************************************************************************************/
//#include <iostream>
//#include <fstream>
//#include <unistd.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <fcntl.h>

#include <dtl.h>


#include "streamwriter.h"

StreamWriter::StreamWriter (const String& file, bool append)   
{
	_path = file;	
	if(append == false)
	{
		_file = open(_path.getCStr(), O_WRONLY | O_TRUNC);		
	}
	else{
		_file = open(_path.getCStr(), O_WRONLY | O_APPEND);			
	}
	if(_file == -1)                                             
	{	
		perror("fail to open");
		return ;
		exit(1);
	}
}

void
StreamWriter::fclose (void)
{	
		if(close(_file) == -1){
			perror("fail to close");
			exit(1);
		}
}

void
StreamWriter::flush (void)
{
	if(fsync(_file) == -1)
	{
		perror("fail to flush");
		exit(1);
	}
}



void
StreamWriter::writeChar (const tchar_t str)
{
	const char *tmp_char = &str;
	ssize_t tmp;
	tmp = write(_file,tmp_char,1);
	if(tmp == -1){
		perror("file to write a char");
		exit(1);
	}
}

void
StreamWriter::writeChars (const tchar_t* str)
{
	if(write(_file,str,strlen(str)) == -1){
		perror("fail to write chars");
		exit(1);
	}
	
}

void
StreamWriter::writeChars (const tchar_t* str, size_t size)
{
	if(write(_file,str,size) == -1){
		perror("fail to write chars2");
		exit(1);
	}
}

void
StreamWriter::writeString (const String& str)        //String
{
	if(write(_file,str.getCStr(),str.getLength()) == -1){
		perror("file to write string ");
		exit(1);
	}
}

void
StreamWriter::writeString (const String& str, tchar_t endChar)      //String
{
	size_t pos = str.find(endChar);
	if(pos == string::npos){
		if(write(_file,str.getCStr(),str.getLength()) == -1){
			perror("fail to write string2");
			exit(1);
		}
	}
	else{
		String tmp = str.subString(0,pos);
		if(write(_file,tmp.getCStr(),pos) == -1){
			perror("fail to write string2");
			exit(1);
		}
	}
	
	
	
}

void
StreamWriter::writeLine (const String& str)           
{
	writeString(str);
	char tmp = '\n';
	writeChar(tmp);
}