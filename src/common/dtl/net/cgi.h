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
	 * �����Ӧ cmd ���¼�����
	 *
	 * @param cmd: �����Ӧ���ַ�������
	 * @param fun: ִ������ľ��庯��
	 *
	 * ������ʽ�� void fun (void);
	 */
	void addCommandFun (const String &cmd, dtCommandFun fun);
	
	/**
	 * ���cmd�¼��Ĳ����б�
	 *
	 * @param cmd: �����Ӧ���ַ�������
	 * @param params: �����б�
	 *
	 * �����б�ͨ�����·�ʽ��ӣ�
	 * 		START_PARAM_MAP(cmd)
	 *		ADD_PARAM_MAP(strtype,strname)
	 *		END_PARAM_MAP
	 */
	void addCommandFunParam (const String &cmd, vector<dtFuncParamTypeMap> &params);

	
	/**
	 * ִ������
	 */
	#ifdef __WINDOWS__
		void execute (int argc, wchar_t* argv[]);
	#else
		void execute (int argc, char** argv);
	#endif

public:
	/**
	 * ��� json д����
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
	 * ���ִ�н��
	 */
	void output (void);
	
	/**
	 * ���� writer ����
	 */
	void createWriter (void);
	void clearWriter (void);
	
private:
	KeyValueType 			_maps;
	//
	//
	// ��Ӧ����ĺ���
	//
	vector <dtCmdFunInfo>	_cmds;
	
	String					_jsonContents;
	JsonTextWriter 			*_jsonWriter;
};



//
// �ӿڲ����б���ӵĺ궨��
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
