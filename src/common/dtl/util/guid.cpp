/***************************************************************************************************
guid.cpp
	Copyright (c) Datatom Software, Inc.(2012)

Purpose:
	This file contain the declaration of classes:
	Guid: Represents a globally unique indentifier.

Author:
	韩欣 (han.xin@datatom.com)

Creating Time:
	2012-3-9  	
***************************************************************************************************/

#include "../prec.h"
#include "../lang/string.h"
#include "../sys/exception.h"

#include "guid.h"

#ifdef __WINDOWS__
	#include <objbase.h>
#endif // __WINDOWS__

#define GUID_STR_BUF	40

/* uuid struct */
struct uuid {
	unsigned int Data1;
	unsigned short Data2;
	unsigned short Data3;
	unsigned char Data4[8];
};


#ifndef __WINDOWS__

/* 
	将struct uuid结构体转换成uuid_t
*/
static void uuid_pack (const struct uuid *uu, uuid_t ptr)
{
    unsigned int   tmp;
    unsigned char   *out = ptr;

    tmp = uu->Data1;
    out[3] = (unsigned char) tmp;
    tmp >>= 8;
    out[2] = (unsigned char) tmp;
    tmp >>= 8;
    out[1] = (unsigned char) tmp;
    tmp >>= 8;
    out[0] = (unsigned char) tmp;
    
    tmp = uu->Data2;
    out[5] = (unsigned char) tmp;
	tmp >>= 8;
    out[4] = (unsigned char) tmp;

    tmp = uu->Data3;
    out[7] = (unsigned char) tmp;
    tmp >>= 8;
    out[6] = (unsigned char) tmp;

	memcpy(out+8, uu->Data4, 8);

}
/* 
	将uuid_t 转换成struct uuid结构体
*/
static void uuid_unpack (const uuid_t in, struct uuid *uu)
{
	const unsigned char  *ptr = in;
	unsigned int tmp;
    tmp = *ptr++;
    tmp = (tmp << 8) | *ptr++;
    tmp = (tmp << 8) | *ptr++;
    tmp = (tmp << 8) | *ptr++;
    uu->Data1 = tmp;
	tmp = *ptr++;
    tmp = (tmp << 8) | *ptr++;
    uu->Data2 = tmp;

	tmp = *ptr++;
    tmp = (tmp << 8) | *ptr++;
	uu->Data3 = tmp;

	memcpy(uu->Data4, ptr, 8);

}

#endif




#if defined(__AIX__) || defined(__HPPA__) || defined(__SOLARIS__)

#include <unistd.h>                /* popen() */
#include <errno.h>                /* errno */
#include <stdio.h>                /* printf() */
#include <stdlib.h> 
#include <ctype.h>

#define UUCMP(u1,u2) if (u1 != u2) return((u1 < u2) ? -1 : 1);

/* uuid生成 for aix */
static void 
uuid_generate (uuid_t _guid)
{
	char buf[3] ={0};
	char temp[128] ={0};
	int inta;
	FILE *fp;
	if( (fp = popen("/etc/ncs/uuid_gen -C", "r")) == NULL )
	{
      throw SystemException (cflResLoader, 
							   _T("IDS_CREATE_GUID_FAILURED"));
	}
	fgets (temp,sizeof (temp),fp);
	buf[0] = temp[6];
	buf[1] = temp [7];
	_guid[0] = (unsigned char)strtoul (buf, NULL, 16);

	buf[0] = temp[8];
	buf[1] = temp [9];
	_guid[1] = (unsigned char)strtoul (buf, NULL, 16);

	buf[0] = temp[10];
	buf[1] = temp [11];
	_guid[2] = (unsigned char)strtoul (buf, NULL, 16);

	buf[0] = temp[12];
	buf[1] = temp [13];
	_guid[3] = (unsigned char)strtoul (buf, NULL, 16);


	memset (temp, 0, sizeof (temp));
	fgets (temp,sizeof (temp),fp);
	buf[0] = temp[6];
	buf[1] = temp [7];
	_guid[4] = (unsigned char)strtoul (buf, NULL, 16);

	buf[0] = temp[8];
	buf[1] = temp [9];
	_guid[5] = (unsigned char)strtoul (buf, NULL, 16);


	memset (temp, 0, sizeof (temp));
	fgets (temp,sizeof (temp),fp);
	buf[0] = temp[6];
	buf[1] = temp [7];
	_guid[6] = (unsigned char)strtoul (buf, NULL, 16);

	buf[0] = temp[8];
	buf[1] = temp [9];
	_guid[7] = (unsigned char)strtoul (buf, NULL, 16);

	memset (temp, 0, sizeof (temp));
	fgets (temp,sizeof (temp),fp);
	buf[0] = temp[6];
	buf[1] = temp [7];
	_guid[8] = (unsigned char)strtoul (buf, NULL, 16);

	memset (temp, 0, sizeof (temp));
	fgets (temp,sizeof (temp),fp);
	buf[0] = temp[7];
	buf[1] = temp [8];
	_guid[9] = (unsigned char)strtoul (buf, NULL, 16);


	buf[0] = temp[13];
	buf[1] = temp [14];
	_guid[10] = (unsigned char)strtoul (buf, NULL, 16);

	buf[0] = temp[19];
	buf[1] = temp [20];
	_guid[11] = (unsigned char)strtoul (buf, NULL, 16);

	buf[0] = temp[25];
	buf[1] = temp [26];
	_guid[12] = (unsigned char)strtoul (buf, NULL, 16);

	buf[0] = temp[31];
	buf[1] = temp [32];
	_guid[13] = (unsigned char)strtoul (buf, NULL, 16);

	buf[0] = temp[37];
	buf[1] = temp [38];
	_guid[14] = (unsigned char)strtoul (buf, NULL, 16);

	buf[0] = temp[43];
	buf[1] = temp [44];
	_guid[15] = (unsigned char)strtoul (buf, NULL, 16);

	pclose(fp);
}


static int 
uuid_parse (const char* in, uuid_t out)
{
	struct uuid uuid;
    int i;
	const char  *cp;
    char buf[3];
	if (strlen(in) != 36)
		return -1;
     for (i=0, cp = in; i <= 36; i++,cp++) {
        if ((i == 8) || (i == 13) || (i == 18) ||
            (i == 23)) {
            if (*cp == '-')
                continue;
            else
              return -1;
         }
         if (i== 36)
           if (*cp == 0)
                 continue;
         if (!isxdigit(*cp))
           return -1;
	 }
	uuid.Data1 = strtoul(in, NULL, 16);
	uuid.Data2 = strtoul(in+9, NULL, 16);
    uuid.Data3 = strtoul(in+14, NULL, 16);
    buf[2] = 0;
	cp = in+19;
	buf[0] = *cp++;
	buf[1] = *cp++;
	uuid.Data4[0] = strtoul(buf, NULL, 16);
	buf[0] = *cp++;
	buf[1] = *cp++;
	uuid.Data4[1] = strtoul(buf, NULL, 16);
	cp++;
	for (i=2; i < 8; i++) {
		buf[0] = *cp++;
		buf[1] = *cp++;
		uuid.Data4[i] = strtoul(buf, NULL, 16);
     }
	uuid_pack(&uuid, out);
	return 0;
}


static void
uuid_unparse (const uuid_t in, char* out)
{
	struct uuid uuid;
	uuid_unpack (in, &uuid);
	snprintf (out,40,"%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x",
		uuid.Data1, uuid.Data2, uuid.Data3,
		uuid.Data4[0], uuid.Data4[1],uuid.Data4[2], uuid.Data4[3], uuid.Data4[4],
		uuid.Data4[5], uuid.Data4[6], uuid.Data4[7]);
}

static int 
uuid_compare (const uuid_t in1, const uuid_t in2)
{
	struct uuid uuid1, uuid2;
	uuid_unpack (in1, &uuid1);
	uuid_unpack (in2, &uuid2);

	UUCMP (uuid1.Data1, uuid2.Data1);
	UUCMP (uuid1.Data2, uuid2.Data2);
	UUCMP (uuid1.Data3, uuid2.Data3);
	return memcmp (uuid1.Data4, uuid2.Data4, 8);
}

#endif // defined(__AIX__) || defined(__HPPA__)


	
// public ctor
Guid::Guid (void)
{
#ifdef __WINDOWS__
	int hr = CoCreateGuid (&_guid);

	if (hr != S_OK) {
		THROW_ID (_T("IDS_CREATE_GUID_FAILURED"), hr);
	}
#else // __WINDOWS__
	uuid_generate (_guid);
#endif // __WINDOWS__
}

// public ctor
Guid::Guid (const String& guid)
{
#ifdef __WINDOWS__
	assign (guid);
#else // __WINDOWS__
	assign (guid);
#endif // __WINDOWS__

}

#ifdef __WINDOWS__

Guid::Guid (const GUID& guid)
{
	assign (guid);
}

#else // __WINDOWS__

Guid::Guid (const uuid_t& guid)
{
	assign (guid);
}

#endif // __WINDOWS__

// public dtor
Guid::~Guid (void)
{
	// Do nothing
}

Guid& 
Guid::assign (const String& guid)
{
	if (guid == String::EMPTY)
		THROW (_T("IDS_ARGUMENT_GUID_IS_EMPTY"));
		
	int hr = 0;

#ifdef __WINDOWS__
	hr = ::CLSIDFromString ((LPOLESTR)guid.getCStr (), (LPCLSID)&_guid);

	if (hr != S_OK) {
		String error;
		THROW_ID (_T("IDS_CONVERT_GUID_FAILURED"), hr);
	}
	
#else // __WINDOWS__
	String temp = guid;
	size_t length = temp.getLength ();
	if (length >= 3 && temp.at (0) == _T('{') && temp.at (length - 1) == _T('}'))
		temp = temp.subString (1, length - 2);

	hr = uuid_parse (temp.getCStr (), _guid);

	if (hr != 0) {		
		THROW (_T("IDS_CONVERT_GUID_FAILURED2"));
	}
#endif // __WINDOWS__

	return *this;
}

#ifdef __WINDOWS__

Guid& 
Guid::assign (const GUID& guid)
{
	_guid.Data1 = guid.Data1;
	_guid.Data2 = guid.Data2;
	_guid.Data3 = guid.Data3;
	::memcpy (_guid.Data4, guid.Data4, 8);

	return *this;
}

#else // __WINDOWS__

Guid& 
Guid::assign (const uuid_t& guid)
{
	::memcpy (_guid, guid, sizeof (uuid_t));

	return *this;
}

#endif // __WINDOWS__

Guid& 
Guid::operator= (const String& guid)
{
	return assign (guid);
}

Guid& 
Guid::operator= (const Guid& guid)
{
	return operator= (guid.getGuid ());
}

#ifdef __WINDOWS__

Guid& 
Guid::operator= (const GUID& guid)
{
	return assign (guid);
}

#else // __WINDOWS__

Guid& 
Guid::operator= (const uuid_t& guid)
{
	return assign (guid);
}

#endif // __WINDOWS__

bool 
Guid::operator== (const Guid& guid)
{
	return operator == (guid.getGuid ());
}

#ifdef __WINDOWS__

bool 
Guid::operator== (const GUID& guid)
{
	return (::IsEqualGUID (_guid, guid) == 1) ? true : false;
}

#else // __WINDOWS__

bool 
Guid::operator == (const uuid_t& guid)
{
	int result = uuid_compare (_guid, guid);
	return (result == 0) ? true : false;
}

#endif // __WINDOWS__

String 
Guid::toString () const
{
	String guidStr;

	tchar_t buf [GUID_STR_BUF];
	::memset (buf, 0, GUID_STR_BUF);

#ifdef __WINDOWS__
	int hr = ::StringFromGUID2 (_guid, buf, GUID_STR_BUF);

	if (hr == 0) {
		THROW_ID (_T("IDS_INSUFFICIENCY_STRING_BUF"),hr);
	}
#else // __WINDOWS__
	uuid_unparse (_guid, buf);
#endif // __WINDOWS__
	
	guidStr = buf;
	return guidStr;
}

String 
Guid::toStdString () const
{
	String guidStr = toString ();
	size_t length = guidStr.getLength ();
	if (length >= 3 && guidStr.at (0) != _T('{') && guidStr.at (length - 1) != _T('}'))
		guidStr = String (_T("{")) + guidStr + String (_T("}"));

	guidStr.toUpper ();
	return guidStr;
}
