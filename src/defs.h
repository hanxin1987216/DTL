/***************************************************************************************************
defs.h:	
 	Copyright (c) Datatom Co., Ltd.(2011 - 2012), All rights reserved.

Purpose:
	Common declarations/definitions 

Author:
	han.xin@datatom.com

Creating Time:
	2011-11-15  	
***************************************************************************************************/

#ifndef __DEFS_H__
#define __DEFS_H__

#include <config.h>

#if PRAGMA_ONCE
	#pragma once
#endif

/*the mount point of a DOM partition*/
#ifndef DOM_PATH
#define DOM_PATH ""
#endif

#ifndef DT_CONF_PATH
#define DT_CONF_PATH ("/etc/dt.d/")
#endif

#ifndef DT_VAR_PATH
#define DT_VAR_PATH ("/var/datatom/")
#endif

#ifndef UINT8
typedef unsigned char UINT8;
#endif
#ifndef UINT16
typedef unsigned short UINT16;
#endif
#ifndef UINT32
typedef unsigned int UINT32;
#endif
#ifndef UINT64
typedef unsigned long UINT64;
#endif

#ifndef NAME_MAX
#define NAME_MAX 256
#endif

#ifndef SSIZE_MAX
#define SSIZE_MAX 256
#endif


//
// HTTP Basic Authentication
#define HTTP_BASIC_AUTH_USER	"datatom"
#define HTTP_BASIC_AUTH_PASSWORD "datatom.com.password"


///////////////////////////////////////////////////////////////////////////////////////////////////
//  macro to define a class without copy ctor nor assignment operator 

#define DTL_DECLARE_NO_COPY_CLASS(cls_name)        	\
    private:                                    \
        cls_name(const cls_name&);            	\
        cls_name& operator=(const cls_name&);



#endif /*  __DEFS_H__ */
