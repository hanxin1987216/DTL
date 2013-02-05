/***************************************************************************************************
tcJson.h:	
	C++ Foundation Library TestCase source files
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	test Json
Author:
       liu.wenxue@datatom.com	

Creating Time:
	2012-01-31
***************************************************************************************************/

#include <stddef.h>
#include <dtl/dtl.h>

#ifndef _TEST_JSON_H__
#define _TEST_JSON_H__

class tcJson 
{
public:
	tcJson(){};
	~tcJson(){};

public:
	cJSON* createJson(cJSON *pRoot);
	char* printFormat(cJSON *pJson);
	void printUnformat(cJSON *ptrJson);
	cJSON* parse(const char *Str);
	
	String getValToStr(cJSON *pItem, const String &key = String::EMPTY);
	char* getStrVal(cJSON *pItem);
	int getIntVal(cJSON *pItem);
	double getDoubleVal(cJSON *pItem);
}; 

#endif // End  _TEST_JSON_H__
