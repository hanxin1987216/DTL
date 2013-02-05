// Configuration.h
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


#ifndef INCLUDED_Configuration_H
#define INCLUDED_Configuration_H


#ifndef INCLUDED_STRING
#include <string>
#define INCLUDED_STRING
#endif

namespace rude{
namespace session{

class Configuration{

	static std::string 	s_path;
	static std::string 	s_domain;
	static bool 			s_discard;
	static int 				s_maxsessionlength;
	static int 				s_maxnewsessionlength;
	static int 				s_maxinactiveinterval;
	static std::string 	s_port;
	static bool 			s_secure;
	static std::string 	s_comment;
	static std::string 	s_commenturl;
	static std::string 	s_sessiondir;
	static std::string 	s_databasecontext;
	static bool				s_usecookies;
	static int 				s_maxsessions;
	static std::string	s_urlidentifier;
	static std::string	s_cookieidentifier;
	static std::string	s_persistancemethod;
	static int 				s_ipmask;
	static bool				s_debugmode;
protected:

	Configuration(){};
	
public:

	static bool setPersistanceMethod(const char *method);
	static const char *getPersistanceMethod();

	static void setMaxSessions(int num);
	static int getMaxSessions();

	static void setCookieIdentifer(const char *name);
	static const char *getCookieIdentifier();

	static void setURLIdentifier(const char *name);
	static const char *getURLIdentifier();

	static void useCookies(bool useCookies);
	static bool useCookies();

	static void setPath(const char *path);
	static const char *getPath();
	
	static void setDomain(const char *domain);
	static const char *getDomain();
	
	static void setDiscard(bool shouldDiscard);
	static bool getDiscard();
	
	static void setMaxSessionLength(int minutes);
	static int getMaxSessionLength();
	
	static void setMaxNewSessionLength(int minutes);
	static int getMaxNewSessionLength();
	
	static void setMaxInactiveInterval(int minutes);
	static int getMaxInactiveInterval();
	
	static void setPort(const char *port);
	static const char * getPort();
	
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

	static void setDefaultIPMask(int maskbits);
	static int getDefaultIPMask();

	static void setDebugMode(bool mode);
	static bool getDebugMode();

	~Configuration(){};
};

}} // end namespaces

#endif

