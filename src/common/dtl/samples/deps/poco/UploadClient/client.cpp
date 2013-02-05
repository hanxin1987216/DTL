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



using Poco::Net::ServerSocket;
using Poco::Net::MessageHeader;
using Poco::Net::HTMLForm;
using Poco::Net::NameValueCollection;
using Poco::StreamCopier;

#define DATA_BUFF_SIZE (3*1024*1024)

class POCOClientThread : public Thread
{
public:
	POCOClientThread(const String &name)
		: _name(name){}
	~POCOClientThread(){}
public:
	void run()
	{
		HttpSocket  http("192.168.1.147",9980);
		String uri("/form.php");
		std::vector<HttpParam>  params;
		
		//响应信息
		String response;
		
		String localFilePath = _name;	
		FileInputStream fin(localFilePath);
		int64 alloc_size = DATA_BUFF_SIZE;
		unsigned char *buff = (unsigned char*) malloc (alloc_size + 1);
		int len = 0;

		while (fin.available ()) {

			memset (buff, 0, alloc_size);
			len = len + fin.read (buff, alloc_size);	
			http.postContent(uri, params, (const char*)buff, alloc_size, response);
			//cout << "send: " << len << " bytes" << endl;
		}

		// free buffer
		if (buff)
			free (buff);
		buff = NULL;
	}
private:
	String		_name;
};

int main(int argc,char** argv)
{
	InitDTLibrary();
	
	if(argc != 3)
	{
		cout << "usage: input the number thread you want to run " << endl
			<< "		ex: ./test  10  /home/testfile" << endl;
			
		exit(0);
	}
	try
	{
INIT_TIME
		int n = Int::getValue(argv[1]);
		String filepath = argv[2];
		list<POCOClientThread*> threadList;
		list<POCOClientThread*>::iterator thrIter;
START_TIME		
		//new thread
		for (int i = 0; i < n; i++) {
			POCOClientThread *task =  new POCOClientThread(filepath);
			task->start();
			threadList.push_back(task);
		} 	
		
		//join
		for (thrIter = threadList.begin(); thrIter != threadList.end(); thrIter++) {
			(*thrIter)->join();
		} 
		
		//delete	
		for (thrIter = threadList.begin(); thrIter != threadList.end(); thrIter++) {
			delete (*thrIter);
			(*thrIter) = NULL;	
		}
STOP_TIME
PRINT_TIME
	}
	catch(Exception &e)
	{
		cout << e.toString().getCStr() << endl;
	}
	return 0;
}
