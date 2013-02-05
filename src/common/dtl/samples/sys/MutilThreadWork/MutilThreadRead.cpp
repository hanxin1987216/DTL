/***************************************************************************************************
MutilThreadRead.cpp:	
	C++ Foundation Library TestCase source files
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	MutilThreadRead

Author:
       liu.wenxue@datatom.com	

Creating Time:
	2013-01-30
***************************************************************************************************/
#include <dtprec.h>
#include <dtl/dtl.h>

#include "MutilThreadRead.h"
#include "MutilThread.h"


MutilThreadRead::MutilThreadRead(String threadName, const String &pathName, String &Content)
	:MutilThread(threadName),_pathname(pathName),_content(Content)
{
	
}

MutilThreadRead::~MutilThreadRead()
{

}

void
MutilThreadRead::threadWork()
{
	start();
	join();
}



void
MutilThreadRead::readFile()
{ 
	try
	{
	    //判断路径是否合法
		String direcName = Path::getDirectoryName(_pathname);
		if (!BaseFile::isDirectory(direcName)) 
			THROW("the Directory is illegal!");
		
		//判断文件名是否合法
		//String fileName = Path::getFileName(pathname);
		//if (!BaseFile::isFile(fileName)) 
		//	THROW("the FileName is illegal!");
		
		//读文件
		StreamReader readContent(_pathname);
	
		while(readContent.hasMore())
		{
		    String line;
			line = readContent.readLine();
			_content.append(line);
		}
	
		cout << "---output--- lineContent :" <<  _content.getCStr()<< endl;
	
		readContent.close();
	}
	catch(Exception &exc)
	{
		cout << exc.toString().getCStr() << endl;
	}
}

void
MutilThreadRead::run()
{
   readFile();
}