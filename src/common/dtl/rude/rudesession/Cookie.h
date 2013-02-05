// Cookie.h
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


#ifndef INCLUDED_Cookie_H
#define INCLUDED_Cookie_H

#include <string>

namespace rude{
namespace session{

class Cookie{

	std::string d_name;
	std::string d_value;
	std::string d_domain;
	std::string d_path;
	bool d_shouldDiscard;
	bool d_isSecure;
	std::string d_port;
	int d_maxAge;
	std::string d_comment;
	std::string d_commentURL;
	std::string d_cookieHeader;


public:

	Cookie();
	~Cookie();
	
	const char * cookieHeader();
	const char * cookie2Header();

	void setName(const char *name);
	const char *getName();

	void setValue(const char *value);
	const char *getValue();

	void setDomain(const char *domain);
	const char *getDomain();
	
	void setPath(const char *path);
	const char * getPath();
	
	void setDiscard(bool shouldDiscard);
	bool getDiscard();
	
	void setSecure(bool isSecure);
	bool getSecure();
	
	void setPort(const char * port);
	const char * getPort();
	
	void setMaxAge(int seconds);
	int getMaxAge();
	
	void setComment(const char *comment);
	const char * getComment();
	
	void setCommentURL(const char *URL);
	const char * getCommentURL();
};

}} // end namespaces

#endif

