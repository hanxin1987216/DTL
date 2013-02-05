// AbstractPersistance.cpp
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


#include "AbstractPersistance.h"


namespace rude{
namespace session{

AbstractPersistance::AbstractPersistance()
{
	d_error = "";
}

AbstractPersistance::~AbstractPersistance()
{

}


const char *AbstractPersistance::getError() const
{
	return d_error.c_str();
}

void AbstractPersistance::setError(const char *error)
{
	d_error = error ? error : "";
}



}} // end namespaces

