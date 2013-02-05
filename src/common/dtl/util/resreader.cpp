/****************************************************************************************************
resreader.cpp
 	Copyright (c) Datatom, Inc.(2011), All rights reserved.

Purpose:
	resource file reader
	
Auther:
	hanxin

Created Time:
	2012-3-08
****************************************************************************************************/

#include <dtprec.h>
#include "../prec.h"
#include "../mono_base/uglify.h"
#include "../lang/string.h"
#include "../sys/exception.h"
#include "../sys/locale.h"

#include "../io/comdef.h"
#include "../io/file.h"
#include "../io/fileinputstream.h"

#include "../config/configfile.h"


#include "resreader.h"

extern IResourceReader* dtlResReader;

			
#define DTL_CONFIG_FILE 	_T("dtl.config")	

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// DoReader
//
class DoReader
{
public:
	DoReader();
	~DoReader();

	void load (const String &file);

	void fill (MessageHash &strHash) const;

private:
	//
	// an entry in the string table
	//
	struct TableEntry
	{
		unsigned int   len;				// length of the string
		unsigned int   ofsString;		// pointer to the string
	};


	//
	// header of a .mo file
	//
	struct HeaderInfo
	{
		unsigned int  magic,				// offset +00:  magic id
					  revision,			//        +04:  revision
					  numStrings;			//        +08:  number of strings in the file
		unsigned int  ofsOrigTable,		//        +0C:  start of original string table
					  ofsTransTable;		//        +10:  start of translated string table
		unsigned int  hashSize,			//        +14:  hash table size
					  ofsHashTable;		//        +18:  offset of hash table start
	};

	//
	// all data is stored here, NULL if no data loaded
	//
	unsigned char *_data;

	//
	// amount of memory pointed to by _data.
	//
	unsigned int _size;

	//
	// data description
	//
	unsigned int	  _numStrings;		// number of strings in this domain
	TableEntry	  *_origTable,		// pointer to original   strings
				*_transTable;		//            translated

	String _charset;

	//
	// swap the 2 halves of 32 bit integer if needed
	//
	unsigned int swap(unsigned int ui) const
	{
		return _swapped ? (ui << 24) | ((ui & 0xff00) << 8) |
						  ((ui >> 8) & 0xff00) | (ui >> 24)
						  : ui;
	}

	const char *stringAtOfs (TableEntry *table, unsigned int len) const
	{
	  const TableEntry * const ent = table + len;

	  //
	  // this check could fail for a corrupt message catalog
	  //
	  unsigned int ofsString = swap (ent->ofsString);
	  if (ofsString + swap (ent->len) > _size)
		  return 0;

	  return (const char *)(_data + ofsString);
	}

	bool _swapped;   // wrong endianness?
}; // end DoReader



//
// magic number identifying the .mo format file
//
const unsigned int MO_MAGIC    = 0x950412de;
const unsigned int MO_MAGIC_SW = 0xde120495;

String toString (const char *asciiStr)
{	
	//
	// TODO  Conversion

	size_t charSize = (size_t) ::strlen (asciiStr);
	if (asciiStr == 0 || charSize == 0) 
		return String::EMPTY;

	return String (asciiStr);

	// return Conversion::toString (asciiStr, charSize, UTF8_ENCODING);

}

DoReader::DoReader()
{
	_data = NULL;
	_size = 0;
}

DoReader::~DoReader()
{
	delete [] _data;
}

void DoReader::load (const String &name)
{
  FileInputStream fin (name);
  int length = (int) fin.available ();
  
  _data = new unsigned char[length];
  if (fin.read (_data, (int) length) != length) {
      String errmsg;	// todo
      THROW (errmsg);
  }
  
  bool valid = (length) + (size_t) 0 > sizeof (HeaderInfo);
  HeaderInfo *header = (HeaderInfo *)_data;
  if (valid == true) {
      _swapped = header->magic == MO_MAGIC_SW;
      valid = _swapped || header->magic == MO_MAGIC;
  }

  if (valid == false) {
      String errmsg; // todo
      THROW (errmsg);
  }

  _numStrings  = swap (header->numStrings);
  _origTable  = (TableEntry *)(_data + swap (header->ofsOrigTable));
  
  _transTable = (TableEntry *)(_data + swap (header->ofsTransTable));
  _size = (unsigned int) length;

  const char* headerData = stringAtOfs (_origTable, 0);
  if (headerData && headerData[0] == 0) {
      String header = toString (stringAtOfs (_transTable, 0));
      
      String charset (_T("Content-Type: text/plain; charset="));
      size_t index = header.find (charset);
      if (index == String::NO_POSITION)
          return;
      
      index += charset.getLength ();

      size_t end = header.find (_T('\n'), index);
      if (end == String::NO_POSITION)
          return;
      
      _charset.assign (header, index, end - index);
      if (_charset == _T("CHARSET"))
          _charset.clear ();
          
      if (_charset.compareIgnoreCase (_T("utf-8")) != 0) {
          String errmsg; // THROW
		  THROW (errmsg);
      }
  }

  return;
}

void DoReader::fill (MessageHash &strHash) const
{
  for (unsigned int i = 0; i < _numStrings; ++i) {
      const char *data = stringAtOfs (_origTable, i);
      
      String msgid = toString (data);

      data = stringAtOfs (_transTable, i);
      size_t length = swap (_transTable[i].len);
      size_t offset = 0;
      size_t index = 0;
      while (offset < length) {
          String msgstr;
          msgstr = toString (data + offset);
          
          if (msgstr.isEmpty () == false)
              strHash[msgid] = msgstr;
          
          offset += ::strlen (data + offset) + 1;
          ++index;
      }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// DoResourceReader
//
// public ctor	
DoResourceReader::DoResourceReader (const String& path)
  : _doName (path)
  , _fileHandle (0)
  , _strHash ()
{
  init (path);
}

DoResourceReader::DoResourceReader (const String& name, bool useLanguage)
  : _doName (name)
  , _fileHandle (0)
  , _strHash ()
{	
	//
	// 1. 读取 dtl.config 配置文件语言项, locale/en_US/dtl.do
	//
	ConfigFile config;
	config.load (DTL_CONFIG_FILE);

	config.setSection (_T("lang"));

	String lang = config.getStringValue ("lang");
	if (lang.isEmpty ())
		THROW ("dtl.config has not language config");

	String res = String (_T("locale/")) + lang + _T("/") + name;  

	init (res);
}


// public virtual dtor
DoResourceReader::~DoResourceReader (void)
{
}

// public virtual 
String 
DoResourceReader::loadString (const String& resName)
{
  return find (resName);
}

// public virtual 
String 
DoResourceReader::getFileName (void) const
{
  return _doName;
}

// public virtual 
void* 
DoResourceReader::getFileHandle (void) const
{
  return reinterpret_cast<void*> (_fileHandle);
}

// protected
void
DoResourceReader::init (const String &name)
{
	DoReader reader;
	reader.load (name);
	reader.fill (_strHash);
}

// protected
String
DoResourceReader::find (const String &msgid)
{
	MessageHash::iterator it = _strHash.find (msgid);
	if (it == _strHash.end())
	  return msgid;

	return (it->second);
}


