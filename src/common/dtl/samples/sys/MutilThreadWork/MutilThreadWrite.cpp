/***************************************************************************************************
MutilThreadWrite.cpp:	
	C++ Foundation Library TestCase source files
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	MutilThreadWrite

Author:
       liu.wenxue@datatom.com	

Creating Time:
	2013-01-30
***************************************************************************************************/

#include <dtprec.h>
#include <dtl/dtl.h>

#include "MutilThread.h"
#include "MutilThreadWrite.h"


MutilThreadWrite::MutilThreadWrite(String threadName, const String &pathName, String Content)
	:MutilThread(threadName),_pathname(pathName),_content(Content)
{
	
}

MutilThreadWrite::~MutilThreadWrite()
{

}

void
MutilThreadWrite::threadWork()
{
	start();
	join();
}

void 
MutilThreadWrite::writeFile()
{
	try{
	/*
		String direct = Path::getDirectoryName(_pathname);
		Directory directName(direct);
	    if (!directName.exists())	
		{
		
		}
		else
		{
		
		}

        String file= Path::getFileName(_pathname);
		File fileName(file);
		if (!fileName.exists())
		{
		
		}
		else
		{
		
		}
	*/
		StreamWriter writeContent(_pathname, false);
		writeContent.writeLine(_content);
	    writeContent.close();
	}
	catch(Exception &exc)	
	{
		cout << exc.toString().getCStr() << endl;
	}

}

void
MutilThreadWrite::run()
{
    writeFile();
}
