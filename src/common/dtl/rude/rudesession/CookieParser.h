// CookieParser.h
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


#ifndef INCLUDED_CookieParser_H
#define INCLUDED_CookieParser_H

#include <string>
#include <vector>

namespace rude{
namespace session{

class Cookie;

class CookieParser{

	std::vector<Cookie*> d_cookie_list;
	std::string d_error;
	
	void setError(const char *error);
	
public:

	CookieParser();
	~CookieParser();
	const char *getError();
	
	bool parseCookie(const char *http_cookie);

	int numCookies();
	Cookie *getCookie(int index);

};

}} // end namespaces

#endif

