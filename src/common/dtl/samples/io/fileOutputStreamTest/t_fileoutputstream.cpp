/***************************************************************************************************
t_fileoutputstream.cpp:	
	Copyright (c) Datatom Software, Inc.(2012)

Purpose:
	This file is to test the t_fileoutputstream

Author:
	Zhang.Wencong

Creating Time:
	2012-07-25
***************************************************************************************************/

#include <dtprec.h>
#include <dtl/dtl.h>
#include <dtl/lang/string.h>
#include <dtl/io/filestream.h>
#include <dtl/io/file.h>
#include <dtl/io/fileoutputstream.h>
#include <dtl/io/fileinputstream.h>

#define BYTE_LENGTH 20

//#define FILE_A "file_input.t"
//#define FILE_B "file_output.t"

int main(void)
{

	InitDTLibrary ();//调用信息dtl的时候要首先包含进去
	
	//const unsigned char str[] = "hao hello world";
	const String filename("a.txt");
	unsigned char ptr[255]= {0};
	
	//FileOutputStream w_stream(filename, OPEN_OR_CREATE_MODE);
	FileInputStream r_stream(filename); //create a intput stream
	
	//w_stream.write(str, BYTE_LENGTH);
	//w_stream.flush();
	//cout<< "the file name is :"<< w_stream.getFileName().getCStr() << endl;
	
	r_stream.read(ptr, BYTE_LENGTH);
	cout<< "the file name is :"<< r_stream.getFileName().getCStr() << endl;
	r_stream.close();
	
	return 0;
}

