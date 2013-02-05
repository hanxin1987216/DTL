#include <dtprec.h>
#include <cppunit/tester.h>
#include <dtl/dtl.h>

#include "stringtc.h"

CPPUNIT_TEST_SUITE_REGISTRATION( StringTestCase );


void
StringTestCase::toUpper (void)
{
	String str = "aBcD";
	str.toUpper ();
	CPPUNIT_ASSERT ( str == String("ABCD"));

	String str1 = "aB";
	str1.toUpper ();
	CPPUNIT_ASSERT ( str1 == String("AB"));

	String str2 = "aB ";
	str2.toUpper ();
	CPPUNIT_ASSERT ( str2 != String("AB"));
	
	String str3 = "aB cd";
	str3.toUpper ();
	CPPUNIT_ASSERT ( str3 == String("AB CD"));	

	String str4 = "abc1;D";
	str4.toUpper ();
	CPPUNIT_ASSERT ( str4 == String("ABC1;D"));
	
	String str5 = "abc1;D";
	str5.toUpper ();
	CPPUNIT_ASSERT ( str5 != String("ABC;D"));
}

void 
StringTestCase::toLower (void)
{
	String str = "aBcD";
	str.toLower ();
	CPPUNIT_ASSERT ( str == String("abcd"));

	String str1 = "aB";
	str1.toLower ();
	CPPUNIT_ASSERT ( str1 == String("ab"));

	String str2 = "aB ";
	str2.toLower ();
	CPPUNIT_ASSERT ( str2 != String("ab"));
	
	String str3 = "aB cd";
	str3.toLower ();
	CPPUNIT_ASSERT ( str3 == String("ab cd"));	

	String str4 = "abc1;D";
	str4.toLower ();
	CPPUNIT_ASSERT ( str4 == String("abc1;d"));
	
	String str5 = "abc1;D";
	str5.toLower ();
	CPPUNIT_ASSERT ( str5 != String("abc;d"));
}

void 
StringTestCase::getLength (void)
{
	String str("123456789");
	CPPUNIT_ASSERT_EQUAL((size_t)9,str.getLength());
	
	String str1("  123456879");
	CPPUNIT_ASSERT_EQUAL((size_t)11,str1.getLength());

	String str2("123456789  ");
	CPPUNIT_ASSERT_EQUAL((size_t)11,str2.getLength());

	String str3("1234  56789");
	CPPUNIT_ASSERT_EQUAL((size_t)11,str3.getLength());

	String str4("你好");
	CPPUNIT_ASSERT_EQUAL((size_t)6,str4.getLength());

	String str5("你hao "); 
	CPPUNIT_ASSERT_EQUAL((size_t)7,str5.getLength());

	String str6(" fewe rg ");
	CPPUNIT_ASSERT_EQUAL((size_t)9,str6.getLength());

	String str7( "\123456789" );
	CPPUNIT_ASSERT_EQUAL((size_t)7,str7.getLength());
	
	String str8("！。，？、"); 
	CPPUNIT_ASSERT_EQUAL((size_t)15,str8.getLength());
	
	String str9("!@"); //英文字符占一个字节
	CPPUNIT_ASSERT_EQUAL((size_t)2,str9.getLength());
}

void 
StringTestCase::assign (void)
{
	String str ("123456789");
    const String source ("123456789");
	
	str.assign (source, 0, 4);
	CPPUNIT_ASSERT ( str == String("1234") );

	str.assign (source);
	CPPUNIT_ASSERT ( str == source);

	str.assign (source, 2, 5);
	CPPUNIT_ASSERT ( str == String("34567"));

	str.assign (source,8,4);
	CPPUNIT_ASSERT ( str == String("9"));

	str.assign (source, 2, 0);
/*	CPPUNIT_ASSERT ( str == String(""));

	const String str1("");
	str.assign (str1, 0, 0);
	CPPUNIT_ASSERT ( str == String(""));
	

	const String str2("   123456");
	str.assign (str2, 0, 5);
	CPPUNIT_ASSERT ( str == String("   12"));

	const String str3 ("123456  ");
	CPPUNIT_ASSERT_THROW (str.assign (str3, 6, 5), Exception);

	const String str4("你好啊!");
	str.assign (str4, 0, 10);
	CPPUNIT_ASSERT ( str == String("你好啊!"));
	
	
	
	const String str5("你好啊！");
	str.assign (str5, 3, 3);
	CPPUNIT_ASSERT ( str == String("好"));

//	const String str6("123456你好");
//	str.assign (str6, -1, 0);
//	CPPUNIT_ASSERT ( str == String(""));
	
	const String str7("");
    str.assign(str7,0,0);
	CPPUNIT_ASSERT ( str == String(""));
	
	const String str8("11");
	str.assign(str8,0,0);
	CPPUNIT_ASSERT ( str == String(""));
  
	const tchar_t ptr1[] = "123456789";
    str.assign (ptr1);
	CPPUNIT_ASSERT ( str == String("123456789"));
	
    str.assign (ptr1, 2);
	CPPUNIT_ASSERT ( str == String("12"));
	
	str.assign (ptr1, 9);
	CPPUNIT_ASSERT ( str == String("123456789"));

	const tchar_t* ptr2 = "\0";
	str.assign (ptr2);
	CPPUNIT_ASSERT ( str == String(""));

//	str.assign (ptr2,4);	
//	cout << "   " <<str.getLength () << endl;
//	CPPUNIT_ASSERT ( str == String("\0"));
	
//	CPPUNIT_ASSERT (String("") == String("\0"));
 	
	const tchar_t* ptr3 = "   5616165";
	str.assign (ptr3, 2);
	CPPUNIT_ASSERT ( str == String("  "));

	const tchar_t* ptr4 = "   561  6165";
	str.assign (ptr4);
	cout<<"the str is:"<<str.getCStr()<<endl;

	const tchar_t* ptr5 = "  5616  165  ";
	str.assign (ptr5);
	cout<<"the str is:"<<str.getCStr()<<endl;

	const tchar_t* ptr6 = "refgreg";
	str.assign (ptr6);
	cout<<"the str is:"<<str.getCStr()<<endl;

	const tchar_t* ptr7 = "  你  好！";//////乱码
	str.assign (ptr7);
	cout<<"the str is:"<<str.getCStr()<<endl;

	str.assign (ptr7, 2);
	cout<<"the str is:"<<str.getCStr()<<endl;

	tchar_t ch1 = ' ';
	str.assign (ch1, 2);
	cout<<"its length is:"<<strlen (str.getCStr())<<endl;

	tchar_t ch2 = '\0';
	str.assign (ch2, 3);
	cout<<"its length is:"<<strlen (str.getCStr())<<endl;

	tchar_t ch3 = '1';
	str.assign (ch3, 5);
	cout<<"str is:"<<str.getCStr()<<endl;

	tchar_t ch4 = '你';//////无输出
	str.assign (ch4, 2);
	cout<<"str is:"<<str.getCStr()<<endl;

	tchar_t ch5 = '*';
	str.assign (ch5, 9);
	cout<<"str is:"<<str.getCStr()<<endl;
*/
}

void 
StringTestCase::append (void)
{
	String str="123";
	String source("abc");
	str.append (source , 0 , 4);
	CPPUNIT_ASSERT ( str == String ("123abc") );
	
    str.append (source , 1 , 3);
	CPPUNIT_ASSERT ( str == String ("123abcbc") );

	str.append (source , 3, 4);
	CPPUNIT_ASSERT ( str == String ("123abcbc") );

	String str2;
	const tchar_t* ptr = "123456";
	str2.append (ptr  ,0);
	CPPUNIT_ASSERT ( str2 == String ("") );

	str2.append(ptr , 4);
	CPPUNIT_ASSERT ( str2 == String ("1234") );

	CPPUNIT_ASSERT_NO_THROW ( str2.append (ptr , 8) );

	String str3;
	const tchar_t ptr2 = 'a';
	str3.append (ptr2 , 5);
	CPPUNIT_ASSERT ( str3 == String ("aaaaa") );
	
	str3.append (ptr2 , 2);
	CPPUNIT_ASSERT ( str3 == String ("aaaaaaa") );
}

void
StringTestCase::at (void)
{
	String str("12349  8gfhb");
	CPPUNIT_ASSERT ( str.at(0) == '1' );
	CPPUNIT_ASSERT ( str.at(2) == '3' );
	CPPUNIT_ASSERT ( str.at(11) == 'b' );

	try {
		str.at (22);
	}
	catch (Exception &e)
	{
		CPPUNIT_ASSERT (e.getMessage () == "out of range");
	}
}

void
StringTestCase::clear (void)
{
	String str("1464bdfrnt");

	str.clear ();
	CPPUNIT_ASSERT ( str == String (""));

	str.clear();
	CPPUNIT_ASSERT ( str == String (""));

	string str1("123456");
	str.assign (str1);
	CPPUNIT_ASSERT ( str == String ("123456"));
}

void 
StringTestCase::compare (void)
{
	String str("brebt");
	const String str1("brebt");
	CPPUNIT_ASSERT(str.compare (str1)==0);
	CPPUNIT_ASSERT(str.compare (0, 4, str1)==-1);
	CPPUNIT_ASSERT(str.compare (2, 5, str1)==1);
	CPPUNIT_ASSERT(str.compare (1, 4, str1, 0, 3)==1);

	const String str2("arebt");
	CPPUNIT_ASSERT(str.compare(str2)==1);
	CPPUNIT_ASSERT(str.compare (0, 4, str2)==1);
	CPPUNIT_ASSERT(str.compare (1, 5, str2)==1);
	CPPUNIT_ASSERT(str.compare (0, 4, str2, 0, 4)==1);

	String str3("bre btd");
	CPPUNIT_ASSERT(str.compare (str3)==1);
	CPPUNIT_ASSERT(str.compare (0, 3, str3)==-4);
	CPPUNIT_ASSERT(str.compare (0, 4, str3)==1);
	CPPUNIT_ASSERT(str.compare (0, 3, str3, 0, 3)==0);

	String str4(" brebt");
	CPPUNIT_ASSERT(str.compare (str4)==1);
	CPPUNIT_ASSERT(str.compare (0, 4, str4)==1);
	CPPUNIT_ASSERT(str.compare (1, 3, str4)==1);
	CPPUNIT_ASSERT(str.compare (0, 4, str4, 1, 5)==-1);

	String str5("brebt ");
	CPPUNIT_ASSERT(str.compare (str5)==-1);
	CPPUNIT_ASSERT(str.compare (0, 6, str5)==-1);

	const tchar_t ptr[] = "15645";
	CPPUNIT_ASSERT(str.compare (ptr)==1);

	const tchar_t ptr1[] = "brebt";
	CPPUNIT_ASSERT(str.compare (ptr1)==0);
	CPPUNIT_ASSERT(str.compare (0, 4, ptr1)==-1);
	CPPUNIT_ASSERT(str.compare (0, 4, ptr1, 4)==0);

	const tchar_t ptr2[] = "rebt";
	CPPUNIT_ASSERT(str.compare (ptr2)==-1);
	CPPUNIT_ASSERT(str.compare (1, 4, ptr2, 3)==1);

	const tchar_t ptr3[] = " brebt";
	CPPUNIT_ASSERT(str.compare (ptr3)==1);
	CPPUNIT_ASSERT(str.compare (0, 4, ptr3)==1);
	CPPUNIT_ASSERT(str.compare (1, 3, ptr3)==1);
	CPPUNIT_ASSERT(str.compare (0, 4, ptr3, 4)==1);

	const tchar_t ptr4[] = "brebt ";
	CPPUNIT_ASSERT(str.compare (ptr4)==-1);
	CPPUNIT_ASSERT(str.compare (2,4,ptr4)==1);
	CPPUNIT_ASSERT(str.compare (0, 4, ptr4, 4)==0);
	
	String str7("adabc");
	String str6("ad");
	CPPUNIT_ASSERT(str7.compare (str6)==3);
}

void 
StringTestCase::compareIgnoreCase (void)
{
	String str("asdf");
	const tchar_t* ptr = "AsDf";
	const String str1("Asdf");
	CPPUNIT_ASSERT(str.compareIgnoreCase (str1)==0);
	CPPUNIT_ASSERT(str.compareIgnoreCase (ptr)==0);

	const String str2("asdf");
	const tchar_t ptr1[] = "asDf";
	CPPUNIT_ASSERT(str.compareIgnoreCase (str2)==0);
	CPPUNIT_ASSERT(str.compareIgnoreCase (ptr1)==0);

	String str3("as df");
	String str4("as DF");
	const tchar_t ptr2[] = "as Df";
	CPPUNIT_ASSERT(str3.compareIgnoreCase (str4)==0);
	CPPUNIT_ASSERT(str3.compareIgnoreCase (ptr2)==0);

	String str5("sdasdf");
	CPPUNIT_ASSERT(str5.compareIgnoreCase (2, 4, str)==0);
	CPPUNIT_ASSERT(str5.compareIgnoreCase (2, 4, ptr1)==0);
}

void 
StringTestCase::copy (void)
{
	String str("123456456789");
	tchar_t ptr[10]={0};
	str.copy (ptr, 4, 0);
	CPPUNIT_ASSERT( String (ptr) == String ( "1234" ) );

	str.copy (ptr, 9, 2);
	CPPUNIT_ASSERT( String (ptr) == String ( "345645678" ));

	str.copy (ptr, 5, 9);
	CPPUNIT_ASSERT( String (ptr) == String ( "789645678" ));

	str.copy (ptr, 15, 7);
	CPPUNIT_ASSERT( String (ptr) == String ( "567895678" ));

	tchar_t ptr1[10] = {0};
	str.copy (ptr1, 3,3);
	CPPUNIT_ASSERT( String (ptr1) == String ( "456" ));
	
	String str1("");
	tchar_t ptr2[10] = {0};
	str.copy (ptr2,0,0 );
	CPPUNIT_ASSERT( String (ptr2) == String ( "" ));
	
	tchar_t ptr3[10] = {0};
	str.copy (ptr3,4,11);
	CPPUNIT_ASSERT( String (ptr3) == String ( "9" ));
	
}

void
StringTestCase::erase (void)
{
	String str("grege  rhre");
	str.erase (3, 6);
	CPPUNIT_ASSERT ( str == String ("grere"));

	str.erase (0, 8);
	CPPUNIT_ASSERT ( str == String (""));

	String str1("你好！");
	CPPUNIT_ASSERT_NO_THROW ( str1.erase(3,3));

	String str2("abc");
	CPPUNIT_ASSERT_NO_THROW ( str2.erase(2,2));
	
	CPPUNIT_ASSERT_THROW (str2.erase(4,1),Exception);
}

void
StringTestCase::find (void)
{
	String str( "1dsdsd2345689dggd" );
	const String str1( "456" );
	const tchar_t ptr[] = "2345";
	CPPUNIT_ASSERT(str.find (str1, 0)==8);
	CPPUNIT_ASSERT_NO_THROW(str.find (str1, 9));
	CPPUNIT_ASSERT (str.find (ptr, 0)==6);
	CPPUNIT_ASSERT(str.find (ptr, 3)==6);

	const String str2( "456 qqq" );
	const tchar_t ptr1[] = "q qq";
	CPPUNIT_ASSERT(str2.find (ptr1, 0, 1)==4);
	CPPUNIT_ASSERT_NO_THROW(str2.find (ptr1, 0, 2));
	CPPUNIT_ASSERT(str2.find (ptr1,2,1)==4);

	tchar_t ch = 's';
	CPPUNIT_ASSERT(str.find (ch, 0)==2);

	tchar_t ch1 = 'd';
	CPPUNIT_ASSERT(str.find(ch1, 0)==1);
}

void
StringTestCase::findFirstOf (void)
{
	String str ( "fsfew fdete fgbecew brilicw" );
	const String str1 ( "aeuf" );
	CPPUNIT_ASSERT_NO_THROW(str.findFirstOf (str1, 20));

	CPPUNIT_ASSERT(str.findFirstOf (str1, 0)==0);

	const String str2("v");
	CPPUNIT_ASSERT_NO_THROW(str.findFirstOf (str2, 0));

	tchar_t ptr[] = "few";
	CPPUNIT_ASSERT_NO_THROW(str.findFirstOf (ptr, 0));
	
	String str3 ("");
	const String str4("ab");
	CPPUNIT_ASSERT_NO_THROW(str3.findFirstOf (str4,0));
}

void 
StringTestCase::findFirstNotOf (void)
{
	String str("fsfew fdete fgbecew brilic");
	const String str1("abcdefghijklmn ");
	CPPUNIT_ASSERT(str.findFirstNotOf (str1,20) == 21);

	CPPUNIT_ASSERT(str.findFirstNotOf ( str1, 0 )== 1);

	const String str2 ( "abcdefghijklmnopqrstuvwxyz " );
	CPPUNIT_ASSERT_NO_THROW(str.findFirstNotOf ( str2, 0 ));

	tchar_t ptr[] = "fewsd";
	CPPUNIT_ASSERT(str.findFirstNotOf ( ptr, 0 )==5);
}

void
StringTestCase::findLastOf (void)
{
	String str ( "fsf ew\\fd /ete\\fgbe /cew\\br ilic" );
	const String str1 ( "/\\" );
	CPPUNIT_ASSERT_NO_THROW(str.findLastOf ( str1, 0 ) );
	CPPUNIT_ASSERT(str.findLastOf ( str1, 6)==6);

	const String str2( " " );
	CPPUNIT_ASSERT_NO_THROW(str.findLastOf ( str2, 0 ));
	CPPUNIT_ASSERT(str.findLastOf ( str2, 3 ) ==3);
	CPPUNIT_ASSERT( str.findLastOf ( str2, 16 ) ==9);

	const tchar_t ptr[] = "fewsd";
	CPPUNIT_ASSERT_NO_THROW(str.findLastOf ( ptr, 14 , 0 ));
	CPPUNIT_ASSERT(str.findLastOf ( ptr, 14 , 1 ) == 7);
	CPPUNIT_ASSERT(str.findLastOf ( ptr, 14 , 2 ) ==13);

	tchar_t ch = 'c';
	CPPUNIT_ASSERT(str.findLastOf ( ch, 26 ) == 21);
	CPPUNIT_ASSERT(str.findLastOf ( 'c', 26 )==21);
	
	String str3 ("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz");
	const String ptr2("c");
	CPPUNIT_ASSERT(str3.findLastOf ( ptr2,30)==28);
}

void
StringTestCase::findLastNotOf (void)
{
	String str ( "fsf ew\\fde    te\\fgbece w\\bril ic" );
	const String str1 ( "\\" );
	CPPUNIT_ASSERT(str.findLastNotOf ( str1, 6 )==5);
	CPPUNIT_ASSERT(str.findLastNotOf ( str1, 50 )==32);

	const String str2 ( " " );
	CPPUNIT_ASSERT(str.findLastNotOf ( str2, 13 )==9);

	const tchar_t ptr[] = "fewsd";
	CPPUNIT_ASSERT(str.findLastNotOf ( ptr, 15, 3 )==14);
	CPPUNIT_ASSERT(str.findLastNotOf ( ptr, 15 )==14);
	
	String str3 ("abcdecdhji");
	const tchar_t ptr1[] = "cde";
	CPPUNIT_ASSERT(str3.findLastNotOf ( ptr1, 6, 3 )==1);
}

void 
StringTestCase::insert (void)
{
	String str( "ge" );
	String str1( "fg" );
	str.insert( 0, str1 );
	CPPUNIT_ASSERT( str == String ("fgge") );

	str.insert( 3, str1 );
	CPPUNIT_ASSERT( str == String ("fggfge") );

	str.insert( 6, str1 );
	CPPUNIT_ASSERT( str == String ("fggfgefg") );

	str.insert( 0, str1, 0, 0 );
	CPPUNIT_ASSERT( str == String ("fggfgefg") );

	
	str.insert( 0, str1, 0, 8 );
	CPPUNIT_ASSERT( str == String ("fgfggfgefg") );

	String str2( "    " );
	str.insert( 0, str2 );
	CPPUNIT_ASSERT( str == String ("    fgfggfgefg") );

	String str4("!;！；;");
	str.insert(0,str4,0,1);
	CPPUNIT_ASSERT( str == String ("!    fgfggfgefg") );
	str.insert( 0, str1, 0, 8 );
	CPPUNIT_ASSERT( str == String ("fg!    fgfggfgefg") );

	String str3( "你好！" );
	str.insert( 0, str2 );
	CPPUNIT_ASSERT( str == String ("    fg!    fgfggfgefg") );

	str.insert( 0, str1, 0, 2 );
	CPPUNIT_ASSERT( str == String ("fg    fg!    fgfggfgefg") );

	str.insert( 0, "regre bern", 6 );
	CPPUNIT_ASSERT( str == String ("regre fg    fg!    fgfggfgefg") );

	str.insert( 0, "你 好 ！", 4 );
	CPPUNIT_ASSERT( str == String ("你 regre fg    fg!    fgfggfgefg") );

	str.insert( 0, "gerge geg" );
	CPPUNIT_ASSERT( str == String ("gerge geg你 regre fg    fg!    fgfggfgefg") );

	str.insert( 0, "你好！" );
	CPPUNIT_ASSERT( str == String ("你好！gerge geg你 regre fg    fg!    fgfggfgefg") );

	str.insert( 0, 5,'d' );
	CPPUNIT_ASSERT( str == String ("ddddd你好！gerge geg你 regre fg    fg!    fgfggfgefg") );

	str.insert( 30, 3, '5'  );
	CPPUNIT_ASSERT( str == String ("ddddd你好！gerge geg你 reg555re fg    fg!    fgfggfgefg") );
}

void
StringTestCase::replace (void)
{
	String str( "fwegerwrthr" );
	str.replace( 'r', 'e', false );
	CPPUNIT_ASSERT( str == String ("fwegeewrthr") );

	str.replace( 'r', 'e', true );
	CPPUNIT_ASSERT( str == String ("fwegeewethe") );

	str.replace( 'e', 'e', false );
	CPPUNIT_ASSERT( str == String ("fwegeewethe") );

	const String str2( "grehrt" );
	str.replace( 0, 3, str2 );
	CPPUNIT_ASSERT( str == String ("grehrtgeewethe") );

	str.replace( 0, 0, str2 ); 
	CPPUNIT_ASSERT( str == String ("grehrtgrehrtgeewethe") );

	str.replace( 10, 1, str2 ); 
	CPPUNIT_ASSERT( str == String ("grehrtgrehgrehrttgeewethe") );

	str.replace( 10, 1, str2, 0, 3 );
	CPPUNIT_ASSERT( str == String ("grehrtgrehgrerehrttgeewethe") );

	const tchar_t ptr[] = "rebbtrn";
	str.replace( 0, 3, ptr );
	CPPUNIT_ASSERT( str == String ("rebbtrnhrtgrehgrerehrttgeewethe") );

	str.replace( 10, 3, ptr );
	CPPUNIT_ASSERT( str == String ("rebbtrnhrtrebbtrnhgrerehrttgeewethe") );

	str.replace( 2, 3, ptr );
	CPPUNIT_ASSERT( str == String ("rerebbtrnrnhrtrebbtrnhgrerehrttgeewethe") );
	
	String str1 ("abc");
	str1.replace( 0, 3, ptr, 4 );
	CPPUNIT_ASSERT( str1 == String ("rebb") );

	str1.replace( 1, 3, ptr, 4 );
	CPPUNIT_ASSERT( str1 == String ("rrebb") );

	str1.replace( 2, 3, ptr, 4 );
	CPPUNIT_ASSERT( str1 == String ("rrrebb") );

	str1.replace( 0, 3, 4, 's' );
	CPPUNIT_ASSERT( str1 == String ("ssssebb") );

	str1.replace( 3, 3, 4, 's' );
	CPPUNIT_ASSERT( str1 == String ("sssssssb") );

	str1.replace( 3, 3, 4, 'd' );
	CPPUNIT_ASSERT( str1 == String ("sssddddsb") );
}

void
StringTestCase::reserve (void)
{
	String str;
	String str1 ( "123456712345678945613" );////当长度小于6时，capacity()为6，大于6小于12时为12，大于12
	                                        ////为实际长度    
	String str2 ( "1234" );

	str2.assign(str1);
	CPPUNIT_ASSERT ( str2 == String ("123456712345678945613"));
	
	str.reserve ( 6 );
	CPPUNIT_ASSERT ( str.getCapacity() == 6 );

	str.assign ( str2 );
	CPPUNIT_ASSERT ( str == String ("123456712345678945613"));
	CPPUNIT_ASSERT ( str.getLength () == 21 );
	CPPUNIT_ASSERT ( str.getCapacity () == 21 );

	str.assign ( str1 );
	CPPUNIT_ASSERT ( str == String ("123456712345678945613"));
	CPPUNIT_ASSERT ( str.getLength () == 21 );
	CPPUNIT_ASSERT ( str.getCapacity ()== 21 );
}

void
StringTestCase::resize (void)
{
	String str;
	str.resize ( 6 );
	CPPUNIT_ASSERT( str.getCapacity () == 6);

	String str1 ( "1234" );
	str.assign ( str1 );
	CPPUNIT_ASSERT( str == String ("1234") );
	CPPUNIT_ASSERT( str.getLength () == 4 );
	CPPUNIT_ASSERT( str.getCapacity () == 6 );

	String str2 ( "123456712345678945613" );
	str.assign ( str2 );
	CPPUNIT_ASSERT( str == String ("123456712345678945613"));
	CPPUNIT_ASSERT( str.getLength () ==21 );
	CPPUNIT_ASSERT( str.getCapacity () ==21 );

	String str3;
	str3.resize ( 8, 'o' );
	CPPUNIT_ASSERT( str3 == String ("oooooooo") );
	CPPUNIT_ASSERT( str3.getLength () ==8 );
	CPPUNIT_ASSERT( str3.getCapacity () ==8 );

	String str4 ("a bc");
	str4.resize ( 5, 'x');
	CPPUNIT_ASSERT( str4 == String ("a bcx") );
	CPPUNIT_ASSERT( str4.getLength () ==5 );
	CPPUNIT_ASSERT( str4.getCapacity () ==8 );
}

void
StringTestCase::rfind (void)
{
	String str ( "123456745689s789wgren" );
	String str1 ( "456" );
	CPPUNIT_ASSERT( str.rfind ( str1, 3 ) == 3 );
	CPPUNIT_ASSERT( str.rfind ( str1, 8 ) == 7 );
	CPPUNIT_ASSERT( str.rfind ( str1, 16 ) == 7 );

	String str2 ( "ren" );
	CPPUNIT_ASSERT_NO_THROW( str.rfind ( str2, 15 ) );

	const tchar_t* ptr = "789";
	CPPUNIT_ASSERT( str.rfind ( ptr, 40 ) == 13 );
	CPPUNIT_ASSERT( str.rfind ( ptr, 13 ) == 13 );
	CPPUNIT_ASSERT ( str.rfind ( ptr, 8, 1 ) == 6 );
	CPPUNIT_ASSERT_NO_THROW ( str.rfind ( ptr, 8, 2 ) );
	CPPUNIT_ASSERT( str.rfind ( ptr, 40, 5 ) == 13 );
}

void 
StringTestCase::subString (void)
{
	String str;
	String str1 ( "123456sdfrnn" );
	str.assign ( str1.subString ( 0, 5 ) );
	CPPUNIT_ASSERT ( str == String ("12345") );

	str.assign ( str1.subString ( 2, 2 ) );
	CPPUNIT_ASSERT ( str == String ("34") );

	str.assign ( str1.subString ( 2, 18 ) );
	CPPUNIT_ASSERT ( str == String ("3456sdfrnn") );
	
	str.assign ( str1.subString ( 2, 0 ) );
	CPPUNIT_ASSERT ( str == String ("") );

	CPPUNIT_ASSERT_THROW (str1.subString ( 18, 1 ),Exception );
}


void
StringTestCase::trim (void)
{
	String str( "  dgsg  dgre we      " );
	str.trim ();
	CPPUNIT_ASSERT ( str == String ("dgsg  dgre we") );

	String str1( "dgsg  dgre we" );
	str1.trim ();
	CPPUNIT_ASSERT ( str1 == String ("dgsg  dgre we") );
}

void
StringTestCase::trimLeft (void)
{
	String str( "  grwgrew gegre" );
	str.trimLeft ();
	CPPUNIT_ASSERT ( str == String ("grwgrew gegre") );

	String str1( "grwgrew gegre" );
	str1.trimLeft ();
	CPPUNIT_ASSERT ( str1 == String ("grwgrew gegre") );

	String str2( "grwgrew gegre   " );
	str2.trimLeft ();
	CPPUNIT_ASSERT ( str2 == String ("grwgrew gegre   ") );

	
	String str3( "gsdafdasf");
	str3.trimLeft ();
	CPPUNIT_ASSERT ( str3 == String ("gsdafdasf") );
}


void
StringTestCase::trimRight (void)
{
	String str( "  grwgrew gegre" );
	str.trimRight ();
	CPPUNIT_ASSERT ( str == String ("  grwgrew gegre") );

	String str1( "grwgrew gegre" );
	str1.trimRight ();
	CPPUNIT_ASSERT ( str1 == String ("grwgrew gegre") );


	String str2( "grwgrew gegre   " );
	str2.trimRight ();
	CPPUNIT_ASSERT ( str2 == String ("grwgrew gegre") );
	CPPUNIT_ASSERT ( str2.getLength () == 13 );
}

void 
StringTestCase::leftString (void)
{
	String str ( "1456gdfghtr" );

	String str1 = str.leftString ( 3 );
	CPPUNIT_ASSERT ( str1 == String ("145") );

	String str2 = str.leftString ( 6 );
	CPPUNIT_ASSERT ( str2 == String ("1456gd") );

	CPPUNIT_ASSERT_THROW ( str.leftString ( 30 ),Exception );
}

void
StringTestCase::rightString (void)
{
	String str ( "1456gdfghtr" );
	CPPUNIT_ASSERT (str.getCSize () == 11);
	
	String str1 = str.rightString ( 3 );
	CPPUNIT_ASSERT ( str1 == String ("htr") );

	String str2 = str.rightString ( 6 );
	CPPUNIT_ASSERT ( str2 == String ("dfghtr") );

	CPPUNIT_ASSERT_THROW ( str.rightString ( 15 ),Exception );
}

void
StringTestCase::split (void)
{
	String str ( "abcdefgabchijklmnabcop123456789qrstuvwxyz" );
	const String str1 ( "12345" );
	std::vector<String> substrs;
	std::vector<String>::iterator it;

	str.split ( str1, substrs );
	it=substrs.begin ();
	CPPUNIT_ASSERT ( String ( (*it).getCStr () ) == String ("abcdefgabchijklmnabcop") );
	it++;
	CPPUNIT_ASSERT ( String ( (*it).getCStr () ) == String ("6789qrstuvwxyz") );
	substrs.clear ();

	tchar_t ptr = 'a';
	str.split ( ptr, substrs );
	it=substrs.begin ();
	CPPUNIT_ASSERT ( String ( (*it).getCStr () ) == String ("bcdefg") );
	it++;
	CPPUNIT_ASSERT ( String ( (*it).getCStr () ) == String ("bchijklmn") );
	it++;
	CPPUNIT_ASSERT ( String ( (*it).getCStr () ) == String ("bcop123456789qrstuvwxyz") );
	substrs.clear ();
}

void
StringTestCase::format (void)
{
/*	String str;
	size_t a = 98;
	str.format ( " %d " , a );
	CPPUNIT_ASSERT ( String ( str.getCStr);

	str.format ( " %c " , a );
	CPPUNIT_ASSERT ( String ( str.getCStr () ) == String ("b") );	

	str.format ( " %o " , a );
	CPPUNIT_ASSERT ( String ( str.getCStr () ) == String ("142") );
	
	str.format ( " %x ", a );
	CPPUNIT_ASSERT ( String ( str.getCStr () ) == String ("62") );

	tchar_t s[]="dgre";
	str.format ( " %s " , s );
	CPPUNIT_ASSERT ( String ( str.getCStr () ) == String ("dgre") );*/
}

void
StringTestCase::operator_t (void)
{
	const String str ("women:");
	const String str1 ("sfsf");
	
	const String str3 = str + str1;
	CPPUNIT_ASSERT ( String ( str3.getCStr ()) == String ("women:sfsf") );
	
	CPPUNIT_ASSERT ( operator<(str , str1) == 0);
	CPPUNIT_ASSERT ( operator>(str , str1) == 1);
	CPPUNIT_ASSERT ( operator<=(str , str1) == 0);
	CPPUNIT_ASSERT ( operator>=(str , str1) == 1);
	CPPUNIT_ASSERT ( operator!=(str , str1) == 1 );
	
	const tchar_t* ptr = "wo";
	CPPUNIT_ASSERT ( operator>(str , ptr ) == 1);
	CPPUNIT_ASSERT ( operator<(str , ptr ) == 0);
	CPPUNIT_ASSERT ( operator<=(str , ptr ) == 0);
	CPPUNIT_ASSERT ( operator>=(str , ptr ) == 1);
	CPPUNIT_ASSERT ( operator!=(str , ptr ) == 1);	
	
	CPPUNIT_ASSERT ( operator>(ptr , str ) ==0);
	CPPUNIT_ASSERT ( operator<(ptr , str ) ==1);
	CPPUNIT_ASSERT ( operator<=(ptr , str ) ==1);
	CPPUNIT_ASSERT ( operator>=(ptr , str ) == 0);
	CPPUNIT_ASSERT ( operator!=(ptr , str ) == 1);	
}