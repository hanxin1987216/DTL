// implementation.cpp
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




#include "implementation.h"

#include "mysqlloaddll.h"


using namespace std;
using namespace rude::db;


namespace rude{
namespace db{


//////////////////////////////////////////
// Static Variable Definitions
//////////////////////////////////////////


//////////////////////////////////////////
// Static Method Definitions
//////////////////////////////////////////




char *Implementation::escape(const char *string, int length)
{
	char *retval = new char[length * 2 + 1];
	mysql_escape_string_c(retval,string,length);
	return retval;
}




//////////////////////////////////////////
// Constructors & Destructor
//////////////////////////////////////////




Implementation::Implementation(const char *username, const char *password, const char *server, int port, const char *database)
{
	d_error="";
	d_username = username ? username : "";
	d_password = password ? password : "";
	d_server = server ? server : "";
	d_port = port ? port : 3306;
	d_database = database ? database : "";


	d_connected = false;
	
	d_conn=0;
	d_result=0;
	d_row=0;
	
	d_simplereturn="";
}




Implementation::~Implementation()
{
	freeResult();
	disconnect();
}




//////////////////////////////////////////
// Instance Method Definitions
//////////////////////////////////////////




void Implementation::setError(const char * error)
{
	d_error = error ? error : "";
}




const char *Implementation::getError() const
{
	return d_error.c_str();
}




RUDEBOOL Implementation::connect()
{
	if(!d_connected)
	{
		MYSQL *initconn = mysql_init_c(0);
		if(initconn)
		{
			MYSQL * conn = mysql_real_connect_c(initconn, 
						d_server.c_str() , 
						d_username.c_str(), 
						d_password.c_str(), 
						d_database.c_str(), 
						d_port, 
						0,
						0);
			if(conn)
			{
				d_conn=conn;
				d_connected=true;
			}
			else
			{
				d_conn = 0;
				setError(mysql_error_c(initconn));
				mysql_close_c(initconn);
			}
		}
		else
		{
			setError("Conn was NULL");
		}
	}
	return d_connected;
}	




RUDEBOOL Implementation::disconnect()
{
	if(d_connected)
	{
		mysql_close_c(d_conn);
		d_connected = false;
		return true;
	}
	else
	{
		setError("Already Disconnected");
		return false;
	}
}




const char *Implementation::stat()
{
	if(d_connected)
	{
		return mysql_stat_c(d_conn);
	}
	else
	{
		return "Not Connected";
	}
}




RUDEBOOL Implementation::executeQuery(const char *query)
{
	if(query)
	{
		if(d_connected)
		{
			if( mysql_query_c(d_conn, query) == 0)
			{
				return true;
			}
			else
			{
				setError(mysql_error_c(d_conn));
			}
		}
		else
		{
			setError("Not Connected");
		}
	}
	else
	{
		setError("Query to be executed was NULL");
	}
	return false;
}




int Implementation::insertQuery(const char *query)
{
	if(query)
	{
		if(d_connected)
		{
			if( mysql_query_c(d_conn, query) == 0)
			{
				return mysql_insert_id_c(d_conn);
			}
			else
			{
				setError(mysql_error_c(d_conn));
			}
		}
		else
		{
			setError("Not Connected");
		}
	}
	else
	{
		setError("Query to be executed was NULL");
	}
	return 0;
}


const char *Implementation::singleValueQuery(const char *query)
{	


	if(query)
	{
		if(d_connected)
		{
			if( mysql_query_c(d_conn, query) == 0)
			{
				//get result set
				//
				MYSQL_RES *result = mysql_store_result_c(d_conn);
				if(result)
				{
					//get first row
					//
					MYSQL_ROW row;
					row = mysql_fetch_row_c(result);
					if(row)
					{
						if(row[0])
						{
							d_simplereturn = row[0];
						}
						else
						{
							// Got a NULL
							//
							d_simplereturn = "";
						}
						mysql_free_result_c(result);
						return d_simplereturn.c_str();
					}
					else
					{
						setError("Could not fetch row for single value query");
					} // end if row
					mysql_free_result_c(result);
				}
				else
				{
					setError(mysql_error_c(d_conn));
				} // end if result
			}
			else
			{
				setError(mysql_error_c(d_conn));
			}
		} 
		else
		{
			setError("Not Connected");
		}
	}
	else
	{
		setError("Query was NULL");
	}
	return 0;
}




RUDEBOOL Implementation::freeResult()
{
	if(d_result)
	{
		mysql_free_result_c(d_result);
		d_result = 0;
	}
	return true;
}


RUDEBOOL Implementation::nextRow()
{
	if(d_result)
	{
		d_row = mysql_fetch_row_c(d_result);
		if(d_row)
		{
			return true;
		}
		setError("No More Rows");
		return false;
	}
	else
	{
		// error should have been set already.....
		return false;
	}
}


const char *Implementation::column(int index)
{
	if(d_result !=0)
	{
		if(d_row != 0)
		{
			return d_row[ index ];
		}
		else
		{
			setError("No row to work with");
		}
	}
	else
	{
		setError("No Result to Work With");
	}
	return 0;


}




RUDEBOOL Implementation::storeResultQuery(const char *query)
{
	if(d_connected)
	{
		if(query)
		{
			if( mysql_query_c(d_conn, query) == 0)
			{
				//get result set
				d_result = mysql_store_result_c(d_conn);
				if(d_result)
				{
					return true;
				}
				else
				{
					setError(mysql_error_c(d_conn));
				}
			}
			else
			{
				setError(mysql_error_c(d_conn));
			}
		}
		else
		{
			setError("Query was NULL");
		}
	}
	return false;
}




RUDEBOOL Implementation::useResultQuery(const char *query)
{
	if(d_connected)
	{
		if(query)
		{
			if( mysql_query_c(d_conn, query) == 0)
			{
				d_result = mysql_use_result_c(d_conn);
				if(d_result)
				{
					return true;
				}
				else
				{
					setError(mysql_error_c(d_conn));
				}
			}
			else
			{
				setError(mysql_error_c(d_conn));
			}
		}
		else
		{
			setError("Query was NULL");
		}
	}
	// else error already set on connect();
	return false;
}


}} // end namespaces
