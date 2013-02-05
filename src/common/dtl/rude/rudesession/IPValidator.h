// IPValidator.h
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


#ifndef INCLUDED_IPValidator_H
#define INCLUDED_IPValidator_H

namespace rude{
namespace session{

class IPValidator{

	static void dec2bin(int dec, char *bin, int pos);

public:

	// mask can be between 0 and 32
	//
	static bool validate(const char *goodip, const char *testip, int mask);
};

}} // end namespaces

#endif

