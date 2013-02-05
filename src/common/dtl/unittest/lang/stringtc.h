// Unit Test code for class cpp::lang::String

#ifndef __STRINGTC_H__
#define __STRINGTC_H__

#include <cppunit/tester.h>


class StringTestCase : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE (StringTestCase);

		CPPUNIT_TEST_DESCRIPTION (toUpper, _T("测试String toUpper  把字符串中的小写字母转化为大写"));	
		CPPUNIT_TEST_DESCRIPTION (toLower, _T("测试String toLower  把字符串中的大写字母转化为小写"));
		CPPUNIT_TEST_DESCRIPTION (getLength, _T("测试String getLength  获得字符串的长度"));
		CPPUNIT_TEST_DESCRIPTION (assign, _T("测试String assign 字符串赋值"));
		CPPUNIT_TEST_DESCRIPTION (append,_T("测试String  append 字符串附加"));
		CPPUNIT_TEST_DESCRIPTION (at,_T("测试String  at 字符串定位"));
		CPPUNIT_TEST_DESCRIPTION (clear,_T("测试String clear 清除字符串"));
		CPPUNIT_TEST_DESCRIPTION (compare,_T("测试String compare 比较两个字符串"));
		CPPUNIT_TEST_DESCRIPTION (compareIgnoreCase,_T("测试String compareIgnoreCase 比较两个字符串，不顾大小写"));
		CPPUNIT_TEST_DESCRIPTION (copy,_T("测试String copy 复制字符串"));
		CPPUNIT_TEST_DESCRIPTION (erase,_T("测试String erase 删除字符串"));
		CPPUNIT_TEST_DESCRIPTION (find,_T("测试String find 找字符串"));
		CPPUNIT_TEST_DESCRIPTION (findFirstOf,_T("测试String  findFirstOf 找出字符串中任意字符或字符组第一次出现的位置"));
		CPPUNIT_TEST_DESCRIPTION (findFirstNotOf,_T("测试String findFirstNotOf 找出第一个不出现在字符串中字符的位置"));
		CPPUNIT_TEST_DESCRIPTION (findLastOf,_T("测试String findLastOf 从母串的末尾开始寻找在子串中任意字符第一次出现的位置"));
		CPPUNIT_TEST_DESCRIPTION (findLastNotOf,_T("测试String findLastNotOf 从母串的末尾开始寻找第一次出现的不在字串中的字符的位置"));
		CPPUNIT_TEST_DESCRIPTION (insert,_T("测试String insert 在字符串中插入一些字符"));
		CPPUNIT_TEST_DESCRIPTION (replace,_T("测试String replace 替换字符串中某些字符"));
		CPPUNIT_TEST_DESCRIPTION (reserve,_T("测试String reserve 设置字符串的容量"));
		CPPUNIT_TEST_DESCRIPTION (resize,_T("测试String resize 重新设置字符串的大小"));
		CPPUNIT_TEST_DESCRIPTION (rfind,_T("测试String rfind 找出指定字符串最后出现的位置"));
		CPPUNIT_TEST_DESCRIPTION (subString,_T("测试String subString 从字符串中截取子字符串"));
		CPPUNIT_TEST_DESCRIPTION (trim,_T("测试String trim 清除字符串左右两端的空格"));
		CPPUNIT_TEST_DESCRIPTION (trimLeft,_T("测试String trimLeft 清除字符串左端的空格"));
		CPPUNIT_TEST_DESCRIPTION (trimRight,_T("测试String trimRight 清除字符串右端的空格"));
		CPPUNIT_TEST_DESCRIPTION (leftString,_T("测试String leftString 得到字符串左边的n个字符"));
		CPPUNIT_TEST_DESCRIPTION (rightString,_T("测试String rightSring 得到字符串右边的n个字符"));
		CPPUNIT_TEST_DESCRIPTION (split,_T("测试String split 把一个字符串分割成几个子字符串"));
		CPPUNIT_TEST_DESCRIPTION (format,_T("测试String format 把一个字符串以特定格式输出"));
		CPPUNIT_TEST_DESCRIPTION (operator_t,_T("测试String operator 字符串一些重载运算符"));
		
	CPPUNIT_TEST_SUITE_END ();
	
public:
	void setUp (void)
	{
	}
	
	void tearDown (void)
	{
	}
	
protected:
	void toUpper (void);
	void toLower (void);
	void getLength (void);
	void assign (void);
	void append (void);
	void at (void);
	void clear (void);
	void compare (void);
	void compareIgnoreCase (void);
	void copy (void);
	void erase (void);
	void find (void);
	void findFirstOf (void);
	void findFirstNotOf (void);
	void findLastOf (void);
	void findLastNotOf (void);
	void insert (void);
	void replace (void);
	void reserve (void);
	void resize (void);
	void rfind (void);
	void subString (void);
	void trim (void);
	void trimLeft (void);
	void trimRight (void);
	void leftString (void);
	void rightString (void);
	void split (void);
	void format (void);
	void operator_t (void);
	
}; // End class IntTestCase

#endif // __INTTC_H__

