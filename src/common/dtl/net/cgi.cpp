/***************************************************************************************************
cgi.cpp:
	Copyright (c) Datatom, Inc.(2011 - 2012), All rights reserved.

Purpose:
	cgi base
		
Author:
	Lyre
	
Creating Time:
	2012-03-26
***************************************************************************************************/
#include <dtprec.h>
#include "../prec.h"
#include "../sys/exception.h"
#include "../lang/string.h"
#include "../lang/int64.h"
#include "../lang/int.h"
#include "../lang/uint.h"
#include "../util/resreader.h"


#include "cgiutil.h"
#include "jsontextwriter.h"
#include "cgiexcept.h"
#include "cgi.h"

#define COMMAND_KEY 			"type"

IResourceReader* cgiResLoader = NULL;

#define LOAD_STRING(IDS)				\
		cgiResLoader->loadString (IDS)
		
		
/*
 * 将十六进制表示的字符转换为 ASCII 表示的字符 （%D4：212）
 *
 * @chars 十六进制表示的字符
 *
 * @return 转换后十进制表示的字符
 */
int intFromHex (const char *chars) // 将"##"转换成十进制数
{  
	int Hi, Lo, Result; 
	Hi = chars[0]; 
	
	if('0'<=Hi && Hi<='9') 
		Hi -= '0'; 
	else if ('A'<=Hi && Hi<='F') 
		Hi -= 'A' - 10; 
	else if ('a'<=Hi && Hi<='f') 
		Hi -= 'a' - 10; 
	else
		return -1;
		
	Lo = chars[1]; 
	
	if('0'<=Lo && Lo<='9') 
		Lo -= '0'; 
	else if ('A'<=Lo && Lo<='F') 
		Lo -= 'A' - 10; 
	else if ('a'<=Lo && Lo<='f') 
		Lo -= 'a' - 10; 
	else
		Lo = -1;
		
	if (Lo != -1) {
		Result = Lo | (Hi << 4);
//		(*chars) += 2;
	}
	else {
		Result = Hi;
//		(*chars)++;
	}

	return (Result); 
}

////////////////////////////////////////////////////////////////////////////
//
// class dtCGIParseData
//
class dtCGIParseData
{
public:
    dtCGIParseData (const String &params, KeyValueType &maps)
		: _params (params)
		, _maps (maps)
	{
		if (_params.isEmpty () == true)
		{
			//
			// 从 getenv 获得参数
			//
			getParams ();
		}
		
		//
		// 初始化并解析出数据
		//
		parse ();
	}
    virtual ~dtCGIParseData()
    {

    }
	
private:
	void getParams ()
	{
		try {
			char *content = NULL;
            char *poststr = NULL;
			char *requestMethod = ::getenv ("REQUEST_METHOD");
			
			if (requestMethod == NULL) {
				throw (LOAD_STRING(_T("IDS_CGI_GET_REQUEST_METHOD_FAILED")));
			}
			
			if (strcmp (requestMethod, "GET") == 0)
			{
				content = ::getenv ("QUERY_STRING");
			}
			else if (strcmp (requestMethod, "POST") == 0)
			{
			    char *lenstr = ::getenv ("CONTENT_LENGTH");
			    if(lenstr != NULL){
    			    int length = atoi(lenstr);
    			    poststr = (char *)malloc(sizeof(char) * length + 1);
                    memset(poststr, 0, length + 1);
    			    if(NULL != poststr){
                        fread(poststr, 1 , length, stdin);
                        content = poststr;
    			    }
                }
			}
			if (content != NULL)
				 _params = String (content, strlen (content));
				 
		    if(poststr != NULL) 
		        free(poststr);
		}
		catch (String &s)
		{
			CGI_THROW(s);
		}
		catch (...)
		{
			CGI_THROW(LOAD_STRING(_T("IDS_CGI_READ_PARAM_ERROR")));
		}
	}
	
    void parse ()
    {
		size_t i = 0;
		size_t length = _params.getLength ();
		String content = _params;
		tchar_t c;
		String str;
		
		for (i = 0; i < length; i++)
		{
		    c = content[i];
	        if (c == '&')
	        {
	            size_t pos = str.find ('=');
	            if (pos != String::NO_POSITION)
	            {
	                String key = str.subString (0, pos);
	                String value = str.subString (pos + 1, str.getLength () - pos);
	                _maps.insert (pair<String, String>(key, value));
	                str = "";
	            }
		        
		    }
		    else if (c == '%')
		    {
		        tchar_t tmp[2];
		        tmp[0] = content[i+1];
		        tmp[1] = content[i+2];
		        int res = intFromHex (tmp);
	            if(res > 0)
	            {
	                tchar_t x = (tchar_t)res;
	                str.append (x, 1);    
	            }
		        i += 2;
		    }
		    else if (c == '+')
		    {
		        str.append (' ', 1);
			}
			else
			{
		        str.append (c, 1); 
		    }
		}
		
		if (str.getLength () > 0)
		{
	        size_t pos = str.find ('=');
	        if(pos != String::NO_POSITION)
	        {
	            String key = str.subString (0, pos);
	            String value = str.subString (pos + 1, str.getLength() - pos);
	            _maps.insert (pair<String, String>(key, value));
	            str = "";
	        }
		}
	}

private:
	String _params;
	KeyValueType &_maps;
};

////////////////////////////////////////////////////////////////////////////
//
// class dtCGIContactBase
//
// public
dtCGIContactBase::dtCGIContactBase (void)
	: _maps ()
	, _cmds ()
	, _jsonContents ()
	, _jsonWriter (NULL)
{
	createWriter ();
	cgiResLoader = dtGetCgiResLoader ("cgi");
}

dtCGIContactBase::~dtCGIContactBase (void)
{
	clearWriter ();
	
	if (cgiResLoader != NULL)
	{
		delete cgiResLoader;
		cgiResLoader = NULL;
	}
}

void
dtCGIContactBase::createWriter (void)
{
	//
	// TODO:
	//
	_jsonWriter = new JsonTextWriter;
}

void
dtCGIContactBase::clearWriter (void)
{
	if (_jsonWriter != NULL)
	{
		delete _jsonWriter;
		_jsonWriter = NULL;
	}
	
	_jsonContents.clear ();
}

void dtCGIContactBase::addCommandFun (const String &cmd,
								 	dtCommandFun fun)
{
	dtCmdFunInfo cmdFun;
	cmdFun.cmd = cmd;
	cmdFun.funInfo.fun = fun;
	
	_cmds.push_back (cmdFun);
}

void dtCGIContactBase::addCommandFunParam (const String &cmd,
								 	vector<dtFuncParamTypeMap> &params)
{
	for (size_t i = 0; i < _cmds.size (); ++i) {
		
		if (cmd == _cmds[i].cmd) {
			
			for (size_t j = 0; j < params.size (); ++j) {
				_cmds[i].funInfo.params.push_back (params[j]);
			}
		}
	}
	
}

String dtCGIContactBase::init (const String &params/* = String::EMPTY */)
{
	dtCGIParseData parseData (params, _maps);
	String command = this->getValue (COMMAND_KEY);
	return command;
}

void dtCGIContactBase::output (void)
{
	_jsonContents = _jsonWriter->getJsonStr ();
	//
	// TODO:输出字符格式（UTF8）
	//
	cout<<_jsonContents.getCStr ()<<endl;
}

#ifdef __WINDOWS__
void dtCGIContactBase::execute (int argc, wchar_t* argv[])
#else
void dtCGIContactBase::execute (int argc, char** argv)
#endif
{
	String params = String::EMPTY;
	
	if (argc == 1) {
		CGI_THROW(LOAD_STRING(_T("IDS_CGI_READ_CMD_PARAM_ERROR")));
	}
	else if (argc >= 2) {
		params = argv[1];
		
		if (params == "__debug_listInterface") {
			dtOutputInterfaceList (_cmds, _jsonWriter);
			this->output ();
			return ;
		}
	}
	
	String command = init (params);

	//
	// 忽略大小写查找
	//
	vector <dtCmdFunInfo>::iterator it, itend = _cmds.end ();
	for (it = _cmds.begin (); it != itend; ++it) {
		if (it->cmd.compare (command) == 0)
			break;
	}
	
	if (it == itend) {
		CGI_THROW(LOAD_STRING(_T("IDS_CGI_UNKNOWN_COMMAND_TYPE")));
	}
	
	dtCmdFunInfo &cmdFun = (*it);
	
	//
	// 执行命令
	//
	dtCommandFun fun = cmdFun.funInfo.fun;
	(this->*fun) ();

	//
	// 输出 json 信息
	//
	this->output ();
}


String dtCGIContactBase::getValue (const String &key)
{
	map<String, String>::const_iterator cit = _maps.find(key);
	if (cit == _maps.end ()) {
		String msg;
		msg.format (LOAD_STRING(_T("IDS_CGI_UNMATCH_KEY")).getCStr (), key.getCStr ());
		CGI_THROW(msg)
	}
	return (*cit).second;
}


int dtCGIContactBase::getInt (const String& key)
{
	String valueStr = this->getValue (key);
	int value = Int::getValue (valueStr);
	return value;
}

unsigned int dtCGIContactBase::getUInt (const String &key)
{
	String valueStr = this->getValue (key);
	unsigned int value = UInt::getValue (valueStr);
	return value;
}

short dtCGIContactBase::getShort (const String& key)
{
	String valueStr = this->getValue (key);
	short value = (short)Int::getValue (valueStr);
	return value;
}

unsigned short dtCGIContactBase::getUShort (const String& key)
{
	String valueStr = this->getValue (key);
	unsigned short value = (unsigned short) UInt::getValue (valueStr);
	return value;
}

bool dtCGIContactBase::getBool (const String &key)
{
	String valueStr = this->getValue (key);
	bool value = false;
	
	if(valueStr == "1" || valueStr == "true")
		value = true;    
	else if(valueStr == "0" || valueStr == "false")
		value = false;
	else
	{
		String msg;
		msg.format (LOAD_STRING(_T("IDS_CGI_UNMATCH_VALUE_TYPE")).getCStr (), key.getCStr ());
		CGI_THROW(msg)
	}  
	return value;
}

String dtCGIContactBase::getString (const String &key)
{
	return this->getValue (key);
}

int64 dtCGIContactBase::getInt64 (const String &key)
{
	String valueStr = this->getValue (key);
	int64 value = Int64::getValue (valueStr);
	return value;
}

void dtCGIContactBase::OutputHead ()
{
	cout<<"Content-type: application/json charset=utf8\n\n";
}
