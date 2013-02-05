// database.cpp: interface for the database class.
//
// Copyright (C) 2002, 2003, 2004, 2005 Matthew Flood
// See file AUTHORS for contact information
//
// This file is part of RudeDatabase.
//
// RudeDatabase is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2, or (at your option)
// any later version.
// 
// RudeDatabase is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with RudeDatabase; (see COPYING) if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
// 02111-1307, USA.
//------------------------------------------------------------------------


#include "database.h"


#ifndef INCLUDED_IMPLEMENTATION_H
#include "implementation.h"
#endif

#ifndef INCLUDED_STRING
#include <string>
#define INCLUDED_STRING
#endif

namespace rude{


std::string invalid_context = "Invalid Context";


std::map<std::string, Database*> Database::s_databases;



//////////////////////////////////////////////////////////
// Static Method definitions
//////////////////////////////////////////////////////////
Database *Database::instance(const char* contextname)
{
	std::string context=contextname? contextname: "";
	Database *database = s_databases[context];
	
	if(!database)
	{
		invalid_context = "Invalid Context '";
		invalid_context += context;
		invalid_context += "'";
		
		// The context they asked for does not exist!!!
		// pretend it does exist, (create a new database)
		// but give it an empty (NULL) implementation
		//
		database = new Database(0);


		// add it to map so other calls to same context are handled
		// without having to re-create object.
		//
		s_databases[context]=database;
	}
	
	// Database should connect here if it is not already connected!!!!
	//
	database->connect();


	return database;
}


void Database::finish()
{
	std::map<std::string, Database*>::iterator iter;
	for(iter = s_databases.begin(); iter != s_databases.end(); iter ++)
	{
		Database *d = (*iter).second;
		if(d)
		{
			delete d;
		}
	}
	s_databases.clear();
}


void Database::addContext(const char *contextname, const char *databasename, 
	const char *username, const char *password, const char *server, int port)
{
	// Database should not connect here!!!!
	//
	
	rude::db::Implementation *implementation = new rude::db::Implementation(  username, 
																			password, 
																			server, 
																			port, 
																			databasename);
	Database *newdatabase = new Database(implementation);
	std::string context=contextname ? contextname : "";


	// if we are replacing existing contexts, we
	// need to delete the old database objects first.
	//
	Database *olddatabase = s_databases[context];
	if(olddatabase)
	{
		delete olddatabase;
	}
	s_databases[context]=newdatabase;
}


char *Database::escape(const char *oldstring, int length)
{
	return rude::db::Implementation::escape(oldstring, length);
}


/////////////////////////////////////////////////////////
// Constructors & Destructors
/////////////////////////////////////////////////////////


Database::Database(rude::db::Implementation *implementation)
{
	d_implementation = implementation;
}


Database::~Database()
{	
	// If database is connected, 
	// deleting implementation should disconnect....
	//
	if(d_implementation)
	{
		delete d_implementation;
		d_implementation=0;
	}
}


//////////////////////////////////////////////////////////
// Instance Method Definitions
//////////////////////////////////////////////////////////


const char *Database::getError() const
{
	return d_implementation ? d_implementation->getError() : invalid_context.c_str();
}


const char *Database::stat()
{
	return d_implementation ? d_implementation->stat() : invalid_context.c_str();
}


RUDEBOOL Database::storeResultQuery(const char *query)
{
	return d_implementation ? d_implementation->storeResultQuery(query) : false;
}
	
RUDEBOOL Database::useResultQuery(const char *query)
{	
	return d_implementation ? d_implementation->useResultQuery(query) : false;
}


RUDEBOOL Database::nextRow()
{
	return d_implementation ? d_implementation->nextRow() : false;
}


RUDEBOOL Database::connect()
{
	return d_implementation ? d_implementation->connect() : false;
}


const char *Database::column(int index)
{
	return d_implementation ? d_implementation->column(index) : 0;
}


RUDEBOOL Database::freeResult()
{
	return d_implementation ?  d_implementation->freeResult() : false;
}


const char *Database::singleValueQuery(const char *query)
{
	return d_implementation ? d_implementation->singleValueQuery(query) : 0;
}


RUDEBOOL Database::executeQuery(const char *query)
{
	return d_implementation ? d_implementation->executeQuery(query) : false;
}


int Database::insertQuery(const char *query)
{
	return d_implementation ? d_implementation->insertQuery(query) : 0;
}





} // end namespace


