/***************************************************************************************************
cgi.h:
	Copyright (c) Datatom, Inc.(2011 - 2012), All rights reserved.

Purpose:
	cgi base
		
Author:
	Lyre
	
Creating Time:
	2012-03-26
***************************************************************************************************/
#ifndef DATRIX_APPS_CGI_CGIBASE_CGI_H_
#define DATRIX_APPS_CGI_CGIBASE_CGI_H_


class dtCGIContactBase
{
public:
	dtCGIContactBase ();
	virtual ~dtCGIContactBase();
	
	/**
	 * 添加响应 cmd 的事件函数
	 *
	 * @param cmd: 命令对应的字符串名称
	 * @param fun: 执行命令的具体函数
	 *
	 * 函数格式： void fun (void);
	 */
	void addCommandFun (const String &cmd, dtCommandFun fun);
	
	/**
	 * 添加cmd事件的参数列表
	 *
	 * @param cmd: 命令对应的字符串名称
	 * @param params: 参数列表
	 *
	 * 参数列表通过如下方式添加：
	 * 		START_PARAM_MAP(cmd)
	 *		ADD_PARAM_MAP(strtype,strname)
	 *		END_PARAM_MAP
	 */
	void addCommandFunParam (const String &cmd, vector<dtFuncParamTypeMap> &params);

	
	/**
	 * 执行命令
	 */
	#ifdef __WINDOWS__
		void execute (int argc, wchar_t* argv[]);
	#else
		void execute (int argc, char** argv);
	#endif

public:
	/**
	 * 获得 json 写对象
	 */
	JsonTextWriter *getJsonWriter (void)
	{
		return _jsonWriter;
	}
	
	int				getInt (const String &key);
	unsigned int	getUInt (const String &key);
    short			getShort (const String &key);
    unsigned short	getUShort (const String &key);
    bool			getBool (const String &key);
    String			getString (const String &key);
    int64			getInt64 (const String &key);
	
public:
	static void OutputHead ();
		
private:
	String getValue (const String &key);

	virtual String init (const String &params/* = String::EMPTY */);
	
	/**
	 * 输出执行结果
	 */
	void output (void);
	
	/**
	 * 创建 writer 对象
	 */
	void createWriter (void);
	void clearWriter (void);
	
private:
	KeyValueType 			_maps;
	//
	//
	// 响应命令的函数
	//
	vector <dtCmdFunInfo>	_cmds;
	
	String					_jsonContents;
	JsonTextWriter 			*_jsonWriter;
};



//
// 接口参数列表添加的宏定义
//
#define START_PARAM_MAP(strfuncname)	do{\
	vector<dtFuncParamTypeMap> params;		\
	dtFuncParamTypeMap tmp;					\
	String funcname = strfuncname;		\
	

#define ADD_PARAM_MAP(strtype,strname)		\
		tmp.type = _T(#strtype);				\
		tmp.name = _T(#strname);				\
		params.push_back (tmp);			\
		

#define END_PARAM_MAP	\
		addCommandFunParam(funcname, params);	\
		}while(0);


    
#endif // DATRIX_APPS_CGI_CGIBASE_CGI_H_
