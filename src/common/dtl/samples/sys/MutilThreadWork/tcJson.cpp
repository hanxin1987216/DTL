#include <dtprec.h>
#include <dtl/dtl.h>

#include "tcJson.h"

// create json
cJSON*
tcJson::createJson(cJSON *pRoot)
{
	cout << "Creat Json: " << endl;
	
	cJSON *name;	
	pRoot=cJSON_CreateObject();     
	cJSON_AddItemToObject(pRoot, "sender", cJSON_CreateString("liu.wenxue@datatom.com"));   
	cJSON_AddItemToObject(pRoot, "receiver", name=cJSON_CreateArray());  
	
	cJSON *info1;
	cJSON_AddItemToArray(name, info1=cJSON_CreateObject());
	cJSON_AddStringToObject(info1, "name", "º«ÐÀ"); 
	cJSON_AddNumberToObject(info1,"qq", 123456);	
	cJSON_AddStringToObject(info1,"adder", "shanghai"); 
	
	cJSON *info2;
	cJSON_AddItemToArray(name, info2=cJSON_CreateObject());   
	cJSON_AddStringToObject(info2, "name", "³Â´óÎ°");  
	cJSON_AddNumberToObject(info2, "qq", 54321);   
	cJSON_AddStringToObject(info2, "addr", "shanghai");   
	
	cJSON *content;
	cJSON_AddItemToObject(pRoot, "Content", content=cJSON_CreateObject());  
    cJSON_AddStringToObject(content, "name", "liuwenue"); 
	cJSON_AddStringToObject(content, "addr", "nanjing");
    cJSON_AddNumberToObject(content, "number", 150930124);
	cJSON_AddFalseToObject(content, "graduate");
	cJSON_AddTrueToObject(content, "working");
	cJSON_AddNullToObject(content, "future");
	
	cJSON *time;
	cJSON_AddItemToObject(pRoot, "Time", time=cJSON_CreateObject());   
	cJSON_AddNumberToObject(time, "month", 2);   
	cJSON_AddNumberToObject(time, "day", 1);  
	cJSON_AddNumberToObject(time, "year", 2013);   
	
	return pRoot;
}

//pintf format
char*
tcJson::printFormat(cJSON *json)
{
	cout << "------cJSON_Print()--------" << endl;
 	cout << cJSON_Print(json) << endl;	
}

// print unformat
void
tcJson::printUnformat(cJSON *json)
{
	cout << "------cJSON_PrintUnformatted()------- " << endl;
	cout << cJSON_PrintUnformatted(json) << endl;
}

cJSON*
tcJson::parse(const char *cStr)
{
    cout << "-------- prase char to cJSON -------- " << endl;
	cJSON *json = cJSON_Parse(cStr);
	cout << cJSON_Print(json) << endl;
}

String 
tcJson::getValToStr(cJSON *pItem, const String &key)
{
	String str = cJSON_GetValueToStr(pItem, key);
	cout << " get the value of " << key.getCStr() << " :" << endl;
	cout << str.getCStr() << endl;
	
}   


char* 
tcJson::getStrVal(cJSON *pItem)
{
	char* str = cJSON_GetStringValue(pItem);
	cout << " get the value of string" << endl;
	cout << str << endl;
	return str;
}

int 
tcJson::getIntVal(cJSON *pItem)
{
	 int itmp = cJSON_GetIntValue(pItem);
	 cout << "get Int value " << endl;
	 return itmp;
}

double 
tcJson::getDoubleVal(cJSON *pItem)
{
	double dtmp = cJSON_GetDoubleValue(pItem);
	cout << "get double value:" << endl;
    cout <<  dtmp << endl;
	return dtmp;
}
