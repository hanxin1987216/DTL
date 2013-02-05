// DatabasePersistance.cpp
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


#include "DatabasePersistance.h"
#include "Configuration.h"
#include "../rudedatabase/database.h"
#include <string>

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


using namespace std;
using namespace rude;
using namespace rude::session;

namespace rude{
namespace session{

DatabasePersistance::DatabasePersistance()
{

}

DatabasePersistance::~DatabasePersistance()
{

}

bool DatabasePersistance::createSession(MetaData& metadata, DataStore& datastore)
{
	if(Configuration::getDebugMode())
	{
		cerr << __FILE__ << ":" << __LINE__ << ": createSession()\n";
	}
	
	

	Database *database = Database::instance(Configuration::getDatabaseContext());
	string sql;

	char *c_safe_id = database->escape( metadata.getId(), strlen( metadata.getId() ) );
	string safe_id=c_safe_id;
	delete [] c_safe_id;

	if(safe_id == "")
	{
		if(Configuration::getDebugMode())
		{
			cerr << __FILE__ << ":" << __LINE__ << ": ID not Set in Meta Data\n";
		}
		setError("ID not Set in Meta Data");
		return false;
	}
	
	string original_ip  = metadata.getOriginalIP();
	string last_ip = metadata.getLastIP();
	
	char max_inactive[20];
	sprintf(max_inactive, "%d", metadata.getMaxInactiveInterval());
	
	char ip_mask[20];
	sprintf(ip_mask,  "%d", metadata.getIPMask());
	
	char times_active[20];
	sprintf(times_active,  "%d", metadata.getNumTimesActive());

	string SiteCode = Configuration::getDomain();

	sql="INSERT INTO Sessions ";
	sql += " SET TimeCreated = NOW(), TimeLastAccessed = NOW(), ";
	sql += " OriginalIP = '";
	sql += original_ip;
	sql += "', LastIP = '";
	sql += last_ip;
	sql += "', MaxInactiveInterval='";
	sql += max_inactive;
	sql += "', NumTimesActive='";
	sql += times_active;
	sql += "', IPMask='";
	sql += ip_mask;
	sql += "', SessionID='";
	sql += safe_id;
	sql += "', SiteCode='";
	sql += SiteCode;
	sql += "'";

	if(!database->executeQuery(sql.c_str()))
	{
		if(Configuration::getDebugMode())
		{
			cerr << __FILE__ << ":" << __LINE__ << ": Insert Query Failed\n";
			cerr << database->getError() << "\n\n";
			cerr << sql << "\n\n";
		}
		setError(database->getError());
		return false;
	}

	int num_names=datastore.getNumValues();
	char y_buffer[20];
	for(int x=0; x< num_names; x++)
	{
		string name = datastore.getNameAt(x);
		
		char *c_safe_name = database->escape(name.c_str(), name.size());
		string safe_name = c_safe_name;
		delete [] c_safe_name;
		
		int num_values = datastore.getNumValues(name.c_str());

		for(int y=0; y < num_values; y++)
		{
			sprintf(y_buffer, "%d", y);

			string value = datastore.getValue(name.c_str(), y);
			char *c_safe_value = database->escape(value.c_str(), value.size());
			string safe_value = c_safe_value;
			delete [] c_safe_value;

			sql="INSERT INTO SessionData SET SessionID='";
			sql += safe_id;
			sql += "', DataName='";
			sql += safe_name;
			sql += "', DataValue='";
			sql += safe_value;
			sql += "', ListOrder = '";
			sql += y_buffer;
			sql += "'";

			if(!database->executeQuery(sql.c_str()))
			{
				setError(database->getError());
				return false;
			}
		}
	}

	return true;
}

	
bool DatabasePersistance::loadSession(MetaData& metadata, DataStore& datastore)
{

		if(Configuration::getDebugMode())
		{
			cerr << __FILE__ << ":" << __LINE__ << ": loadSession()\n";
		}

	string session_id=metadata.getId();
	if(session_id == "")
	{
		if(Configuration::getDebugMode())
		{
			cerr << __FILE__ << ":" << __LINE__ << ": No Session ID in MetaData\n";
		}
		setError("No Session ID Set in MetaData");
		return false;
	}

	Database *database = Database::instance(Configuration::getDatabaseContext());
	string sql;
	
	char *c_safe_id = database->escape( metadata.getId(), strlen( metadata.getId() ) );
	string safe_id=c_safe_id;
	delete [] c_safe_id;

	sql="SELECT OriginalIP, LastIP, IPMask, UNIX_TIMESTAMP(TimeCreated), UNIX_TIMESTAMP(TimeLastAccessed), MaxSessionLength, NumTimesActive, MaxInactiveInterval ";
	sql += " FROM Sessions WHERE SessionID='";
	sql += safe_id;
	sql += "'";

	if(database->storeResultQuery(sql.c_str()))
	{
		if(database->nextRow())
		{
			metadata.setOriginalIP(database->column(0));
			metadata.setLastIP(database->column(1));
			metadata.setIPMask(atoi(database->column(2)));
			metadata.setCreationTime(atol(database->column(3)));
			metadata.setLastAccessedTime(atol(database->column(4)));

			metadata.setNumTimesActive(atoi(database->column(6)));
			metadata.setMaxInactiveInterval(atoi(database->column(7)));

			metadata.isNew(false);
			metadata.isModified(false);
		}
		else
		{
			if(Configuration::getDebugMode())
			{
				cerr << __FILE__ << ":" << __LINE__ << ": no rows returned for meta data\n";
				cerr << database->getError() << "\n\n";
				cerr << sql << "\n\n";
			}
			setError("No Rows Returned");
			return false;
		}
	}
	else
	{
		if(Configuration::getDebugMode())
		{
			cerr << __FILE__ << ":" << __LINE__ << ": Failed to load meta data\n";
			cerr << database->getError() << "\n\n";
			cerr << sql << "\n\n";
		}
		setError(database->getError());
		return false;
	}

	// LOAD DATA
	//
	sql="SELECT DataName, DataValue FROM SessionData WHERE SessionID='";
	sql += safe_id;
	sql += "' ORDER BY ListOrder ";
	if(database->storeResultQuery(sql.c_str()))
	{
		while(database->nextRow())
		{
			datastore.addValue(database->column(0), database->column(1));			
		}
	}
	else
	{
		if(Configuration::getDebugMode())
		{
			cerr << __FILE__ << ":" << __LINE__ << ": Failed to load data\n";
			cerr << database->getError() << "\n\n";
			cerr << sql << "\n\n";
		}
		setError(database->getError());
		return false;
	}
	datastore.isModified(false);
	return true;
	
}

bool DatabasePersistance::deleteSession(const char *id)
{
	if( !id || id[0] == 0)
	{
		setError("id was null");
		return false;
	}

	Database *database = Database::instance(Configuration::getDatabaseContext());
	
	string sql="DELETE Sessions, SessionData FROM Sessions, SessionData ";
	sql += " WHERE Sessions.SessionID = '";
	sql += id;
	sql += " AND SessionData.SessionID=Sessions.SessionID ";



	if(database->executeQuery(sql.c_str()))
	{
		return true;
	}
	else
	{
		setError(database->getError());
		return false;
	}
}


bool DatabasePersistance::saveSession(MetaData& metadata, DataStore& datastore)
{

	if(Configuration::getDebugMode())
	{
		cerr << __FILE__ << ":" << __LINE__ << ": saveSession()\n";
	}
	
	Database *database = Database::instance(Configuration::getDatabaseContext());
	string sql;

	char *c_safe_id = database->escape( metadata.getId(), strlen( metadata.getId() ) );
	string safe_id=c_safe_id;
	delete [] c_safe_id;
	
	string last_ip = metadata.getLastIP();
	
	char max_inactive[20];
	sprintf(max_inactive, "%d", metadata.getMaxInactiveInterval());
	
	char ip_mask[20];
	sprintf(ip_mask, "%d", metadata.getIPMask());
	
	char times_active[20];
	sprintf(times_active, "%d", metadata.getNumTimesActive());

	sql="UPDATE Sessions ";
	sql += " SET TimeLastAccessed = NOW(), ";
	sql += " LastIP = '";
	sql += last_ip;
	sql += "', MaxInactiveInterval='";
	sql += max_inactive;
	sql += "', NumTimesActive='";
	sql += times_active;
	sql += "', IPMask='";
	sql += ip_mask;
	sql += "'";
	sql += " WHERE SessionID='";
	sql += safe_id;
	sql += "'";

	if(!database->executeQuery(sql.c_str()))
	{
		if(Configuration::getDebugMode())
		{
			cerr << __FILE__ << ":" << __LINE__ << ": error updating meta data\n";
			cerr << database->getError() << "\n\n";
			cerr << sql << "\n\n";
		}
		setError(database->getError());
		return false;
	}

	if(!datastore.isModified())
	{
		return true;
	}

	sql="DELETE FROM SessionData ";
	sql += " WHERE SessionData.SessionID='";
	sql += safe_id;
	sql += "'";

	if(!database->executeQuery(sql.c_str()))
	{
		if(Configuration::getDebugMode())
		{
			cerr << __FILE__ << ":" << __LINE__ << ": error deleting old data values\n";
			cerr << database->getError() << "\n\n";
			cerr << sql << "\n\n";
		}
		setError(database->getError());
		return false;
	}

	int num_names=datastore.getNumValues();
	char y_buffer[20];
	for(int x=0; x< num_names; x++)
	{
		if(Configuration::getDebugMode())
		{
				cerr << __FILE__ << ":" << __LINE__ << ": trying to save " << num_names << " data value names\n";
		}
		string name = datastore.getNameAt(x);
		
		char *c_safe_name = database->escape(name.c_str(), name.size());
		string safe_name = c_safe_name;
		delete [] c_safe_name;
		
		int num_values = datastore.getNumValues(name.c_str());

		for(int y=0; y < num_values; y++)
		{
			if(Configuration::getDebugMode())
			{
					cerr << __FILE__ << ":" << __LINE__ << ": trying to save " << num_values << " data values\n";
			}
			sprintf(y_buffer, "%d", y);

			string value = datastore.getValue(name.c_str(), y);
			char *c_safe_value = database->escape(value.c_str(), value.size());
			string safe_value = c_safe_value;
			delete [] c_safe_value;

			sql="INSERT INTO SessionData SET SessionID='";
			sql += safe_id;
			sql += "', DataName='";
			sql += safe_name;
			sql += "', DataValue='";
			sql += safe_value;
			sql += "', ListOrder = '";
			sql += y_buffer;
			sql += "'";

			if(!database->executeQuery(sql.c_str()))
			{
				if(Configuration::getDebugMode())
				{
					cerr << __FILE__ << ":" << __LINE__ << ": error adding new data value\n";
					cerr << database->getError() << "\n\n";
					cerr << sql << "\n\n";
				}
				setError(database->getError());
				return false;
			}
		}
	}

	return true;
}



bool DatabasePersistance::purgeSessions()
{
	int maxnewsession = Configuration::getMaxNewSessionLength();
	int maxsession = Configuration::getMaxSessionLength();
	int maxinactiveinterval = Configuration::getMaxInactiveInterval();
	char buffer[20];
	string sql;
	
	Database *database = Database::instance(Configuration::getDatabaseContext());
	
	// If Configuration Setting for MaxSessionLength is non-zero,
	// then all sessions older than MaxSessionLength minutes must be deleted.
	//
	if(maxsession != 0)
	{
		sprintf(buffer, "%d", maxsession);
		sql=" DELETE Sessions, SessionData ";
		sql += " FROM Sessions, SessionData ";
		sql += " WHERE TIMESTAMPDIFF(MINUTE,Sessions.TimeCreated, NOW()) > ";
		sql += buffer;
		sql += " AND SessionData.SessionID = Sessions.SessionID ";
		
		if(!database->executeQuery(sql.c_str()))
		{
			setError(database->getError());
			return false;
		}
	}

	// If Configuration Setting for MaxNewSessionLength is non-zero,
	// then all new sessions older than MaxNewSessionLength minutes must be deleted
	//
	if(maxnewsession != 0)
	{
		sprintf(buffer, "%d", maxnewsession);
		sql=" DELETE Sessions, SessionData ";
		sql += " FROM Sessions, SessionData ";
		sql += " WHERE TIMESTAMPDIFF(MINUTE,Sessions.TimeCreated, NOW()) > ";
		sql += buffer;
		sql += " AND Sessions.NumTimesActive = 0";
		sql += " AND SessionData.SessionID = Sessions.SessionID ";
		
		
		if(!database->executeQuery(sql.c_str()))
		{
			setError(database->getError());
			return false;
		}
	}

	
	// If Configuration Setting for MaxInactiveInterval is non-zero,
	// then all sessions where TimeLastActive is greater than MaxInactiveInterval minutes must be deleted
	// 
	if(maxinactiveinterval != 0)
	{
		sprintf(buffer, "%d", maxinactiveinterval);
		sql=" DELETE Sessions, SessionData ";
		sql += " FROM Sessions, SessionData ";
		sql += " WHERE TIMESTAMPDIFF(MINUTE,Sessions.TimeLastAccessed, NOW()) > ";
		sql += buffer;
		sql += " AND SessionData.SessionID = Sessions.SessionID ";
		
		if(!database->executeQuery(sql.c_str()))
		{
			setError(database->getError());
			return false;
		}
	}

	return true;

}

}} // end namespaces

