/***************************************************************************************************
HttpSocket.h:	
	C++ Foundation Library header files
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	This file contain the declaration of classes: HttpSocket通信类

Author:
	chen.dawei@datatom.com

Creating Time:
	2012-12-06
***************************************************************************************************/

#ifndef __DTL_HTTP_SOCKET_H__DAWEI
#define __DTL_HTTP_SOCKET_H__DAWEI

#if PRAGMA_ONCE
#	pragma once
#endif

#include <Poco/Net/HTTPClientSession.h>
#include <Poco/URI.h>
#include <Poco/Net/HTTPCredentials.h>
#include <Poco/Net/HTTPBasicCredentials.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTMLForm.h>
#include <Poco/Net/PartHandler.h>
#include <Poco/Net/MessageHeader.h>
#include <Poco/Net/ServerSocket.h>
#include <Poco/StreamCopier.h>
#include <Poco/Net/Net.h>
#include <Poco/Net/NameValueCollection.h>
#include <Poco/Net/PartSource.h>
#include <Poco/MemoryStream.h>
#include <Poco/Net/FilePartSource.h>
#include <Poco/Net/StringPartSource.h>
#include <Poco/FileStream.h>
#include <iostream> 

using Poco::Net::ServerSocket;
using Poco::Net::MessageHeader;
using Poco::Net::HTMLForm;
using Poco::Net::NameValueCollection;
using Poco::StreamCopier;


#include "string.h"

#ifndef __WINDOWS__
	#include <stdio.h>
	#include <stdlib.h>
	#include <arpa/inet.h>
	#include <netdb.h>

	#include <netinet/in.h>  
	#include <sys/socket.h>
#endif

//////////////////////////////////////////////////////////////////
///  An implementation of PartSource for Memory data

class  MemoryPartSource: public Poco::Net::PartSource

{
public:

	MemoryPartSource(const char* buffer,size_t bufferSize);

	
	MemoryPartSource(const char* buffer,size_t bufferSize, const std::string& mediaType);

		
	MemoryPartSource(const char* buffer,  size_t bufferSize, const std::string& mediaType,const std::string& filename);


	~MemoryPartSource();
		
	std::istream& stream();
		
	const std::string& filename();

private:
	Poco::MemoryInputStream		_istr;
	std::string       			_filename;
	
	MemoryPartSource(const MemoryPartSource&);
	MemoryPartSource& operator = (const MemoryPartSource&);
};

/////////////////////////////////////////
/**
* HTTP Form 表单请求KV值
*/
struct HttpParam
{
public:
	HttpParam(const String& key, const String& value)
		: _key(key)
		,_value (value)
	{
	}
		
public:
	String _key;			// http 参数名 
	String _value;		// http 参数值
};


//////////////////////////////////////////////
///标准URL：
///    http://192.168.1.147:8880/form.php


/**
*  网卡管理
*/
class DTL_DLLEXPORT HttpSocket
{
public:
	HttpSocket (const String& hostIP, int port = 80);
	~HttpSocket (void);

	/**
	* 设置Basic认证信息
	*/
	void setBasicAuthInfo (const String& auth_user = HTTP_BASIC_AUTH_USER,
							const String& auth_pwd = HTTP_BASIC_AUTH_PASSWORD);
	
public:
	/**
	* 发送 HTTP POST 请求
	* 
	* @param uri      请求发送的目的url地址 ex:   /form.php
	* @param params   KV参数，通过form表单发送 
	* @param response 相应消息 (已经去除消息头，只返回数据部分)
	*
	* @throw Exception  网络错误等抛异常
	*
	* @return 错误码， 返回错误码, 200， 500等， 
	**/
	int post (const String& uri, 
				const vector<HttpParam>& params, 
				String& response);
	

	/**
	* 发送 HTTP GET 请求
	* 
	* @param uri      请求发送的目的url地址 ex:/form.php
	* @param params    KV参数，可以是多个
	* @param response 相应消息 (已经去除消息头，只返回数据部分)
	*
	* @throw Exception  网络错误等抛异常
	*
	* @return 错误码， 返回错误码, 200， 500等， 
	**/
	int get (const String& uri, 
				const vector<HttpParam>& params, 
				String& response);


	/**
	* 发送 HTTP POST 请求
	* 
	* @param uri      请求发送的目的url地址   ex:/form.php
	* @param Params   KV参数，通过form表单发送
	* @param content  放在content 区传递内容
	* @param response 相应消息 (已经去除消息头，只返回数据部分)
	*
	* @throw Exception  网络错误等抛异常
	*
	* @return 错误码， 返回错误码, 200， 500等， 
	**/
	int postContent (const String& uri, 
						const vector<HttpParam>& Params,
						const char* buffer, 
						size_t bufferSize,
						String& response);
	
	/**
	* HTTP upload file
	* 
	* @param uri      		请求发送的目的url地址   ex:/form.php
	* @param Params   		KV参数，通过form表单发送
	* @param localFilePath 	要上传的本地文件全路径
	* @param uploadFileName 上传的文件在服务器显示的文件名.
	* @param response 	    相应消息 (已经去除消息头，只返回数据部分)
	*
	* @throw Exception  网络错误等抛异常
	*
	* @return 错误码， 返回错误码, 200， 500等， 
	**/
	int uploadFile(const String& uri, 
					const vector<HttpParam>& params, 
					const String & localFilePath,
					const String& uploadFileName, 
					String &response);
	
	
protected:

	///接收响应信息
	int receiveResponse(Poco::Net::HTTPClientSession &session, String &response);

	///实现类似PHP的urlencode函数 
	String php_url_encode(char const *s, int len, int *new_length);
	
private:
	String		_host;		// 主机 IP
	int			_port;		// 连接端口号,	// 默认为80
	
	String		_authUser;
	String		_authPwd;
}; // End class HttpSocket


#endif // __DTL_HTTP_SOCKET_H__
