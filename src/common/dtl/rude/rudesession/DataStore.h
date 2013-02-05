// DataStore.h
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


#ifndef INCLUDED_DataStore_H
#define INCLUDED_DataStore_H

#include "AbstractData.h"
#include <map>
#include <vector>
#include <string>

namespace rude{
namespace session{


typedef std::vector<std::string> stringlist;

class DataStore: public AbstractData {

	bool d_ismodified; // "should save" flag. Starts out as 'false'
	std::string d_returnstring;
	std::map<std::string, stringlist> d_datamap;
	
public:

	
	DataStore();
	
	~DataStore();

	// Returns the number of Data Sets (the number of distinct names)
	//
	int getNumValues(); // returns number of names

	// Returns the number of data items associated with a particular name
	//
	int getNumValues(const char *name);

	// Returns the Nth distinct name
	//
	const char *getNameAt(int);

	// Returns the first data value of the Nth distinct name
	//
	const char *getValueAt(int); // returns first value

	// Wipes out all existing values associated with "name"
	// and sets the first value associated with "name" to "value"
	//
	void setValue(const char *name, const char *value); // replaces all old values

	// Appends a new value to the list of values associated with "name"
	//
	void addValue(const char *name, const char *value);

	// Returns the value of the Nth piece of data identified by "name"
	// If there is nodata identfied by name, or the index is out of bounds, 
	// returns the empty string.
	//
	const char *getValue(const char *name, int index);

	// shorthand for getValue(name, 0)
	// 
	const char *getValue(const char *name);

	// Returns true if there is any data associated with "name"
	//
	bool exists(const char *name) const;

	// Erases all data associated with "name"
	//
	void deleteValue(const char *name);

	// Erases the Nth value associated with "name"
	// If there is data after the Nth value, they are shifted over
	// (e.g. there are no holes left in the array of values)
	//
	const char * removeValue(const char *name, int index);

	// Erases all data
	//
	void clear();

	// Returns true if the data in the structure has changed
	//
	bool isModified();

	// Sets or clears the Modified Flag
	//
	void isModified(bool);

};

}} // end namespaces

#endif

