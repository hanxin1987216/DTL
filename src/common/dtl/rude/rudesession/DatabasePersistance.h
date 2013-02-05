// DatabasePersistance.h
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


#ifndef INCLUDED_DatabasePersistance_H
#define INCLUDED_DatabasePersistance_H


#include "AbstractPersistance.h"

#ifndef INCLUDED_STRING
#include <string>
#define INCLUDED_STRING
#endif

namespace rude{
namespace session{

class DatabasePersistance: public AbstractPersistance{

public:
	DatabasePersistance();
	~DatabasePersistance();

	virtual bool loadSession(MetaData&, DataStore&);
	virtual bool deleteSession(const char *id);
	virtual bool saveSession(MetaData&, DataStore&);
	virtual bool createSession(MetaData&, DataStore&);
	virtual bool purgeSessions();
};

}} // end namespaces

#endif


