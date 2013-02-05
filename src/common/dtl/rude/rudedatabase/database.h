// database.h: interface for the database class.
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


#ifndef INCLUDED_DATABASE_H
#define INCLUDED_DATABASE_H


// Borland can choke on BOOLs
// so we convert to unsigned int on windows
//
#ifndef RUDE_DB_BOOL
#ifdef WIN32
typedef unsigned int RUDEBOOL;
#else
typedef bool RUDEBOOL;
#endif
#define RUDE_DB_BOOL
#endif

#ifndef	INCLUDED_MAP
#include <map>
#define INCLUDED_MAP
#endif

#ifndef INCLUDED_STRING
#include <string>
#define INCLUDED_STRING
#endif


namespace rude{

namespace db{
class Implementation;
}


class Database
{
	static std::map<std::string, Database*> s_databases;


	rude::db::Implementation *d_implementation; // Bridge
	
protected:
	//=
	// Database objects cannot be instantiated directly
	// Instead, call instance() to obtain a reference to the object. This component uses 
	// the Singleton design pattern to ensure global accessability and improve performance.
	// This architecture allows multiple parts of your program to access a particular database 
	// without having to worry about connecting or disconnecting to/from the database.  
	// If every section of your program needed to use a database and was responsible for 
	// connecting/disconnecting, then multiple connections would be opened and closed - consuming 
	// both resources and time.  Our architecture ensures that a connection is established 
	// once - and then only if necessary - and can be shared throughout the program.  Multiple 
	// contexts allow multiple connections to different databases or database accounts simultaneously.
	//=
	Database(db::Implementation *implementation);
	RUDEBOOL connect();
		
public:
	//=
	// Adds a database, username, password, server and port identified by <i>contextname</i>. 
	// The context name can be anything and is simply used as an identifier to the context.
	// After a context is added, the database represented by the context name can be obtained by
	// calling the Database::instance(contextname) method.
	// Any number of contexts can be added.  Each context should have a unique contextname.
	//= 
	static void addContext(	const char *contextname, 
									const char *database, 
									const char *username, 
									const char *password, 
									const char *server, 
									int port);
	
	//=
	// Escapes illegal characters within a string
	// This ensures that string or binary data won't mess up your queries.
	// You should escape all string data that can possibly be tainted 
	// (eg. you are not sure what is in it).
	// The caller (you) is responsible for deleting the resulting string.
	// 
	// <B>Note:</b> To avoid memory leaks, you <i>MUST</i> delete the resulting string. 
	// As such, the following sequence should always be followed when using this method:
	//
	// <code>
	// // 1. Obtain safe strings 
	// // ( as a static method, it can be called through an object or directly from the class )
	// //
	// const char *safe_string = database->escape( unsafe_string , strlen(unsafe_string) );
	// const char *safe_string2 = rude::Database::escape( another_string, strlen(another_string) );
	// 
	// // 2. ... use the safe strings
	// 
	// // 3. Delete the safe strings
	// //
	// delete [] safe_string
	// delete [] safe_string2
	// </code>
	//
	// <b>Example:</b>
	//
	//<code>
	// // Obtain database object
	// //
	// rude::Database *database = rude::Database::instance("stock");
	// 
	// const char *catname="A very ''' Awkward ===== Category Name !!'' \"\"\" ****** Indeed!!";
	// 
	// // Escape illegal characters in the new category name
	//	//
	// char *safe_name = database->escape( catname, strlen(catname));
	// 
	// // Build the SQL statement
	// // string / character data (whether escaped or not) should be surrounded by single quotes.
	// //
	//	std::string sqlstatement = "INSERT INTO tbl_category SET name='";
	//	sqlstatement += safe_name;
	//	sqlstatement += "'";
	// 
	// // REMEMBER to delete the escaped string
	// //
	//	delete [] safe_name;
	// 
	// // Perform the INSERT
	// //
	//	int newid = database->insertQuery(sqlstatement.c_str());
	//</code>
	// 
	//=
	static char *escape(const char *string, int length);
	
	//=
	// Returns the singleton database object for a given context
	//
	// <b>Example:</b>
	//
	// <code>
	// rude::Database *database = rude::Database::instance("context1");
	//
	// // use the database object...
	// </code>
	//=
	static Database *instance(const char *contextname);


	//=
	// Closes all open database connections
	// You can safely call this even if no connections were open and no instances were accessed.
	// We recommend that this method be called at the end of your main() method in any application 
	// that may use the database object.
	//=
	static void finish();


	//=
	// Returns the last known error
	//
	// <b>Example</b>
	// 
	// <code>
	// std::cout << database->getError() << "\n";
	// </code>
	//=
	const char *getError() const;
	
	//=
	// Returns MYSQL server status information
	//
	// <b>Example</b>
	//
	// <code>
	// std::cout << database->stat() << "\n";
	// </code>
	//
	//=
	const char *stat();
	
	//=
	// Sends a query that expects a result set (time friendly)
	// Obtains results from server all at once 
	// This is the faster alternative to calling useResultQuery(),
	// and is the preferred method when small result sets are expected. 
	// Returns false if an error occurs.
	// If it returns true, use nextRow() and column() to access the results.
	// If the first call to nextRow() returns false, then the result set is empty.
	// After you are done with the results, call freeResult() to free the system resources.
	//
	// <b>Example</b>
	//
	// <code>
	// if(database->storeResultQuery("SELECT username, password from tbl_users"))
	// {
	//    while(database->nextRow())
	//		{
	//			std::string username = database->column(0);
	//			std::string password = database->column(1);
	//       std::cout << "Username: << username << " Password: " << password << "\n";
	//		}
	//		database->freeResult();
	//	}
	//	else
	//	{
	//		std::cout << database->getError() << "\n";
	//	}
	// </code>
	//
	//=
	RUDEBOOL storeResultQuery(const char *query);


	//=
	// Sends a query that expects a result set (memory / network friendly)
	// Obtains results from server one row at a time 
	// This uses less memory and network resources than calling useResultQuery(),
	// and is the preferred method when large result sets are expected
	// Returns false if an error occurs.
	// If it returns true, use nextRow() and column() to access the results
	// If the first call to nextRow() returns false, then the result set is empty.
	// After you are done with the results, call freeResult() to free the system resources.
	// 
	// <b>Example</b>
	//
	// <code>
	// if(database->storeResultQuery("SELECT username, password from tbl_users"))
	// {
	//    while(database->nextRow())
	//		{
	//			std::string username = database->column(0);
	//			std::string password = database->column(1);
	//       std::cout << "Username: << username << " Password: " << password << "\n";
	//		}
	//		database->freeResult();
	//	}
	//	else
	//	{
	//		std::cout << database->getError() << "\n";
	//	}
	// </code>
	//
	//=
	RUDEBOOL useResultQuery(const char *query);


	//=
	// Selects the next row from query result set
	// Returns true if the next row is selected
	// Returns false if there are no more rows.
	// Must be called to get the first row.
	// 
	// <b>Example</b>
	//
	// <code>
	// if(database->storeResultQuery("SELECT category_name tbl_categories"))
	// {
	//    if(database->nextRow())
	//		{
	//			// We got some data back
	//			
	//			std::cout << "Current Categories:\n";
	//			do
	//			{
	//				std::cout << database->column(0) << "\n";
	//			}
	//			while(database->netxRow())
	//
	//		}
	//    else
	//		{
	//			// The result set was empty
	//
	//			std::cout << "There are no categories at this time\n";
	//		}
	//		database->freeResult();
	//	}
	//	else
	//	{
	//		std::cout << database->getError() << "\n";
	//	}
	// </code>
	//=
	RUDEBOOL nextRow();


	//=
	// Returns the value located at the specified column within the current row set
	// first index is 0.
	// will return NULL when out of range.
	// 
	// <b>Example</b>
	//
	// <code>
	// if(database->storeResultQuery("SELECT fname, lname, address, age from tbl_contacts"))
	// {
	//    while(database->nextRow())
	//		{
	//			const char *first_name = database->column(0);
	//			const char *last_name = database->column(1);
	//			const char *address = database->column(2);
	//			
	//			// convert the age to integer
	//			//
	//			int age = atoi( database->column(3) );
	//       
	//			// do stuff with data.....
	//
	//		}
	//		database->freeResult();
	//	}
	//	else
	//	{
	//		std::cout << database->getError() << "\n";
	//	}
	// </code>
	//
	//=
	const char *column(int index);


	//=
	// Frees resources consumed by a query result set
	// For every call to useResultQuery() or storeResultQuery() in your application, 
	// there should be an accompanying freeResult() call as well.
	//=
	RUDEBOOL freeResult();


	//=
	// Send a query that expects a single value result
	// Use this method when you expect a single value to be the result.
	// Returns c-string (const char *) representation of data if successful
	// Returns null if a result could not be obtained or an error occurs
	// <b>Example:</b>
	//
	// <code>
	// const char *username = db_database->singleValueQuery( "SELECT username form tbl_users where userid=348" );
	// if(username)
	// {
	//	   std::cout << "Username for givevn ID is " << username << "\n";
	// }
	// else
	// {
	//	   std::cout << "Userid 348 does not exist: " << db_database->getError() << "\n";
	// }
	// </code>	
	//=
	const char *singleValueQuery(const char *query);


	//=
	// Sends queries that do not return a result (UPDATE, DELETE, CREATE, INSERT, ALTER, etc...)
	// Returns true if successful, false otherwise.
	// NOTE: Use insertQuery() for INSERT's when you want to know the resulting insert-id.
	// 
	// <b>Example:</b>
	//
	// <code>
	// if( db_database->executeQuery( "DELETE FROM tbl_color WHERE color='blue'" ) )
	// {
	//	   std::cout << "Deleted the color blue"\n";
	// }
	// else
	// {
	//	   std::cout << db_database->getError() << "\n";
	// }
	// </code>	
	//=

RUDEBOOL executeQuery(const char *query);


	//=
	// Sends an INSERT query and returns the insert id
	// This is only applicable for tables with an AUTO_INCREMENT primary key.
	// For tables without an AUTO_INCREMENT primary key, use executeQuery() instead.
	// Returns 0 if an error occurs.
	// 
	// <b>Example:</b>
	//
	// <code>
	// if( int insertid = db_database->insertQuery( "INSERT INTO tbl_color SET color='blue'" ) )
	// {
	//	   std::cout << "Inserted a color with id of " << y << "\n";
	// }
	// else
	// {
	//	   std::cout << db_database->getError() << "\n";
	// }
	// </code>
	//=
	int insertQuery(const char *query);


	//=
	// 
	//=
	virtual ~Database();
};
}
#endif














