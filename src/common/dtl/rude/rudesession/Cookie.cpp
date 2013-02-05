// Cookie.cpp
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

#include "Cookie.h"

#include <stdio.h>

namespace rude{
namespace session{

// TODO - portlist is comma separated value - so it should be string instead of int...

	Cookie::Cookie()
	{
		d_name="";
		d_value="";
		d_domain="";
		d_path="";
		d_shouldDiscard=false;
		d_isSecure=false;
		d_port="";
		d_maxAge=0;
		d_comment="";
		d_commentURL="";
		d_cookieHeader="";
	}
	
	Cookie::~Cookie()
	{

	}

	// Cookie Header omits Port, CommentURL, Discard
	// Only has semi-colon bewteen attributes, not at end of list...
	// RFC 2109
	//
	const char * Cookie::cookieHeader()
	{
		if(d_name != "")
		{
			d_cookieHeader="Set-Cookie: ";
			d_cookieHeader += d_name;
			d_cookieHeader += "=";
			d_cookieHeader += d_value;
			//d_cookieHeader += "; Version=1";
			if(d_domain != "")
			{
				d_cookieHeader += "; domain=";
				// prepend a dot to the domain...
				if(d_domain[0] != '.')
				{
					d_cookieHeader += ".";
				}
				d_cookieHeader += d_domain;
			}
			if(d_path != "")
			{
				d_cookieHeader += "; path=";
				d_cookieHeader += d_path;
			}
			if(d_maxAge != 0 || d_value == "")
			{
				char buffer[10];
				sprintf(buffer, "%d", d_maxAge);
				d_cookieHeader += "; Max-Age=";
				d_cookieHeader += buffer;
				d_cookieHeader += "; expires=Sun, 13-Jan-1980 10:00:00 GMT";
			}
			if(d_isSecure)
			{
				d_cookieHeader += "; Secure";
			}
			if(d_comment != "")
			{
				d_cookieHeader += "; Comment=\"";
				d_cookieHeader += d_comment;
				d_cookieHeader += "\"";
			}
			d_cookieHeader += "\n";
			return d_cookieHeader.c_str();
		}
		else
		{
			return "";
		}
	}
	const char * Cookie::cookie2Header()
	{
		if(d_name != "")
		{
			d_cookieHeader="Set-Cookie2: ";
			d_cookieHeader += d_name;
			d_cookieHeader += "=\"";
			d_cookieHeader += d_value;
			d_cookieHeader += "\"; Version=\"1\"";
			if(d_domain != "")
			{
				d_cookieHeader += "; Domain=\"";
				// prepend a dot to the domain...
				if(d_domain[0] != '.')
				{
					d_cookieHeader += ".";
				}
				d_cookieHeader += d_domain;
				d_cookieHeader += "\"";
			}
			if(d_path != "")
			{
				d_cookieHeader += "; Path=\"";
				d_cookieHeader += d_path;
				d_cookieHeader += "\"";
			}
			if(d_port != "")
			{
				d_cookieHeader += "; Port=\"";
				d_cookieHeader += d_port;
				d_cookieHeader += "\"";
			}
			if(d_maxAge != 0)
			{
				char buffer[10];
				sprintf(buffer, "%d", d_maxAge);
				d_cookieHeader += "; Max-Age=\"";
				d_cookieHeader += buffer;
				d_cookieHeader += "\"";
			}
			if(d_shouldDiscard)
			{
				d_cookieHeader += "; Discard";
			}
			
			if(d_isSecure)
			{
				d_cookieHeader += "; Secure";
			}
			if(d_comment != "")
			{
				d_cookieHeader += "; Comment=\"";
				d_cookieHeader += d_comment;
				d_cookieHeader += "\"";
			}
			if(d_commentURL != "")
			{
				d_cookieHeader += "; CommentURL=\"";
				d_cookieHeader += d_commentURL;
				d_cookieHeader += "\"";
			}
			d_cookieHeader += "\n";
			return d_cookieHeader.c_str();
		}
		else
		{
			return "";
		}
	}

	void Cookie::setName(const char *name)
	{
		d_name = name ? name : "";
	}
	
	const char *Cookie::getName()
	{
		return d_name.c_str();
	}
	
	void Cookie::setValue(const char *value)
	{
		d_value = value ? value : "";
	}
	
	const char *Cookie::getValue()
	{
		return d_value.c_str();
	}
	
	void Cookie::setDomain(const char *domain)
	{
		d_domain = domain ? domain : "";
	}
	
	const char *Cookie::getDomain()
	{
		return d_domain.c_str();
	}
	
	void Cookie::setPath(const char *path)
	{
		d_path = path ? path : "";
	}
	
	const char * Cookie::getPath()
	{
		return d_path.c_str();
	}
	
	void Cookie::setDiscard(bool shouldDiscard)
	{
		d_shouldDiscard = shouldDiscard;
	}
	
	bool Cookie::getDiscard()
	{
		return d_shouldDiscard;
	}
	
	void Cookie::setSecure(bool isSecure)
	{
		d_isSecure = isSecure;
	}
	
	bool Cookie::getSecure()
	{
		return d_isSecure;
	}
	
	void Cookie::setPort(const char * port)
	{
		d_port =   port  ? port : "";
	}
	
	const char * Cookie::getPort()
	{
		return d_port.c_str();
	}
	
	void Cookie::setMaxAge(int seconds)
	{
		d_maxAge = (seconds > 0) ? seconds : 0;
	}
	int Cookie::getMaxAge()
	{
		return d_maxAge;
	}
	
	void Cookie::setComment(const char *comment)
	{
		d_comment = comment ? comment : "";
	}
	
	const char * Cookie::getComment()
	{
		return d_comment.c_str();
	}
	
	void Cookie::setCommentURL(const char *URL)
	{
		d_commentURL = URL ? URL : "";
	}
	const char * Cookie::getCommentURL()
	{
		return d_commentURL.c_str();
	}
}} // end namespaces

