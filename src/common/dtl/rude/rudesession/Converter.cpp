// Converter.cpp
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

#include "Converter.h"

#include "Base64Encoder.h"
#include <stdio.h>
#include <stdlib.h>

namespace rude{
namespace session{


std::string Converter::s_result="";



Converter::Converter()
{}

Converter::~Converter()
{}

int Converter::stringToInt(const char *value)
{
	return atoi(value);
}

double Converter::stringToDouble(const char *value)
{
	return atof(value);
}

bool Converter::stringToBool(const char *value)
{
		// Values that mean true:
		// yes, on, true, 1
			
		// Values that mean false:
		// no, off, false, 0

		switch(value[0])
		{
			case 't':
				return true;
			case 'T':
				return true;
			case 'y':
				return true;
			case 'Y':
				return true;
			case '1':
				return true;
			case 'o':
				if(value[1] == 'n' || value[1] == 'N')
				{
					return true;
				}
				break;	
			case 'O':
				if(value[1] == 'n' || value[1] == 'N')
				{
					return true;
				}
				break;
			default:
				return false;
		}
		return false;
}

const char * Converter::intToString(int x)
{
	char buffer[30];
	sprintf(buffer, "%d", x);
	s_result = buffer;
	return s_result.c_str();
}

const char * Converter::doubleToString(double x)
{
	char buffer[30];
	sprintf(buffer, "%f", x);
	s_result = buffer;
	return s_result.c_str();
}

const char * Converter::boolToString(bool x)
{
	const char *boolvalue = x ? "true" : "false";
	return boolvalue;
}

char* Converter::stringToBinary(const char *value, int &outlength)
{
	char *decoded = Base64Encoder::decode(value, outlength);
	return decoded;
}

const char * Converter::binaryToString(const char *data, int length)
{
	char * encoded = Base64Encoder::encode(data, length);
	s_result = encoded;
	delete [] encoded;
	return s_result.c_str();
}



}} // end namespaces

