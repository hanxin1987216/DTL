// Implementation.h
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


#ifndef INCLUDED_Implementation_H
#define INCLUDED_Implementation_H


#include "MetaData.h"
#include "DataStore.h"

#include <string>
#include <map>




namespace rude{
namespace session{

class AbstractPersistance;


class Implementation{

	static std::string s_error;
	bool d_isreadonly;
	MetaData d_metadata;
	DataStore d_datastore;
	AbstractPersistance *d_persistance;


protected:

	// done
	static void setError(const char *error);


public:

	Implementation();
	~Implementation();


	//////////////////
	// Global
	///////////////////


	// done
	static const char *getError();




	// TODO
	int purgeSessions();


	// done
	bool terminate();


	// done
	bool save();


	// done (should we save or just mark as modified?)
	bool update();


	// done (should we terminate expired?)
	bool validate();



bool createSession();
bool loadSession(const char *id);


	////////////////////
	// Must use instance
	/////////////////////


	bool generateNewSessionID();


	// done
	long getCreationTime();


	// done
	long getLastAccessedTime();


	// done
	const char *getOriginalIP();


	// done
	const char *getLastIP();


	// done
	int getNumTimesActive();


	// done
	const char *getId();


	// done
	void setMaxInactiveInterval(int minutes);


	// done
	int getMaxInactiveInterval();


	// done
	int getIPMask();


	// done
	void setIPMask(int maskbits);


	// done
	bool isNew();




////////////////////////////////
// Data Methods
////////////////////////////////

	bool exists(const char *name);

	int getNumValues();
	int getNumValues(const char *name);
	
	const char *getNameAt(int);
	const char *getValueAt(int);

	void setValue(const char *name, const char *value);
	const char *getValue(const char *name);

	void addValue(const char *name, const char *value);
	const char *getValue(const char *name, int index);

	void deleteValue(const char *name);
	const char * removeValue(const char *name, int index);

	void clear();
};


}}


#endif
