/***************************************************************************************************
int.h:	
	C++ Foundation Library header files
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	This file contain the declaration of classes:
	#Int64: Represents a 64-bit signed int type.

Author:
	韩欣 (han.xin@datatom.com)

Creating Time:
	2011-10-10
***************************************************************************************************/

#include "../prec.h"



#ifndef __WINDOWS__
	#include <sys/stat.h>
	#include <unistd.h>
	#include <cstdlib>
	#include <cstdio>
	#include <cerrno>
	#include <stdio.h>
	#include <stdlib.h>
	#include <fcntl.h>
	#include <string.h>

#endif

#ifdef	HAVE_SYS_TIME_H
#include <sys/time.h>
#endif

#ifdef	HAVE_SYS_WAIT_H
#include <sys/wait.h>
#endif

#include <pwd.h>
#include <grp.h>

#ifdef	SIGTSTP
#include <sys/file.h>
#include <sys/ioctl.h>
#endif

#include "../sys/exception.h"


#include <cctype>
#include <string>
#include <cstring>

#ifdef	HAVE_STRINGS_H
extern "C" {
#include <strings.h>
}
#endif

#ifndef	stricmp
#define	stricmp(x, y) strcasecmp(x, y)
#endif


#ifndef strnicmp
#define	strnicmp(x, y, n) strncasecmp(x, y, n)
#endif


#include "lockfile.h"

#ifdef	WIN32

Lockfile::Lockfile()
{
	_mutex = INVALID_HANDLE_VALUE;
	_flagged = false;
	_path = NULL;
}


Lockfile::Lockfile(const char *name)
{
	_mutex = INVALID_HANDLE_VALUE;
	_flagged = false;
	_path = NULL;
	lock(name);
}

bool Lockfile::lock(const char *name)
{
	char mname[65];
	char *ext = strrchr(name.getCStr (), '/');

	if(ext)
		name = ++ext;

	unlock();

	snprintf(mname, sizeof(mname) - 4, "_lock_%s", name);
	ext = strrchr(mname, '.');
	if(ext && !stricmp(ext, ".lock")) {
		*ext = 0;
		ext = NULL;
	}
	if(!ext)
		addString(mname, sizeof(mname), ".lck");
	_mutex = CreateMutex(NULL, FALSE, mname);
	if(WaitForSingleObject(_mutex, 200) == WAIT_OBJECT_0)
		_flagged = true;
	return _flagged;
}

void Lockfile::unlock(void)
{
	if(_mutex == INVALID_HANDLE_VALUE)
		return;

	if(_flagged)
		ReleaseMutex(_mutex);
	CloseHandle(_mutex);
	_flagged = false;
	_mutex = INVALID_HANDLE_VALUE;
}

bool Lockfile::isLocked(void)
{
	return _flagged;
}

#else	// __LINUX__


Lockfile::Lockfile()
{
	_path = NULL;
}

Lockfile::Lockfile(const char *name)
{
	_path = NULL;
	lock(name);
}

bool Lockfile::lock(const char *name)
{
	struct stat ino;
	int fd, pid, status;
	const char *ext;
	char buffer[128];
	bool rtn = true;

	unlock();

	ext = strrchr(name, '/');
	if(ext)
		ext = strrchr(ext, '.');
	else
		ext = strrchr(name, '.');

	if(strchr(name, '/')) {
		_path = new char[strlen(name) + 1];
		strcpy(_path, name);
	}
	else if(ext && !stricmp(ext, ".pid")) {
		if(stat("/var/run", &ino))
			snprintf(buffer, sizeof(buffer), "/tmp/.%s", name);
		else
			snprintf(buffer, sizeof(buffer), "/var/run/%s", name);
		_path = new char[strlen(buffer) + 1];
		strcpy(_path, buffer);
	}
	else {
		if(!ext)
			ext = ".lock";
		if(stat("/var/lock", &ino))
			snprintf(buffer, sizeof(buffer), "/tmp/.%s%s", name, ext);
		else
			snprintf(buffer, sizeof(buffer), "/var/lock/%s%s", name, ext);

		_path = new char[strlen(buffer) + 1];
		strcpy(_path, buffer);
	}

	for(;;) {
		fd = ::open(_path, O_WRONLY | O_CREAT | O_EXCL, 0660);
		if(fd > 0) {
			pid = getpid();
			snprintf(buffer, sizeof(buffer), "%d\n", pid);
			if(::write(fd, buffer, strlen(buffer)))
				rtn = false;
			::close(fd);
			return rtn;
		}
		if(fd < 0 && errno != EEXIST) {
			delete[] _path;
			return false;
		}

		fd = ::open(_path, O_RDONLY);
		if(fd < 0) {
			if(errno == ENOENT)
				continue;
			delete[] _path;
			return false;
		}

		sleep(2);

		status = ::read(fd, buffer, sizeof(buffer) - 1);
		if(status < 1) {
			::close(fd);
			continue;
		}

		buffer[status] = 0;
		pid = atoi(buffer);
		if(pid) {
			if(pid == getpid()) {
				status = -1;
				errno = 0;
			}
			else
				status = kill(pid, 0);

			if(!status || (errno == EPERM)) {
				::close(fd);
				delete[] _path;
				return false;
			}
		}
		::close(fd);
		::unlink(_path);
	}
}

void Lockfile::unlock(void)
{
	if(_path) {
		remove(_path);
		delete[] _path;
		_path = NULL;
	}
}

bool Lockfile::isLocked(void)
{
	if(_path)
		return true;

	return false;
}

#endif	// end __LINUX__

