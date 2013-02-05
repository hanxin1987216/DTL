/***************************************************************************************************
exceptiontc.cpp:	
	C++ Foundation Library TestCase cpp files
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	Exception 测试

Author:
	fan.fei@datatom.com

Creating Time:
	2012-3-15
***************************************************************************************************/
#include <dtprec.h>
#include <cppunit/tester.h>
#include <dtl/dtl.h>

#include "exceptiontc.h"

CPPUNIT_TEST_SUITE_REGISTRATION( ExceptionTestCase );

void
ExceptionTestCase::setUp(void) {
}

void 
ExceptionTestCase::tearDown(void) {
}

void
ExceptionTestCase::testGetMessage(void) {
    Exception evoid;
    CPPUNIT_ASSERT(evoid.getMessage() == String());

    Exception ec1 = Exception("test","exceptiontc.cpp",1024);
    CPPUNIT_ASSERT(ec1.getMessage() == String("test"));

    Exception ec2 = Exception("test2","exceptiontc.cpp",1025, ec1);
    CPPUNIT_ASSERT(ec2.getMessage() == String("test2"));
}

void
ExceptionTestCase::testToString(void) {
    Exception evoid;
    String standard;
    standard.format("Error:%s, Error Provider:%s, File:%s, Line:%d",
                    "",
                    _T("Unknown Provider"),
                    "",
                    0);

    CPPUNIT_ASSERT(evoid.toString() == standard);

    Exception ec1 = Exception("test",
                            "exceptiontc.cpp",
                            100, //line
                            10,  //errId
                            ncGetDTLErrorProvider());
    //CPPUNIT_ASSERT(ec1.toString() == String("Error:test, ErroCode:10, Error Provider:DTL, File:exception.cpp, h
    standard.format("Error:%s, ErrorCode:%d, Error Provider:%s, File:%s, Line:%d",
                    "test",
                    10,
                    ec1.getErrorProvider()->getProviderName().getCStr(),
                    "exceptiontc.cpp",
                    100);
    //cout<<"  " << ec1.toString().getCStr()<<endl;
    CPPUNIT_ASSERT(ec1.toString() == standard);

    Exception ec2 = Exception("test2",
                            "exceptiontc.cpp",
                            101, //line
                            11);  //errId
    standard.format("Error:%s, ErrorCode:%d, Error Provider:%s, File:%s, Line:%d",
                    "test2",
                    11,
                    _T("Unknown Provider"),
                    "exceptiontc.cpp",
                    101);
    CPPUNIT_ASSERT(ec2.toString() == standard);
}

void
ExceptionTestCase::testGetAdditionalInfo(void) {
    Exception evoid;
    CPPUNIT_ASSERT(evoid.getAdditionalInfo() == String());

    Exception ec1 = Exception("ec1", "this", 0);
    CPPUNIT_ASSERT(ec1.getAdditionalInfo() == String());

    Exception ec2 = Exception("ec2", "this", 1, ec1);
    CPPUNIT_ASSERT(ec2.getAdditionalInfo() == ec1.toString());

    Exception ec3 = Exception("ec3", "this", 2, ec2);
    CPPUNIT_ASSERT(ec3.getAdditionalInfo() == ec2.toString() + ec1.toString());
}

void
ExceptionTestCase::testToFullString(void) {
    Exception evoid;
    CPPUNIT_ASSERT(evoid.toFullString() == evoid.toString());

    Exception ec1 = Exception("ec1", "this", 0);
    CPPUNIT_ASSERT(ec1.toFullString() == ec1.toString() + ec1.getAdditionalInfo());

    Exception ec2 = Exception("ec2", "this", 1, ec1);
    CPPUNIT_ASSERT(ec2.toFullString() == ec2.toString() 
                                        + "Additional Info:"
                                        + ec2.getAdditionalInfo());
}

void
ExceptionTestCase::testClone(void) {
    //Exception segmentfault = Exception("ec2", "this", 1, segmentfault);
    Exception evoid;
    CPPUNIT_ASSERT(evoid.toFullString() == evoid.toString());
    const Exception *evoidc = evoid.clone();
    CPPUNIT_ASSERT(evoidc->toFullString() == evoid.toFullString());
    delete evoidc;

    Exception ec1 = Exception("ec1", "this", 0);
    const Exception *ec1c = ec1.clone();
    CPPUNIT_ASSERT(ec1c->toFullString() == ec1.toFullString());
    delete ec1c;

    Exception ec2 = Exception("ec2", "this", 1, ec1);
    const Exception *ec2c = ec2.clone();
    CPPUNIT_ASSERT(ec2c->toFullString() == ec2.toFullString());
    delete ec2c;
}

void
ExceptionTestCase::testGetBaseException(void) {

    Exception ec1 = Exception("ec1", "this", 0);
    Exception ec2 = Exception("ec2", "this", 1, ec1);
    Exception ec3 = Exception("ec3", "this", 2, ec2);
    CPPUNIT_ASSERT(ec3.getBaseException()->getMessage() == String("ec1")); 
}

void
ExceptionTestCase::testGetErrorId(void) {

    Exception ec1 = Exception("ec1", "this", 0);
    CPPUNIT_ASSERT(ec1.getErrorId() == 0);
}

void
ExceptionTestCase::testErrorProvider(void) {

    Exception ec1;
    ec1.setErrorProvider(ncGetDTLErrorProvider());
    CPPUNIT_ASSERT(ec1.getErrorProvider() == ncGetDTLErrorProvider());
}

void
ExceptionTestCase::testGetCause(void) {
    Exception ec1 = Exception("ec1", "this", 0);
    Exception ec2 = Exception("ec2", "this", 1, ec1);
    Exception ec3 = Exception("ec3", "this", 2, ec2);
    CPPUNIT_ASSERT(ec3.getCause()->getMessage() == String("ec2")); 
    CPPUNIT_ASSERT(ec2.getCause()->getMessage() == String("ec1")); 
}

void
ExceptionTestCase::testOperatorAssign(void) {
    Exception ec1 = Exception("ec1", "this", 0);
    Exception ec2 = Exception("ec2", "this", 1, ec1);
    Exception ec3 = Exception("ec3", "this", 2, ec2);
    Exception ec3a = ec3;
    CPPUNIT_ASSERT(ec3a.getCause()->getMessage() == String("ec2")); 
    CPPUNIT_ASSERT(ec3a.getBaseException()->getMessage() == String("ec1")); 
    CPPUNIT_ASSERT(&ec3a != &ec3);
    CPPUNIT_ASSERT(ec3a.getCause() != ec3.getCause());
}
