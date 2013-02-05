/***************************************************************************************************
util.cpp:
	Copyright (c) Datatom, Inc.(2011 - 2012), All rights reserved.

Purpose:
	util for cgi
		
Author:
	Lyre
	
Creating Time:
	2012-03-31
***************************************************************************************************/
#ifndef DATRIX_APPS_CGI_CGIBASE_UTIL_H_
#define DATRIX_APPS_CGI_CGIBASE_UTIL_H_

#include "jsontextwriter.h"

#define	CGI_RET_CODE_SUCCESS		200
#define	CGI_RET_CODE_EXCPTION		300
#define CGI_RET_CODE_ERROR			400


#ifdef __WINDOWS__
	#define MAIN_FUN				int wmain (int argc, wchar_t* argv[])
	#define CANCEL_OUTPUT_ERROR
#else
	#define MAIN_FUN				int main (int argc, char** argv)
	#define CANCEL_OUTPUT_ERROR		
#endif

//
// main ����
//
#define MAIN_CODE(CgiContact, libResName, debug)						\
	MAIN_FUN															\
	{																	\
		try {															\
			CANCEL_OUTPUT_ERROR;										\
			CgiContact::OutputHead ();									\
																		\
			CgiContact contact;											\
																		\
			if (debug == true) {										\
				contact.execute (argc, argv);							\
			}															\
			else														\
				contact.execute (0, NULL);								\
		}																\
		catch (dtCGIException &e) {										\
			dtOutputExptError (e);										\
			return 1;													\
		}																\
		catch (Exception &e) {											\
			dtOutputExptError (e);										\
			return 1;													\
		}																\
																		\
		return 0;														\
	}																	\

//
// ����ָ�룬������Ӧ execute �е������
//
class dtCGIContactBase;
typedef void (dtCGIContactBase::*dtCommandFun) (void);

struct dtFuncParamTypeMap
{
	String type;
	String name;
};

struct dtCommandFunInfo
{
	dtCommandFun fun;				// �ص�����
	vector<dtFuncParamTypeMap> params;
};

//
// ������ص���Ϣ
//
struct dtCmdFunInfo
{
	String cmd;					// �����ַ�������
	dtCommandFunInfo funInfo;			
};

//
// ��� post �� get ���ݵ�����
// ������ map<key, value> ����
//
typedef map<String, String> KeyValueType;


/**
 * ��� cgi ��Դװ����
 */
IResourceReader *dtGetResLoader (IResourceReader *resLoader, const String &libResFile);

IResourceReader *dtGetCgiResLoader (const String &libResFile);


void dtOutputExptError (Exception& e);

void dtOutputInterfaceList (vector <dtCmdFunInfo> &cmds, JsonTextWriter *writer);

#endif // DATRIX_APPS_CGI_CGIBASE_UTIL_H_
