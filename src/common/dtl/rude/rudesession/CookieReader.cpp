// CookieReader.cpp
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

#include "CookieReader.h"

#include "Cookie.h"
#include "Configuration.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

namespace rude{
namespace session{

CookieReader::CookieReader()
{
	d_path="";
	d_domain="";
	const char *http_cookie=getenv("HTTP_COOKIE");


	
	if(http_cookie != 0)
	{
		if(Configuration::getDebugMode())
		{
			cerr << "SESSION DEBUG: " << __FILE__ << __LINE__ << " HTTP_COOKIE='" << http_cookie << "'\n";
		}
		//cout << "<br/>PARSING '" << http_cookie << "'<br/>";
		if(!d_parser.parseCookie(http_cookie))
		{
			cerr << d_parser.getError() << "\n<br/>";
		}
	}
	else
	{
		if(Configuration::getDebugMode())
		{
			cerr << "SESSION DEBUG: " << __FILE__ << __LINE__ << " NO HTTP_COOKIE!!\n";
		}
	}
}
	
CookieReader::~CookieReader()
{

}
	
void CookieReader::setPath(const char *path)
{
	d_path = path ? path : "";
}

void CookieReader::setDomain(const char *domain)
{
	d_domain = domain ? domain : "";
}

const char *CookieReader::getValue(const char *name)
{
	if(Configuration::getDebugMode())
	{
		cerr << "SESSION DEBUG: " << __FILE__ << __LINE__ << " getValue('" << name << "')\n";
	}
	
	// This must return the last value it finds, instead
	// of the first value, in order to give the most specific cookie value
	// 

	int num=d_parser.numCookies();
	for(int x=num; x > 0; x--)
	{
		Cookie *c=d_parser.getCookie( x - 1 );
		string cookie_name=c->getName();
		if(Configuration::getDebugMode())
		{
			cerr << "SESSION DEBUG: " << __FILE__ << __LINE__ << " Found a Cookie name='" << cookie_name << "'\n";
		}
		if( cookie_name == name )
		{
			if(d_path == "" || d_path == c->getPath())
			{
				if(d_domain == "" || d_domain == c->getDomain())
				{
					return c->getValue();
				}
				else
				{
					if(Configuration::getDebugMode())
					{
						cerr << "SESSION DEBUG: " << __FILE__ << __LINE__ << "Cookie Domain was bad\n";
					}
				}
			}
			else
			{
				if(Configuration::getDebugMode())
				{
					cerr << "SESSION DEBUG: " << __FILE__ << __LINE__ << "Cookie Path was bad\n";
				}
			}
		}
		else
		{
			if(Configuration::getDebugMode())
			{
				cerr << "SESSION DEBUG: " << __FILE__ << __LINE__ << "Name did not match\n";
			}
		}
	}
	return "";
}

}} // end namespaces



































