/***************************************************************************************************
directory.cpp:	
	C++ Foundation Library header files
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	This file contain the declaration of classes:

Author:
	韩欣

Creating Time:
	2011-10-10
***************************************************************************************************/

#include "../prec.h"
#include "../mono_base/uglify.h"

#include "../lang/string.h"
#include "../sys/exception.h"

#include "comdef.h"
#include "basefile.h"
#include "file.h"
#include "path.h"

#include "directory.h"

#ifndef __WINDOWS__
	#include <sys/stat.h>
	#include <sys/types.h>
	#include <stdlib.h>
	#include <dirent.h>
	#include <unistd.h>
#endif

#ifdef __WINDOWS__
#define t_strnlen wcsncmp
#else
#define t_strnlen strncmp
#endif


#define PATH_ERROR_ID  2


// public dtor
Directory::~Directory (void)
{
	// Do nothing
}


String
Directory::getName () const
{
	const String& path = _fullPath;

	//String name = Path::getFileName (path);
	//if (name.isEmpty () == false)
	//	return name;

	//return path;
    return Path::getFileName(path);
}

void
Directory::create (void)
{
	String fullPath = _fullPath;

	if (fullPath.isEmpty ())
		THROW_ID ("IDS_PATH_IS_NULL", PATH_ERROR_ID);
			
	if (fullPath.findAny (Path::getInvalidPathChars ()) != String::NO_POSITION)
		THROW_ID ("IDS_ILLEGAL_PATH", PATH_ERROR_ID);

	if (fullPath.trim ().isEmpty ())
		THROW_ID ("IDS_BLANK_CHARS_IN_DIR", PATH_ERROR_ID);
	
	if (!isRoot ()) {
		Directory parent = this->getParent ();

		// Make sure the parent directory exists
		if (!parent.isRoot () && !parent.exists ())
			parent.create ();

		if (!::CreateDirectory (fullPath.getCStr (), 0)) {
			unsigned error = ::GetLastError ();
			if (error != ERROR_ALREADY_EXISTS)
				THROW_ID ("CreateDirectory Failed", error);
		}
		else
			_needLoad = true;
	} 
}


void
Directory::remove (void)
{	
	int ret = ::RemoveDirectory (this->_fullPath.getCStr ());
	if(ret == FALSE) {
		unsigned int error = ::GetLastError ();		
		if (error != ERROR_FILE_NOT_FOUND)
			THROW_ID ("RemoveDirectory Failed", error);
	} 
	else
		_needLoad = true;

}


// public 
void 
Directory::removeTree (void)
{
	
	if (this->exists () == false)
		return;
		
	vector<String> subs;
	this->list (subs);

	// Remove its subs recursively.
	vector<String>::iterator itend = subs.end ();
	for (vector<String>::iterator it = subs.begin (); it != itend; ++it) {
		String name = *it;

		if (BaseFile::isDirectory (name)) {
			Directory dir (name); // Recursively to remove the subdirectories.
			dir.removeTree ();
		}
		else if (BaseFile::isFile (name)){
			File file (name);
			file.remove ();
		}

	}

	// OK, all subs has been removed, remove itself safely.
	this->remove ();
}


Directory
Directory::createSubDirectory (const String& name) const
{	
	String fileName = Path::getFileName (name);
	String path;
	if (fileName.isEmpty ()) {
        /**  TODO
         *  fileName.isEmpty() == true means /name/ is like dir1/
         *
         *
        String errmsg = "Can't get a valid dir name from " + name;
        THROW(errmsg);
        */
		path = Path::combine (_fullPath, name);
    }
	else
		path = Path::combine (_fullPath, fileName);

	Directory dir (path);
	dir.create ();  

	return dir;
}


// public virtual 
bool 
Directory::exists (void) const
{	
	if (_needLoad) {
		const_cast<Directory*>(this)->loadFileAttrs ();
	}

	FileAttributes attrs = _data->attrs;
	return (attrs == INVALID_FILE ? false : (attrs & DIRECTORY) != 0 ? true: false);
}


enum F_MODE {
	//LIST_ALL = 0,
	//LIST_DIR = 1,
	//LIST_FILE = 2,

    /** in genList, F_MODE is using like (mode & LIST_FILE) != 0
    * so LIST_ALL == LIST_DIR | list_FILE
    */
	LIST_DIR = 0x01,
	LIST_FILE = 0x02,
	LIST_ALL = 0x03,
};


inline bool
isNotDotDir (const tchar_t* fileName)
{
	return (t_strnlen (fileName, _T("."), 2) != 0 &&
			  t_strnlen (fileName, _T(".."), 3) != 0);
}


template<class T>
inline void genList (const String &dirPath, vector<T>& subs, int mode, const String& pattern)
{

	//String wild = Path::combine (dirPath, pattern);

    /**
     * use Path::makeFullPath to support '.' and '..' in /dirPath/
     */
	String wild = Path::combine (Path::makeFullPath(dirPath), pattern);
		
	WIN32_FIND_DATA data;
	void* find = ::FindFirstFile (wild.getCStr (), &data);
	if (find == INVALID_HANDLE_VALUE) {
		//
		// AFAK, If append a pattern like *.h to the directory, and this directory
		// don't have any file or dir to match it, the FindFirstFile will fail.
		//
		unsigned int errCode = ::GetLastError ();
		if (pattern != _T("*") && (errCode == ERROR_FILE_NOT_FOUND || errCode == ERROR_PATH_NOT_FOUND))
			return;
#ifndef __WINDOWS__
		else if (errCode == ERROR_NO_MORE_FILES)
			return;
#endif

		THROW_ID ("genList failed", errCode);
	}
	
	int result = TRUE;
	while (result) {
		 //
		 // Ignore entries of "." and ".." the documentation doesn't mention it.
		 //
        // ------------ can deal with '.' and '..' now -----
		if (((mode & LIST_DIR) != 0 && 
            (data.dwFileAttributes & DIRECTORY) != 0 && 
            isNotDotDir ((const tchar_t*) data.cFileName))
            || 
            ((mode & LIST_FILE) != 0 && 
            (data.dwFileAttributes & DIRECTORY) == 0)) {

			subs.push_back (T(Path::combine (dirPath, (const tchar_t*)data.cFileName).getCStr ()));
		}
		
		result = ::FindNextFile (find, &data);
	}
	
	::FindClose (find);		
}


void 
Directory::list (vector<String>& subs, const String& pattern) const
{
	genList (_fullPath, subs, LIST_ALL, pattern);
}


void
Directory::list (vector<Directory>& subs, const String& pattern) const
{
	genList (_fullPath, subs, LIST_ALL, pattern);
}


void
Directory::listDirs (vector<String>& dirs, const String& pattern) const
{
	genList (_fullPath, dirs, LIST_DIR, pattern);
}

void
Directory::listDirs (vector<Directory>& dirs, const String& pattern) const
{
	genList (_fullPath, dirs, LIST_DIR, pattern);
}


void
Directory::listFiles (vector<String>& files, const String& pattern) const
{
	genList (_fullPath, files, LIST_FILE, pattern);
}


void 
Directory::listFiles (vector<File>& files, const String& pattern) const
{
	genList (_fullPath, files, LIST_FILE, pattern);
}


// public
Directory 
Directory::getParent (void) const
{	
	if (isRoot ())
		THROW_ID("IDS_ROOT_DIR", PATH_ERROR_ID);

    String fpath = Path::adaptSep(_fullPath);
    if (fpath[fpath.getLength() - 1] == Path::separator) {
        fpath = String(fpath, 0, fpath.getLength() - 1);
    }
	return Directory (Path::getDirectoryName (fpath));
}
