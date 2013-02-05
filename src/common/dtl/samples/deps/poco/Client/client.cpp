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
#include <iostream> 
#include <dtl/dtl.h>

using Poco::Net::ServerSocket;
using Poco::Net::MessageHeader;
using Poco::Net::HTMLForm;
using Poco::Net::NameValueCollection;
using Poco::StreamCopier;
using namespace Poco;
using namespace Net;




int main()
{
INIT_TIME
	std::string strURI = "http://192.168.1.147:8800/form.php"; 
	Poco::URI uri(strURI);  
	std::string path(uri.getPath());

	Poco::Net::HTTPClientSession session(uri.getHost(), uri.getPort());
	Poco::Net::HTTPRequest req(Poco::Net::HTTPRequest::HTTP_POST, path, Poco::Net::HTTPMessage::HTTP_1_1);
	req.setContentType("multipart/form-data;boundary=MIME_boundary_0123456789");
	req.setChunkedTransferEncoding(true);	
	// 信息验证
	//Add username and password (HTTP basic authentication) to the request.
	//Poco::Net::HTTPBasicCredentials cred("domain\\uid", "password");
	//cred.authenticate(req);

	//json包
	String loginname("1005");
	String pwd("123");
	String ip("192.168.1.38");
	String ip1("192.168.1.138");
	cJSON *root;
	root=cJSON_CreateObject();	
	cJSON_AddStringToObject(root, "cmd",loginname.getCStr());
	cJSON_AddStringToObject(root, "pwd",pwd.getCStr());
	cJSON_AddStringToObject(root, "ip",ip.getCStr());
	cJSON_AddStringToObject(root, "ip1",ip1.getCStr());
	char* buffer = cJSON_Print(root);
	cJSON_Delete(root);
		
	//构造form表单
	Poco::Net::HTMLForm form("multipart/form-data");	//if no param can use --->form.setEncoding("multipart/form-data");
	form.set("param",buffer);
	form.set("cmd","1005");
START_TIME
	//upload file
	std::string 	name("file");
	FilePartSource* pSPS = new FilePartSource("/home/testfile","text/plain");	
	form.addPart(name,pSPS);
	
	//设置超时限制
	const Poco::Timespan	time(60000000);
	session.setTimeout(time);

	std::ostream& ostr = session.sendRequest(req);

	//发送请求
	form.prepareSubmit(req);
	form.write(ostr,"MIME_boundary_0123456789");
	 

	//接受响应信息
	Poco::Net::HTTPResponse res;
	std::istream& rs = session.receiveResponse(res);

	std::string responseText;
	Poco::StreamCopier copier;
	copier.copyToString(rs, responseText);
STOP_TIME
PRINT_TIME
	std::cout << responseText << std::endl;

	return 0;
}