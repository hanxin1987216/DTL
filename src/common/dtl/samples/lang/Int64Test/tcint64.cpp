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
#include <time.h>
#include <sys/time.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>

class TcInt64
{
public:
	void toString ( void );
	void getValue ( void );
};

void
TcInt64::toString ( void )
{
	cout << "test the toString ():" << endl;

	String str;
	str = Int64::toString ( (int64)6 );
	cout << "the str is:" << str.getCStr () << endl;

	str = Int64::toString ( (int64)556 );
	cout << "the str is:" << str.getCStr () << endl;

	str = Int64::toString ( (int64)0xaa6 );
	cout << "the str is:" << str.getCStr () << endl;

	str = Int64::toString ( (int64)0776 );
	cout << "the str is:" << str.getCStr () << endl;

	str = Int64::toString ( (int64)0000 );/////输出0
	cout << "the str is:" << str.getCStr () << endl;

	str = Int64::toString ( (int64)0006 );/////输出6
	cout << "the str is:" << str.getCStr () << endl;

	str = Int64::toString ( (int64)'a' );
	cout << "the str is:" << str.getCStr () << endl;

	str = Int64::toString ( (int64)'1234' );
	cout << "the str is:" << str.getCStr () << endl;

	str = Int64::toString ( (int64)'\$' );////输出36
	cout << "the str is:" << str.getCStr () << endl;

	str = Int64::toString ( (int64)-456 );////输出36
	cout << "the str is:" << str.getCStr () << endl;
}

void
TcInt64::getValue ( void )
{
	cout << "test the getValue ():" << endl;
	String str ( "123456789" );
	cout << "the value is:" << Int64::getValue ( str ) << endl;

	str = "0123789";
	cout << "the value is:" << Int64::getValue ( str ) << endl;

	//str = "abc";
	//cout << "the value is:" << Int64::getValue ( str ) << endl;报错

	str = " 123456555";
	cout << "the value is:" << Int64::getValue ( str ) << endl;

	str = "    12";
	cout << "the value is:" << Int64::getValue ( str ) << endl;

	str = "1   2";////输出1
	cout << "the value is:" << Int64::getValue ( str ) << endl;

	str = "12   ";
	cout << "the value is:" << Int64::getValue ( str ) << endl;

	str = "-12";
	cout << "the value is:" << Int64::getValue ( str ) << endl;


	//str = "\t";报错
	//cout << "the value is:" << Int64::getValue ( str ) << endl;
}

int main ()
{
	TcInt64 tin;
	tin.toString ();
	tin.getValue ();
}