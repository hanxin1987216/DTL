// Session.h
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


#ifndef INCLUDED_SESSION_H
#define INCLUDED_SESSION_H

namespace rude{

namespace session{
class Implementation;
}

class Session{

	static Session *s_instance;

	session::Implementation * d_implementation;

protected:

	Session(session::Implementation * implementation);

public:

	~Session();

////////////////////////////////
// Configuration
////////////////////////////////

	static void setPath(const char *path);
	static const char *getPath();

	static void setDomain(const char *domain);
	static const char *getDomain();

	static void setDiscard(bool shouldDiscard);
	static bool getDiscard();

	static void setMaxSessions(int num);
	static int getMaxSessions();

	static void setMaxSessionLength(int minutes);
	static int getMaxSessionLength();

	static void setMaxNewSessionLength(int minutes);
	static int getMaxNewSessionLength();

	static void setDefaultMaxInactiveInterval(int minutes);
	static int getDefaultMaxInactiveInterval();

	static void setPort(const char *port);
	static const char *getPort();

	static void setSecure(bool isSecure);
	static bool getSecure();

	static void setComment(const char *comment);
	static const char *getComment();

	static void setCommentURL(const char *url);
	static const char *getCommentURL();

	static void setSessionDirectory(const char *path);
	static const char *getSessionDirectory();

	static void setDatabaseContext(const char *contextname);
	static const char *getDatabaseContext();

	static bool setPersistanceMethod(const char *method);
	static const char *getPersistanceMethod();

	static void setCookieIdentifer(const char *name);
	static const char *getCookieIdentifier();

	static void setURLIdentifier(const char *name);
	static const char *getURLIdentifier();

	static void useCookies(bool useCookies);
	static bool useCookies();

	static void setDefaultIPMask(int maskbits);
	static int getDefaultIPMask();

   static void setDebugMode(bool mode);
	static bool getDebugMode();
	
////////////////////////////////
// Static Methods
////////////////////////////////
	static Session * getSession();
	static Session * getSession(const char *id);
	static Session * getSession(bool shouldCreate);
	static const char *getError();

////////////////////////////////
// Instance Methods
////////////////////////////////

	bool terminate();
	bool save();
	bool isNew();
	
	const char *getSessionID();
	const char *getId(); // deprecated version of above method...
	bool generateNewSessionID();

	
////////////////////////////////
// Instance Configuration Methods
////////////////////////////////

	long getCreationTime();
	long getLastAccessedTime();
	const char *getOriginalIP();
	const char *getLastIP();
	int getNumTimesActive();
	void setMaxInactiveInterval(int minutes);
	int getMaxInactiveInterval();
	int getIPMask();
	void setIPMask(int maskbits);


////////////////////////////////
// Data Methods
////////////////////////////////

	bool exists(const char *name);

	int getNumValues();
	int getNumValues(const char *name);
	
	const char *getNameAt(int);
	const char *getValueAt(int);

	void setValue(const char *name, const char *value);
	const char *getValue(const char *name);

	void addValue(const char *name, const char *value);
	const char *getValue(const char *name, int index);

	void setStringValue(const char *name, const char *value);
	const char *getStringValue(const char *name);

	void setIntValue(const char *name, int value);
	int getIntValue(const char *name);

	void setDoubleValue(const char *name, double value);
	double getDoubleValue(const char *name);

	void setBoolValue(const char *name, bool value);
	bool getBoolValue(const char *name);

	void setBinaryValue(const char *name, const char *data, int length);
	char *getBinaryValue(const char *name, int &outlength);

	void deleteValue(const char *name);
	const char * removeValue(const char *name, int index);

	void clear();


};

}

#endif
