
#include <dtprec.h>
#include <dtl/dtl.h>

#include "Poco/Net/HTTPServer.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPServerParams.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTTPServerParams.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/WebSocket.h"
#include "Poco/Net/NetException.h"
#include "Poco/Util/ServerApplication.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/HelpFormatter.h"
#include "Poco/Format.h"
#include <iostream>


using Poco::Net::ServerSocket;
using Poco::Net::WebSocket;
using Poco::Net::WebSocketException;
using Poco::Net::HTTPRequestHandler;
using Poco::Net::HTTPRequestHandlerFactory;
using Poco::Net::HTTPServer;
using Poco::Net::HTTPServerRequest;
using Poco::Net::HTTPResponse;
using Poco::Net::HTTPServerResponse;
using Poco::Net::HTTPServerParams;
using Poco::Timestamp;
using Poco::ThreadPool;
using Poco::Util::ServerApplication;
using Poco::Util::Application;
using Poco::Util::Option;
using Poco::Util::OptionSet;
using Poco::Util::HelpFormatter;

#define SEND_LENGTH (4)

class TestThread : public Thread
{
public:
	TestThread (int argc, char** argv)
		: _argc (argc)
		, _argv(argv)
	{
	}
	
	void run ()
	{
	
		if (_argc < 4) {
			cout << "usege: ./app host port uri(/ws)" << endl;
		}	
		
		String host = _argv[1];
		int	port	= Int::getValue(_argv[2]);
		String uri = _argv[3];
		
		char *buffer = new char[SEND_LENGTH];
		memset(buffer, 'a', SEND_LENGTH );
		
		char *recvBuffer = new char[100];
		
	
		Poco::Net::HTTPClientSession session(host.getCStr(), port);
		Poco::Net::HTTPRequest req(Poco::Net::HTTPRequest::HTTP_GET, uri.getCStr(), Poco::Net::HTTPMessage::HTTP_1_1);
		Poco::Net::HTTPResponse res;
	
		WebSocket socket(session, req, res);
		int i = 0;
		while (i++ < 1000){
			int sendLen = 0;
			while (sendLen < SEND_LENGTH) {
				int len = socket.sendFrame (buffer, SEND_LENGTH, WebSocket::FRAME_BINARY);	
				sendLen += len;
			}

			int flags= 0;
			socket.receiveFrame ((void*)recvBuffer, 10, flags);
			recvBuffer[10] = '\0';
			
			cout << "recv: " << i << ", " << recvBuffer << endl;
			
		}
		socket.shutdown();
		
		delete []buffer;
		delete []recvBuffer;
	}

private:
	int 		_argc;
	char** 		_argv;
	
};


int main(int argc, char** argv)
{ 
	InitDTLibrary();
	try
	{	
		vector<TestThread*> threads;
		for (int i = 0; i < 1; i++) {
			TestThread *thread = new TestThread (argc, argv);
			threads.push_back (thread);
			
			thread->start();
		}
		
		for (int j=0; j < threads.size(); j++) {
			threads[j]->join();
		}
		
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


