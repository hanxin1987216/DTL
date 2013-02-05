// CookieReader.h
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


#ifndef INCLUDED_CookieReader_H
#define INCLUDED_CookieReader_H

#include "CookieParser.h"

#include <string>
#include <vector>

namespace rude{
namespace session{

class CookieReader{

	CookieParser d_parser;
	std::string d_path;
	std::string d_domain;
	
public:

	CookieReader();
	~CookieReader();

	void setPath(const char *path);
	void setDomain(const char *domain);
	const char *getValue(const char *name);

};

}} // end namespaces

#endif

