// implementation.h
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



#ifndef INCLUDED_RUDE_DATABASE_IMPLEMENTATION_H
#define INCLUDED_RUDE_DATABASE_IMPLEMENTATION_H


#ifndef INCLUDED_STRING
#include <string>
#define INCLUDED_STRING
#endif


#ifndef WIN32
#ifndef INCLUDED_MYSQL_H
#include <mysql.h>
#define INCLUDED_MYSQL_H
#endif
#endif

// These header files need to be included last,
// for some odd reason...
//
#ifdef WIN32
#include "my_global.h"
#include "mysql.h"
#endif

#ifndef RUDE_DB_BOOL
#ifdef WIN32
typedef unsigned int RUDEBOOL;
#else
typedef bool RUDEBOOL;
#endif
#define RUDE_DB_BOOL
#endif


namespace rude{
namespace db{


class Implementation 
{
	std::string d_username;
	std::string d_password;
	std::string d_server;
	std::string d_database;
	int d_port;


	std::string d_error;


	RUDEBOOL d_connected;
	
	MYSQL *d_conn;
	MYSQL_RES *d_result;
	MYSQL_ROW d_row;
	std::string d_simplereturn; // stores simple return data...
	
protected:
	
	void setError(const char * error);
public:


	static char *escape(const char *string, int length);


	
	Implementation(const char *username, 
						const char *password, 
						const char *server, 
						int port, 
						const char *database);
	
	~Implementation();
	
	RUDEBOOL connect();
	RUDEBOOL disconnect();
	
	const char *stat();
	const char *getError() const;


	RUDEBOOL executeQuery(const char *query);
	const char *singleValueQuery(const char *query);
	int insertQuery(const char *query);


	RUDEBOOL storeResultQuery(const char *query);
	RUDEBOOL useResultQuery(const char *query);


	RUDEBOOL nextRow();
	const char *column(int index);
	RUDEBOOL freeResult();
};


}} // end namespaces


#endif


