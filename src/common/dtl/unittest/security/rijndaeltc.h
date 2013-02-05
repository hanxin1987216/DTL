/***************************************************************************************************
rijndaeltc.h:	
	C++ Foundation Library TestCase header files
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	rijndael ≤‚ ‘

Author:
	yan.zhineng@datatom.com

Creating Time:
	2012-3-20
***************************************************************************************************/
#ifndef __RIJNDAEL_TC_H__
#define __RIJNDAEL_TC_H__

#include <cppunit/tester.h>


class RijndaelTestCase : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE (RijndaelTestCase);

		CPPUNIT_TEST_DESCRIPTION (init,_T("≤‚ ‘Rijndael,init  ") );	
//		CPPUNIT_TEST_DESCRIPTION ( );	

	CPPUNIT_TEST_SUITE_END ();
	
public:
	void setUp (void)
	{
	
	}
	
	void tearDown (void)
	{
	
	}
	
protected:
	
	void init (void);
private:
}; // End class Rc4TestCase

#endif // __RC4_TC_H__

