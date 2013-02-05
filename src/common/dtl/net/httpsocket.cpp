/***************************************************************************************************
HttpSocket.cpp:	
	C++ Foundation Library header files
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	This file contain the declaration of classes: HttpSocket通信类

Author:
	chen.dawei@datatom.com

Creating Time:
	2012-12-06
***************************************************************************************************/
#include "../prec.h"
#include "../sys/exception.h"
#include "../lang/string.h"
#include "../lang/int.h"
#include "httpsocket.h"
#include <iostream>
#include <fstream>

using namespace Poco;
using namespace Net;


#define POST_PART_NAME 			("PostData")
#define FORM_BOUNDARY			("MIME_boundary_0123456789")
#define REQUEST_CONTENT_TYPE 	("multipart/form-data;boundary=MIME_boundary_0123456789")
#define APPLICATION_MEDIA_TYPE	("multipart/form-data")



MemoryPartSource::MemoryPartSource(const char* buffer,size_t bufferSize)
	: PartSource(APPLICATION_MEDIA_TYPE)
	, _istr(buffer,bufferSize)
{

}


MemoryPartSource::MemoryPartSource(const char* buffer,size_t bufferSize, const std::string& mediaType)
	: PartSource(mediaType)
	, _istr(buffer,bufferSize)
{
}

MemoryPartSource::MemoryPartSource(const char* buffer, size_t bufferSize,const std::string& mediaType, const std::string& filename)
	: PartSource(mediaType)
	, _filename(filename)
	, _istr(buffer,bufferSize)
{	
}


MemoryPartSource::~MemoryPartSource()
{
}


std::istream& MemoryPartSource::stream()
{
	return _istr;
}


const std::string& MemoryPartSource::filename()
{
	return _filename;
}


//////////////////////////////////////////////////////////////////////////////////////////////
// public ctor
HttpSocket::HttpSocket (const String& hostIP, int port)
	: _host (hostIP)
	, _port (port)
{
}

// public dtor
HttpSocket::~HttpSocket (void)
{
}


void 
HttpSocket::setBasicAuthInfo (const String& auth_user,
							const String& auth_pwd)
{
	_authUser = auth_user;
	_authPwd = auth_pwd;
}

/**
* 发送 post请求
*/
int
HttpSocket::post (const String& uri, const vector<HttpParam>& params, String& response)
{

	Poco::Net::HTTPClientSession session(_host.getCStr(), _port);
	Poco::Net::HTTPRequest req(Poco::Net::HTTPRequest::HTTP_POST, uri.getCStr(), Poco::Net::HTTPMessage::HTTP_1_1);
	
	// 
	// basic auth
	HTTPBasicCredentials cred(_authUser.getCStr(), _authPwd.getCStr());
	cred.authenticate(req);
			
	
	Poco::Net::HTMLForm form;
	int dd_len = 0;
	for (size_t i= 0; i < params.size (); i++) { 
										
		form.add( params[i]._key.getCStr(),params[i]._value.getCStr()); 
	}
	//发送请求
	form.prepareSubmit(req);
	std::ostream& ostr = session.sendRequest(req);
	

	form.write(ostr);
	
	//接受响应信息
	return  receiveResponse(session,response);
}



/**
* 发送get请求
*/
int
HttpSocket::get (const String& uri, const vector<HttpParam>& params, String& response)
{
	Poco::Net::HTTPClientSession session(_host.getCStr(), _port);
	Poco::Net::HTTPRequest req(Poco::Net::HTTPRequest::HTTP_GET, uri.getCStr(), Poco::Net::HTTPMessage::HTTP_1_1);
	
	// 
	// basic auth
	HTTPBasicCredentials cred(_authUser.getCStr(), _authPwd.getCStr());
	cred.authenticate(req);
		
	Poco::Net::HTMLForm form;
	
	int dd_len = 0;
	for (size_t i= 0; i < params.size (); i++) {
		form.add(params[i]._key.getCStr(),params[i]._value.getCStr()); 
	}
	
	form.prepareSubmit(req);
	
	std::ostream& ostr = session.sendRequest(req);
	
	//发送请求
	form.write(ostr);
	
	//接受响应信息
	return  receiveResponse(session,response);
}


int
HttpSocket::postContent (const String& uri, 
							const vector<HttpParam>& params,
							const char* buffer, 
							size_t bufferSize, 
							String& response)
{
	Poco::Net::HTTPClientSession session(_host.getCStr(), _port);
	Poco::Net::HTTPRequest req(Poco::Net::HTTPRequest::HTTP_POST, uri.getCStr(), Poco::Net::HTTPMessage::HTTP_1_1);
	req.setContentType(REQUEST_CONTENT_TYPE);
	
	// 
	// basic auth
	HTTPBasicCredentials cred(_authUser.getCStr(), _authPwd.getCStr());
	cred.authenticate(req);
			
	
	Poco::Net::HTMLForm form(APPLICATION_MEDIA_TYPE);

	for (size_t i= 0; i < params.size (); i++) {
		form.add( params[i]._key.getCStr(),params[i]._value.getCStr()); 
	}
	
	//form添加content区
	MemoryPartSource* pSPS = new MemoryPartSource(buffer,bufferSize,APPLICATION_MEDIA_TYPE,POST_PART_NAME);
	form.addPart(POST_PART_NAME, pSPS);
	
	//发送请求
	std::ostream& ostr = session.sendRequest(req);
	
	form.prepareSubmit(req);
	form.write(ostr,FORM_BOUNDARY);
	
	//接受响应信息
	return  receiveResponse(session,response);
}

int 
HttpSocket::uploadFile(const String& uri, const vector<HttpParam>& params, const String & filePath, const String & uploadFileName,String &response)
{
	Poco::Net::HTTPClientSession session(_host.getCStr(), _port);
	Poco::Net::HTTPRequest req(Poco::Net::HTTPRequest::HTTP_POST, uri.getCStr(), Poco::Net::HTTPMessage::HTTP_1_1);
	req.setContentType(REQUEST_CONTENT_TYPE);

	// 
	// basic auth
	HTTPBasicCredentials cred(_authUser.getCStr(), _authPwd.getCStr());
	cred.authenticate(req);
	
	Poco::Net::HTMLForm form(APPLICATION_MEDIA_TYPE);
	
	int dd_len = 0;
	for (size_t i= 0; i < params.size (); i++) {
		form.add( params[i]._key.getCStr(),params[i]._value.getCStr()); 
	}
	//form添加content区		
	FilePartSource* pSPS = new FilePartSource(filePath.getCStr(),APPLICATION_MEDIA_TYPE,uploadFileName.getCStr());
	form.addPart(POST_PART_NAME, pSPS);
	
	//发送请求
	std::ostream& ostr = session.sendRequest(req);
	
	form.prepareSubmit(req);
	form.write(ostr,FORM_BOUNDARY);
	
	//接受响应信息
	return  receiveResponse(session,response);
	
}


int 
HttpSocket::receiveResponse(Poco::Net::HTTPClientSession &session,String &response)
{
	Poco::Net::HTTPResponse res;
	std::istream& rs = session.receiveResponse(res);

	std::string responseText;
	Poco::StreamCopier copier;
	copier.copyToString(rs, responseText);
	response = responseText.c_str();
	
	return res.getStatus();
}

/**
*  实现类似PHP的urlencode函数
* 
* @param s 需要urlencode的字符串
* @param len 为字符串的长度
* @param new_length  为urlencode后新字符串的长度
*/
String 
HttpSocket::php_url_encode(char const *s, int len, int *new_length)
{
	#define safe_emalloc(nmemb, size, offset)	malloc((nmemb) * (size) + (offset))
	static unsigned char hexchars[] = "0123456789ABCDEF";
	register unsigned char c;
	unsigned char *to, *start;
	unsigned char const *from, *end;

	from = (unsigned char *)s;
	end = (unsigned char *)s + len;
	start = to = (unsigned char *) safe_emalloc(3, len, 1);

	while (from < end) {
		c = *from++;

		if (c == ' ') {
			*to++ = '+';
#ifndef CHARSET_EBCDIC
		} else if ((c < '0' && c != '-' && c != '.') ||
				   (c < 'A' && c > '9') ||
				   (c > 'Z' && c < 'a' && c != '_') ||
				   (c > 'z')) {
			to[0] = '%';
			to[1] = hexchars[c >> 4];
			to[2] = hexchars[c & 15];
			to += 3;
#else /*CHARSET_EBCDIC*/
		} else if (!isalnum(c) && strchr("_-.", c) == NULL) {
			/* Allow only alphanumeric chars and '_', '-', '.'; escape the rest */
			to[0] = '%';
			to[1] = hexchars[os_toascii[c] >> 4];
			to[2] = hexchars[os_toascii[c] & 15];
			to += 3;
#endif /*CHARSET_EBCDIC*/
		} else {
			*to++ = c;
		}
	}
	*to = 0;
	if (new_length) {
		*new_length = to - start;
	}

	String ret ((char *) start);
	free (start);
	start = 0;

	return ret;
}
