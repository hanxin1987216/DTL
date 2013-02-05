// IDGenerator.cpp
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

#include "IDGenerator.h"


#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <string>

#include "Base64Encoder.h"


namespace rude{
namespace session{

std::string IDGenerator::s_returnvalue="";

const char *  IDGenerator::generateID(int keylength)
{
   if(keylength <=0)
	{
      return "";
	}
	char *id = new char[keylength];
	long int myseed = getpid() * time(0);
	srandom(myseed);
	FILE *fh;
	fh = fopen("/dev/urandom", "r");
	if(fh)
	{
		for(int x=0; x< keylength; x++)
		{
			id[x++]=(int) fgetc(fh);
			id[x] = random() %256;
		}
	}
	else
	{
		for(int x=0; x< keylength; x++)
		{
			id[x] = random() %256;
		}
	}
	char * encoded = Base64Encoder::encode(id, keylength);
	s_returnvalue=encoded;

	delete [] id;
	delete [] encoded;
	
	s_returnvalue = s_returnvalue.substr(0,keylength);
	// base64 provides +, = and / characters, which we should escape
	for(int x=0; x < keylength; x++)
	{
		if(s_returnvalue[x] == '/')
		{
			s_returnvalue[x] = '_';
		}
		else if(s_returnvalue[x] == '=')
		{
			s_returnvalue[x] = '_';
		}
		else if(s_returnvalue[x] == '+')
		{
			s_returnvalue[x] = '_';
		}
	}
	return s_returnvalue.c_str();
}

}} // end namespaces

