/***************************************************************************************************
env.cpp:
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	
	环境变量配置
	
Author:
	韩欣

Creating Time:
	2012-03-10  	
  	
***************************************************************************************************/


#include "../prec.h"
#include "../mono_base/uglify.h"

#include "../lang/string.h"
#include "../sys/exception.h"

#include "env.h"


#ifdef __WINDOWS__
#include <Winuser.h>
#include <shlobj.h>
#include <dsclient.h>
#else
#include <sys/utsname.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/sysinfo.h>
#endif



#if (AIX_VERS == 403)
static char *__findenv (const char *, int *);

/*
 * setenv --
 *      Set the value of the environmental variable "name" to be
 *      "value".  If rewrite is set, replace any current value.
 */
int
setenv(register const char *name,
        register const char *value,
        int rewrite)
{
        extern char **environ;
        static int alloced;                     /* if allocated space before */
        register char *c;
        const char *c2;
        int l_value, offset;

        if (*value == '=')                      /* no `=' in value */
                ++value;
        l_value = strlen(value);
        if ((c = __findenv(name, &offset))) {   /* find if already exists */
                if (!rewrite)
                        return (0);
                if (strlen(c) >= l_value) {     /* old larger; copy over */
                        while ((*c++ = *value++));
                        return (0);
                }
        } else {                                        /* create new slot */
                register int cnt;
                register char **p;

                for (p = environ, cnt = 0; *p; ++p, ++cnt);
                if (alloced) {                  /* just increase size */
                        environ = (char **)realloc((char *)environ,
                            (size_t)(sizeof(char *) * (cnt + 2)));
                        if (!environ)
                                return (-1);
                }
                else {                          /* get new space */
                        alloced = 1;            /* copy old entries into it */
                        p = (char **)malloc((size_t)(sizeof(char *) * (cnt + 2)));
                        if (!p)
                                return (-1);
                        memcpy(p, environ, cnt * sizeof(char *));
                        environ = p;
                }
                environ[cnt + 1] = NULL;
                offset = cnt;
        }
        for (c2 = name; *c2 && *c2 != '='; ++c2);       /* no `=' in name */
        if (!(environ[offset] =                 /* name + `=' + value */
            (char*)malloc((size_t)((int)(c2 - name) + l_value + 2))))
                return (-1);
        for (c = environ[offset]; (*c = *name++) && *c != '='; ++c);
        for (*c++ = '='; (*c++ = *value++););
        return (0);
}

/*
 * unsetenv(name) --
 *      Delete environmental variable "name".
 */
void
unsetenv (const char *name)
{
        extern char **environ;
        register char **p;
        int offset;

        while (__findenv(name, &offset))        /* if set multiple times */
                for (p = &environ[offset];; ++p)
                        if (!(*p = *(p + 1)))
                                break;
}

/*
 * getenv --
 *      Returns ptr to value associated with name, if any, else NULL.
 */
char *
getenv(const char *name)
{
        int offset;

        return (__findenv(name, &offset));
}

/*
 * __findenv --
 *      Returns pointer to value associated with name, if any, else NULL.
 *      Sets offset to be the offset of the name/value combination in the
 *      environmental array, for use by setenv(3) and unsetenv(3).
 *      Explicitly removes '=' in argument name.
 */
static char *
__findenv (register const char *name,
        int *offset)
{
        extern char **environ;
        register unsigned int len;
        register const char *np;
        register char **p, *c;

        if (name == NULL || environ == NULL)
                return (NULL);
        for (np = name; *np && *np != '='; ++np)
                continue;
        len = np - name;
        for (p = environ; (c = *p) != NULL; ++p)
                if (strncmp(c, name, len) == 0 && c[len] == '=') {
                        *offset = p - environ;
                        return (c + len + 1);
                }
        return (NULL);
}

#endif



#ifdef __WINDOWS__
typedef void(WINAPI * PGNSI)(LPSYSTEM_INFO);
#endif // __WINDOWS__

////////////////////////////////////////////////////////////////////////////////////////////////////
// class Environment

#ifdef __UNICODE__
/* An arbitrary size that is digestable. True max is a bit less than 32000 */
#define PATH_MAX_LEN 8192
#else /* !_UNICODE */
#define PATH_MAX_LEN MAX_PATH
#endif
	
// public static 
/*
User* 
Environment::getCurrentUser (void)
{
#ifdef __WINDOWS__	
	return User::getCurrentUser ();
#else
	return 0;
#endif
}

*/

// public static 
OSVersion 
Environment::getCurrentOSVersion (void)
{
#ifdef __WINDOWS__
	OSVersion osLevel = OS_UNKNOWN;

    OSVERSIONINFOEX oslev;
    SYSTEM_INFO si;
    
    ZeroMemory(&si, sizeof(SYSTEM_INFO));
    ZeroMemory(&oslev, sizeof(OSVERSIONINFOEX));

	oslev.dwOSVersionInfoSize = sizeof (OSVERSIONINFOEX);
    if (!::GetVersionEx ((OSVERSIONINFO*) &oslev)) {
    	oslev.dwOSVersionInfoSize = sizeof (OSVERSIONINFO);
    	
    	if (!::GetVersionEx ((OSVERSIONINFO*) &oslev))
			THROW ("GetVersionEx failed");
	}

	GetSystemInfo(&si);
	
    if (oslev.dwPlatformId == VER_PLATFORM_WIN32_NT) 
    {
        static unsigned int servpack = 0;
        tchar_t *pservpack;
        if (pservpack = oslev.szCSDVersion)
		{
			while (*pservpack && !Char::isDigit ((unsigned char)(*pservpack)))
                pservpack++;

            if (*pservpack)
				servpack = Int::getValue(pservpack);
        }

        if (oslev.dwMajorVersion < 3)
            osLevel = OS_UNKNOWN;
        else if (oslev.dwMajorVersion == 3)
		{
            if (oslev.dwMajorVersion < 50)
                osLevel = OS_UNKNOWN;
            else if (oslev.dwMajorVersion == 50)
                osLevel = OS_WINNT35;
            else
                osLevel = OS_WINNT351;
        }
        else if (oslev.dwMajorVersion == 4)
		{
            if (servpack < 2)
                osLevel = OS_WINNT4;
            else if (servpack <= 2)
                osLevel = OS_WINNT4_SP2;
            else if (servpack <= 3)
                osLevel = OS_WINNT4_SP3;
            else if (servpack <= 4)
                osLevel = OS_WINNT4_SP4;
            else if (servpack <= 5)
                osLevel = OS_WINNT4_SP5;
            else 
                osLevel = OS_WINNT4_SP6;
        }
        else if (oslev.dwMajorVersion == 5)
		{
            if (oslev.dwMinorVersion == 0)
			{
				if (oslev.wProductType == VER_NT_SERVER || 
					oslev.wProductType == VER_NT_DOMAIN_CONTROLLER) {
					if (servpack == 0)
						osLevel = OS_WIN2000_SVR;
					else if (servpack == 1)
						osLevel = OS_WIN2000_SVR_SP1;
					else if (servpack == 2)
						osLevel = OS_WIN2000_SVR_SP2;
					else if (servpack == 3)
						osLevel = OS_WIN2000_SVR_SP3;
					else if (servpack == 4)
						osLevel = OS_WIN2000_SVR_SP4;
				}
				else {
					if (servpack == 0)
						osLevel = OS_WIN2000;
					else if (servpack == 1)
						osLevel = OS_WIN2000_SP1;
					else if (servpack == 2)
						osLevel = OS_WIN2000_SP2;
					else if (servpack == 3)
						osLevel = OS_WIN2000_SP3;
					else if (servpack == 4)
						osLevel = OS_WIN2000_SP4;
				}
            }
			else if (oslev.dwMinorVersion == 1) {
                osLevel = OS_WINXP;
            }
			else if (oslev.dwMinorVersion == 2) {
				if (::GetSystemMetrics (SM_SERVERR2))
					osLevel = OS_WIN2003_SP2;
				else {
					SYSTEM_INFO si2;
					PGNSI psi;
					psi = (PGNSI)::GetProcAddress (::GetModuleHandle (_T("kernel32.dll")), "GetNativeSystemInfo");
					if (psi != NULL)
						psi (&si2);

					if (oslev.wProductType == VER_NT_WORKSTATION &&
            			 si2.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64)
            			osLevel = OS_WINXP_64;
            		else
            			osLevel = OS_WIN2003;
				}
			}
        }
        else if (oslev.dwMajorVersion == 6 && oslev.dwMinorVersion == 0)
        {
        	if (oslev.wProductType == VER_NT_WORKSTATION)
        		osLevel = OS_WINVISTA;
        	else
        		osLevel = OS_WIN2008;
        }
        else if (oslev.dwMajorVersion == 6 && oslev.dwMinorVersion == 1)
        {
        	if (oslev.wProductType == VER_NT_WORKSTATION)
        		osLevel = OS_WIN7;
        	else
        		osLevel = OS_WIN2008_R2;
        }
    }
    else if (oslev.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS)
	{
        tchar_t *prevision;
        if (prevision = oslev.szCSDVersion)
		{
            while (*prevision && !isdigit ((unsigned char)(*prevision)))
				prevision++;
        }
        else prevision = _T("");

        if (oslev.dwMinorVersion < 10)
		{
            if (*prevision < 'C')
                osLevel = OS_WIN95;
            else
                osLevel = OS_WIN95_OSR2;
        }
        else if (oslev.dwMinorVersion < 90)
		{
            if (*prevision < 'A')
                osLevel = OS_WIN98;
            else
                osLevel = OS_WIN98_SE;
        }
        else
            osLevel = OS_WIN98_ME;
    }
    else
        osLevel = OS_UNKNOWN;

    return osLevel;
#endif /* __WINDOWS__ */

#ifdef __LINUX__
	return OS_LINUX;
#endif

#ifdef __AIX__
	return OS_AIX;
#endif

#ifdef __HPPA__
	return OS_HPUX;
#endif

#ifdef __SOLARIS__
	return OS_SOLARIS;
#endif

	return OS_UNKNOWN;
}

// public static 
String 
Environment::getOSVerName (OSVersion ver)
{
	switch (ver) {
		case OS_WIN95:
			return _T("Windows 95");

		case OS_WIN95_B:
			return _T("Windows 95 B");

		case OS_WIN95_OSR2:
			return _T("Windows 95 OSR2");
			
		case OS_WIN98:
			return _T("Windows 98");

		case OS_WIN98_SE:
			return _T("Windows 98 SE");

		case OS_WIN98_ME:
			return _T("Windows ME");
			
		case OS_WINNT35:
			return _T("Windows NT 3.5");
			
		case OS_WINNT351:
			return _T("Windows NT 3.51");

		case OS_WINNT4:
		case OS_WINNT4_SP2:
		case OS_WINNT4_SP3:
		case OS_WINNT4_SP4:
		case OS_WINNT4_SP5: 	
		case OS_WINNT4_SP6:
			return _T("Windows NT 4.0");			
			
		case OS_WIN2000:
		case OS_WIN2000_SP1:
		case OS_WIN2000_SP2:
		case OS_WIN2000_SP3:
		case OS_WIN2000_SP4:
			return _T("Windows 2000 Professional");

		case OS_WIN2000_SVR:
		case OS_WIN2000_SVR_SP1:
		case OS_WIN2000_SVR_SP2:
		case OS_WIN2000_SVR_SP3:
		case OS_WIN2000_SVR_SP4:
			return _T("Windows 2000 Server");

		case OS_WINXP:
		case OS_WINXP_SP2:
			return _T("Windows XP");

		case OS_WINXP_64:
			return _T("Windows XP x64");

		case OS_WIN2003:
		case OS_WIN2003_SP1:
		case OS_WIN2003_SP2:
			return _T("Windows 2003");

		case OS_WINVISTA:
			return _T("Windows Vista");			

		case OS_WIN2008:
			return _T("Windows 2008");
			
		case OS_WIN2008_R2:
			return _T("Windows Server 2008 R2");

		case OS_WIN7:
			return _T("Windows 7");

		case OS_LINUX:
			return _T("Linux");
		
		case OS_AIX:
			return _T("AIX");
			
		case OS_HPUX:
			return _T("HP-UX");
			
		case OS_SOLARIS:
			return _T("Solaris");
			
		default:
			break;
	}
	
	return String(_T("IDS_UNKOWN_OS_TYPE"));
}

// public static 
String 
Environment::getComputerName (void)
{

#ifdef __WINDOWS__	
	unsigned int size = MAX_COMPUTERNAME_LENGTH + 1;
	tchar_t strName [MAX_COMPUTERNAME_LENGTH + 1];
	
	if (!::GetComputerName (strName, TO_DWORD_PTR(&size))) {
		String strTemp;
		strTemp.format (_T("cannot get computer name, %s"), strName);
		 THROW_ID (strTemp, ::GetLastError ());
	}

	return (String (strName));

#else
	char name [MAX_PATH];
	int ret = gethostname (name, MAX_PATH);

	if (ret == -1)
		THROW_ID ("IDS_ENV_CANN0T_GET_COMPUTER_NAME", errno);

	return name;
#endif /* __WINDOWS__ */
}

// public static 
void 
Environment::setComputerName (const String& newName)
{
	if (newName.isEmpty ())
	{
		THROW(_T("IDS_NULL_ARGUMENT"));
	}
	
#ifdef __WINDOWS__
	if (!::SetComputerName (newName.getCStr ()))
		THROW (_T("IDS_ENV_CANNOT_SET_COMPUTER_NAME"), 
							   ::GetLastError ());


#elif defined(__AIX__) || defined(__SOLARIS__)
	THROW ("NotImplementedException");
#else
	if (sethostname(newName.getCStr (), newName.getLength ()))
		THROW_ID (_T("IDS_ENV_CANNOT_SET_COMPUTER_NAME"),errno); 

#endif /* __WINDOWS__ */
}

// public static 
size_t 
Environment::getAvailProcessors (void)
{	
#ifdef __WINDOWS__
   	SYSTEM_INFO siSysInfo;
   	::memset (&siSysInfo, 0, sizeof (SYSTEM_INFO));
   	// Copy the hardware information to the SYSTEM_INFO structure. 
   	::GetSystemInfo (&siSysInfo);
   	
   	return siSysInfo.dwNumberOfProcessors;
#elif defined(__AIX__) || defined(__HPPA__) || defined(__SOLARIS__)
	THROW ("NotImplementedException");
#else
	struct sysinfo info;
	if (sysinfo(&info) == -1)
		THROW (strerror (errno));

	return info.procs;
#endif /* __WINDOWS__ */
}

// public static 
size_t 
Environment::getAvailPhysicalMemory (void)
{	
#ifdef __WINDOWS__
	MEMORYSTATUS ms;
	::memset (&ms, 0, sizeof (MEMORYSTATUS));
	ms.dwLength = sizeof (MEMORYSTATUS);
	
	::GlobalMemoryStatus (&ms);
	
	return ms.dwAvailPhys;
#elif defined(__AIX__) || defined(__HPPA__) || defined(__SOLARIS__)
	THROW ("NotImplementedException");
#else
	struct sysinfo info;
	if (sysinfo(&info) == -1)
		THROW (strerror (errno));

	return (size_t)info.freeram;
#endif /* __WINDOWS__ */
}

// public static 
size_t 
Environment::getTotalPhysicalMemory (void)
{
#ifdef __WINDOWS__
	MEMORYSTATUS ms;
	::memset (&ms, 0, sizeof (MEMORYSTATUS));
	ms.dwLength = sizeof (MEMORYSTATUS);
	
	::GlobalMemoryStatus (&ms);
	
	return ms.dwTotalPhys;	
#elif defined(__AIX__) || defined(__HPPA__) || defined(__SOLARIS__)
	THROW ("NotImplementedException");
#else
	struct sysinfo info;
	if (sysinfo(&info) == -1)
		THROW (strerror (errno));

	return (size_t)info.totalram;
#endif /* __WINDOWS__ */
}

// public static 
String 
Environment::getEnvVariable (const String& name)
{	
#ifdef __WINDOWS__
	if (name.isEmpty ())
	{
		THROW (_T("IDS_NULL_ARGUMENT"));
	}
	
	String strEnv (_T(""));
	
	tchar_t strTemp [PATH_MAX_LEN], dummy;
	
	size_t size = ::GetEnvironmentVariable (name.getCStr (), &dummy, 0);
	
	if (size == 0)
		return strEnv;
	
	size = ::GetEnvironmentVariable (name.getCStr (), 
									 strTemp, 
									 (unsigned int) size);
	
	if (size == 0)
		return strEnv;

	strEnv = strTemp;

	return strEnv;
#else
	char* str = getenv(name.getCStr ());

	if (str == NULL)
		return String::EMPTY;
	
	return String (str);
#endif /* __WINDOWS__ */
}

// public static 
void 
Environment::setEnvVariable (const String& name, const String& value)
{
	
#ifdef __WINDOWS__
	if (name.isEmpty ())
	{
		THROW (_T("IDS_NULL_ARGUMENT"));
	}
		
	if (value.isEmpty ())
		deleteEnvVariable (name);
		
	if (!::SetEnvironmentVariable (name.getCStr (), value.getCStr ()))
		THROW (strerror (errno));

#elif defined(__HPPA__)
	THROW ("NotImplementedException");
#elif defined(__SOLARIS__)
	THROW ("NotImplementedException");
#else
	if (setenv(name.getCStr (), value.getCStr (), 1) == -1)
		THROW (strerror (errno));
#endif /* __WINDOWS__ */
}

// public static 
void 
Environment::deleteEnvVariable (const String& name)
{
#ifdef __WINDOWS__
	if (name.isEmpty ())
	{
		THROW (_T("IDS_NULL_ARGUMENT"));
	}
		
	if (!::SetEnvironmentVariable (name.getCStr (), NULL))
		THROW (strerror (errno));

#elif defined(__HPPA__)
	THROW ("NotImplementedException");
#elif defined(__SOLARIS__)
	THROW ("NotImplementedException");
#else
	 unsetenv(name.getCStr ());
#endif /* __WINDOWS__ */
}

// public static 
String 
Environment::getTempPath (void)
{
	tchar_t strTemp [PATH_MAX_LEN];
	
	if (!::GetTempPath (PATH_MAX_LEN, 
#ifdef __WINDOWS__
							 strTemp))
#else
							(gchar*) (strTemp)))
#endif
	THROW (strerror (errno));
		
	return (String (strTemp));
}

//
// The following codes comes from MS support site.
//
#ifdef __WINDOWS__

#define SECURITY_WIN32
#include <sspi.h>
#ifndef SEC_I_COMPLETE_NEEDED
#include <issperr.h>
#endif

typedef struct _AUTH_SEQ 
{
   int fInitialized;
   int fHaveCredHandle;
   int fHaveCtxtHandle;
   CredHandle hcred;
   struct _SecHandle hctxt;
} AUTH_SEQ, *PAUTH_SEQ;


// Function pointers
ACCEPT_SECURITY_CONTEXT_FN       _AcceptSecurityContext     = NULL;
ACQUIRE_CREDENTIALS_HANDLE_FN    _AcquireCredentialsHandle  = NULL;
COMPLETE_AUTH_TOKEN_FN           _CompleteAuthToken         = NULL;
DELETE_SECURITY_CONTEXT_FN       _DeleteSecurityContext     = NULL;
FREE_CONTEXT_BUFFER_FN           _FreeContextBuffer         = NULL;
FREE_CREDENTIALS_HANDLE_FN       _FreeCredentialsHandle     = NULL;
INITIALIZE_SECURITY_CONTEXT_FN   _InitializeSecurityContext = NULL;
QUERY_SECURITY_PACKAGE_INFO_FN   _QuerySecurityPackageInfo  = NULL;

void 
UnloadSecurityDll (void* hModule) 
{
   if (hModule)
      FreeLibrary ((HMODULE) hModule);

   _AcceptSecurityContext      = NULL;
   _AcquireCredentialsHandle   = NULL;
   _CompleteAuthToken          = NULL;
   _DeleteSecurityContext      = NULL;
   _FreeContextBuffer          = NULL;
   _FreeCredentialsHandle      = NULL;
   _InitializeSecurityContext  = NULL;
   _QuerySecurityPackageInfo   = NULL;
}

void* 
LoadSecurityDll (void) 
{
   void* hModule;
   int fAllFunctionsLoaded = FALSE;
   tchar_t   lpszDLL[MAX_PATH];
   OSVERSIONINFO VerInfo;

   //
   //  Find out which security DLL to use, depending on
   //  whether we are on NT or Win95 or 2000 or XP or Windows Server 2003
   //  We have to use security.dll on Windows NT 4.0.
   //  All other operating systems, we have to use Secur32.dll
   //
   VerInfo.dwOSVersionInfoSize = sizeof (OSVERSIONINFO);
   if (!GetVersionEx (&VerInfo))   // If this fails, something has gone wrong
   {
      return FALSE;
   }

   if (VerInfo.dwPlatformId == VER_PLATFORM_WIN32_NT &&
      VerInfo.dwMajorVersion == 4 &&
      VerInfo.dwMinorVersion == 0)
   {
      lstrcpy (lpszDLL, _T("security.dll"));
   }
   else
   {
      lstrcpy (lpszDLL, _T("secur32.dll"));
   }


   hModule = LoadLibrary(lpszDLL);
   if (!hModule)
      return NULL;

   __try {

      _AcceptSecurityContext = (ACCEPT_SECURITY_CONTEXT_FN)
            GetProcAddress((HMODULE) hModule, "AcceptSecurityContext");
      if (!_AcceptSecurityContext)
         __leave;

#ifdef UNICODE
      _AcquireCredentialsHandle = (ACQUIRE_CREDENTIALS_HANDLE_FN)
            GetProcAddress((HMODULE) hModule, "AcquireCredentialsHandleW");
#else
      _AcquireCredentialsHandle = (ACQUIRE_CREDENTIALS_HANDLE_FN)
            GetProcAddress((HMODULE) hModule, "AcquireCredentialsHandleA");
#endif
      if (!_AcquireCredentialsHandle)
         __leave;

      // CompleteAuthToken is not present on Windows 9x Secur32.dll
      // Do not check for the availablity of the function if it is NULL;
      _CompleteAuthToken = (COMPLETE_AUTH_TOKEN_FN)
            GetProcAddress((HMODULE) hModule, "CompleteAuthToken");

      _DeleteSecurityContext = (DELETE_SECURITY_CONTEXT_FN)
            GetProcAddress((HMODULE) hModule, "DeleteSecurityContext");
      if (!_DeleteSecurityContext)
         __leave;

      _FreeContextBuffer = (FREE_CONTEXT_BUFFER_FN)
            GetProcAddress((HMODULE) hModule, "FreeContextBuffer");
      if (!_FreeContextBuffer)
         __leave;

      _FreeCredentialsHandle = (FREE_CREDENTIALS_HANDLE_FN)
            GetProcAddress((HMODULE) hModule, "FreeCredentialsHandle");
      if (!_FreeCredentialsHandle)
         __leave;

#ifdef UNICODE
      _InitializeSecurityContext = (INITIALIZE_SECURITY_CONTEXT_FN)
            GetProcAddress((HMODULE) hModule, "InitializeSecurityContextW");
#else
      _InitializeSecurityContext = (INITIALIZE_SECURITY_CONTEXT_FN)
            GetProcAddress((HMODULE) hModule, "InitializeSecurityContextA");
#endif
      if (!_InitializeSecurityContext)
         __leave;

#ifdef UNICODE
      _QuerySecurityPackageInfo = (QUERY_SECURITY_PACKAGE_INFO_FN)
            GetProcAddress((HMODULE) hModule, "QuerySecurityPackageInfoW");
#else
      _QuerySecurityPackageInfo = (QUERY_SECURITY_PACKAGE_INFO_FN)
            GetProcAddress((HMODULE) hModule, "QuerySecurityPackageInfoA");
#endif
      if (!_QuerySecurityPackageInfo)
         __leave;

      fAllFunctionsLoaded = TRUE;

   } __finally {

      if (!fAllFunctionsLoaded) {
         UnloadSecurityDll(hModule);
         hModule = NULL;
      }

   }

   return hModule;
}

/*++

 Routine Description:

   Optionally takes an input buffer coming from the server and returns
   a buffer of information to send back to the server.  Also returns
   an indication of whether or not the context is complete.

 Return Value:

   Returns TRUE if successful; otherwise FALSE.

--*/
int 
GenClientContext (PAUTH_SEQ pAS, 
				  PSEC_WINNT_AUTH_IDENTITY pAuthIdentity,
      			  void* pIn, 
      			  unsigned int cbIn, 
      			  void* pOut, 
      			  unsigned long* pcbOut, 
      			  PBOOL pfDone) 
{
   unsigned int ss;
   TimeStamp       tsExpiry;
   SecBufferDesc   sbdOut;
   SecBuffer       sbOut;
   SecBufferDesc   sbdIn;
   SecBuffer       sbIn;
   unsigned int           fContextAttr;

   if (!pAS->fInitialized) {

      ss = _AcquireCredentialsHandle (NULL, 
      								  _T("NTLM"),
      								  SECPKG_CRED_OUTBOUND, 
      								  NULL, 
      								  pAuthIdentity, 
      								  NULL, 
      								  NULL,
      								  &pAS->hcred, 
      								  &tsExpiry);
      if (ss < 0) {
         //fprintf(stderr, "AcquireCredentialsHandle failed with %08X\n", ss);
         return FALSE;
      }

      pAS->fHaveCredHandle = TRUE;
   }

   // Prepare output buffer
   sbdOut.ulVersion = 0;
   sbdOut.cBuffers = 1;
   sbdOut.pBuffers = &sbOut;

   sbOut.cbBuffer = *pcbOut;
   sbOut.BufferType = SECBUFFER_TOKEN;
   sbOut.pvBuffer = pOut;

   // Prepare input buffer
   if (pAS->fInitialized)  {
      sbdIn.ulVersion = 0;
      sbdIn.cBuffers = 1;
      sbdIn.pBuffers = &sbIn;

      sbIn.cbBuffer = cbIn;
      sbIn.BufferType = SECBUFFER_TOKEN;
      sbIn.pvBuffer = pIn;
   }

   ss = _InitializeSecurityContext (&pAS->hcred,
   									pAS->fInitialized ? &pAS->hctxt : NULL, 
   									NULL, 
   									0, 
   									0,
   									SECURITY_NATIVE_DREP, 
   									pAS->fInitialized ? &sbdIn : NULL,
   									0, 
   									&pAS->hctxt, 
   									&sbdOut, 
   									(ULONG*) &fContextAttr, 
   									&tsExpiry);
   if (ss < 0)  {
      // <winerror.h>
      //fprintf(stderr, "InitializeSecurityContext failed with %08X\n", ss);
      return FALSE;
   }

   pAS->fHaveCtxtHandle = TRUE;

   // If necessary, complete token
   if (ss == SEC_I_COMPLETE_NEEDED || ss == SEC_I_COMPLETE_AND_CONTINUE) {

      if (_CompleteAuthToken) {
         ss = _CompleteAuthToken(&pAS->hctxt, &sbdOut);
         if (ss < 0)  {
            //fprintf(stderr, "CompleteAuthToken failed with %08X\n", ss);
            return FALSE;
         }
      }
      else {
         //fprintf (stderr, "CompleteAuthToken not supported.\n");
         return FALSE;
      }
   }

   *pcbOut = sbOut.cbBuffer;

   if (!pAS->fInitialized)
      pAS->fInitialized = TRUE;

   *pfDone = !(ss == SEC_I_CONTINUE_NEEDED
         || ss == SEC_I_COMPLETE_AND_CONTINUE );

   return TRUE;
}

/*++

 Routine Description:

    Takes an input buffer coming from the client and returns a buffer
    to be sent to the client.  Also returns an indication of whether or
    not the context is complete.

 Return Value:

    Returns TRUE if successful; otherwise FALSE.

--*/
int 
GenServerContext (PAUTH_SEQ pAS, 
				  void* pIn, 
				  unsigned int cbIn, 
				  void* pOut,
      			  unsigned long* pcbOut, 
      			  PBOOL pfDone) 
{
   unsigned int ss;
   TimeStamp       tsExpiry;
   SecBufferDesc   sbdOut;
   SecBuffer       sbOut;
   SecBufferDesc   sbdIn;
   SecBuffer       sbIn;
   unsigned int           fContextAttr;

   if (!pAS->fInitialized)  {

      ss = _AcquireCredentialsHandle (NULL, 
      								  _T("NTLM"),
      								  SECPKG_CRED_INBOUND, 
      								  NULL, 
      								  NULL, 
      								  NULL, 
      								  NULL, 
      								  &pAS->hcred,
      								  &tsExpiry);
      if (ss < 0) {
         //fprintf(stderr, "AcquireCredentialsHandle failed with %08X\n", ss);
         return FALSE;
      }

      pAS->fHaveCredHandle = TRUE;
   }

   // Prepare output buffer
   sbdOut.ulVersion = 0;
   sbdOut.cBuffers = 1;
   sbdOut.pBuffers = &sbOut;

   sbOut.cbBuffer = *pcbOut;
   sbOut.BufferType = SECBUFFER_TOKEN;
   sbOut.pvBuffer = pOut;

   // Prepare input buffer
   sbdIn.ulVersion = 0;
   sbdIn.cBuffers = 1;
   sbdIn.pBuffers = &sbIn;

   sbIn.cbBuffer = cbIn;
   sbIn.BufferType = SECBUFFER_TOKEN;
   sbIn.pvBuffer = pIn;

   ss = _AcceptSecurityContext (&pAS->hcred,
         					   pAS->fInitialized ? &pAS->hctxt : NULL, 
         					   &sbdIn, 
         					   0,
         					   SECURITY_NATIVE_DREP, 
         					   &pAS->hctxt, 
         					   &sbdOut, 
         					   (ULONG*) &fContextAttr,
         					   &tsExpiry);
   if (ss < 0)  {
      //fprintf(stderr, "AcceptSecurityContext failed with %08X\n", ss);
      return FALSE;
   }

   pAS->fHaveCtxtHandle = TRUE;

   // If necessary, complete token
   if (ss == SEC_I_COMPLETE_NEEDED || ss == SEC_I_COMPLETE_AND_CONTINUE) {

      if (_CompleteAuthToken) {
         ss = _CompleteAuthToken(&pAS->hctxt, &sbdOut);
         if (ss < 0)  {
            //fprintf(stderr, "CompleteAuthToken failed with %08X\n", ss);
            return FALSE;
         }
      }
      else {
         //fprintf (stderr, "CompleteAuthToken not supported.\n");
         return FALSE;
      }
   }

   *pcbOut = sbOut.cbBuffer;

   if (!pAS->fInitialized)
      pAS->fInitialized = TRUE;

   *pfDone = !(ss = SEC_I_CONTINUE_NEEDED
         || ss == SEC_I_COMPLETE_AND_CONTINUE);

   return TRUE;
}
#endif // __WINDOWS__

// public static
void
Environment::getDomainNames (vector<String>& domains)
{
#ifdef __WINDOWS__
    unsigned int             hr;
    IDsBrowseDomainTree *pBrowseTree;

    CoInitialize(NULL);

    hr = CoCreateInstance(CLSID_DsDomainTreeBrowser,
                          NULL,
                          CLSCTX_INPROC_SERVER,
                          IID_IDsBrowseDomainTree,
                          (void**)&pBrowseTree);

    if(SUCCEEDED(hr))
    {
        DOMAINTREE  *pDomTreeStruct;

        hr = pBrowseTree->GetDomains(&pDomTreeStruct, DBDTF_RETURNFQDN);
        if(SUCCEEDED(hr))
        {
            int count = (int) pDomTreeStruct->dwCount;
			for (int i = 0; i < count; i++) {
				domains.push_back (pDomTreeStruct->aDomains[i].pszName);
			}
           
            hr = pBrowseTree->FreeDomains(&pDomTreeStruct);
        }
        
        pBrowseTree->Release();
    }
    
    CoUninitialize();
#else // __WINDOWS__
	THROW ("NotImplementedException");
#endif
}

// public static 
bool 
Environment::logonUser (const String& domain, 
					    const String& user, 
						const String& password)
{
#ifdef __WINDOWS__
	AUTH_SEQ    asServer   = {0};
   	AUTH_SEQ    asClient   = {0};
   	int    fDone      = FALSE;
   	bool        fResult    = false;
   	unsigned int       cbOut      = 0;
   	unsigned int       cbIn       = 0;
   	unsigned int       cbMaxToken = 0;
   	void*       pClientBuf = NULL;
   	void*       pServerBuf = NULL;
   	PSecPkgInfo pSPI       = NULL;
   	void*     hModule    = NULL;   	

   	__try {

      	hModule = LoadSecurityDll ();
      	if (!hModule)
        	__leave;

      	// Get max token size
      	_QuerySecurityPackageInfo(_T("NTLM"), &pSPI);
      	cbMaxToken = pSPI->cbMaxToken;
      	_FreeContextBuffer(pSPI);

      	// Allocate buffers for client and server messages
      	pClientBuf = HeapAlloc (GetProcessHeap(), HEAP_ZERO_MEMORY, cbMaxToken);
      	pServerBuf = HeapAlloc (GetProcessHeap(), HEAP_ZERO_MEMORY, cbMaxToken);

		SEC_WINNT_AUTH_IDENTITY ai;
      	// Initialize auth identity structure
      	ZeroMemory (&ai, sizeof(ai));
#if defined(UNICODE) || defined(_UNICODE)
      	ai.Domain = (unsigned short*) (domain.getCStr ());
      	ai.DomainLength = (unsigned long) domain.getLength ();
      	ai.User = (unsigned short*) (user.getCStr ());
      	ai.UserLength = (unsigned long) user.getLength ();
      	ai.Password = (unsigned short *) (password.getCStr ());
      	ai.PasswordLength = (unsigned long) password.getLength ();
      	ai.Flags = SEC_WINNT_AUTH_IDENTITY_UNICODE;
#else
#if 0
      	ai.Domain = (unsigned char *)szDomain;
      	ai.DomainLength = lstrlen(szDomain);
      	ai.User = (unsigned char *)szUser;
      	ai.UserLength = lstrlen(szUser);
      	ai.Password = (unsigned char *)szPassword;
      	ai.PasswordLength = lstrlen(szPassword);
      	ai.Flags = SEC_WINNT_AUTH_IDENTITY_ANSI;
#else
#error pls implement it.
#endif

#endif

      	// Prepare client message (negotiate) .
      	cbOut = cbMaxToken;
      	if (!GenClientContext (&asClient, &ai, NULL, 0, pClientBuf, (unsigned long*) &cbOut, &fDone))
        	 __leave;

      	// Prepare server message (challenge) .
      	cbIn = cbOut;
      	cbOut = cbMaxToken;
      	if (!GenServerContext (&asServer, pClientBuf, cbIn, pServerBuf, (unsigned long*) &cbOut,
            &fDone))
        	 __leave;
         // Most likely failure: AcceptServerContext fails with SEC_E_LOGON_DENIED
         // in the case of bad szUser or szPassword.
         // Unexpected Result: Logon will succeed if you pass in a bad szUser and
         // the guest account is enabled in the specified domain.

      	// Prepare client message (authenticate) .
      	cbIn = cbOut;
      	cbOut = cbMaxToken;
      	if (!GenClientContext (&asClient, &ai, pServerBuf, cbIn, pClientBuf, (unsigned long*) &cbOut,
            &fDone))
         	__leave;

      	// Prepare server message (authentication) .
      	cbIn = cbOut;
      	cbOut = cbMaxToken;
      	if (!GenServerContext (&asServer, pClientBuf, cbIn, pServerBuf, (unsigned long*) &cbOut,
            &fDone))
        	 __leave;

      	fResult = true;

	} __finally {

      	// Clean up resources
      	if (asClient.fHaveCtxtHandle)
         	_DeleteSecurityContext (&asClient.hctxt);

      	if (asClient.fHaveCredHandle)
         	_FreeCredentialsHandle (&asClient.hcred);

      	if (asServer.fHaveCtxtHandle)
        	_DeleteSecurityContext (&asServer.hctxt);

      	if (asServer.fHaveCredHandle)
         	_FreeCredentialsHandle (&asServer.hcred);

      	if (hModule)
         	UnloadSecurityDll (hModule);

      	HeapFree (GetProcessHeap(), 0, pClientBuf);
      	HeapFree (GetProcessHeap(), 0, pServerBuf);
   }

   return fResult;
#else // __WINDOWS__
	THROW ("NotImplementedException");

#endif
}

// public static 
size_t 
Environment::getPageSize (void)
{
#ifdef __WINDOWS__
	static size_t pageSize = 0; 
	
	if (pageSize == 0) {
		SYSTEM_INFO siSysInfo;
	   	::memset (&siSysInfo, 0, sizeof (SYSTEM_INFO));
	   	::GetSystemInfo (&siSysInfo);
	   	
	   	pageSize = siSysInfo.dwPageSize;
	}
	
	return pageSize;
#else
	int sz = getpagesize();
	return sz;
#endif /* __WINDOWS__ */
}
