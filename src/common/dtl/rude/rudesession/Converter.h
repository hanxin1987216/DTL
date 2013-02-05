// Converter.h
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


#ifndef INCLUDED_Converter_H
#define INCLUDED_Converter_H

#include <string>

namespace rude{
namespace session{

class Converter{

	static std::string s_result;

protected:

	Converter();

public:

	~Converter();

	static int stringToInt(const char *);
	static double stringToDouble(const char *);
	static bool stringToBool(const char *);
	static char* stringToBinary(const char *, int &outlength);

	static const char * intToString(int x);
	static const char * doubleToString(double x);
	static const char * boolToString(bool x);
	static const char * binaryToString(const char *, int length);

};

}} // end namespaces

#endif

