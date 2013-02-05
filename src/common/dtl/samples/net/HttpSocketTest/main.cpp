/***************************************************************************************************
 main.cpp
	C++ Network Library, Copyright (c) Datatom Software, Inc.(2012)

Author:
	chen.dawei@datatom.com
Creating Time:
	2012-11-5
***************************************************************************************************/
#include <dtprec.h>
#include <dtl/dtl.h>
#import <Poco/Net/HTTPClientSession.h>
#import <Poco/URI.h>
#import <Poco/Net/HTTPCredentials.h>
#import <Poco/Net/HTTPBasicCredentials.h>
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTMLForm.h"
#include "Poco/Net/PartHandler.h"
#include "Poco/Net/MessageHeader.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/StreamCopier.h"
#include "Poco/Net/Net.h"
#include "Poco/Net/NameValueCollection.h"
#include "Poco/Net/PartSource.h"
#include <Poco/Net/FilePartSource.h>
#include <Poco/Net/StringPartSource.h>
#include <Poco/FileStream.h>
#include "Poco/Exception.h"

using Poco::Net::ServerSocket;
using Poco::Net::MessageHeader;
using Poco::Net::HTMLForm;
using Poco::Net::NameValueCollection;
using Poco::StreamCopier;

#define TEST_POST			"post"
#define TEST_GET			"get"
#define TEST_UPLOAD			"upload"
#define TEST_POST_CONTENT	"postcontent"

void splitParam(String &pa, std::vector<HttpParam>	&params)
{
	std::vector<String>	vt1;
	std::vector<String>	vt2;
	vt1.clear();
	pa.split(":", vt1);	
	size_t n = 0;
	
	for (n = 0;  n < vt1.size(); n++)
	{
		vt1[n].split("=",vt2);
			
		if(vt2.size() != 2)
		{
			cout << "Error key value " << endl;
			exit(1);
		}		
		HttpParam param(vt2[0],vt2[1]);
		params.push_back(param);	
		vt2.clear();
		
	}
}

void help()
{
	cout << "usage: Error use" << endl
		 << "Sample:./tc_http	get		URL	key1=value1:key2=value2 " << endl
		 <<	"	./tc_http	post		URL	key1=value1:key2=value2 " << endl
		 <<	"	./tc_http	upload		URL	key1=value1:key2=value2	localfilepath	uploadname(the name you want show in server)" << endl
		 <<	"	./tc_http	postcontent	URL	key1=value1:key2=value2	content " << endl;
	
	exit(1);
}

int main(int argc, char** argv)
{ 
	InitDTLibrary();
	try
	{
		if(argc < 3)
			help();
		
		//传输模式及URL
		String  method = argv[1];
		Poco::URI url(argv[2]);  
		String uri(url.getPath());
		HttpSocket  http(url.getHost().c_str(),url.getPort());
		
		//传输参数 KV
		std::vector<HttpParam>  params;
		String pa = argv[3];
		splitParam(pa,params);
		
		//响应信息
		String response;
		
		//test get
		if(method.compareIgnoreCase(TEST_GET) == 0)
		{
			if(argc != 4)
				help();			
				
			cout << http.get(uri, params, response) << endl;
		}
		//test post
		else if (method.compareIgnoreCase(TEST_POST) == 0)
		{
			if(argc != 4)
				help();
				
			cout << http.post(uri, params, response) << endl;
		}
		//test postcontent
		else if (method.compareIgnoreCase(TEST_POST_CONTENT) == 0)
		{
			if(argc != 5)
				help();
			
			const char* content = argv[4];
			size_t size = sizeof(content);
			cout << http.postContent(uri, params, content, size, response) << endl;
		}
		//test upload
		else if (method.compareIgnoreCase(TEST_UPLOAD) == 0)
		{
			if(argc != 6)
				help();
			
			String loaclfilepath = argv[4];
			String uploadfilename = argv[5];
			cout << http.uploadFile(uri, params, loaclfilepath ,uploadfilename,response) << endl;
		}		
		else 
		{
			help();
		}

		params.clear();
		cout << response.getCStr() << endl;	
	}
	catch(Poco::Exception &e)
	{
		cout << e.what() << endl;
	}
	catch (Exception &exp)
	{
		cout << exp.toString().getCStr() << endl;
	}
	
	return 0;
}
