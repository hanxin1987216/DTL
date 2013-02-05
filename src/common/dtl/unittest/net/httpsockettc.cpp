#include "httpsockettc.h"


CPPUNIT_TEST_SUITE_REGISTRATION(HttpSocketTest);


void HttpSocketTest::setUp()
{
	//_pSocket = new HttpSocket("127.0.0.1", 5000);
}

void HttpSocketTest::tearDown()
{
	//delete _pSocket;
}

void HttpSocketTest::testPost()
{
	HttpSocket socket("192.168.1.5", 80);
	vector<HttpParam> httpParams;
	HttpParam param("nod", "ranklist");
	httpParams.push_back(param);
	String result;
	int err = 0;
	
	//
	//	向192.168.1.5发送Post请求
	//
	try
	{
		printf("\n\tSending post command to 192.168.5...\n");
		err = socket.post("/forum.php", httpParams, result);
	}
	catch (Exception &e)
	{
		CPPUNIT_ASSERT_THROW_MESSAGE(e.getMessage().getCStr(), e, Exception);
	}
	printf("\t\tCode:\t%d\n", err);
	CPPUNIT_ASSERT(!result.isEmpty());


	//
	//	向百度发送Post请求
	//
	HttpSocket socketBaidu("www.baidu.com", 80);
	try
	{
		printf("\n\tSending post command to www.baidu.com...\n");
		err = socketBaidu.post("/index.html", httpParams, result);
	}
	catch (Exception &e)
	{
		CPPUNIT_ASSERT_THROW_MESSAGE(e.getMessage().getCStr(), e, Exception);
	}
	
	printf("\t\tCode:\t%d\n", err);

	CPPUNIT_ASSERT(!result.isEmpty());
}

void HttpSocketTest::testGet()
{
	HttpSocket socket("192.168.1.5", 80);
	vector<HttpParam> httpParams;
	HttpParam param("mod", "ranklist");
	httpParams.push_back(param);
	String result;
	int err = 0;

	
	//
	//	向192.168.1.5发送Get请求
	//
	try
	{
		printf("\n\tSending get command to 192.168.1.5...\n");
		err = socket.get("/misc.php", httpParams, result);
	}
	catch (Exception &e)
	{
		CPPUNIT_ASSERT_THROW_MESSAGE(e.getMessage().getCStr(), e, Exception);
	}
	printf("\t\tCode:\t%d\n", err);
	
	CPPUNIT_ASSERT(!result.isEmpty());
	
	
	//
	//	向google发送Get请求
	//
	httpParams.clear();
	HttpSocket socketGoogle("www.google.com.hk", 80);
	try
	{
		printf("\n\tSending get command to www.google.com.hk...\n");
		err = socketGoogle.get("", httpParams, result);
	}
	catch (Exception &e)
	{
		CPPUNIT_ASSERT_THROW_MESSAGE(e.getMessage().getCStr(), e, Exception);
	}
	printf("\t\tCode:\t%d\n", err);
	
	CPPUNIT_ASSERT(!result.isEmpty());
}
