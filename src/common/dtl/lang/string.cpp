/***************************************************************************************************
string.cpp:	
	C++ Foundation Library header files
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	This file contain the declaration of classes:
	#Int64: Represents a 64-bit signed int type.

Author:
	韩欣

Creating Time:
	2011-10-10
***************************************************************************************************/
#include "../prec.h"
#include "../mono_base/uglify.h"

#include "string.h"
#include "../sys/exception.h"

#include <sstream>
#include <limits.h>
#include <algorithm>
#include <stdarg.h> 


// public static 
const String String::EMPTY;	
const size_t String::NO_POSITION = string::npos;



#ifndef __WINDOWS__
size_t 
getGunichar2Len (const tchar_t* str)
{
	return strlen (str);
}

// public static 
int 
printfToStr (tchar_t* buf, size_t bufSize, const tchar_t* fmt, ...)
{
	va_list ap;
	va_start (ap, fmt);

	int len = ::vsprintf (buf, fmt, ap);
	
	va_end (ap);

	return len;
	//return snprintf (buf, bufSize, fmt);
}

char* 
convertWcharToChar (const wchar_t* wchar)
{
#if (__SIZEOF_WCHAR__ == 4)
	gunichar2* unichar2 = g_ucs4_to_utf16 ((gunichar*)wchar, -1, NULL, NULL, NULL);
	gchar* charStr = g_utf16_to_utf8 (unichar2, -1, NULL, NULL, NULL);
	g_free (unichar2);
	return charStr;
#else
	return g_utf16_to_utf8 ((gunichar2*) wchar, -1, NULL, NULL, NULL);
#endif
}

#endif


string itos(int i) //   convert   int   to   string 
{ 
	stringstream s; 
	s<<i; 
	return s.str(); 
} 


// public ctor
String::String (void)
{
	// Do nothing
}


// public dtor
String::~String (void)
{
	// Do nothing
}


// public
String& 
String::assign(const String& source)
{
	_str.assign (source.getCStr ());
	return (*this);
}


// public
String& 
String::assign(const String& source, size_t offset, size_t count)
{
	if (offset >= source.getLength ())
		THROW (_T("the offset is out of range"));

	_str.assign (source.getCStr (), offset, count);

	return (*this);
}



// public
String& 
String::assign(const tchar_t* ptr)
{
	if (ptr != NULL)
		_str.assign (ptr);

	return (*this);
}


// public
String& 
String::assign(const tchar_t* ptr, size_t num)
{
	if (ptr != NULL)
		_str.assign (ptr, num);
	return (*this);
}

String&
String::assign (tchar_t ch, size_t count)
{
	_str.assign (count, ch);
	return (*this);
}



// public
String& 
String::append (const String& source, size_t offset, size_t count)
{	
	_str.append (source.getCStr (), offset, count);
	return (*this);
}

// public
String& 
String::append (const tchar_t* ptr, size_t count)
{	
	if (ptr != NULL)
		_str.append (ptr, count);
	return (*this);
}


String& 
String::append(tchar_t ch, size_t count)
{
	_str.append (count, ch);

	return (*this);
}


// public
const tchar_t & 
String::at (size_t n) const 
{
	// subscript mutable sequence with checking
	if (_str.size () <= n)
		THROW ("out of range");
	
	return _str.at (n);
}
 
// public
tchar_t& 
String::at (size_t n) // read/write access
{
	// subscript mutable sequence with checking
	if (_str.size () <= n)
		THROW ("out of range");
	
	return _str.at (n);
}

//public
void
String::clear ()
{
	_str.clear ();
}


int
String::compare ( const String& str ) const
{
	return _str.compare (str.getCStr ());
}

int
String::compare ( const tchar_t* s ) const
{
	return _str.compare (s);	
}


int
String::compare ( size_t pos1, size_t n1, const String& str ) const
{
	return _str.compare (pos1,n1, str.getCStr ());
}

int
String::compare ( size_t pos1, size_t n1, const tchar_t* s) const
{
	return _str.compare (pos1,n1, s);	
}
int
String::compare ( size_t pos1, size_t n1, const String& str, size_t pos2, size_t n2 ) const
{
	//return _str.compare (pos1, n1, str);
    String tempstr = str.subString( pos2, n2 );
	return _str.compare( pos1, n1, tempstr.getCStr ());
}

int
String::compare ( size_t pos1, size_t n1, const tchar_t* s, size_t n2) const
{
	return _str.compare(pos1,n1, s, n2);
}


//////////////////////////////////////////////////////////////////////


int
String::compareIgnoreCase (const String& source) const
{
	size_t size = getLength ();
	if (size != source.getLength ())
		return 1;

	//
	// 逐字符比较
	//
	for (size_t i = 0; i < size; i++) {
		if (tolower (_str[i]) != tolower (source[i]))
			return 1;
	}

	return 0;
}

int
String::compareIgnoreCase(const tchar_t *ptr) const
{
    String tempstr(ptr);
	return compareIgnoreCase (tempstr);
}


int 
String::compareIgnoreCase (size_t offset, size_t number, const String& source) const
{
	String temp = _str.substr (offset, number);
	return temp.compareIgnoreCase (source);
}


int
String::compareIgnoreCase (size_t offset, size_t number, const tchar_t *ptr) const
{
	String temp = _str.substr (offset, number);
	return temp.compareIgnoreCase (ptr);
}



////////////////////////////////////////////////////////////////////

size_t
String::copy ( tchar_t* s, size_t n, size_t pos) const
{
	return _str.copy (s, n, pos);
}

String&
String::erase ( size_t pos, size_t n)
{
	if (pos > _str.length ())
		THROW (_T("erase pos is out of range"));

	if (pos + n > _str.length ())
		n = _str.length () - pos;

	_str.erase (pos, n);
	return (*this);
}



size_t
String::find ( const String& str, size_t pos ) const
{
	return _str.find (str.getCStr (), pos);
}

size_t
String::find ( const tchar_t* s, size_t pos ) const
{
	return _str.find (s, pos);
}


size_t
String::find ( const tchar_t* s, size_t pos, size_t n ) const
{
	return _str.find (s, pos, n);
}


size_t
String::find ( tchar_t c, size_t pos ) const
{
	return _str.find (c,pos);
}

/////////////////////////////////////////////////////////////////////



size_t
String::findAny (const String& chars) const
{
	return findAny (0, chars);
}

size_t
String::findAny (size_t offset, const String& chars) const
{
	size_t size = _str.size ();
	if (offset > size)
		THROW (_T("IDS_OFFSET_OFR"));

	//size -= offset;
	size_t charsSize = chars.getLength ();
	const tchar_t* ptr = _str.c_str ();

	for (size_t pos = offset; pos < size; pos++) {				
		for (size_t loop = 0; loop != charsSize; loop++)
			if (ptr[pos] == chars[loop])
				return (int) pos; // return the position
	}

	return NO_POSITION;
}



//////////////////////////////////////////////////////////////////////

size_t
String::findFirstOf ( const String& str, size_t pos ) const
{
	return _str.find_first_of (str.getCStr (), pos);
}


size_t
String::findFirstOf ( const tchar_t* s, size_t pos ) const
{
	return _str.find_first_of (s, pos);
}


size_t 
String::findFirstOf ( const tchar_t* s, size_t pos, size_t n ) const
{
	return _str.find_first_of (s, pos, n);

}


size_t 
String::findFirstOf ( tchar_t c, size_t pos) const
{
	return _str.find_first_of (c, pos);
}



/////////////////////////////////////
size_t
String::findFirstNotOf ( const String& str, size_t pos ) const
{
	return _str.find_first_not_of (str.getCStr (), pos);
}


size_t
String::findFirstNotOf ( const tchar_t* s, size_t pos ) const
{
	return _str.find_first_not_of (s, pos);
}


size_t 
String::findFirstNotOf ( const tchar_t* s, size_t pos, size_t n ) const
{
	return _str.find_first_not_of (s, pos, n);

}


size_t 
String::findFirstNotOf ( tchar_t c, size_t pos) const
{
	return _str.find_first_not_of (c, pos);
}

//////////////////////////////

size_t
String::findLastOf ( const String& str, size_t pos ) const
{
	return _str.find_last_of (str.getCStr (), pos);
}


size_t
String::findLastOf ( const tchar_t* s, size_t pos ) const
{
	return _str.find_last_of (s, pos);
}


size_t 
String::findLastOf ( const tchar_t* s, size_t pos, size_t n ) const
{
	return _str.find_last_of (s, pos, n);

}


size_t 
String::findLastOf ( tchar_t c, size_t pos) const
{
	return _str.find_last_of (c, pos);
}

////////////////////////////////


size_t
String::findLastNotOf ( const String& str, size_t pos ) const
{
	return _str.find_last_not_of (str.getCStr (), pos);
}


size_t
String::findLastNotOf ( const tchar_t* s, size_t pos ) const
{
	return _str.find_last_not_of (s, pos);
}


size_t 
String::findLastNotOf ( const tchar_t* s, size_t pos, size_t n ) const
{
	return _str.find_last_not_of (s, pos, n);

}


size_t 
String::findLastNotOf ( tchar_t c, size_t pos) const
{
	return _str.find_last_not_of (c, pos);
}


/////////////////////////////////////////////////////////////////////////////////////////////


size_t
String::findLastOfAny (size_t offset, const String& chars) const
{
	size_t size = _str.size ();
	if (offset >= size)
		THROW (_T("IDS_OFFSET_OFR"));

	size_t charsSize = chars.getLength ();
	const tchar_t* ptr = _str.c_str ();
	
	for (size_t pos = offset; pos != NO_POSITION; --pos) {
		for (size_t loop = 0; loop != charsSize; loop++)
			if (ptr[pos] == chars[loop])
				return (int) pos; // return the position
	}

	return NO_POSITION;
}


////////////////////////////////////////////////////////////////////////////////////////////

String& 
String::insert ( size_t pos1, const String& str )
{
	_str.insert (pos1, str.getCStr ());
	return (*this);
}

String&
String::insert ( size_t pos1, const String& str, size_t pos2, size_t n )
{
	_str.insert (pos1, string (str.getCStr ()), pos2, n);
	return (*this);
}

String&
String::insert ( size_t pos1, const tchar_t* s, size_t n)
{
	_str.insert (pos1, s, n);
	return (*this);
}
String&
String::insert ( size_t pos1, const tchar_t* s )
{
	_str.insert (pos1, s);
	return (*this);
}


String&
String::insert ( size_t pos1, size_t n, tchar_t c )
{
	_str.insert (pos1, n, c);
	return (*this);
}





//////////////////////////////////////////////////////////////////////

String&
String::replace (tchar_t oldValue, tchar_t newValue, bool replaceAll)
{
	if (oldValue != newValue) {
		size_t size = _str.length ();
		
	    for (size_t i = 0; i < size; ++i) {
	    	if (_str[i] == oldValue) {
	    		_str[i] = newValue;
	    		
	    		if (!replaceAll)
	    			break; //don't replace all char, break the loop.
	    	}
	    }
	}
	
	return (*this);

}

String&
String::replace ( size_t pos1, size_t n1,   const String& str )
{
	_str.replace (pos1, n1, str.getCStr ());
	return (*this);
}


String&
String::replace ( size_t pos1, size_t n1, const String& str, size_t pos2, size_t n2 )
{
	_str.replace (pos1, n1, string (str.getCStr ()), pos2, n2);
	return (*this);
}


String&
String::replace ( size_t pos1, size_t n1,   const tchar_t* s, size_t n2 )
{
	_str.replace (pos1, n1, s, n2);
	return (*this);
}


String& 
String::replace ( size_t pos1, size_t n1,   const tchar_t* s )
{
	_str.replace (pos1, n1, s);
	return (*this);
}

String&
String::replace ( size_t pos1, size_t n1,   size_t n2, tchar_t c )
{
	_str.replace (pos1, n1, n2, c);
	return (*this);
}


void
String::reserve ( size_t res_arg)
{
	_str.reserve (res_arg);
}



void
String::resize ( size_t n, tchar_t c )
{
	_str.resize (n,c);
}


void 
String::resize ( size_t n )
{
	_str.resize (n);
}


size_t
String::rfind ( const String& str, size_t pos) const
{
	return _str.rfind (str.getCStr (), pos);
}
size_t
String::rfind ( const tchar_t* s, size_t pos, size_t n ) const
{
	//
	//  如果n 大于搜索字符串s， 按照s的长度搜索
	//
	if (n > getGunichar2Len (s))
		n = getGunichar2Len (s);

	return _str.rfind (s, pos, n);
}
size_t
String::rfind ( const tchar_t* s, size_t pos) const
{
	return _str.rfind (s, pos);
}

size_t
String::rfind ( tchar_t c, size_t pos) const
{
	return _str.rfind (c, pos);
}


String
String::subString (size_t pos, size_t n) const
{
	if (pos > _str.length ())
		THROW (_T("subString offset is out of range"));

	if (pos + n > _str.length ())
		n = _str.length () - pos;

	return _str.substr (pos, n);
}



// public
void 
String::toUpper (void)
{
	size_t size = getLength ();
	
	for (size_t i = 0; i < size; i++)
		_str[i] = toupper (_str[i]);
}

// public
void 
String::toLower (void)
{
	size_t size = getLength ();
	
	for (size_t i = 0; i < size; i++)
		_str[i] = tolower (_str[i]);

}

// public
String 
String::trim ()
{
 	_str.erase (0, _str.find_first_not_of(" \t\n\r"));
	_str.erase (_str.find_last_not_of(" \t\n\r") + 1); 

	return _str;
}

// public
String 
String::trimLeft ()
{
 	_str.erase (0, _str.find_first_not_of(" \t\n\r"));
	return _str;
}

// public
String 
String::trimRight ()
{
	_str.erase (_str.find_last_not_of(" \t\n\r") + 1); 
	return _str;
}

/////////////////////////////////////////////////////////////////


	  	
// public
String 
String::leftString (size_t count) const
{
	if (count > _str.size ())
		count = _str.size ();
		
	return String ( *this, 0, count);
}

// public
String 
String::rightString (size_t count) const 
{
	size_t size = _str.size ();
	if (count > size)
		count = size;
		
	return String ( *this, size - count, size );
}



/////////////////////////////////////////////////////////////////////////////////////////

void
String::split (const String& separators, std::vector<String>& substrs) const
{
	substrs.clear ();

	if (_str.empty()) {
		return;  
	}  

	string tmp;  
	string::size_type pos_begin = _str.find_first_not_of(separators.getCStr ());  
	string::size_type comma_pos = 0; 
	while (pos_begin != string::npos)   
	{
		comma_pos = _str.find(separators.getCStr (), pos_begin); 
		if (comma_pos != string::npos)   
		{  
			tmp = _str.substr(pos_begin, comma_pos - pos_begin);     
			pos_begin = comma_pos + separators.getLength ();    
		}  
		else 
		{
			tmp = _str.substr(pos_begin);
			pos_begin = comma_pos;    
		} 

		substrs.push_back(tmp);     
		tmp.clear(); 
	} 
}


void
String::split (tchar_t separator, std::vector<String>& substrs) const
{
	substrs.clear ();

	if (String(separator) == String(""))
		THROW ("split separate cannot be empty");
		
	if (separator == ' ') {	
		String tmp;
		for (int i =0; i < _str.length (); i++) {
			if (i == (_str.length () -1) && _str[i] != ' ') {
				tmp.append (String(_str[i]));
				substrs.push_back (tmp);
				tmp.clear ();
			}
				
			if (_str[i] == ' ') 
			{
				if (tmp.isEmpty ())
					continue;
				
				substrs.push_back (tmp);
				tmp.clear ();
			}
			else 
				tmp.append (String(_str[i]));			
		}
	}
	else {
		String tmp (separator);
		split (tmp, substrs);
	}
}





///////////////////////////////////////////////////////////////////////////////////////////

#define F_BUFF_SIZE 4096

void
String::format (const tchar_t* fmt, ...)
{
	va_list ap;
	char text[F_BUFF_SIZE] = {0};
	va_start(ap, fmt);
	vsnprintf(text, F_BUFF_SIZE, fmt, ap);
	va_end(ap);

	_str = string (text);
}


					 
// public 
void
String::formatv (const tchar_t* fmt, va_list ap)
{
	char text[F_BUFF_SIZE] = {0};
	vsnprintf(text, F_BUFF_SIZE, fmt, ap);

	_str = string (text);
}

String
String::Format(const tchar_t * fmt, ...) {
    String tmp;
    va_list ap;
    va_start(ap, fmt);
    tmp.formatv(fmt, ap);
    va_end(ap);
    return tmp;
}


/////////////////////////////////////////////////////////////////////////////////////////////////
// String operators

String DTL_DLLEXPORT 
operator+(const String& str1,  const String& str2)
{
	String s = str1;
  	s += str2;

  	return s;
}

String DTL_DLLEXPORT 
operator+(const String& str, tchar_t ch)
{
	String s = str;
  	s += ch;

  	return s;
}

String DTL_DLLEXPORT 
operator+(tchar_t ch, const String& str)
{
	String s(ch);
  	s += str;

	return s;
}

String DTL_DLLEXPORT 
operator+(const String& str, const tchar_t* ptr)
{
	String s = str;
	s += ptr;
	
	return s;
}

String DTL_DLLEXPORT 
operator+(const tchar_t *ptr, const String& str)
{
	String s = ptr;
  	s += str;

  	return s;
}
