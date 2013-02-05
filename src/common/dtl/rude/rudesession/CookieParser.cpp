// CookieParser.cpp
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

#include "CookieParser.h"

#include "Cookie.h"
#include <ctype.h>
#include <string.h>


using namespace std;

namespace rude{
namespace session{

	enum CookieParserState {RCOOKIE, RVER, RVER1, RVER2, RVER3, RVER4, RVER5, RC, RNAME, RNAME1, RVAL, RVAL1, RVAL2, RSEMI, RATT, RATT1, RATT2, RATT3, RATT4};

	CookieParser::CookieParser()
	{
 			d_error = "";
	}
	
	CookieParser::~CookieParser()
	{
		int num=d_cookie_list.size();
		for(int x=0; x< num; x++)
		{
			Cookie *c = d_cookie_list[x];
			delete c;
		}
	}
	
	void CookieParser::setError(const char *error)
	{
		d_error = error ? error : "";
	}

	const char *CookieParser::getError()
	{
		return d_error.c_str();
	}

	int CookieParser::numCookies()
	{
		return d_cookie_list.size();
	}
	
	Cookie *CookieParser::getCookie(int index)
	{
		if((unsigned int) index >= d_cookie_list.size())
		{
			return 0;
		}
		return d_cookie_list[index];
	}

	bool CookieParser::parseCookie(const char *http_cookie)
	{
		if(!http_cookie)
		{
			// should we allow this?
			//
			setError("Cookie was Null");
			return false;
		}
		
		int size = strlen(http_cookie);

		if(size == 0)
		{
			// should we allow this?
			//
			setError("Cookie was empty");
			return false;
		}

		CookieParserState state=RCOOKIE;
		int position=0;
		string version = "";
		string name="";
		string value="";
		string attname="";
		string attvalue="";
		
		Cookie * cookie=0;


		while(position < size)
		{
        char c = http_cookie[position];
		  //printf("Next Char: %c\n", c);
		  
		switch(state)
		{
			case RCOOKIE:
			{
				//printf("Case RCOOKIE\n");
				if(c == '$')
				{
					position++;
					state = RVER;
				}
				else if(isspace(c))
				{
					position++;
				}
				else
				{
					// We are reading from apache, which leaves out all 
					// Meta attributes, and presents a string of all cookies passed in
					// In the form 'name 1=value1; name2=value 2; name 1=value3 '
					// Notice that no quotes are used, and names can have spaces and be repeated
					// without any indication of what path / domain / port they are for
					// I believe the order of same - name attributes follows tge specs,
					// eg. more general come before less general.
					// These problems can be avoided as long as you set the
					// Cookies using a hard-coded general domain and path "/"
					//
					// read next cookie->..
					//
					state = RC;
				}
				break;
			}
			
			case RVER:
			{
				//printf("Case RVER\n");
				if(isspace(c))
				{
					position++;
				}
				else
				{
					// there must be at least 7 more characters
					//
					if( size - position < 6)
					{
							setError("Incomplete Cookie");
							return false;
					}
					else if(
						( http_cookie[position + 1] == 'V' || http_cookie[position + 1] == 'v')
						&&
						( http_cookie[position + 2] == 'E' || http_cookie[position + 2] == 'e')
						&&
						( http_cookie[position + 3] == 'R' || http_cookie[position + 3] == 'r')
						&&
						( http_cookie[position + 4] == 'S' || http_cookie[position + 4] == 's')
						&&
						( http_cookie[position + 5] == 'I' || http_cookie[position + 5] == 'i')
						&&
						( http_cookie[position + 6] == 'O' || http_cookie[position + 6] == 'o')
						&&
						( http_cookie[position + 7] == 'N' || http_cookie[position + 7] == 'n')
					)
					{
						position += 7;
						state = RVER1;
					}
					else
					{
						setError("Expected Version");
						return false;
					}
				}
				break;
			}

			
			case RVER1:
			{
				//printf("Case RVER1\n");
				if(isspace(c))
				{
					position++;
				}
				else if(c == '=')
				{
					position++;
					state = RVER2;
				}
				else
				{
					setError("Malformed Cookie, expected '=' after $Version");
					return false;
				}
				break;
			}

			
			case RVER2:
			{
				//printf("Case RVER2\n");
				if(isspace(c))
				{
					position++;
				}
				else if(c == '"')
				{
					position++;
					state = RVER4;
				}
				else
				{
					state = RVER3;
				}
				break;
			}
			
			case RVER3:
			{
				//printf("Case RVER3\n");
				if(c == ';')
				{
					state = RC;
					position++;
				}
				else
				{
					version += c;
					position++;
				}
				break;
			}
			
			case RVER4:
			{
				//printf("Case RVER4\n");
				if(c == '"')
				{
					state = RVER5;
					position++;
				}
				else
				{
					version += c;
					position++;
				}
				break;
			}
			
			case RVER5:
			{
				//printf("Case RVER5\n");
				if(isspace(c))
				{
					position++;
				}
				else if(c == ';')
				{
					position++;
					state = RC;
				}
				else
				{
					setError("Malformed Cookie - expected ';' after $Version");
					return false;
				}
				break;
			}
			
			case RC:
			{
				//printf("Case RC\n");
				cookie = new Cookie();
				d_cookie_list.push_back(cookie);
				state = RNAME;
				name="";
				value="";
				attname="";
				attvalue="";
				break;
			}
			
			case RNAME:
			{
				//printf("Case RNAME\n");
				if(isspace(c))
				{
					position++;
				}
				else
				{
					state = RNAME1;
				}
				break;
			}
			
			case RNAME1:
			{
				//printf("Case RNAME1\n");
				if(c == '=')
				{
					position++;
					// Strip Trailing Whitespace here...
					cookie->setName(name.c_str());
					state = RVAL;
				}
				else
				{
					name += c;
					position++;
				}
				break;
			}
			
			case RVAL:
			{
				//printf("Case RVAL\n");
				if(isspace(c))
				{
					position++;
				}
				else if(c == '"')
				{
					position++;
					state = RVAL2;
				}
				else
				{
					state = RVAL1;
				}
				break;
			}
			
			case RVAL1:
			{
				//printf("Case RVAL1\n");
            if(c == ';')
				{
					cookie->setValue(value.c_str());
					position++;
					state = RATT;
				}
				// The following was removed because original cookie values can contain anything
				// except the semi-colon. Which means we should consider stripping trailing whitespace
				// from the value - although it is safe to assume that it will never need to be done
				// because the browsers and apache will strip whitespace off for us.
				//
				// else if(isspace(c))
				// {
				//	 cookie->setValue(value.c_str());
				//	 position++;
				//	 state=RSEMI;
				// }
				else
				{
					value += c;
					position++;
					if(position == size)
					{
						// if we run out of letters, we need to capture the value or we'll fall out and lose it...
			    	   //
						// end of header
						//
						cookie->setValue(value.c_str());
					}
				}
				break;
			}
			
			case RVAL2:
			{
				//printf("Case RVAL2\n");
				if(c == '"')
				{
					position++;
					cookie->setValue(value.c_str());
					state = RSEMI;
				}
				else
				{
					value += c;
					position++;
				}
				break;
			}
			
			case RSEMI:
			{
				//printf("Case RSEMI\n");
				if(c == ';')
				{
					position++;
					state = RATT;
				}
				else if(isspace(c))
				{
					position++;
				}
				// The following block for the COMMA was added as a result of
				// researching apache's HTTP_COOKIE contents.
				else if(c == ',')
				{
					position++;
					state = RC;
				}
				else
				{
					// read next cookie->..
					//
					state = RC;
				}
				break;
			}
			
			case RATT:
			{
				//printf("Case RATT\n");
				if(c == '$')
				{
					position++;
					attname = "";
					attvalue = "";
					state = RATT1;
				}
				else if(isspace(c))
				{
					position++;
				}
				else
				{
					// Someone ended the cookie with a semi-colon! Dumb-ass!
					// read next cookie->..
					//
					state = RC;
				}
				break;
			}
			
			case RATT1:
			{
				//printf("Case RATT1\n");
				if(c == '=')
				{
					position++;
					state = RATT2;
				}
				else if(isspace(c))
				{
					//ignore whitespace
					position++;
				}
				else
				{
					if(islower(c))
					{
						c=toupper(c);
					}
					
					attname += c;
					position++;
				}
				break;
			}
			
			case RATT2:
			{
				//printf("Case RATT2\n");
				if(c == '"')
				{
					position++;
					state = RATT4;
				}
				else if(isspace(c))
				{
					//ignore whitespace
					position++;
				}
				else
				{
					state = RATT3;
				}
				break;
			}
			
			case RATT3:
			{
				//printf("Case RATT3\n");
            if(c == ';')
				{
					// PROCESS ATTRIBUTE
					//
					if(attname == "PATH")
					{
						cookie->setPath(attvalue.c_str());
					}
					else if(attname == "DOMAIN")
					{
						cookie->setDomain(attvalue.c_str());
					}
					else if(attname == "PORT")
					{
						cookie->setPort(attvalue.c_str());
					}
					else
					{
						// unknown attribute, ignore it..
					}
					position++;
					state = RATT;
				}
				else if(isspace(c))
				{
					// PROCESS ATTRIBUTE
					//
					if(attname == "PATH")
					{
						cookie->setPath(attvalue.c_str());
					}
					else if(attname == "DOMAIN")
					{
						cookie->setDomain(attvalue.c_str());
					}
					else if(attname == "PORT")
					{
						cookie->setPort(attvalue.c_str());
					}
					else
					{
						// unknown attribute, ignore it..
					}
					position++;
					state=RSEMI;
				}
				else
				{
					attvalue += c;
					position++;
					if(position == size)
					{
						// if we run out of letters, we need to capture the value or we'll fall out and lose it...
			    	   //
						// end of header
						//
						if(attname == "PATH")
						{
							cookie->setPath(attvalue.c_str());
						}
						else if(attname == "DOMAIN")
						{
							cookie->setDomain(attvalue.c_str());
						}
						else if(attname == "PORT")
						{
							cookie->setPort(attvalue.c_str());
						}
						else
						{
							// unknown attribute, ignore it..
						}
						cookie->setValue(value.c_str());
					}
				}
				break;
			}
			
			case RATT4:
			{
				//printf("Case RATT4\n");
				if(c == '"')
				{
					// PROCESS ATTRIBUTE
					//
					if(attname == "PATH")
					{
						cookie->setPath(attvalue.c_str());
					}
					else if(attname == "DOMAIN")
					{
						cookie->setDomain(attvalue.c_str());
					}
					else if(attname == "PORT")
					{
						cookie->setPort(attvalue.c_str());
					}
					else
					{
						// unknown attribute, ignore it..
					}
					position++;
					state = RSEMI;
				}
				else
				{
					attvalue += c;
					position++;
				}
				break;
			}
			default:
			{
				setError("Unknown State Reached");
				return false;
			}
		} // end switch
		} // end while position < size
		return true;
	}	


}} // end namespaces



































