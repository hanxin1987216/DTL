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
#include "../prec.h"
#include "../mono_base/uglify.h"
#include "../lang/string.h"
#include "../sys/exception.h"
#include "./comdef.h"
#include "./file.h"
#include <stdio.h>
#include <fcntl.h>

#include "./streamwriter.h"

#define CHECK_CLOSE(file)	\
	if (file == 0)	\
		return;


StreamWriter::StreamWriter (const String& file, bool append)  
{	
	_path = file;
	File wfile (file);
	if (!wfile.exists ())
		wfile.create ();

	
	if(append)
		_file = ::open(file.getCStr(), O_WRONLY | O_APPEND);		
	else
		_file = ::open(file.getCStr(), O_WRONLY | O_TRUNC);	
		
	if(_file == -1)                                             
		THROW (strerror (errno));
}

void
StreamWriter::close (void)
{	
	CHECK_CLOSE (_file);

	if(::close(_file) == -1){
		THROW ("close file failed");
	}
	
	_file = 0;
}

void
StreamWriter::flush (void)
{
	CHECK_CLOSE (_file);

	if(fsync(_file) == -1)
	{
		THROW (strerror (errno));
	}
}



void
StreamWriter::writeChar (const tchar_t str)
{
	CHECK_CLOSE (_file);

	if(write(_file, &str, sizeof (tchar_t)) == -1)
		THROW (strerror (errno));
}

void
StreamWriter::writeChars (const tchar_t* str)
{
	CHECK_CLOSE (_file);
	
	if(write(_file, str, strlen(str) * sizeof (tchar_t)) == -1)
		THROW (strerror (errno));
}

void
StreamWriter::writeChars (const tchar_t* str, size_t size)
{
	CHECK_CLOSE (_file);

	if (write(_file, str, size * sizeof (tchar_t)) == -1) 
		THROW (strerror (errno));
}


void
StreamWriter::writeString (const String& str)       
{
	CHECK_CLOSE (_file);

	if(write(_file, str.getCStr (), str.getLength () * sizeof (tchar_t)) == -1)
		THROW (strerror (errno));
}



void
StreamWriter::writeString (const String& str, tchar_t endChar)      
{
	CHECK_CLOSE (_file);

	size_t pos = str.find (endChar);

	String tmp = str.subString (0, pos == String::NO_POSITION ? str.getLength () : pos);
	if(write(_file, tmp.getCStr(), tmp.getLength () * sizeof (tchar_t)) == -1){
		THROW (strerror (errno));
	}		
}

void
StreamWriter::writeLine (const String& str)           
{
	String tmp = str;
	tmp.trimRight ();
	writeString (tmp);

#ifdef __WINDOWS__
	const tchar_t* lineChars = _T("\r\n");
	writeChars (lineChars, 2);	
#else
	const tchar_t* lineChars = _T("\n");
	writeChars (lineChars, 1);
#endif

}


void
StreamWriter::writeLines (vector<String> &lines)
{
	CHECK_CLOSE (_file);
	
	String tmp;	
	size_t i;
	for (i = 0; i < lines.size (); ++i)
		writeLine (lines[i]);

}

int
StreamWriter::reopen (bool append)
{
	//
	// if file has opened, close it first and then reopen it
	//
	if(_file != 0)
		close ();
		
	if(append){
		_file = ::open(_path.getCStr(), O_WRONLY | O_APPEND);		
	}
	else{
		_file = ::open(_path.getCStr(), O_WRONLY | O_TRUNC);	
	}
	
	if(_file == -1){	
		//
		// TODO, 文件打开失败需要处理具体的错误ID，暂时用 errno代替
		//
		THROW (strerror (errno));
	}
	
	return _file;
}
