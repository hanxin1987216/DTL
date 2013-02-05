// ConfigFilePersistance.cpp
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

#include "ConfigFilePersistance.h"

#include "Configuration.h"
#include "../rudeconfig/config.h"
#include <string>
#include <dirent.h> // linux read directory
#include <unistd.h> // linux unlink


#include <iostream> // DEBUG
#include <stdio.h>
#include <stdlib.h>

using namespace std;
using namespace rude;
namespace rude{
namespace session{

bool ConfigFilePersistance::createSession(MetaData& metadata, DataStore& datastore)
{
			std::string path= Configuration::getSessionDirectory();
			if(path == "")
			{
				setError("Session Directory not Set");
				return false;
			}

			string id=metadata.getId();
			if(id == "")
			{
				setError("Session ID not set");
				return false;
			}

			rude::Config config;

			// Just in case the main application changes the default values...
			//
			config.setDelimiter('=');
			config.setCommentCharacter('#');
			config.preserveDeletedData(false);
			
			// Store Meta Data
			//
			char buffer[50];

			config.setStringValue("Session ID", metadata.getId());
			config.setStringValue("Original IP", metadata.getOriginalIP());
			config.setStringValue("Last IP", metadata.getLastIP());
			config.setIntValue("Max Inactive Interval", metadata.getMaxInactiveInterval());
			config.setIntValue("IP Mask", metadata.getIPMask());
			config.setIntValue("Num Times Active", metadata.getNumTimesActive());

			sprintf(buffer, "%ld", (long) metadata.getCreationTime() );
			config.setStringValue("Time Created", buffer);

			sprintf(buffer, "%ld", (long) metadata.getLastAccessedTime());
			config.setStringValue("Time Last Accessed", buffer);

			// Store User Data
			//
			config.setSection("DATA");
			int numvalues = datastore.getNumValues();
			for(int x=0; x < numvalues; x++)
			{
				string name = datastore.getNameAt(x);
				string value= datastore.getValueAt(x);
				config.setStringValue( name.c_str(), value.c_str());
			}

			int size=path.size();
			if(path[size -1] != '/')
			{
				path += "/";
			}
			path +=  metadata.getId();
			if(!config.save(path.c_str()))
			{
				setError(config.getError());
				return false;
			}
			else
			{
				//cout << "Saved session to '" << path.c_str() << "'\n";
			}
			metadata.isModified(false);
			datastore.isModified(false);
			
			return true;
}

bool ConfigFilePersistance::loadSession(MetaData& metadata, DataStore& datastore)
{

			bool debugmode = Configuration::getDebugMode();
			if(debugmode)
			{
				cerr << "SESSION DEBUG: " << __FILE__ << ":" << __LINE__ << " loadSession()\n";
			}
			

		
		string session_id=metadata.getId();
		if(session_id == "")
		{
			if(debugmode)
			{
				cerr << "SESSION DEBUG: " << __FILE__ << ":" << __LINE__ << " No Session ID Set in MetaData\n";
			}
			setError("No Session ID Set in MetaData");
			return false;
		}
		
		if(debugmode)
		{
			cerr << "SESSION DEBUG: " << __FILE__ << ":" << __LINE__ << " Attempting to load ID='" << session_id << "'\n";
		}
			
		rude::Config config;
		std::string path = Configuration::getSessionDirectory();
		path += "/";
		path += session_id;
		if(config.load(path.c_str()))
		{
			if(debugmode)
			{
				cerr << "SESSION DEBUG: " << __FILE__ << ":" << __LINE__ << " Config file loaded - reading metadata\n";
			}
			// Load Meta Data
			//
			config.setSection("");
			metadata.setOriginalIP(config.getStringValue("Original IP"));
			metadata.setLastIP(config.getStringValue("Last IP"));
			metadata.setMaxInactiveInterval(config.getIntValue("Max Inactive Interval"));
			metadata.setIPMask(config.getIntValue("IP Mask"));
			metadata.setNumTimesActive(config.getIntValue("Num Times Active"));
			metadata.setCreationTime( atol( config.getStringValue("Time Created") ));
			metadata.setLastAccessedTime( atol( config.getStringValue("Time Last Accessed") ));
			metadata.isNew(false);
			metadata.isModified(false);
			
			// Load User Data
			//
			datastore.clear();
			config.setSection("DATA");
			int numdata = config.getNumDataMembers();
			for(int x=0; x< numdata; x++)
			{
				std::string myname = config.getDataNameAt(x);
				std::string value= config.getStringValue(myname.c_str());
				datastore.setValue(myname.c_str(), value.c_str());
			}
			datastore.isModified(false);
			return true;
		}
		else
		{
			if(debugmode)
			{
				cerr << "SESSION DEBUG: " << __FILE__ << ":" << __LINE__ << " Faild to load file '" << path << "'\n";
				cerr << "SESSION DEBUG: " << config.getError() << "\n";
			}
			setError(config.getError());
			return false;
		}
}

bool ConfigFilePersistance::deleteSession(const char *sessionID)
{
	// Erase the session file
	//
	if(sessionID == 0 || sessionID[0] == 0)
	{
		setError("sessionID was blank");
		return false;
	}
	std::string path = Configuration::getSessionDirectory();
	path += "/";
	path += sessionID;	
	::unlink(path.c_str());

}

bool ConfigFilePersistance::saveSession(MetaData& metadata, DataStore& datastore)
{
			std::string path= Configuration::getSessionDirectory();
			if(path == "")
			{
				setError("Session Directory not Set");
				return false;
			}

			string id=metadata.getId();
			if(id == "")
			{
				setError("Session ID not set");
				return false;
			}

			rude::Config config;

			// Store Meta Data
			//
			char buffer[50];

			config.setStringValue("Session ID", metadata.getId());
			config.setStringValue("Original IP", metadata.getOriginalIP());
			config.setStringValue("Last IP", metadata.getLastIP());
			config.setIntValue("Max Inactive Interval", metadata.getMaxInactiveInterval());
			config.setIntValue("IP Mask", metadata.getIPMask());
			config.setIntValue("Num Times Active", metadata.getNumTimesActive());

			sprintf(buffer, "%ld", (long) metadata.getCreationTime() );
			config.setStringValue("Time Created", buffer);

			sprintf(buffer, "%ld", (long) metadata.getLastAccessedTime());
			config.setStringValue("Time Last Accessed", buffer);

			// Store User Data
			//
			config.setSection("DATA");
			int numvalues = datastore.getNumValues();
			for(int x=0; x < numvalues; x++)
			{
				string name = datastore.getNameAt(x);
				string value= datastore.getValueAt(x);
				config.setStringValue( name.c_str(), value.c_str());
				
			}

			int size=path.size();
			if(path[size -1] != '/')
			{
				path += "/";
			}
			path +=  metadata.getId();
			if(!config.save(path.c_str()))
			{
				setError(config.getError());
				return false;
			}
			metadata.isModified(false);
			datastore.isModified(false);
			
			return true;
}

bool ConfigFilePersistance::purgeSessions()
{
		string session_dir  = Configuration::getSessionDirectory();
		if(session_dir == "")
		{
			setError("Session Directory Not set");
			return false;
		}
		
  		DIR *dirhandle = opendir(session_dir.c_str());
		if(dirhandle == 0)
		{
				setError("Could not read session directory");
				return false;
		}

		struct dirent * dirp;
		rude::Config config;

		while((dirp = readdir(dirhandle)) != NULL)
    	{
			if ( (dirp->d_name)[0] == '.')
			{
            continue ; 
			}
			std::string newpath=session_dir;
			newpath += "/";
			newpath += dirp->d_name;
			
			if(   config.load(newpath.c_str())  )
			{
				bool do_delete = false;
				long timenow = (long)time(0);

				// Check inactivity
				//
				long interval = atol(config.getStringValue("Max Inactive Interval"));
				if(interval)
				{
					// convert minutes to seconds
					//
					interval *= 60;

					// timenow - lastactive cannot exceed interval
					//
					
					long lastaccessed = atol(config.getStringValue("Time Last Accessed"));
					long difference = timenow - lastaccessed;
					if(difference > interval)
					{
						do_delete = true;
					}
				}
				
				// Check age of new sessions
				//
				if(atoi(config.getStringValue("Num Times Active")) == 0)
				{
					// session is new
					//
					int maxnewsession = Configuration::getMaxNewSessionLength();
					if(maxnewsession)
					{
						maxnewsession *=60;
						long created = atol(config.getStringValue("Time Created"));
						long difference = timenow - created;
						if(difference > maxnewsession)
						{
							do_delete = true;
						}
					}
				}
				
				// Check against maximum session lifetime
				//
				int maxsession = Configuration::getMaxSessionLength();
				if(maxsession)
				{
					maxsession *=60;
					long created = atol(config.getStringValue("Time Created"));
					long difference = timenow - created;
					if(difference > maxsession)
					{
						do_delete = true;
					}
				}
				
				if(do_delete)
				{
						unlink(newpath.c_str());
				}
			}
		}
		closedir(dirhandle);
		return true;
}

}} // end namespaces

