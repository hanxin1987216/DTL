

#ifndef __HUANG_STRING_TEST_H__

#define __HUANG_STRING_TEST_H__ 2000

#include "dtprec.h"
#include "dtl/dtl.h"
#include "dtl/lang/string.h"

/**
*	test case for String class
*/
class tcString
{
public:

	/**
	* test case for constructors of String
	*/
	static void constructors();

	/**
	* test case for assign() functions of String 
	*/
	static void assign();

	/**
	* test case for append() functions of String
	*/
	static void append();

	/**
	* test case for at() functions of String
	*/
	static void at();

	/**
	* test case for clear() functions of String
	*/
	static void clear();

	/**
	* test case for compare() functions of String
	*/
	static void compare();

	/**
	* test case for compareIgnoreCase() functions of String
	*/
	static void compareIgnoreCase();

	/**
	* test case for copy() functions of String
	*/
	static void copy();

	/**
	* test case for find() functions of String
	*/
	static void find();


	static void findAny();

	static void findFirstOf();

	static void findFirstNotOf();

	static void findLastOf();

	static void findLastOfAny();

	static void findLastNotOf();

	static void insert();

	static void replace();

	static void reserve();

	static void resize();

	static void rfind();

	static void subString();

	static void toUpper();

	static void toLower();

	static void trim();

	static void leftString();

	static void rightString();

	static void split();

	static void getCStr();

	static void getSize();

	static void getLength();

	static void getCapacity();

	static void getMaxSize();

	static void isEmpty();

	static void operators();

	static void toString();
	
};

#endif 
