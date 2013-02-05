/****************************************************************************************************
hash.h
 	Copyright (c) Datatom Software, Inc.(2010 - 2011), All rights reserved.

Purpose:
	哈希函数集合
	
Auther:
	韩欣 (han.xin@datatom.com)

Created Time:
	2011-5-5

****************************************************************************************************/

#ifndef __DTL_HASH__
#define __DTL_HASH__

#if AB_PRAGMA_ONCE
	#pragma once
#endif

/* A Simple Hash Function */
DTL_DLLEXPORT unsigned int simple_hash(const char *str);

/* RS Hash Function */
DTL_DLLEXPORT unsigned int RS_hash(const char *str);

/* JS Hash Function */
DTL_DLLEXPORT unsigned int JS_hash(const char *str);

/* P. J. Weinberger Hash Function */
DTL_DLLEXPORT unsigned int PJW_hash(const char *str);

/* ELF Hash Function */
DTL_DLLEXPORT unsigned int ELF_hash(const char *str);

/* BKDR Hash Function */
DTL_DLLEXPORT unsigned int BKDR_hash(const char *str);

/* SDBM Hash Function */
DTL_DLLEXPORT unsigned int SDBM_hash(const char *str);

/* DJB Hash Function */
DTL_DLLEXPORT unsigned int DJB_hash(const char *str);

/* AP Hash Function */
DTL_DLLEXPORT unsigned int AP_hash(const char *str);

/* CRC Hash Function */
DTL_DLLEXPORT unsigned int CRC_hash(const char *str);

#endif // __DTL_HASH__
