// Configuration.cpp
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


#include "Configuration.h"

namespace rude{
namespace session{

std::string 	Configuration::s_path="/";
std::string 	Configuration::s_domain="";
bool 				Configuration::s_discard=true;
int 				Configuration::s_maxsessionlength=43200;
int 				Configuration::s_maxnewsessionlength=300;
int 				Configuration::s_maxinactiveinterval=3600;
std::string		Configuration::s_port="";
bool 				Configuration::s_secure=false;
std::string 	Configuration::s_comment="";
std::string 	Configuration::s_commenturl="";
std::string 	Configuration::s_sessiondir="";
std::string 	Configuration::s_databasecontext="";
bool				Configuration::s_usecookies=true;
int 				Configuration::s_maxsessions=0;
std::string		Configuration::s_urlidentifier="SESSIONID";
std::string		Configuration::s_cookieidentifier="RUDESESSIONID";
std::string		Configuration::s_persistancemethod="database";
int 				Configuration::s_ipmask=0;
bool				Configuration::s_debugmode=false;

void Configuration::setMaxSessions(int num)
{
	s_maxsessions = (num > 0) ? num : 0;
}

int Configuration::getMaxSessions()
{
	return s_maxsessions;
}

void Configuration::setDefaultIPMask(int maskbits)
{
	if(maskbits < 0)
	{
		s_ipmask = 0;
	}
	else if(maskbits > 32)
	{
		s_ipmask = 32;
	}
	else
	{
		s_ipmask = maskbits;
	}
}
	
int Configuration::getDefaultIPMask()
{
	return s_ipmask;
}

bool Configuration::setPersistanceMethod(const char *method)
{
	std::string temp = method ? method : "";
	s_persistancemethod = method ? method : "";
	if(temp == "config" || temp == "database")
	{
		s_persistancemethod = temp;
		return true;
	}
	return false;
}

const char *Configuration::getPersistanceMethod()
{
	return s_persistancemethod.c_str();
}

void Configuration::setCookieIdentifer(const char *name)
{
    // if this isn't set, then cookies will not be sent to the client!!
	 //
	s_cookieidentifier = name ? name : "";
}

const char *Configuration::getCookieIdentifier()
{
	return s_cookieidentifier.c_str();
}

void Configuration::setURLIdentifier(const char *name)
{
	s_urlidentifier = name ? name : "SESSIONID";
}

const char *Configuration::getURLIdentifier()
{
	return s_urlidentifier.c_str();
}

void Configuration::useCookies(bool useCookies)
{
	s_usecookies = useCookies;
}

bool Configuration::useCookies()
{
	return s_usecookies;
}

void Configuration::setPath(const char *path)
{
	s_path = path ? path : "";
}

const char *Configuration::getPath()
{
	return s_path.c_str();
}
	
void Configuration::setDomain(const char *domain)
{
	s_domain = domain ? domain : "";
}

const char *Configuration::getDomain()
{
	return s_domain.c_str();
}

void Configuration::setDiscard(bool shouldDiscard)
{
	s_discard = shouldDiscard;
}

bool Configuration::getDiscard()
{
	return s_discard;
}
	
void Configuration::setMaxSessionLength(int minutes)
{
	s_maxsessionlength = ( minutes > 0) ? minutes : 0;
}

int Configuration::getMaxSessionLength()
{
	return s_maxsessionlength;
}
	
void Configuration::setMaxNewSessionLength(int minutes)
{
	s_maxnewsessionlength = ( minutes > 0) ? minutes : 0;
}

int Configuration::getMaxNewSessionLength()
{
	return s_maxnewsessionlength;
}
	
void Configuration::setMaxInactiveInterval(int minutes)
{
	s_maxinactiveinterval = ( minutes > 0) ? minutes : 0;
}

int Configuration::getMaxInactiveInterval()
{
	return s_maxinactiveinterval;
}
	
void Configuration::setPort(const char * port)
{
	s_port = port ? port : "";
}

const char * Configuration::getPort()
{
	return s_port.c_str();
}

void Configuration::setSecure(bool isSecure)
{
	s_secure = isSecure;
}

bool Configuration::getSecure()
{
	return s_secure;
}
	
void Configuration::setComment(const char *comment)
{
	s_comment = comment ? comment : "";
}

const char *Configuration::getComment()
{
	return s_comment.c_str();
}
	
void Configuration::setCommentURL(const char *url)
{
	s_commenturl = url ? url : "";
}

const char *Configuration::getCommentURL()
{
	return s_commenturl.c_str();
}	

void Configuration::setSessionDirectory(const char *path)
{
	s_sessiondir = path ? path : "";
}

const char *Configuration::getSessionDirectory()
{
	return s_sessiondir.c_str();
}
	
void Configuration::setDatabaseContext(const char *contextname)
{
	s_databasecontext = contextname ? contextname : "";
}

const char *Configuration::getDatabaseContext()
{
	return s_databasecontext.c_str();
}
	

void Configuration::setDebugMode(bool mode)
{
	s_debugmode = mode;
}

bool Configuration::getDebugMode()
{
	return s_debugmode;
}

}} // end namespaces

