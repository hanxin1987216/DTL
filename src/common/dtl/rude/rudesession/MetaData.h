// MetaData.h
//
// Copyright (C) 2005 Matthew Flood
// See file AUTHORS for contact information
//
// This file is part of RudeSession.
//
// RudeSession is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2, or (at your option)
// any later version.
// 
// RudeSession is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with RudeSession; (see COPYING) if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
// 02111-1307, USA.
//------------------------------------------------------------------------


#ifndef INCLUDED_MetaData_H
#define INCLUDED_MetaData_H

#include "AbstractData.h"

#ifndef INCLUDED_STRING
#include <string>
#define INCLUDED_STRING
#endif

namespace rude{
namespace session{

class MetaData: public AbstractData {

	std::string d_sessionid;
	std::string d_original_ip;
	std::string d_last_ip;
	
	long d_creationtime;
	long d_lastaccessed;

	int d_maxinactiveinterval;
	int d_maxsessionlength;
	int d_numtimesactive;
	int d_ipmask;
	
	bool d_ismodified; // should save flag
	bool d_isnew; // 
	bool d_isreadonly; 

	bool d_sidfromcookie;

public:

	MetaData();
	~MetaData();

	bool update();

	const char *getId() const;
	void setID(const char *id);

	// Returns dotted octets
	//
	const char *getOriginalIP() const;
	void setOriginalIP(const char *ip);

	// Returns IP address as dotted octet
	//
	const char *getLastIP() const;
	void setLastIP(const char *ip);

	bool isNew() const;
	void isNew(bool isit);

	bool isModified() const;
	void isModified(bool isit);

	bool isReadOnly() const;
	void isReadOnly(bool isit);

	int getMaxInactiveInterval() const;
	void setMaxInactiveInterval(int minutes);

	int getMaxSessionLength() const;
	void setMaxSessionLength(int minutes);

	int getIPMask() const;
	void setIPMask(int maskbits);

	long getCreationTime() const;
	void setCreationTime(long t);
	
	long getLastAccessedTime() const;
	void setLastAccessedTime(long t);
	
	int getNumTimesActive() const;
	void setNumTimesActive(int numtimes);

};

}} // end namespaces

#endif

