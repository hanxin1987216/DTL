/***************************************************************************************************
config.h:	
	Public header
	Copyright (c) Datatom Co., Ltd. (2011), All rights reserved

Purpose:
	Define config macro for platform Windows of compiler VC++

Author:
	han.xin@datatom.com

Creating Time:
	2011-9-7
***************************************************************************************************/

#ifndef __CONFIG_H__
#define __CONFIG_H__

//////////////////////////////////////////////////////////////////////////////////
// Platform definition, On Windows platform, __WINDOWS mus be defined.
	
#ifdef _MSC_VER
// Windows Platform
	
	#define __VISUALC__  _MSC_VER

	#ifdef __WINDOWS__
		#undef __WINDOWS__
		#define __WINDOWS__
	#else
		#define __WINDOWS__
	#endif

	#ifdef _WIN64
		#define __WIN64__ // on 64bit windows machine
		#define __64BIT__	
	#else
		#define __WIN32__
		#undef __64BIT__
	#endif

	#if _MSC_VER > 1000
		#pragma once
		#define PRAGMA_ONCE 1
	#else
		#define PRAGMA_ONCE 0
	#endif // _MSC_VER

	#define AB_PRAGMA_ONCE		1

	#ifndef VC_EXTRALEAN
		#define VC_EXTRALEAN		// exclude some features in Windows header.
	#endif

	#ifndef WINVER
		#define WINVER 0x0501
	#endif

	#ifndef _WIN32_WINNT
		#define _WIN32_WINNT 0x0501
	#endif						

	#ifndef _WIN32_WINDOWS
		#define _WIN32_WINDOWS 0x0510
	#endif

	#ifndef _WIN32_IE
		#define _WIN32_IE 0x0500
	#endif

	// Imports Windows Library
	#ifdef __VISUALC__
		#pragma comment(lib, "shell32.lib")
		#pragma comment(lib, "advapi32.lib")
		#pragma comment(lib, "user32.lib")
		// 'identifier' : class 'type' needs to have dll-interface to be used by clients of class 'type2'
		#pragma warning(disable:4251)
		// 'function': was declared deprecated
		#pragma warning(disable:4996)
		// 'this' : used in base member initializer list
		#pragma warning(disable:4355)
	#endif

	#define __STATICINLINE__	1
	//
	// Support LIDAH HDRW SDK
	//
	#define __USE_HDRW__
	
	// is little endian
	#define __IS_LITTLE_ENDIAN__
	#undef __IS_BIG_ENDIAN__
	
	// On linux, wchar_t size is 2bytes
	#define __SIZEOF_WCHAR__		(2)
	
#elif defined(__xlC__)
	// IBM AIX Platform.
	
	#ifdef __AIX__
		#undef __AIX__
		#define __AIX__
	#else
		#define __AIX__
	#endif
	
	// 32bit defined __powerpc__, 64bit defined __64BIT__
	/*#ifdef __powerpc64__
		#if defined(__64BIT__)
			#undef __64BIT__
		#endif
	#endif*/
	
	#ifdef __WINDOWS__
		#undef __WINDOWS__
	#endif

	// is big endian
	#undef __IS_LITTLE_ENDIAN__
	#define __IS_BIG_ENDIAN__

	//
	// On AIX32, wchar_t size is 2bytes, on AIX64, it is 4bytes
	//
	#ifdef __64BIT__
		#if (AIX_VERS == 403)
			#define __SIZEOF_WCHAR__	(2)
		#else
			#define __SIZEOF_WCHAR__	(4)
		#endif	
	#else
		#define __SIZEOF_WCHAR__		(2)
	#endif

#elif defined(__HPPA__)
 //HP-UX platfrom
	#ifdef __HPPA__
		#undef __HPPA__
		#define __HPPA__
	#else
		#define __HPPA__
	#endif

	#if (defined(__GNUC__) && (defined(__x86_64__) || defined(_LLP64)))
	#if !defined(__64BIT__)
	#define __64BIT__
	#endif
	#else
	#if defined(__64BIT__)
	#undef __64BIT__
	#endif
	#endif

	#ifdef __WINDOWS__
		#undef __WINDOWS__
	#endif

	// is little endian
	#define __IS_BIG_ENDIAN__
	#undef __IS_LITTLE_ENDIAN__

	// On hpux, wchar_t size is 4bytes
	#define __SIZEOF_WCHAR__		(4)
	#define __64BIT__

#elif defined(__SOLARIS__)
 //Solaris platfrom
	#ifdef __SOLARIS__
		#undef __SOLARIS__
		#define __SOLARIS__
	#else
		#define __SOLARIS__
	#endif

	#if (defined(__GNUC__) && (defined(__x86_64__) || defined(_LLP64)))
	#if !defined(__64BIT__)
	#define __64BIT__
	#endif
	#else
	#if defined(__64BIT__)
	#undef __64BIT__
	#endif
	#endif

	#ifdef __WINDOWS__
		#undef __WINDOWS__
	#endif

	// is little endian
	#define __IS_BIG_ENDIAN__
	#undef __IS_LITTLE_ENDIAN__

	// On solaris, wchar_t size is 4bytes
	#define __SIZEOF_WCHAR__		(4)
	#define __64BIT__

#else // _MSC_VER
	// Linux Platform
	#if (defined(__GNUC__) && (defined(__x86_64__) || defined(_LLP64)))
		#if !defined(__64BIT__)
			#define __64BIT__
		#endif
	#else
		#if defined(__64BIT__)
			#undef __64BIT__
		#endif
	#endif
	
	#ifdef __LINUX__
		#undef __LINUX__
		#define __LINUX__
	#else
		#define __LINUX__
	#endif
	
	#ifdef __WINDOWS__
		#undef __WINDOWS__
	#endif
	
	#define __STATICINLINE__	1
	
	// is little endian
	#define __IS_LITTLE_ENDIAN__
	#undef __IS_BIG_ENDIAN__
	
	// On linux, wchar_t size is 4bytes
	#define __SIZEOF_WCHAR__		(4)

#endif

#ifndef __WINDOWS__
	#define HAVE_INET_PTON 1
	#define HAVE_INET_ATON 1
	#define HAVE_MSG_NOSIGNAL 1
	#define HAVE_SOL_IP 1
	/* #undef HAVE_SOL_TCP */
	#define HAVE_SOL_IPV6 1
	#define HAVE_IP_PKTINFO 1
	#define HAVE_IPV6_PKTINFO 1
	#define HAVE_STRUCT_IP_MREQN 1
	/* #undef HAVE_STRUCT_IP_MREQ */
	#define HAVE_PTHREAD_MUTEX_TIMEDLOCK 1
	/* #undef USE_MONO_MUTEX */
	#define HAVE_LARGE_FILE_SUPPORT 1
	/* #undef HAVE_NEW_ICONV */
	#define NAME_DEV_RANDOM "/dev/random"
	#define HAVE_CRYPT_RNG 1
	#define HAVE_BOEHM_GC 1
	#define USE_INCLUDED_LIBGC 1
	/* #undef DISABLE_SHARED_HANDLES */
	/* #undef HAVE_TIMEZONE */
	
#ifndef __AIX__
	#define HAVE_TM_GMTOFF 1
#endif
	
#if defined(__HPPA__) || defined(__SOLARIS__)
	#undef  HAVE_TM_GMTOFF
#endif
	#define MONO_SIZEOF_SUNPATH 108
	#define MONO_ZERO_ARRAY_LENGTH 0
	/* #undef PTHREAD_POINTER_ID */
	/* #undef WITH_BUNDLE */
	#define HAVE_GETHOSTBYNAME2_R 1
	/* #undef HAVE_ICU */
	#define HAVE_KW_THREAD 1
	#define HAVE_SIGNBIT 1
	/* #undef USE_MACH_SEMA */
	#define HAVE_SOCKLEN_T 1
	/* #undef HAVE_TRUNCL */
	/* #undef HAVE_AINTL */
	/* #undef HAVE_SCANDIR */
	/* #undef HAVE_WORKING_SIGALTSTACK */
	
	
	/* Define to 1 if you have the <aio.h> header file. */
	#define HAVE_AIO_H 1
	
	/* Supports C99 array initialization */
	#define HAVE_ARRAY_ELEM_INIT 1
	
	/* Define to 1 if you have the <attr/xattr.h> header file. */
	#define HAVE_ATTR_XATTR_H 1
	
	/* Define to 1 if you have the `backtrace_symbols' function. */
	#define HAVE_BACKTRACE_SYMBOLS 1
	
	/* Define to 1 if you have the <checklist.h> header file. */
	/* #undef HAVE_CHECKLIST_H */
	
	/* Define to 1 if you have the <curses.h> header file. */
	#define HAVE_CURSES_H 1
	
	/* Define to 1 if you have the <dlfcn.h> header file. */
	#define HAVE_DLFCN_H 1
	
	/* Define to 1 if you have the <elf.h> header file. */
	#define HAVE_ELF_H 1
	
	/* epoll supported */
	#define HAVE_EPOLL 1
	
	/* Define to 1 if you have the `epoll_ctl' function. */
	#define HAVE_EPOLL_CTL 1
	
	/* Define to 1 if you have the <execinfo.h> header file. */
	#define HAVE_EXECINFO_H 1
	
	/* Define to 1 if you have the `fgetgrent' function. */
	#define HAVE_FGETGRENT 1
	
	/* Define to 1 if you have the `fgetpwent' function. */
	#define HAVE_FGETPWENT 1
	
	/* Define to 1 if you have the `finite' function. */
	#define HAVE_FINITE 1
	
	/* Define to 1 if you have the <fstab.h> header file. */
	#define HAVE_FSTAB_H 1
	
	/* Define to 1 if you have the `fstatfs' function. */
	#define HAVE_FSTATFS 1
	
	/* Define to 1 if you have the `fstatvfs' function. */
	#define HAVE_FSTATVFS 1
	
	/* Define to 1 if you have the `getdomainname' function. */
	#define HAVE_GETDOMAINNAME 1
	
	/* Define to 1 if you have the `getfsstat' function. */
	/* #undef HAVE_GETFSSTAT */
	
	/* Define to 1 if you have the `getgrgid_r' function. */
	#define HAVE_GETGRGID_R 1
	
	/* Define to 1 if you have the `getgrnam_r' function. */
	#define HAVE_GETGRNAM_R 1
	
	/* Define to 1 if you have the `GetProcessId' function. */
	#define HAVE_GETPROCESSID 1
	
	/* Define to 1 if you have the `getpwnam_r' function. */
	#define HAVE_GETPWNAM_R 1
	
	/* Define to 1 if you have the `getpwuid_r' function. */
	#define HAVE_GETPWUID_R 1
	
	/* Define to 1 if you have the `getresuid' function. */
	#define HAVE_GETRESUID 1
	
	/* Define to 1 if you have the <grp.h> header file. */
	#define HAVE_GRP_H 1
	
	/* Define to 1 if you have the <ieeefp.h> header file. */
	/* #undef HAVE_IEEEFP_H */
	
	/* Define to 1 if you have the `inet_aton' function. */
	#define HAVE_INET_ATON 1
	
	/* Define to 1 if you have the `inet_pton' function. */
	#define HAVE_INET_PTON 1
	
	/* Define to 1 if you have the <inttypes.h> header file. */
	#define HAVE_INTTYPES_H 1
	
	/* Define to 1 if you have the `isfinite' function. */
	#define HAVE_ISFINITE 1
	
	/* isinf available */
	#define HAVE_ISINF 1
	
	/* Define to 1 if you have the `kqueue' function. */
	/* #undef HAVE_KQUEUE */
	
	/* Define to 1 if you have the `unwind' library (-lunwind). */
	/* #undef HAVE_LIBUNWIND */
	
	/* Define to 1 if you have the <linux/rtc.h> header file. */
	#define HAVE_LINUX_RTC_H 1
	
	/* Define to 1 if you have the `lutimes' function. */
	/* #undef HAVE_LUTIMES */
	
	/* Define to 1 if you have the <memory.h> header file. */
	#define HAVE_MEMORY_H 1
	
	/* Define to 1 if you have the `mremap' function. */
	#define HAVE_MREMAP 1
	
	/* Define to 1 if you have the <netdb.h> header file. */
	#define HAVE_NETDB_H 1
	
	/* Define to 1 if you have the <net/if.h> header file. */
	#define HAVE_NET_IF_H 1
	
	/* Define to 1 if you have the `poll' function. */
	#define HAVE_POLL 1
	
	/* Define to 1 if you have the <poll.h> header file. */
	#define HAVE_POLL_H 1
	
	/* Define to 1 if you have the `posix_fadvise' function. */
	#define HAVE_POSIX_FADVISE 1
	
	/* Define to 1 if you have the `posix_fallocate' function. */
	#define HAVE_POSIX_FALLOCATE 1
	
	/* Define to 1 if you have the `posix_madvise' function. */
	#define HAVE_POSIX_MADVISE 1
	
	/* Define to 1 if you have the `pthread_attr_getstack' function. */
	#define HAVE_PTHREAD_ATTR_GETSTACK 1
	
	/* Define to 1 if you have the `pthread_attr_get_np' function. */
	/* #undef HAVE_PTHREAD_ATTR_GET_NP */
	
	/* Define to 1 if you have the `pthread_attr_setstacksize' function. */
	#define HAVE_PTHREAD_ATTR_SETSTACKSIZE 1
	
	/* Define to 1 if you have the `pthread_getattr_np' function. */
	#define HAVE_PTHREAD_GETATTR_NP 1
	
	/* Define to 1 if you have the `pthread_get_stackaddr_np' function. */
	/* #undef HAVE_PTHREAD_GET_STACKADDR_NP */
	
	/* Define to 1 if you have the `pthread_get_stacksize_np' function. */
	/* #undef HAVE_PTHREAD_GET_STACKSIZE_NP */
	
	/* Define to 1 if you have the <pthread.h> header file. */
	#define HAVE_PTHREAD_H 1
	
	/* Define to 1 if you have the `pthread_mutex_timedlock' function. */
	#define HAVE_PTHREAD_MUTEX_TIMEDLOCK 1
	
	/* Define to 1 if you have the `remap_file_pages' function. */
	#define HAVE_REMAP_FILE_PAGES 1
	
	/* Define to 1 if you have the <semaphore.h> header file. */
	#define HAVE_SEMAPHORE_H 1
	
	/* Define to 1 if you have the `sendfile' function. */
	#define HAVE_SENDFILE 1
	
	/* Define to 1 if you have the `setdomainname' function. */
	#define HAVE_SETDOMAINNAME 1
	
	/* Define to 1 if you have the `sethostid' function. */
	#define HAVE_SETHOSTID 1
	
	/* Define if setkey(3) is available */
	#define HAVE_SETKEY 1
	
	/* Define to 1 if you have the `setresuid' function. */
	#define HAVE_SETRESUID 1
	
	/* Can get interface list */
	#define HAVE_SIOCGIFCONF 1
	
	/* Define to 1 if you have the `statfs' function. */
	#define HAVE_STATFS 1
	
	/* Define to 1 if you have the `statvfs' function. */
	#define HAVE_STATVFS 1
	
	/* Define to 1 if you have the <stdint.h> header file. */
	#define HAVE_STDINT_H 1
	
	/* Define to 1 if you have the <stdlib.h> header file. */
	#define HAVE_STDLIB_H 1
	
	/* Define to 1 if you have the `stime' function. */
	#define HAVE_STIME 1
	
	/* Define to 1 if you have the `strerror_r' function. */
	#define HAVE_STRERROR_R 1
	
	/* Define to 1 if you have the <strings.h> header file. */
	#define HAVE_STRINGS_H 1
	
	/* Define to 1 if you have the <string.h> header file. */
	#define HAVE_STRING_H 1
	
	/* Define to 1 if `d_off' is member of `struct dirent'. */
	#define HAVE_STRUCT_DIRENT_D_OFF 1
	
	/* Define to 1 if `d_reclen' is member of `struct dirent'. */
	#define HAVE_STRUCT_DIRENT_D_RECLEN 1
	
	/* Define to 1 if `d_type' is member of `struct dirent'. */
	#define HAVE_STRUCT_DIRENT_D_TYPE 1
	
	/* Define to 1 if you have the <syslog.h> header file. */
	#define HAVE_SYSLOG_H 1
	
	/* Define to 1 if you have the <sys/aio.h> header file. */
	/* #undef HAVE_SYS_AIO_H */
	
	/* Define to 1 if you have the <sys/epoll.h> header file. */
	#define HAVE_SYS_EPOLL_H 1
	
	/* Define to 1 if you have the <sys/extattr.h> header file. */
	/* #undef HAVE_SYS_EXTATTR_H */
	
	/* Define to 1 if you have the <sys/filio.h> header file. */
	/* #undef HAVE_SYS_FILIO_H */
	
	/* Define to 1 if you have the <sys/ioctl.h> header file. */
	#define HAVE_SYS_IOCTL_H 1
	
	/* Define to 1 if you have the <sys/mman.h> header file. */
	#define HAVE_SYS_MMAN_H 1
	
	/* Define to 1 if you have the <sys/poll.h> header file. */
	#define HAVE_SYS_POLL_H 1
	
	/* Define to 1 if you have the <sys/sendfile.h> header file. */
	#define HAVE_SYS_SENDFILE_H 1
	
	/* Define to 1 if you have the <sys/sockio.h> header file. */
	/* #undef HAVE_SYS_SOCKIO_H */
	
	/* Define to 1 if you have the <sys/statvfs.h> header file. */
	#define HAVE_SYS_STATVFS_H 1
	
	/* Define to 1 if you have the <sys/stat.h> header file. */
	#define HAVE_SYS_STAT_H 1
	
	/* Define to 1 if you have the <sys/types.h> header file. */
	#define HAVE_SYS_TYPES_H 1
	
	/* Define to 1 if you have the <sys/un.h> header file. */
	#define HAVE_SYS_UN_H 1
	
	/* Define to 1 if you have the <sys/vfstab.h> header file. */
	/* #undef HAVE_SYS_VFSTAB_H */
	
	/* Define to 1 if you have the <sys/wait.h> header file. */
	#define HAVE_SYS_WAIT_H 1
	
	/* Define to 1 if you have the <sys/xattr.h> header file. */
	#define HAVE_SYS_XATTR_H 1
	
	/* Define to 1 if you have the <termios.h> header file. */
	#define HAVE_TERMIOS_H 1
	
	/* Define to 1 if you have the <term.h> header file. */
	#define HAVE_TERM_H 1
	
	/* tld_model available */
	#define HAVE_TLS_MODEL_ATTR 1
	
	/* Define to 1 if you have the `trunc' function. */
	#define HAVE_TRUNC 1
	
	/* Define to 1 if you have the `ttyname_r' function. */
	#define HAVE_TTYNAME_R 1
	
	/* Define to 1 if you have the <unistd.h> header file. */
	#define HAVE_UNISTD_H 1
	
	/* Define to 1 if you have the <utime.h> header file. */
	#define HAVE_UTIME_H 1
	
	/* Define to 1 if you have the <valgrind/memcheck.h> header file. */
#ifndef __AIX__
	#define HAVE_VALGRIND_MEMCHECK_H 1
#endif

	/* Define to 1 if you have the `vsnprintf' function. */
	#define HAVE_VSNPRINTF 1
	
	/* Define to 1 if you have the <wchar.h> header file. */
	#define HAVE_WCHAR_H 1
	
	/* Platform is Win32 */
	/* #undef PLATFORM_WIN32 */
	
	/* Pointer field name in 'union sigval' */
	#define SIGVAL_PTR sival_ptr
	
	/* The size of a `size_t', as computed by sizeof. */
	#define SIZEOF_SIZE_T 4
	
	/* The size of a `void *', as computed by sizeof. */
	#define SIZEOF_VOID_P 4
	
	/* Define to 1 if you have the ANSI C header files. */
	#define STDC_HEADERS 1
	
	/* Define to 1 for read&write large size file over 2G.*/
	#define _LARGEFILE_SOURCE 1
	#define _FILE_OFFSET_BITS 64

#endif // __WINDOWS__

#define HAVE_WCHAR_T
#define HAVE_SIZE_T
#define HAVE_CHECKED_EXCEPTION

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
	
////////////////////////////////////////////////////////////////////////
// Debug and trace definition

#ifdef _DEBUG
#	define __DEBUG__
#endif

#if defined(__ENABLE_TRACE__)
#	define __USE_TRACE__
#endif

////////////////////////////////////////////////////////////////////////
// character encoding definition: windows -> utf16, other -> utf8

#ifndef HAVE_WCHAR_T
typedef unsigned short wchar_t;
#endif

//
// On Windows platform use UTF16, *nix platform use UTF8
//

#ifdef __WINDOWS__

	// Always believe that DTL use UTF16 string as its default
	#ifndef _UNICODE
		#define _UNICODE
	#endif

	#ifndef UNICODE
		#define UNICODE
	#endif

	#define _ON_UNICODE
	#define __UNICODE__

	typedef wchar_t 	tchar_t;
	typedef wchar_t	utchar_t;
	//
	// Never define macro _T directly, avoid compilation warning C4005.
	//
	#ifndef _INC_TCHAR
		#include <tchar.h>
	#endif
	//#if !defined(_T)
		//#define _T(str) 	L##str
	//#endif

		
#else // __WINDOWS_
	// *nix use utf-8 code.
	typedef char  tchar_t;
	typedef unsigned char utchar_t;

	#if !defined(_T)
		#define _T(str)	str
	#endif
	
#endif // __WINDOWS__

///////////////////////////////////////////////////////////////////////////////////////////////////
// type definition

#ifdef __WINDOWS__
	typedef signed __int64 int64;
	typedef unsigned __int64 uint64;

	#ifndef __INT64_C
		#define __INT64_C(val) (val##i64)
	#endif

#else // __WINDOWS__

//
// On AIX64, int64 already defines at sys/inttypes.h, at line 622
//
#if !defined(__AIX__) || !defined(__64BIT__)
#ifndef int64
	typedef signed long long int64;
	#define INT64_HAVE_DEFINED 1
#endif
#endif

#ifndef uint64
	typedef unsigned long long uint64;
	#define UINT64_HAVE_DEFINED 1
#endif

	#ifndef __INT64_C
		#define	__INT64_C(val)	(val##ll)
	#endif

#endif  // __WINDOWS__

#ifndef HAVE_SIZE_T
#ifdef __64BIT__
typedef uint64 size_t;
#else
typedef unsigned int size_t;
#endif
#endif

#ifndef __64BIT__
#define SIZE_TO_INT(size) ((int)(size))
#define SIZE_TO_UINT(size) ((unsigned int)(size))
#else
// TODO:
#define SIZE_TO_INT(size) ((int)(size))
#define SIZE_TO_UINT(size) ((unsigned int)(size))
#endif

#ifndef intptr
#ifdef __64BIT__
typedef int64 intptr;
#else
typedef int intptr;
#endif
#endif

#ifndef uintptr
#ifdef __64BIT__
typedef uint64 uintptr;
#else
typedef unsigned int uintptr;
#endif
#endif

#ifndef TO_DWORD_PTR
#ifdef __WINDOWS__
#define TO_DWORD_PTR(ptr)	((LPDWORD)(ptr))
#define TO_LONG_PTR(ptr)	((LPLONG)(ptr))
#else
#define TO_DWORD_PTR(ptr)   ((unsigned int*)ptr)
#define TO_LONG_PTR(ptr)	((int*)ptr)
#endif
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
// Compilter default config

#if defined(__VISUALC__)
	#define DTL_CDECL __cdecl
	#define DTL_STDCALL _stdcall
#else
	#define DTL_CDECL
	#define DTL_STDCALL
#endif

//  Macro to issue warning when using deprecated functions with MSVC7: 
#if defined(__VISUALC__) && (__VISUALC__ >= 1300)
	#define DEPRECATED(x) __declspec(deprecated) x
#else
	#define DEPRECATED(x) x
#endif

#ifdef __64BIT__
		#define PTR_TO_VALUE(p) ((uint64)(p))
		typedef uint64 ptr_value_t;
#else
		#define PTR_TO_VALUE(p) ((unsigned)(p))
		typedef unsigned ptr_value_t;
#endif 

///////////////////////////////////////////////////////////////////////////////////////////////////
// C++ exception

#ifdef HAVE_CHECKED_EXCEPTION

	#define NO_THROW		throw()
	#define THROW_(exception) throw(exception)
	#define AB_NOTHROW		throw()
	#define AB_THROW(exception) throw(exception)

#else

	#define NO_THROW	
	#define THROW_(exception) 

#endif // HAVE_CHECKED_EXCEPTION

// Some compiler doesn't support static inline, 
#ifdef __STATICINLINE__
#define _STATICINLINE static inline
#else
#define _STATICINLINE inline
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
// type definition

/**
 * message ID type
 */
typedef unsigned int ab_msgid;

/**
 * Define the connected service Id as unsigned int.
 */
typedef unsigned int ab_svcid;

/**
 * Define the connected ab_sobj_mgrid as unsigned int.
 */
typedef unsigned int ab_sobj_mgrid;

/**
 * Define the connected ab_sobjid as unsigned int.
 */
typedef unsigned int ab_sobjid;

/**
 * serialization suid type.
 */
typedef uint64 ab_suid;

///////////////////////////////////////////////////////////////////////////////////////////////////
//
// 
//
#ifndef __WINDOWS__
	#define SECURITY_CONFIG_PATH			(_T("/var/lib"))
#endif

#endif /* __CONFIG_H__ */

