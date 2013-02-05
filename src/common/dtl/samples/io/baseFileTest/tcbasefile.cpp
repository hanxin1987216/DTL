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

class TcBaseFile
{
public:
	/*void baseFile ( void );
	void loadFileAttrs ( void );*/
	//void setFileAttrs ( void );
	void isFile ( void );
	void isDirectory ( void );
	void getLastModified ( void );
	void getCreationTime ( void );
	void getLastAccess ( void );
	void getFileAttrs ( void );
};

/*void
TcBaseFile::baseFile ()
{
	cout << "test the baseFile ():" << endl; 
	const String str ( "123456" );
	BaseFile::BaseFile( str );
	cout << "the bf is:" << ( BaseFileget::FullName () ).getCStr () << endl;

	BaseFile bf1 ( bf );
	cout << "the bf1 is:" << ( bf1.getFullName () ).getCStr () << endl;

	BaseFile bf2 = bf;
	cout << "the bf2 is:" << ( bf2.getFullName () ).getCStr () << endl;
}*/

/*void
TcBaseFile::loadFileAttrs ( void )
{
	cout << "test the loadFileAttrs ():" << endl;

	open ( "basefile", O_CREAT, S_IRUSR );
	String str = "basefile";
	BaseFile bf ( str );
	bf.loadFileAttrs ();
}*/

/*void
TcBaseFile::setFileAttrs ( void )
{
	BaseFile::setFileAttrs (int attrs);

}*/

void
TcBaseFile::isFile ( void )
{
	cout << "test the isFile ():" << endl;
	String str = "/yingyemin/tcbasefile/tcbasefile.cpp";
	if ( BaseFile::isFile ( str ) )
		cout << "it's a file !" << endl;
	else
		cout << "it isn't a file !" << endl;

	str = "/yingyemin/tcbasefile/Makefile";
	if ( BaseFile::isFile ( str ) )
		cout << "it's a file !" << endl;
	else
		cout << "it isn't a file !" << endl;

	str = "/yingyemin/tcbasefile";////输出it is a file!
	if ( BaseFile::isFile ( str ) )
		cout << "it's a file !" << endl;
	else
		cout << "it isn't a file !" << endl;

	str = "123456";
	if ( BaseFile::isFile ( str ) )
		cout << "it's a file !" << endl;
	else
		cout << "it isn't a file !" << endl;


	str = "abcd1234hihui56";////////***错误//跟前面一样
	if ( BaseFile::isFile ( str ) )
		cout << "it's a file !" << endl;
	else
		cout << "it isn't a file !" << endl;

	str = "   ";//////////***错误//跟前面一样
	if ( BaseFile::isFile ( str ) )
		cout << "it's a file !" << endl;
	else
		cout << "it isn't a file !" << endl;

	/*str = "\0";异常
	if ( BaseFile::isFile ( str ) )
		cout << "it's a file !" << endl;
	else
		cout << "it isn't a file !" << endl;*/

	mkdir ( "123456", S_IRUSR );
	str = "123456";
	if ( BaseFile::isFile ( str ) )
		cout << "it's a file !" << endl;
	else
		cout << "it isn't a file !" << endl;

}

void
TcBaseFile::isDirectory ( void )
{
	cout << "test the isDirectory ():" << endl;
	String str ( "/yingyemin/tcbasefile" );
	if ( BaseFile::isDirectory ( str ) )
		cout << "it is a directory !" << endl;
	else
		cout << "it isn't a directory !" << endl;

	str = "   ";
	if ( BaseFile::isDirectory ( str ) )
		cout << "it is a directory !" << endl;
	else
		cout << "it isn't a directory !" << endl;

	str = "123456";
	if ( BaseFile::isDirectory ( str ) )
		cout << "it is a directory !" << endl;
	else
		cout << "it isn't a directory !" << endl;

	str = "5478dfh";
	if ( BaseFile::isDirectory ( str ) )
		cout << "it is a directory !" << endl;
	else
		cout << "it isn't a directory !" << endl;
}

void
TcBaseFile::getLastModified ( void )
{
	cout << "test the getLastModified ():" << endl;
	String str = "123456";
	cout << "the time is:" << BaseFile::getLastModified ( str ) << endl;

	//str = "4651";/////异常
	//cout << "the time is:" << BaseFile::getLastModified ( str ) << endl;

	//str = "/yingyemin/tcbasefile";/////****无法检测
	//cout << "the time is:" << BaseFile::getLastModified ( str ) << endl;

	//str = "/yingyemin/tcstring";/////****无法检测
	//cout << "the time is:" << BaseFile::getLastModified ( str ) << endl;

	open( "abcd", O_CREAT, S_IRUSR );
	str = "abcd";
	cout << "the time is:" << BaseFile::getLastModified ( str ) << endl;

	tchar_t ptr[] = "hovnreborehtbioee";
	size_t i;
	FILE* in;
	in = fopen ( "abcd", "w" );
	for ( i = 0; i < strlen (ptr); i++ )
		fputc( ptr[i], in );
	cout << "the time is:" << BaseFile::getLastModified ( str ) << endl;
}

void
TcBaseFile::getCreationTime ( void )
{ 
	cout << "test the getCreationTime ():" << endl;
	chdir ( "123456" );
	//creat ( "11111", S_IRUSR );

	String str = "123456";
	//cout << "the time is:" << BaseFile::getCreationTime ( str ) << endl;

	//str = "abcd";
	//cout << "the time is:" << BaseFile::getCreationTime ( str ) << endl;

	str = "11111";
	cout << "the time is:" << BaseFile::getCreationTime ( str ) << endl;

	//str = "e56g4re6g46";
	//cout << "the time is:" << BaseFile::getCreationTime ( str ) << endl;

	//str = "/yingyemin/tcbasefile";
	//cout << "the time is:" << BaseFile::getCreationTime ( str ) << endl;

	tchar_t ptr[] = "vfebre456t4hrrt15ergf5w6g4re6";
	size_t i;
	FILE* in;
	in = fopen ( "11111", "w" );
	for ( i = 0; i < strlen ( ptr ); i++ )
		fputc ( ptr[i], in );
	cout << "the time is:" << BaseFile::getCreationTime ( str ) << endl;
}

void
TcBaseFile::getLastAccess ( void )
{
	cout<<"******getLastAccess*******" << endl;
	String str = "11111";
	cout << "the time is:" << BaseFile::getLastAccess ( str ) << endl;

	/*chdir ( "123465" );
	str = "123465";
	cout << "the time is:" << BaseFile::getLastAccess ( str ) << endl;*/

}

void
TcBaseFile::getFileAttrs ( void )
{
	cout << "*********getFileAttrs********** " << endl;
	String str ( "11111" );
	FileAttributes fa2;
	chmod ( "11111", S_IWOTH|S_IWGRP|S_IWUSR|S_IROTH );
	fa2 = BaseFile::getFileAttrs ( str );
	cout << "the attrs is:" << fa2 << endl;

	chmod ( "11111",S_IRUSR);
	fa2 = BaseFile::getFileAttrs ( str );
	cout << "the attrs is:" << fa2 << endl;

	chmod ( "11111", S_IWOTH|S_IWGRP|S_IWUSR|S_IROTH|S_IXUSR );
	fa2 = BaseFile::getFileAttrs ( str );
	cout << "the attrs is:" << fa2 << endl;

	FileAttributes fa1;
	str = "123456";
	fa1 = BaseFile::getFileAttrs ( str );
	cout << "the attrs is:" << fa1 << endl;

	mkdir ( "654321", S_IWOTH|S_IWGRP|S_IWUSR );
	str = "654321";
	FileAttributes fa3;
	fa3 = BaseFile::getFileAttrs ( str );
	cout << "the attrs is:" << fa3 << endl;
}

int main ()
{
	TcBaseFile tcbf;
	tcbf.isFile ();///// ***tcbf.isFile ( void )?错
	//tcbf.baseFile ( void );
	tcbf.isDirectory ();
	tcbf.getLastModified ();
	tcbf.getCreationTime ();
	tcbf.getLastAccess ();
	tcbf.getFileAttrs ();
}