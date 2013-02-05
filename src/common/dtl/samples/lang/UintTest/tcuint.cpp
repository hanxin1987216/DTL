/***************************************************************************************************
tcdate.cpp:	
	C++ Foundation Library header files
	Copyright (c) Datatom Software, Inc.(2012)

Purpose:
test the date function

Author:
	应业敏

Creating Time:
	2012-2-9
***************************************************************************************************/
#include <dtprec.h>
#include <dtl.h>
#include "../../../lang/uint.h"

class TcUInt
{
public:
	void toString ( void );
};

void
TcUInt::toString ( void )
{
	cout << "test the toString ():" << endl;

	String str;
	str = UInt::toString ( (unsigned int) 6 );
	cout << "the str is:" << str.getCStr () << endl;

	str = UInt::toString ( (unsigned int) 556 );
	cout << "the str is:" << str.getCStr () << endl;

	str = UInt::toString ( (unsigned int) -556 );
	cout << "the str is:" << str.getCStr () << endl;

	str = UInt::toString ( (unsigned int) 0xaa6 );
	cout << "the str is:" << str.getCStr () << endl;

	str = UInt::toString ( (unsigned int) -0xaa6 );
	cout << "the str is:" << str.getCStr () << endl;

	str = UInt::toString ( (unsigned int) 0776 );
	cout << "the str is:" << str.getCStr () << endl;

	str = UInt::toString ( (unsigned int) -0776 );
	cout << "the str is:" << str.getCStr () << endl;

	str = UInt::toString ( (unsigned int) 0000 );/////输出0
	cout << "the str is:" << str.getCStr () << endl;

	str = UInt::toString ( (unsigned int) -0000 );/////输出0
	cout << "the str is:" << str.getCStr () << endl;

	str = UInt::toString ( (unsigned int) 0006 );/////输出6
	cout << "the str is:" << str.getCStr () << endl;

	str = UInt::toString ( (unsigned int) -0006 );/////输出6
	cout << "the str is:" << str.getCStr () << endl;

	str = UInt::toString ( (unsigned int) 'a' );
	cout << "the str is:" << str.getCStr () << endl;

	str = UInt::toString ( (unsigned int) -'a' );
	cout << "the str is:" << str.getCStr () << endl;

	str = UInt::toString ( (unsigned int) '1234' );
	cout << "the str is:" << str.getCStr () << endl;

	str = UInt::toString ( (unsigned int)  -'1234' );
	cout << "the str is:" << str.getCStr () << endl;

	str = UInt::toString ( (unsigned int)  '\$' );////输出36
	cout << "the str is:" << str.getCStr () << endl;

	str = UInt::toString ( (unsigned int) -'\$' );////输出36
	cout << "the str is:" << str.getCStr () << endl;
}

int main ()
{
	TcUInt tin;
	tin.toString ();
}