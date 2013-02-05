// AbstractPersistance.h
// Acts as the base Element that accepts visitors in the Visitor design pattern
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


#ifndef INCLUDED_AbstractPersistance_H
#define INCLUDED_AbstractPersistance_H

#include "MetaData.h"
#include "DataStore.h"

namespace rude{
namespace session{


class AbstractPersistance{

	std::string d_error;
	
protected:

	AbstractPersistance();
	void setError(const char *error);

public:

	virtual ~AbstractPersistance();
	virtual const char *getError() const;

	virtual bool loadSession(MetaData&, DataStore&) = 0;


	// Given a Session ID
	// delete all persistant data associated with it
	// such that subsequent searches for the session will fail.
	// 
	virtual bool deleteSession(const char *id) = 0;


	// Should preserve original data for:
	// 	Date Created
	//		Original IP
	//	
	//	Should update values for
	//		Max Inactive Interval
	//		Last IP
	//		Num Times Active
	//		IP Mask
	//		
	//	Should determine and update value for
	//		Date Last Accessed
	//
	// If datastore is modified, should update all data values
	// 
	virtual bool saveSession(MetaData&, DataStore&) = 0;


	virtual bool createSession(MetaData&, DataStore&) = 0;



	// If Configuration Setting for MaxSessionLength is non-zero,
	// then all sessions older than MaxSessionLength minutes must be deleted.
	//
	// If Configuration Setting for MaxNewSessionLength is non-zero,
	// then all new sessions older than MaxNewSessionLength minutes must be deleted
	//
	// If Configuration Setting for MaxInactiveInterval is non-zero,
	// then all sessions where TimeLastActive is greater than MaxInactiveInterval minutes must be deleted
	//
	// 
	virtual bool purgeSessions() = 0;
	
};


}} // end namespaces

#endif

