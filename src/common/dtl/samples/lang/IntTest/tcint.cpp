/***************************************************************************************************
tcdate.cpp:	
	C++ Foundation Library header files
	Copyright (c) Datatom Software, Inc.(2012)

Purpose:
test the date function

Author:
	应业敏

Creating Time:
	2012-2-8
***************************************************************************************************/
#include <dtprec.h>
#include <dtl.h>
#include <time.h>
#include <sys/time.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>

class TcInt
{
public:
	void toString ( void );
	void getValue ( void );
	void isInteger ( void );
};

void
TcInt::toString ( void )
{
	cout << "test the toString ():" << endl;

	String str;
	str = Int::toString ( 6 );
	cout << "the str is:" << str.getCStr () << endl;

	str = Int::toString ( 556 );
	cout << "the str is:" << str.getCStr () << endl;

	str = Int::toString ( 0xaa6 );
	cout << "the str is:" << str.getCStr () << endl;

	str = Int::toString ( 0776 );
	cout << "the str is:" << str.getCStr () << endl;

	str = Int::toString ( 0000 );/////输出0
	cout << "the str is:" << str.getCStr () << endl;

	str = Int::toString ( 0006 );/////输出6
	cout << "the str is:" << str.getCStr () << endl;

	str = Int::toString ( 'a' );
	cout << "the str is:" << str.getCStr () << endl;

	str = Int::toString ( '1234' );
	cout << "the str is:" << str.getCStr () << endl;

	str = Int::toString ( '\$' );////输出36
	cout << "the str is:" << str.getCStr () << endl;
}

void
TcInt::getValue ( void )
{
	cout << "test the getValue ():" << endl;
	String str ( "123456789" );
	cout << "the value is:" << Int::getValue ( str ) << endl;

	str = "0123789";
	cout << "the value is:" << Int::getValue ( str ) << endl;

	//str = "abc";
	//cout << "the value is:" << Int::getValue ( str ) << endl;报错

	str = " 123456555";
	cout << "the value is:" << Int::getValue ( str ) << endl;

	str = "    12";
	cout << "the value is:" << Int::getValue ( str ) << endl;

	str = "1   2";////输出1
	cout << "the value is:" << Int::getValue ( str ) << endl;

	str = "12   ";
	cout << "the value is:" << Int::getValue ( str ) << endl;

	//str = "\t";报错
	//cout << "the value is:" << Int::getValue ( str ) << endl;
}

void
TcInt::isInteger ( void )
{
	cout << "test the isInteger ():" << endl;
	tchar_t ptr[] = "123456";
	if ( Int::isInteger ( ptr, 6 ) )
		cout << "it's the integer !" << endl;
	else
		cout << "it is not the integer !" << endl;

	if ( Int::isInteger ( ptr ) )
		cout << "//////it's the integer !" << endl;
	else
		cout << "//////it is not the integer !" << endl;

	if ( Int::isInteger ( ptr, 0 ) )
		cout << "@@@it's the integer !" << endl;
	else
		cout << "@@@it is not the integer !" << endl;

	tchar_t ptr1[] = "  123456";////不是
	if ( Int::isInteger ( ptr1, 8 ) )
		cout << "it's the integer !" << endl;
	else
		cout << "it is not the integer !" << endl;

	if ( Int::isInteger ( ptr1 ) )
		cout << "/////it's the integer !" << endl;
	else
		cout << "/////it is not the integer !" << endl;

	tchar_t ptr2[] = "123456  ";//////不是
	if ( Int::isInteger ( ptr2, 8 ) )
		cout << "it's the integer !" << endl;
	else
		cout << "it is not the integer !" << endl;

	if ( Int::isInteger ( ptr2, 6 ) )/////是
		cout << "it's the integer !" << endl;
	else
		cout << "it is not the integer !" << endl;

	tchar_t ptr3[] = "1234  56";///不是
	if ( Int::isInteger ( ptr3, 6 ) )
		cout << "it's the integer !" << endl;
	else
		cout << "it is not the integer !" << endl;

	if ( Int::isInteger ( ptr3, 4 ) )////是
		cout << "it's the integer !" << endl;
	else
		cout << "it is not the integer !" << endl;

	tchar_t *ptr4;
	if ( Int::isInteger ( ptr4, 8 ) )
		cout << "@@@@it's the integer !" << endl;
	else
		cout << "@@@@it is not the integer !" << endl;

	String str ( "123456" );
	if ( Int::isInteger ( str ) )////是
		cout << "*****it's the integer !" << endl;
	else
		cout << "*****it is not the integer !" << endl;

	str = "  123456";
	if ( Int::isInteger ( str ) )////是
		cout << "*****it's the integer !" << endl;
	else
		cout << "*****it is not the integer !" << endl;
}

int main ()
{
	TcInt tin;
	tin.toString ();
	tin.getValue ();
	tin.isInteger ();
}