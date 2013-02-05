/***************************************************************************************************
Path.cpp:	
	C++ Foundation Library header Paths
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	This Path contain the declaration of classes:

Author:
	韩欣

Creating Time:
	2011-10-10
***************************************************************************************************/

#include "../prec.h"
#include "../lang/string.h"
#include "../sys/exception.h"

#include "path.h"

#ifndef __WINDOWS__
	#include <sys/types.h>
	#include <sys/stat.h>
	#include <fcntl.h>
	#include <unistd.h>
#endif

// windows path is quiet different from posix
#ifdef __WINDOWS__
#define handleSegment winHandleSegmentPath
#else
#define handleSegment posixHandleSegmentPath
#endif

// 全局变量，避免重复获取
static String g_CurrentModulePath;
static String PARDIR = _T("..");
static String CURDIR = _T(".");
static String EXTSEP = _T(".");
	
#ifdef __WINDOWS__		 
	const tchar_t Path::separator = _T('\\');
	const tchar_t Path::altSeparator = _T('/');	
	const tchar_t Path::volumeSeparator = _T(':');
	const tchar_t Path::pathSeparator = _T(';');
#else
	const tchar_t Path::separator = '/';
	//const tchar_t Path::altSeparator = '\\'; in POSIX path \ is an ordinary char in path
	const tchar_t Path::altSeparator = '/';		
	const tchar_t Path::volumeSeparator = '/';
	const tchar_t Path::pathSeparator = ':';
#endif

inline bool
isSeparator (tchar_t ch)
{
/**
 * change feature, in posix path format, "\" is a legal character in path
 *
 * fan.fei@datatom.com 2012.3.20
 */
#ifdef __WINDOWS__
	return (ch == Path::separator || ch == Path::altSeparator);
#else
    return (ch == Path::separator);
#endif

}


int 
toLatestSeparator (const tchar_t* ptr, const tchar_t* endPtr)
{
	int num = 0;
	while (ptr != endPtr) {
		if (isSeparator (*ptr))
			return num;
			
		num++;
		ptr++;
	}
	
	return -1;
}

// private static 
const tchar_t Path::invalidPathChars[] = {
#if defined(__WINDOWS__)
	'"',				/* double quote, which seems allowed in MS.NET but should be rejected */
	'<',				/* less than */
	'>',				/* greater than */
	//'/',
	//'\\',
	'|',				/* pipe */
	//'*',
	//'?',
	0x08,				/* backspace */
	0x10,				/* data link escape */
	0x11,				/* device control 1 */
	0x12,				/* device control 2 */
	0x13,				/* device control 3 */
	0x14,				/* device control 4 */
	0x15,				/* negative acknowledge */
	0x16,				/* synchronous idle */
	0x17,				/* end of trans, block */
	0x18,				/* cancel */
	0x19,				/* substitute */
#else
	//'/',              /* '/' in linux is root path.*/
#endif
	0x0000				/* null */
};


// private static 
const tchar_t Path::separatorChars[] = { Path::separator, Path::altSeparator, 0x0000 };

// public ctor
Path::Path (void)
{
	// Do nothing
}

// public dtor
Path::~Path (void)
{
	// Do nothing
}

// public static 
String 
Path::combine (const String& path1, const String& path2)
{
	if (path1.isEmpty () && path2.isEmpty ())
		THROW("IDS_ILLEGAL_PATH");

	if (path1.findFirstOf (Path::invalidPathChars, 0) != String::NO_POSITION)
		THROW("IDS_ILLEGAL_PATH");

	if (path1.isEmpty ())
		return path2;

	if (path2.isEmpty ())
		return path1;

	if (Path::isAbsolutePath (path2))
		return path2;

	

	//
	// isAbsolutePath have checked the invalid characters of the path2
	//			
	if (isSeparator (path1 [(int) path1.getLength () - 1]))
		return path1 + path2;	

	String result (path1);
	result += Path::separator;
	result += path2;

	return result;
}



bool
Path::isAbsolutePath (const String& path)
{

	if (path.isEmpty ())
		return false;

	size_t pos = path.findFirstOf (Path::invalidPathChars, 0);
	if (pos != String::NO_POSITION)
		THROW ("invalid path!");

	// Check the first character.
	tchar_t ch = path [0];

	return (ch == Path::separator || 
			ch == Path::altSeparator ||
			((separator !=Path::volumeSeparator) && path.getLength () > 1 && path [1] == Path::volumeSeparator));

}


// public static 
String 
Path::getCurrentPath (void)
{
	char pCurrentPath[MAX_PATH];
	getcwd (pCurrentPath, MAX_PATH);

	if (pCurrentPath[strlen (pCurrentPath) - 1] != '/') {
		strcat(pCurrentPath, "/");
	}

	char *ptr = strrchr(pCurrentPath, '/');
	*(++ptr) = 0;

	return pCurrentPath;
}

void
Path::split(const String &path,String& dirpath, String& filename)
{	
	if (path.isEmpty ())
		THROW("IDS_ILLEGAL_PATH");

	if (path.findFirstOf (Path::invalidPathChars, 0) != String::NO_POSITION)
		THROW("IDS_ILLEGAL_PATH");

    dirpath.clear();
    filename.clear();
    String p = Path::adaptSep(path);
#ifdef __WINDOWS__
    // TODO
    // deal route like \\.\device\somthing
    // and \\?\volume\something
    // and driver: like C:
    // C:dir should throw an error?
#endif
    // deal when start with separator
    size_t headSlashNum = 0;
    if (isSeparator(p[0])) {
        while (isSeparator( p[headSlashNum])) { 
            dirpath += Path::separator; 
            headSlashNum++;
            if (headSlashNum == p.getLength()) {
                break;
            }
        }
    }
    p = p.subString(headSlashNum);
    // find most right sep pos
    size_t posLastSlash = p.findLastOf(Path::separator);
    if (posLastSlash == p.getLength() - 1) { 
        dirpath += p.subString(0, p.getLength() - 1);
        filename = String::EMPTY;
    } else if (posLastSlash == String::NO_POSITION) {
        filename = p;
    } else {
        dirpath += String(p, 0, posLastSlash);
        filename.assign(p, posLastSlash + 1, String::NO_POSITION);
    }
}

// public static 
String 
Path::getDirectoryName (const String& path)
{
	if (path.isEmpty ())
		THROW("IDS_ILLEGAL_PATH_FORM");

    String dirpath,filename;
    split(path, dirpath, filename);
    return dirpath;
}


// public static 
String 
Path::getFileName (const String& path)
{
    String dirpath,filename;
    split(path, dirpath, filename);
    return filename;
}


// public static 
String 
Path::getPathRoot (const String& path)
{
	if (path.isEmpty ())
		return path;

	if (!Path::isAbsolutePath (path)) 
		return String::EMPTY;
	
	if (Path::separator == _T('/')) {
		// UNIX
		if (isSeparator (path [0]))
			return String(Path::separator, 1);
		else
			return String::EMPTY;
	} 
	else {
		// Windows
		size_t len = 2;

		size_t size = path.getLength ();
		if (size == 1 && isSeparator (path [0]))
			return String (Path::separator, 1);
		else if (size < 2)
			return String::EMPTY;

		if (isSeparator (path [0]) && isSeparator (path[1])) {
			// UNC: \\server or \\server\share
			// Get server
			while (len < size && !isSeparator (path [(int) len])) 
				len++;

			len++;

			// Get share
			while (len < size && !isSeparator (path [(int)len])) 
				len++; 

			String subString;
			subString.append (Path::separator, 1);
			subString.append (Path::separator, 1);

			subString.insert (2, path, 2, len - 2);
			subString.replace (Path::altSeparator, Path::separator, true);
			subString.append (Path::separator, 1);

			return subString;
		} 
		else if (isSeparator (path [0])) {
			// path starts with '\' or '/'
			return String (Path::separator, 1);

		}
		else if (path[1] == Path::volumeSeparator) {
			// C:\folder
			if (size >= 3 && (isSeparator (path [2]))) 
				len++;
		}
		else
			return Path::getCurrentPath ().subString (0, 2);

		return path.subString (0, len);
	}
}

inline size_t 
findExt (const String& path)
{
	//
	// This method should return the index of the path extension
	// start or -1 if no valid extension.
	//
	// if (!path.isEmpty ()) {
	if (!path.isEmpty () && path.getLength() > 1) {
		// size_t lastDot = path.findLastOf ('.', path.getLength () - 1);  
        // when '.' is lastchar of file, it not means separator of filename and extname
		size_t lastDot = path.findLastOf ('.', path.getLength () - 2); 
		size_t lastSep = path.findLastOf (Path::getSeparatorChars (), path.getLength () - 1);

		if (lastSep == String::NO_POSITION || lastDot > (size_t) lastSep)
			return lastDot;
	}

	return String::NO_POSITION;
}


// public static 
void 
Path::changeExtension (String& path, const String& extension)
{
	if (path.findFirstOf (Path::invalidPathChars) != String::NO_POSITION)
		THROW ("IDS_ILLEGAL_PATH");

    if (Path::getFileName(path) == String::EMPTY)
		THROW ("IDS_ILLEGAL_FILENAME");

	size_t dotPos = findExt (path);
	
	if (extension.isEmpty () == true) {
		if (dotPos != String::NO_POSITION)
			path = path.subString (0, dotPos);
			
		return;
	}
	
	String ext;
		
	if (extension [0] != '.') {
		ext += '.';
		ext += extension;
	} 
	else
		ext = extension;

	if (dotPos == String::NO_POSITION) {
		path += ext;
	} 
	else if (dotPos > 0) {
		path.replace (dotPos, path.getLength () - dotPos, ext);
	}
	else {
		path = ext;
	}
}

// public static
void 
Path::addExtension (String& path, const String& extension) {
	if (path.findFirstOf (Path::invalidPathChars) != String::NO_POSITION)
		THROW ("IDS_ILLEGAL_PATH");

    if (Path::getFileName(path) == String::EMPTY)
		THROW ("IDS_ILLEGAL_FILENAME");
    
    if (extension == String::EMPTY)
        return;
    
    if (extension[0] != '.')
        path += '.';
    path += extension;
}

// public static 
String 
Path::getExtensionName (const String& path)
{
	if (path.findFirstOf ( Path::invalidPathChars) != String::NO_POSITION)
		THROW ("IDS_ILLEGAL_PATH");

	size_t ext = findExt (path);

	if (ext != String::NO_POSITION) {
		if ((size_t) ext < (path.getLength () - 1))
			return path.subString (ext);
	}

	return String::EMPTY;
}


// public static 
bool 
Path::isValidPath (const String& path)
{
#ifdef __WINDOWS__
	static String validChars;

	if (validChars.isEmpty ()) {
		const tchar_t vchars[] = {
			'"',				/* double quote, which seems allowed in MS.NET but should be rejected */
			'<',				/* less than */
			'>',				/* greater than */
			'|',				/* pipe */
			'*',
			'?',
		};

		validChars.append (vchars, 7);
	}

	if (path.findFirstOf (validChars) != String::NO_POSITION)
		return false;

	// Check invalid ':' character
	if (Path::isAbsolutePath (path)) {
		// absolute path, skip the volume token
		if (path.find (':', 2) != String::NO_POSITION) 
			return false;
	}
	else {
		if (path.find (':') != String::NO_POSITION) 
			return false;
	}

	return true;
#else
	if (path.getLength () > NAME_MAX)
		return false;

	return true;
#endif
}

inline String getPath ()
{

#ifndef  __WINDOWS__
	//
	// linux current module path
	//
	unsigned int pid = getpid ();
	String fileName;
#ifdef __AIX__
	fileName.format (_T("/proc/%d/map"), pid);
#else
	fileName.format (_T("/proc/%d/maps"), pid);
#endif	
	int fd = open (fileName.getCStr (), 0);
	if (fd == -1) {
		//printf ("getModulePath - errno: %d\n", errno);
		//THROW (::getlasterr ());
	}

	char buf [1024];
	String line;

	errno = 0;
	char* ptr = buf;
	while (true) {
		ssize_t len = read (fd, ptr, 1024);
		if (len > SSIZE_MAX)
			break;

		if (len < 0) // TODO: error occurred.
			break;

		if (len == 0)
			break;

		line.append (ptr, len);
	}

	//
	// 关闭打开的文件
	//
	close (fd);

	if (line == String::EMPTY)
		return String::EMPTY;			

	size_t pos = 0;
	pos = line.find (_T("libdtl.so"));
	if (pos == String::NO_POSITION)
		return String::EMPTY;

	size_t posBegin = pos;
	while (true) {
#ifdef __AIX__
		posBegin = line.rfind (_T('\0'), posBegin);
#else
		posBegin = line.rfind (_T(" "), posBegin);
#endif
		if (line[posBegin + 1] == '/')
			break;
	}
	
	String fullModulePath = line.subString (posBegin + 1, pos - posBegin - 1);

	//
	// 在 linu live CD 环境中运行时，获取 current Module Path 将会在实际路径前加上一个前缀：_T("/mnt/live/memory/changes")
	// 所以在获取真实路径时，需要把路径前缀去掉。
	//
	String liveCDStr = _T("/mnt/live/memory/changes");
	posBegin = fullModulePath.find (liveCDStr);
	
	if (posBegin != String::NO_POSITION) {
		size_t liveCDStrLen = liveCDStr.getLength ();
		return fullModulePath.subString (posBegin + liveCDStrLen, fullModulePath.getLength () - liveCDStrLen);
	}

	return fullModulePath;

#endif	// end linux

	return String::EMPTY;

}


// public static 
String 
Path::getCurrentModulePath (void)
{
	if (!g_CurrentModulePath.isEmpty ())
		return g_CurrentModulePath;

	g_CurrentModulePath = getPath ();
	return g_CurrentModulePath;
}



// public static 
bool 
Path::equal (const String& path1, const String& path2)
{
	String realPath1 = path1;
	String realPath2= path2;
	realPath1.trim ();
	realPath2.trim ();

    return Path::makeFullPath(realPath1) == Path::makeFullPath(realPath2);

}

// public static
bool
Path::isParentPath (const String& path1, const String& path2)
{

	String tmp1 = path1;
	String tmp2 = path2;

	String realPath1 = makeFullPath (tmp1.trim ());
	String realPath2 = makeFullPath (tmp2.trim ());

	if (isSeparator (realPath1 [(int) realPath1.getLength () - 1]) == false)
		realPath1 += Path::separator;	
	
	if (isSeparator (realPath2 [(int) realPath2.getLength () - 1]) == false)
		realPath2 += Path::separator;

#ifdef __WINDOWS__
	if (realPath2.compareIgnoreCase (realPath1) == 1)
		return false;

	realPath1.toLower ();
	realPath2.toLower ();
	if (realPath2.find (realPath1) == 0)
		return true;
	else
		return false;
#else
	if (realPath2.compare (realPath1) == 0)
		return false;
	else 
		if (realPath2.find (realPath1) == 0)
			return true;
		else
			return false;
#endif
}


// public static 
String 
Path::getInvalidPathChars (void)
{
	return String (Path::invalidPathChars);
}
		
// public static 
String 
Path::getSeparatorChars (void)
{
	return String (Path::separatorChars);
}



static void
handleSegmentPath (vector<String>& segPath, const tchar_t* beginPtr, int count)
{
#ifdef __WINDOWS__
	if (::wcsncmp (beginPtr, _T("."), count) == 0) {
#else
	if (::strncmp (beginPtr, _T("."), count) == 0) {
#endif
		return;
	}
#ifdef __WINDOWS__
	else if (::wcsncmp (beginPtr, _T(".."), count) == 0) {
#else
	else if (::strncmp (beginPtr, _T(".."), count) == 0) {
#endif
		if (segPath.size () > 1) // Don't over the root path
			segPath.pop_back ();
	}
	else {
		segPath.push_back (String (beginPtr, count));
	}
}

/**
 * handle . and .. in path
 * ./   =====> .
 * a/.  =====> a
 * ./a  =====> a
 * a/.. =====> .
 * ../a =====> ../a
 * ..   =====> ..
 *
 */
static String
winHandleSegmentPath(const String &path) {
    //TODO
    return String::EMPTY;
}


// assume path is adapted by Path::adaptSep
static String
posixHandleSegmentPath(const String &path) {
    size_t len = path.getLength();
    if (len == 0) { return String::EMPTY; }

    //  path = "." or path = "./"
    if (path == CURDIR || path == CURDIR + Path::separator)
        return CURDIR;

    int slashCombo = 0; 
    if (path[0] == Path::separator) {
        if (len > 1) {
            path[1] == Path::separator ? slashCombo = 2 : slashCombo = 1;
        } else {
            slashCombo = 1;
        }
    }

    vector<String> oldSegments,newSegments;
    path.split(Path::separator, oldSegments);

    for (vector<String>::iterator it = oldSegments.begin();
            it != oldSegments.end(); ++it) {
        if (*it == String::EMPTY || *it == CURDIR) {
            continue;
        } else if (*it != PARDIR 
                 || (slashCombo == 0 && newSegments.empty())
                 || (!newSegments.empty() && newSegments.back() == PARDIR)) {
            newSegments.push_back(*it);
        } else {
            newSegments.pop_back();
        }
    }
    String ret = String::EMPTY;
    for (int i=0; i<slashCombo; i++) { ret += Path::separator; }

    for (size_t i=0; i<newSegments.size(); i++) {
        ret += newSegments[i];
        if (i != newSegments.size() - 1)
            ret += Path::separator;
    }

    if (!(slashCombo > 0 && len <= 2) /* // or / */
        && path[len-1] == Path::separator) { 
        ret += Path::separator; 
    }
    return ret;
}


String
Path::makeFullPath (const String &path)
{
	if (Path::isAbsolutePath (path)) 
		return handleSegment(path);

	if (path.isEmpty ())
        return Path::getCurrentPath();

    String adtpath = Path::adaptSep(path);

    return handleSegment(Path::combine(Path::getCurrentPath(), path));
}

String
Path::adaptSep(const String &path) {
#ifdef __WINDOWS__
    //in windows,'/' should be treat as '\'
    path.replace(Path::altSeparator, Path::separator, true);
#endif

    String ret = String::EMPTY;
    size_t len = path.getLength();
    int slashCombo = 0;
    size_t i = 0;
    if (isSeparator(path[0])) {
#ifdef __WINDOWS__
        /** 
         * in windows, if path start with '\', it's maybe an absolute path
         * or an UNC path(\\server\mount\dir), or current drive(\dir1\dir2\dir3)
         * so when a path start with '\', such as \\\a\b, we preserve it unchanged
         * where a\\\b changed to a\b
         */
        while (isSeparator(path[i])) {
            ret += path[i++];
            if (i == len) { break; } 
        }
#else
        /**
         * in POSIX path, only double slash is preserved(//server/mnt/dir)
         * path start with '\' like ///dir1/dir2/dir3 will be changed to /dir1/dir2/dir3
         */
        while (isSeparator(path[i])) {
            slashCombo++;
            i++;
            if (i == len) { break; } 
        }
        ret += Path::separator;
        if (slashCombo == 2) {
            ret += Path::separator;
        }
#endif
    }
    slashCombo = 0;
    for (; i<len; i++) {
        if (isSeparator(path[i])) {
            if (slashCombo != 0) { continue; }
            slashCombo += 1;
            ret += path[i];
        } else {
            slashCombo = 0;
            ret += path[i];
        }
    }
    return ret;
}
