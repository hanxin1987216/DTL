#include "tcString.h"

void tcString::constructors(void)
{
	cout << "--------------- test case of String::String() ---------------" << endl;

	char *ptrChar = "characters test 测试用例";
	cout << "char* ptrChar: \"" <<  ptrChar << "\"" << endl;
	
	string strString = "string test 测试用例";
	cout << "string strString: \"" << strString << "\""<< endl;
	
	char c = 'a';
	
	String strEmpty;
	cout << "String::String(void): \"" << strEmpty.getCStr() << "\"" << endl;

	String strStringTest(strString);
	cout << "String::String(const string&) with strString: \"" << strStringTest.getCStr() << "\"" << endl;

	String strStringCpy(strStringTest);
	cout << "String::String(const String&) with strStringTest: \"" <<  strStringCpy.getCStr() << "\"" << endl;

	String strOffset(strStringTest, 2, 7);
	cout << "String::String(const String&, size_t, size_t) with strStringTest, 2, 7: \"" << strOffset.getCStr() << "\"" << endl;
	

	String strCharTest(ptrChar);
	cout << "String::String(const tchar_t*) with ptrChar: \"" <<  strCharTest.getCStr() << "\"" << endl;
	
	String strCharacters(c, 20);
	cout << "String::String(const tchar_t, size_t) with \'c\', 20: \"" << strCharacters.getCStr() << "\"" << endl;
	
	String strCharOffset(ptrChar, 5);
	cout << "String::String(const tchar_t*, size_t) with ptrChar, 5: \"" <<  strCharOffset.getCStr() << "\"" << endl;


	cout << "=============== test case of String::String() ===============" << endl << endl << endl;
}


void tcString::assign(void)
{
	printf("--------------- test case of String::assign() ---------------\n\n");
	
	String strTest(_T("this is a test String 测试用例"));
	char* chs = "characters test 测试用例";
	char ch = 'a';
	String strResult;

	printf("Test String:\"%s\"\n", strTest.getCStr());
	cout << "Test char*:\"" << chs << "\"" << endl;
	
	strResult.assign(strTest);
	printf("assign result String with test String: \"%s\"\n", strResult.getCStr());

	strResult.assign(strTest, 7, 27);
	printf("assign result String with test String from  7th character to the end:\"%s\"\n", strResult.getCStr());
	
	strResult.assign(chs, 8);
	printf("assign result String with test char* from 1st character to 8th character: \"%s\"\n", strResult.getCStr());

	strResult.assign(chs);
	printf("assign result String with test char*:\"%s\"\n", strResult.getCStr());

	strResult.assign(ch, 55);
	printf("assign result String with test character(a):\"%s\"\n", strResult.getCStr());

	printf("=============== test case of String::assign()===============\n\n\n");
}

void tcString::append()
{
	cout << "--------------- test case of String::append() ---------------" << endl << endl;
	
	String strTest(_T("test String 测试用例"));
	char* chs ="test characters 测试用例";
	char ch = 'a';
	String strResult(_T("eee"));

	cout << "test String: \"" << strTest.getCStr() << "\"" << endl;
	cout << "test characters: \"" << chs << "\"" << endl;
	cout << "test character: \'" << ch << "\'" << endl;
	cout << "result String: \"" << strResult.getCStr() << "\"" << endl;
	cout << endl; 

	strResult.append(strTest);
	cout << "append test String to result String: \"" << strResult.getCStr() << "\"" << endl;

	strResult.append(chs);
	cout << "append test characters to result String: \"" << strResult.getCStr() << "\"" << endl;

	strResult.append(strTest, 5, 5);
	cout << "append to result String with the 5th to 10th character in test String: \"" << strResult.getCStr() << "\"" << endl;

	strResult.append(chs, 10);
	cout << "append to result String with the first ten characters in test characters:\"" << strResult.getCStr() << "\"" << endl;

	strResult.append(ch, 5);
	cout << "append to result String with 5 \'a\': \"" << strResult.getCStr() << "\"" << endl;

	cout << "=============== test case of String::assign() ===============" << endl << endl << endl;
}

void tcString::at()
{
	cout << "--------------- test case of String::at() ---------------" << endl << endl;
	
	String strTest(_T("test String 测试用例"));
	cout << "test String:\"" << strTest.getCStr() << "\"" << endl;
	for (int i = 0; i < strTest.getLength(); i ++)
	{
		cout << "character at " << i+1 << " of test String is \'" << strTest.at(i) << "\'" << endl;
	}
	
	cout << "=============== test case of String::at() ===============" << endl << endl << endl;
}
void tcString::clear()
{
	cout << "--------------- test case of String::clear() ---------------" << endl << endl;
	
	String strTest(_T("test String 测试用例"));
	cout << "test String: \"" << strTest.getCStr() << "\"" << endl;
	strTest.clear();
	cout << "After clear() called, test String: \"" << "\"" << endl;
	
	cout << "=============== test case of String::clear() ===============" << endl << endl << endl;
}

void tcString::compare()
{
	cout << "--------------- test case of String::compare() ---------------" << endl << endl;
	
	String strTest1(_T("this is a String"));
	String strTest2(_T("aaaaais a Sbbbbb"));
	char *chs1 = "this is a String";
	char *chs2 = "this is a Str";
	
	cout << "test String1:\"" << strTest1.getCStr() << "\"" << endl;
	cout << "test String2:\"" << strTest2.getCStr() << "\"" << endl;
	cout << "test characters1: \"" << chs1 << "\"" << endl;
	cout << "test characters2: \"" << chs2 << "\"" << endl;
	
	cout << "test String1 compares with test String2: " << strTest1.compare(strTest2) << endl;
	cout << "test String1 compares with test character1: " << strTest1.compare(chs1) << endl;
	cout << "test String1 compares with test String2 between 6th and 11th character: "<< strTest1.compare(5, 10, strTest2, 5, 10) << endl;
	cout << "test String1 compares with test character2 between 1st and 7th character: " << strTest1.compare(0, 6, chs2, 0, 6) << endl;
	cout << "test String1 compares with test character2 between 1st and 14th character: " << strTest1.compare(0, 13, chs2) << endl;
	cout << "test String1 compares with test character2 between 1st and 15th character: " << strTest1.compare(0, 14, chs2) << endl;

	cout << "=============== test case of String::compare() ===============" << endl << endl << endl;
}

void tcString::compareIgnoreCase()
{
	cout << "--------------- test case of String::compareIgnoreCase() ---------------" << endl << endl;
	
	cout << "=============== test case of String::compareIgnoreCase() ===============" << endl << endl << endl;
}
