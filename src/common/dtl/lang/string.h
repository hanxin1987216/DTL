/***************************************************************************************************
string.h:	
	C++ Foundation Library header files
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	This file contain the declaration of classes String

Author:
	韩欣

Creating Time:
	2011-10-10
***************************************************************************************************/

#ifndef __DTL__STRING_H__
#define __DTL__STRING_H__

#if PRAGMA_ONCE
#	pragma once
#endif

#include <wchar.h>
#include <vector>


#ifndef __WINDOWS
	char* convertWcharToChar (const wchar_t* wchar);
	size_t  getGunichar2Len (const tchar_t* str);
	int printfToStr (tchar_t* buf, size_t bufSize, const tchar_t* fmt, ...);
#endif


string itos(int i);

#ifdef __WINDOWS__
#define t_strlen wcslen
#define t_snwprintf _snwprintf
#else
#define t_strlen getGunichar2Len
#define t_snwprintf printfToStr
#endif

/**
 * String 类声明
 */
class DTL_DLLEXPORT String
{
public:
	String (void);
	String (const string& str) 
	{
		_str = str;
	}

	String (const String& str) {
		assign (str);
	}

	String (const String& source, 
			size_t offset, 
			size_t count = NO_POSITION)
	{
		assign (source, offset, count);
	}
	
	explicit String (tchar_t ch, 
					 size_t count = 1)
	{
		assign (ch, count);
	}

	String(const tchar_t* ptr)
	{
		assign (ptr);
	}

	String (const tchar_t* ptr, size_t count)
	{
		assign (ptr, count);
	}


	~String (void);

public:


	/**
	 * Assigns new string with specified offset and count to the contents of this string.
	 *
	 * @param source 	The source string whose characters are to be assigned to this 
	 *					string.
	 * @throw Exception If offset is over than the length of @source.
	 * @return A reference to this string object that is being assigned.
	 */
	String& assign (const String& source);

	/**
	 * Assigns new string with specified offset and count to the contents of this string.
	 *
	 * @param source 	The source string whose characters are to be assigned to this 
	 *					string.
	 * @param offset 	The index of a character in @param source string that is the 
	 *					first to be used to assign character values for the string 
	 *					being constructed. 
	 * @param count 	The number of characters to be assigned. 
	 * 
	 * @throw Exception If offset is over than the length of @source.
	 * @return A reference to this string object that is being assigned.
	 */
	String& assign (const String& source, size_t offset, size_t count);
	String& assign (const tchar_t* ptr, size_t num);
	String& assign(const tchar_t* ptr);
	String& assign (tchar_t ch, size_t count);



	/**
	 * Adds a string to the end of this string.
	 * @param source 	The string whose characters are to be appended. 
	 * @return A reference to this string object that is being appended.
	 */
	String& append (const String& source)
	{	
		return append (source, 0, NO_POSITION);
	}

	String& append (const tchar_t* ptr)
	{	
		return append (ptr, t_strlen (ptr));
	}

	String& append (const String& source, size_t offset, size_t count);
	String& append (const tchar_t* ptr, size_t count);
	String& append (tchar_t ch, size_t count);


	/**
	 * Returns the character value with a specified index in a string.
	 * @param n 	The index of the position of the element to be returned. 
	 *				the base index is 0.		 
	 *
	 * @throw OutOfRangeException if @n is over than the length of this string.
	 */
	const tchar_t& at (size_t n) const; // read access
	tchar_t& at (size_t n); 


	/**
	* Clear the String, release memory
	*/
	void clear ();


	/**
	 * Compares a string with a specified string to determine if the two strings are equal 
	 * 	or if one is lexicographically less than the other.
	 *
	 */
	int compare ( const String& str ) const;
	int compare ( const tchar_t* s ) const;
	int compare ( size_t pos1, size_t n1, const String& str ) const;
	int compare ( size_t pos1, size_t n1, const tchar_t* s) const;
	int compare ( size_t pos1, size_t n1, const String& str, size_t pos2, size_t n2 ) const;
	int compare ( size_t pos1, size_t n1, const tchar_t* s, size_t n2) const;


	/**
	 * Compares a string with a specified string and ignore case to determine if the 
	 * 	two strings are equal or if one is lexicographically less than the other.
	 *
	 * @param source The string that is to be compared to this string.
	 * @return 	A < 0 value if this string is less than the parameter string; 
	 *			= 0 if the two strings are equal; 
	 *			or a > 0 value if this string is greater than the parameter string.
	 */		
	int compareIgnoreCase (const String& source) const;
	int compareIgnoreCase(const tchar_t *ptr) const;
	int compareIgnoreCase (size_t offset, size_t number, const String& source) const;
	int compareIgnoreCase (size_t offset, size_t number, const tchar_t *ptr) const;
						 

	/**
	* Copy sequence of characters from string to outStr
	* 
	* @param outStr  Array where the sequence of characters is copied. The storage space of the array shall already be allocated and should be large enough to contain n characters.
	* @param n      Number of characters to be copied. If this number is greater than the amount  of characters between pos and the end of the string content
	* @param pos    Position of the first character to be copied from the string.
	* 
	* @return       The effective length of the sequence of characters copied to outStr
	*/
	size_t copy ( tchar_t* outStr, size_t n, size_t pos = 0) const;

	/**
	* Erases a sequence of n characters starting at position pos.
	* Notice that both parameters are optional: with only one argument, 
	* the function deletes everything from position pos forwards, and with no arguments,
	* the function deletes the entire string, like member clear. 
	* @param pos  Position within the string of the first character to be erased.
	* @param n  Amount of characters to be removed. It may remove less characters if the end of the string is reached before the n characters have been erased. The default value of npos indicates that all the characters until the end of the string should be erased.
	* @return For the member that returns a string&, the function returns *this.
	*/
	String& erase ( size_t pos = 0, size_t n = NO_POSITION);


	/**
	* Searches the string for the content specified in either str, s or c,
	* and returns the position of the first occurrence in the string
	* 
	* @param str string to be searched for in the object. The entire content of str must be matched in some part of the string to be considered a match
	* @param pos Position of the first character in the string to be taken into consideration for possible matches. A value of 0 means that the entire string is considered.	
	* @return  The position of the first occurrence in the string of the searched content, If the content is not found, the member value npos is returned.
	* 			if not find return String::NO_POSTION
	*/
	size_t find ( const String& str, size_t pos = 0 ) const;

	/**
	* Searches the string for the content specified in either str, s or c,
	* and returns the position of the first occurrence in the string
	* 
	* @param s string to be searched for in the object. The entire content of str must be matched in some part of the string to be considered a match
	* @param pos Position of the first character in the string to be taken into consideration for possible matches. A value of 0 means that the entire string is considered.	
	* @return  The position of the first occurrence in the string of the searched content, If the content is not found, the member value npos is returned.
	*/
	size_t find ( const tchar_t* s, size_t pos = 0 ) const;
	size_t find ( const tchar_t* s, size_t pos, size_t n ) const;
	size_t find ( tchar_t c, size_t pos = 0 ) const;

	/**
	 * Reports the index of the first occurrence in this string of any character string.
	 * 
	 * @param chs   A character string containing one or more characters to seek. 
	 * @return 	The index position of the first occurrence in this instance where any character in chs was found; otherwise, -1 if no character in chs was found.
	 */
	size_t findAny (const String& chs) const;
	size_t findAny (size_t offset, const String& chs) const;

	/**
	* Searches the string for any of the characters that are part of either str, s or c, 
	* and returns the position of the first occurrence in the string.
	* When pos is specified the search only includes characters on or after position pos, 
	* ignoring any possible occurrences at previous character positions.
	* Notice that for a match to happen it is enough that one of the characters matches 
	* in the string (any of them). To search for an entire sequence of characters use find instead.
	*/
	size_t findFirstOf ( const String& str, size_t pos = 0 ) const;
	size_t findFirstOf ( const tchar_t* s, size_t pos = 0 ) const;
	size_t findFirstOf ( const tchar_t* s, size_t pos, size_t n ) const;
	size_t findFirstOf ( tchar_t c, size_t pos = 0 ) const;


	/**
	* Searches for the first character in the object which is not part of either str, s or c, and returns its position.
	* When pos is specified the search only includes characters on or after position pos, ignoring any content in the previous character positions.
	*/
	size_t findFirstNotOf ( const String& str, size_t pos = 0 ) const;
	size_t findFirstNotOf ( const tchar_t* s, size_t pos = 0 ) const;
	size_t findFirstNotOf ( const tchar_t* s, size_t pos, size_t n ) const;
	size_t findFirstNotOf ( tchar_t c, size_t pos = 0 ) const;


	/**
	* Searches the string from the end for any of the characters that are part of either str, s or c,
	* and returns the position of the last occurrence in the string.
	* When pos is specified the search only includes characters on or before position pos, ignoring any possible
	* occurrences at character positions after it.	
	* Notice that for a match to happen is enough that one of the characters matches in the string (any of them). 
	* To search from the end for an entire sequence of characters use rfind instead.
	*/
	size_t findLastOf ( const String& str, size_t pos = NO_POSITION ) const;
	size_t findLastOf ( const tchar_t* s, size_t pos = NO_POSITION ) const;
	size_t findLastOf ( const tchar_t* s, size_t pos, size_t n ) const;
	size_t findLastOf ( tchar_t c, size_t pos = NO_POSITION ) const;



			
	/**
	 * Reports the index of the last occurrence in this string of any character string.
	 *
	 * @param chs 	A character string containing one or more characters to seek.
	 * @return 	The index position of the last occurrence in this string where any 
	 *			character in chs was found; otherwise, NO_POSITION if no character in 
	 *			was found.
	 */
	size_t findLastOfAny (const String& chs) const
	{
		return findLastOfAny (getLength () - 1, chs);
	}
	
	size_t findLastOfAny (size_t offset, const String& chs) const;		


	/**
	* Searches for the last character in the object which is not part of either str, s or c, and returns its position.
	* When pos is specified the search only includes characters on or before position pos, ignoring any content in the character positions after it.
	*/
	size_t findLastNotOf ( const String& str, size_t pos = String::NO_POSITION ) const;
	size_t findLastNotOf ( const tchar_t* s, size_t pos = String::NO_POSITION ) const;
	size_t findLastNotOf ( const tchar_t* s, size_t pos, size_t n ) const;
	size_t findLastNotOf ( tchar_t c, size_t pos = String::NO_POSITION) const;


	/**
	* The current string content is extended by inserting some additional content at a
	* specific location within the string content (this position is determined by either 
	* pos1 or p, depending on the function version used).
	*/
	String& insert ( size_t pos1, const String& str );
	String& insert ( size_t pos1, const String& str, size_t pos2, size_t n );
	String& insert ( size_t pos1, const tchar_t* s, size_t n);
	String& insert ( size_t pos1, const tchar_t* s );
	String& insert ( size_t pos1, size_t n, tchar_t c );


	/**
	* Replaces a section of the current string by some other content determined by the arguments passed.
	*
	*/	
	String& replace (tchar_t oldValue, tchar_t newValue, bool replaceAll = false);                        	   
	String& replace ( size_t pos1, size_t n1,   const String& str );
	String& replace ( size_t pos1, size_t n1, const String& str, size_t pos2, size_t n2 );
	String& replace ( size_t pos1, size_t n1,   const tchar_t* s, size_t n2 );
	String& replace ( size_t pos1, size_t n1,   const tchar_t* s );
	String& replace ( size_t pos1, size_t n1,   size_t n2, tchar_t c );


	/**
	* Request a change in capacity
	* Requests that the capacity of the allocated storage space in the string be at least res_arg.
	* res_arg 
	*    Minimum amount of allocated storage to be reserved.
	*    size_t is an unsigned integral type. 
	*/
	void reserve ( size_t res_arg = 0);
	

	/**
	* Resizes the string content to n characters.
	* n : New size for the string, expressed in characters.
	* size_t : is an unsigned integral type. 
	* c Character to be used to fill any additional character space in the string. 
	*/
	void resize ( size_t n, tchar_t c );
	void resize ( size_t n );


	/** 
	* Searches the string for the content specified in either str, s or c, and returns the position of the last occurrence in the string.
	* When pos is specified, the search only includes characters between the beginning of the string and position pos, ignoring any possible occurrences after pos.
	*
	*	s Array with a sequence of characters.
	*	  In the second member function version, the size of the content to be matched is only determined by parameter n.
	*	  In the third version, a null-terminated sequence is expected, and its end is determined by the first occurrence of a null character in it.
	*	n
	*	  Length of sequence of characters to search for.
	*	c
	*	  Individual character to be searched for.
	*	pos
	*	  Position of the last character in the string to be taken into consideration for possible matches. The default value npos indicates that the entire string is searched.	
	*
	*/
	size_t rfind ( const String& str, size_t pos = NO_POSITION ) const;
	size_t rfind ( const tchar_t* s, size_t pos, size_t n ) const;
	size_t rfind ( const tchar_t* s, size_t pos = NO_POSITION ) const;
	size_t rfind ( tchar_t c, size_t pos = NO_POSITION ) const;


	/** 
	*  Returns a string object with its contents initialized to a substring of the current object.
	*  This substring is the character sequence that starts at character position pos and has a length of n characters.
	*/
	String subString (size_t pos = 0, size_t n = NO_POSITION) const;


	/**
	 * Convert to upper case in place.
	 */
  	void toUpper (void);
      
    /**
     * Convert to lower case in place.
     */
  	void toLower (void);
  
  	/**
	 * 删除字符两边的空格、换行符
	 *
	 * @return The string that has been trimmed.  
	 */
  	String trim ();
	String trimLeft ();
	String trimRight ();
  	
  	/**
  	 * Get first count characters.
  	 */
	String leftString (size_t count) const;
	
	/**
	 * Get last count characters.
	 */
	String rightString (size_t count) const;	

  	/**
	 * Creates an array of strings by splitting this string with a 
	 *	specified separator string.
	 * The separator is searched for and, if found, the substring 
	 *	preceding the occurrence is stored as the first element in 
	 *	the array of strings. It is continued in this manner by searching 
	 *	the substring that follows the occurrence.
	 * On the other hand, if the separator is not found, the array of 
	 *	strings will contain this instance as its only element. 
	 *
	 * @param separators	The specified separator string. 
	 * @param substrs		The vector returns the separated strings.
	 */
	void split (const String& separators, std::vector<String>& substrs) const;
	void split (tchar_t separator, std::vector<String>& substrs) const;



	/**
	 * This method writes formatted data to a String in the same way that sprintf 
	 *	formats data into a C-style character array.
	 *
	 * @param fmt 	Specifies a format-control string.
	 * @throw FormatException If cannot format the string.
	 */
	void format (const tchar_t* fmt, ...);


				 
	/**
	 * This method writes formatted data to a String in the same way that vprintf 
	 *	formats data into a C-style character array.
	 *
	 * @param fmt 	Specifies a format-control string.
	 * @param ap 	Pointer of list of arguments.
	 * @throw FormatException If cannot format the string.
	 */
	void formatv (const tchar_t* fmt, va_list ap);		

public:

	/**
	 * Returns the contents of a String as a C-style, null-terminated, string.
	 * @return The C-style string pointer. The type is wide character (UTF16).
	 */
	const tchar_t* getCStr (void) const 
	{
		return _str.c_str (); 
	}

	const size_t getCSize ( void ) const
	{
		return _str.size ();
	}

	/**
     * Returns the length of this string. The length is equal to the number of 16-bit
     * Unicode characters in the string.
     *
     * @return  the length of the sequence of characters represented by this string.
     */
	size_t getLength (void) const
	{	
		return _str.length ();	
	}

	/** 
	 * Returns the largest number of elements that could be stored in a string without 
	 * increasing the memory allocation of the string
	 *
	 * @return the size of storage currently allocated in memory to hold the string.
	 */
	size_t getCapacity (void) const
	{
		return _str.capacity ();
	}

	/** 
	 * Returns the maximum number of characters a string could contain.
	 *
	 * @return The maximum number of characters a string could contain.
	 */
	size_t getMaxSize (void) const
	{
		return string::npos;
	}

	/**
	 * Tests whether the string is contains characters or not.
	 * @return true if the string object contains no characters; 
	 * false if it has at least one character.
	 */
	bool isEmpty () const
	{	
		return _str.empty (); 
	}



// public operator
public:
	String& operator= (const String& source)
	{	
		return assign (source);
	}

	String& operator= (const tchar_t* ptr)
	{	
		return assign (ptr);
	}

	String& operator= (tchar_t ch)
	{	
		return assign(ch, 1);
	}

	String& operator+= (const String& source)
	{	
		return append (source);
	}

	String& operator+=(const tchar_t* ptr)
	{	
		return append (ptr);
	}

	String& operator+=(tchar_t ch)
	{	
		return append (ch, (size_t) 1);
	}

	/**
	 * Operator version of at
	 */
	tchar_t  operator[] (size_t n) const
	{ 
		return at (n);
	}
	tchar_t& operator[] (size_t n)
	{ 
		return at (n);
	}

	/**
	 * Append an bool into string
	 */
	String& operator<<(bool b)
	{ 
		if (b)
			return append ("True", 4);
		else
			return append ("False", 5);
	}

	/**
	 * Append an int into string
	 */
	String& operator<<(int i)
	{ 
		tchar_t buf[32];

		int len = t_snwprintf (buf, 32, _T("%d"), i);
		return append (buf, len); 
	}
	
	/**
	 * Append an unsigned int into string
	 */
	String& operator<<(unsigned int ui)
	{ 
		tchar_t buf[32];

		int len = t_snwprintf (buf, 32, _T("%u"), ui);
		return append (buf, len);
	}
	
	/**
	 * Append a int64 into string
	 */
	String& operator<<(const int64& l)
	{
		tchar_t buf[64];

		int len = t_snwprintf (buf, 
									 64, 
#ifdef __VISUALC__
									 _T("%I64d"),
#else
									 "%lli",
#endif
									  l);

		return append (buf, len);
	}
	
	/**
	 * Append an unsigned int64 into string
	 */
	String& operator<<(const uint64& ul)
	{ 
		tchar_t buf[64];

#ifdef __VISUALC__
		int len = t_snwprintf (buf, 64, _T("%I64u"), ul);
#else
		int len = t_snwprintf (buf, 64, "%llu", ul);
#endif
		return append (buf, len);
	}

	/**
	 * Append a float into string
	 */
	String& operator<<(float f)
	{ 
		tchar_t buf[32];

		int len = t_snwprintf (buf, 32, _T("%f"), f);

		return append (buf, len);
	}

	/**
	 * Append a double into string
	 */
	String& operator<<(double d)
	{ 
		tchar_t buf[64];

		int len = t_snwprintf (buf, 64, _T("%g"), d);

		return append (buf, len);
	}

	String& operator<< (const String& source)
	{
		return append (source);
	}

	String& operator<< (const tchar_t* ptr)
	{
		return append(ptr); 
	}
	
	String& operator<< (tchar_t ch) 
	{ 
		return append (ch, (size_t) 1); 
	}


public:

    static String Format(const tchar_t *fmt, ...);

	// number to string
	static String toString (bool b)
	{
		String str;
		str << b;
		
		return str;
	}
	
	static String toString (short s)
	{
		String str;
		str << s;
		
		return str;
	}
	
	static String toString (unsigned short us)
	{
		String str;
		str << us;
		
		return str;
	}
	
	static String toString (int i)
	{
		String str;
		str << i;
		
		return str;
	}
	
	static String toString (unsigned int ui)
	{
		String str;
		str << ui;
		
		return str;
	}
	
	static String toString (const int64& l)
	{
		String str;
		str << l;
		
		return str;
	}
	
	static String toString (const uint64& ul)
	{
		String str;
		str << ul;
		
		return str;
	}
	
	static String toString (float f)
	{
		String str;
		str << f;
		
		return str;
	}
	
	static String toString (double d)
	{
		String str;
		str << d;
		
		return str;
	}


// Data members
private:

#ifdef __UNICODE__
		wstring		_str;
#else
		string	 _str;
#endif

public:
		static const size_t NO_POSITION;

		/**
		 * The empty string instance.
		 */ 
		static const String EMPTY;

}; // End class String



/////////////////////////////////////////////////////////////////////////////////////////////////
// String comparison functions: operator versions are always case sensitive

inline bool operator== (const String& s1, const String& s2)
{ 
	return (s1.getLength () == s2.getLength()) && (s1.compare (s2) == 0); 
}

inline bool operator== (const String& s1, const tchar_t* s2)
{ 
	return (s1.compare (s2) == 0); 
}

inline bool operator== (const tchar_t* s1, const String& s2)
{ 
	return (s2.compare (s1) == 0); 
}

inline bool operator!= (const String& s1, const String& s2)
{
	return (s1.getLength() != s2.getLength()) || (s1.compare (s2) != 0);
}

inline bool operator!= (const String& s1, const tchar_t* s2)
{ 
	return (s1.compare (s2) != 0); 
}

inline bool operator!= (const tchar_t* s1, const String& s2)
{
	return (s2.compare (s1) != 0); 
}

inline bool operator< (const String& s1, const String& s2)
{ 
	return (s1.compare (s2) < 0); 
}

inline bool operator< (const String& s1, const tchar_t* s2)
{ 
	return (s1.compare (s2) <  0); 
}

inline bool operator< (const tchar_t* s1, const String& s2)
{ 
	return (s2.compare(s1) >  0);
}
	
inline bool operator> (const String& s1, const String& s2)
{ 
	return (s1.compare (s2) >  0); 
}

inline bool operator> (const String& s1, const tchar_t* s2)
{ 
	return (s1.compare (s2) >  0); 
}

inline bool operator> (const tchar_t* s1, const String& s2)
{ 
	return (s2.compare (s1) <  0); 
}

inline bool operator<= (const String& s1, const String& s2)
{ 
	return (s1.compare (s2) <= 0); 
}

inline bool operator<= (const String& s1, const tchar_t* s2)
{ 
	return (s1.compare (s2) <= 0); 
}

inline bool operator<= (const tchar_t* s1, const String& s2)
{ 
	return (s2.compare(s1) >= 0); 
}

inline bool operator>= (const String& s1, const tchar_t* s2)
{ 
	return (s1.compare (s2) >= 0); 
}


inline bool operator>= (const String& s1, const String& s2)
{ 
	return (s1.compare (s2) >= 0); 
}

inline bool operator>= (const tchar_t* s1, const String& s2)
{ 
	return (s2.compare (s1) <= 0); 
}


String DTL_DLLEXPORT operator+(const String& str1,  const String& str2);
String DTL_DLLEXPORT operator+(const String& str, tchar_t ch);
String DTL_DLLEXPORT operator+(tchar_t ch, const String& str);
String DTL_DLLEXPORT operator+(const String& str, const tchar_t* ptr);
String DTL_DLLEXPORT operator+(const tchar_t *ptr, const String& str);




#endif // __DTL__STRING_H__
