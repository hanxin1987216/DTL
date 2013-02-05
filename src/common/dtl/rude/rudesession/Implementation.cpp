// session.h
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


#include "Implementation.h"

#include "Configuration.h"
#include "IPValidator.h"
#include "IDGenerator.h"
#include "Cookie.h"
#include "CookieReader.h"

#include "AbstractPersistance.h"
#include "ConfigFilePersistance.h"
#include "DatabasePersistance.h"

//#define USING_VISUAL_STUDIO


#ifdef USING_VISUAL_STUDIO
#include <io.h>
#else
#ifndef INCLUDED_DIRENT_H
#include <dirent.h> // for unlink()
#define INCLUDED_DIRENT_H
#endif
#endif

#ifdef WIN32
#include <process.h> // for getpid
#else
#include <sys/types.h> // for getpid()
#include <unistd.h> // for getpid() and unlink()
#endif

#include <dirent.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <string.h>
using namespace std;

namespace rude{
namespace session{

std::string Implementation::s_error="";


int Implementation::purgeSessions()
{
		if(! d_persistance->purgeSessions())
		{
			setError(d_persistance->getError());
			return false;
		}
		return true;
}


void Implementation::setError(const char *error)
{
	s_error = error ? error : "";
}

// CONSTRUCTOR & DESTRUCTOR
///////////////////////////////

Implementation::Implementation()
{
	d_isreadonly=false;

   bool debugmode = Configuration::getDebugMode();

	string persistanceType = Configuration::getPersistanceMethod();
	if(persistanceType == "database")
	{
		if(debugmode)
		{
			cerr << "SESSION DEBUG: " << __FILE__ << ":" << __LINE__ << " Creating Database Persistance Object\n";
		}
		d_persistance = new DatabasePersistance();
	}
	else
	{
		if(debugmode)
		{
			cerr << "SESSION DEBUG: " << __FILE__ << ":" << __LINE__ << " Creating Config File Persistance Object\n";
		}
		d_persistance = new ConfigFilePersistance();
	}


   string requestmethod=(getenv("REQUEST_METHOD") ? getenv("REQUEST_METHOD") : "");
   string request_id;
	
	if(requestmethod != "")
	{
	  // untaint supplied sid - it might contain .././../../..


	  if(debugmode)
	  {
	  	  cerr << "SESSION DEBUG: " << __FILE__ << ":" << __LINE__ << " Obtaining Requested Session ID from CookieReader using IDENTIFIER '" << Configuration::getCookieIdentifier() << "'\n";
	  }
 	  CookieReader cookie_reader;
	  request_id = cookie_reader.getValue(Configuration::getCookieIdentifier());
	}
	else
	{
	  if(debugmode)
	  {
	  	  cerr << "SESSION DEBUG: " << __FILE__ << ":" << __LINE__ << " Obtaining Requested Session ID from Command Line\n";
	  }
        cerr << "Session Command Line:  Please enter your session ID (x for none): ";
  		  std::getline(std::cin, request_id);
		  if(request_id == "x")
		  {
	        request_id="";
		  }
	}

	if(debugmode)
	{
	 	  cerr << "SESSION DEBUG: " << __FILE__ << ":" << __LINE__ << "Using ID: '" << request_id << "'\n";
	}
	d_metadata.setID(request_id.c_str());



	if(debugmode)
	{
		cerr << "SESSION DEBUG: " << __FILE__ << ":" << __LINE__ << " Attempting to Load and Validate Session\n";
	}
	if(request_id != "" && loadSession(request_id.c_str()) && validate())
	{
		if(debugmode)
		{
			cerr << "SESSION DEBUG: " << __FILE__ << ":" << __LINE__ << " Session Loaded and Validated - updating session meta data\n";
		}
		update();
	}
	else
	{
		if(debugmode)
		{
			cerr << "SESSION DEBUG: " << __FILE__ << ":" << __LINE__ << " Could not load session, creating new one\n";
		}
		createSession();
	}
}

bool Implementation::createSession()
{
   bool debugmode = Configuration::getDebugMode();
	
	// Comeup with an ID
	//
	int id_length=25;
	string requestmethod=(getenv("REQUEST_METHOD") ? getenv("REQUEST_METHOD") : "");
	string session_id;
	
	if(requestmethod == "")
	{
        cerr << "Session Command Line:  Creating Session -  please enter a session ID to use for future requests (g to generate): ";
  		  std::getline(std::cin, session_id);
		  if(session_id == "g")
		  {
		     cerr << "Generating ID\n";
	        session_id=IDGenerator::generateID(id_length);
		  }
	}
	else
	{
	      session_id=IDGenerator::generateID(id_length);
	}
	
	// Set the client cookie
	//
	Cookie c;
	c.setName(Configuration::getCookieIdentifier());
	c.setValue(session_id.c_str());
	c.setPath(Configuration::getPath());
	c.setDomain(Configuration::getDomain());
	c.setPort(Configuration::getPort());
	c.setDiscard(Configuration::getDiscard());
	c.setComment(Configuration::getComment());
	c.setCommentURL(Configuration::getCommentURL());
	c.setSecure(Configuration::getSecure());

	std::cout << c.cookieHeader();

	// The session might be be able to be created, for wahtever reason.
	// It might be argued to set ismodified to false so that the reason for failure
	// can be determined when explicitly calling save().
	// With this mindset, it would be tempting to only write out the cookie
	// after a successful save, but we have to do it in the creae method to ensure that
	// the set-cookie header acutally gets sent with the headers.
	// if we rely on a view to call save, or let the save be performed when the session
	// is destroyed, then the client may never get the cookie....
	//
	

		// Set the Meta Data
		//
		d_metadata.setID(session_id.c_str());
		
		const char *remoteaddr=getenv("REMOTE_ADDR");
		if(remoteaddr == (char*) 0 || strlen(remoteaddr) == 0)
		{
			remoteaddr= "127.0.0.1";
		}
		d_metadata.setOriginalIP(remoteaddr);
		d_metadata.setLastIP(remoteaddr);
		
		d_metadata.setMaxInactiveInterval(Configuration::getMaxInactiveInterval());
		d_metadata.setIPMask(Configuration::getDefaultIPMask());
		
		d_metadata.setCreationTime((long)time(0));
		d_metadata.setLastAccessedTime((long)time(0));
		d_metadata.setNumTimesActive(0);
		
		d_metadata.isNew(true);
	
		// Make sure there is no User Data
		//
		d_datastore.clear();

		if(d_persistance->createSession(d_metadata, d_datastore))
		{
			d_metadata.isModified(false);
			d_datastore.isModified(false);
			return true;
		}
		else
		{
				purgeSessions();
				d_metadata.isModified(true);
				d_datastore.isModified(true);
				setError(d_persistance->getError());
				return false;
		}
}

bool Implementation::generateNewSessionID()
{
	// This is a good place to purge sessions!!
	//

	purgeSessions();
		
	// Comeup with an ID
	//
	int id_length=25;
	string session_id=IDGenerator::generateID(id_length);
		
	// Set the client cookie
	//
	Cookie c;
	c.setName(Configuration::getCookieIdentifier());
	c.setValue(session_id.c_str());
	c.setPath(Configuration::getPath());
	c.setDomain(Configuration::getDomain());
	c.setPort(Configuration::getPort());
	c.setDiscard(Configuration::getDiscard());
	c.setComment(Configuration::getComment());
	c.setCommentURL(Configuration::getCommentURL());
	c.setSecure(Configuration::getSecure());

	std::cout << c.cookieHeader();

	// delete old session stuff
	//
	
	d_persistance->deleteSession(d_metadata.getId());

	// Set the new ID
	//
	d_metadata.setID(session_id.c_str());

	if(d_persistance->createSession(d_metadata, d_datastore))
	{
		d_metadata.isModified(false);
		d_datastore.isModified(false);
		return true;
	}
	else
	{
		d_metadata.isModified(true);
		d_datastore.isModified(true);
		setError(d_persistance->getError());
		return false;
	}
}	

bool Implementation::loadSession(const char *id)
{
		if( d_persistance->loadSession(d_metadata, d_datastore))
		{
			return true;
		}
		else
		{
			setError(d_persistance->getError());
			purgeSessions();
			return false;
		}
}

Implementation::~Implementation()
{
	save();
}

// INSTANCE METHODS

bool Implementation::terminate()
{
	// Clear cookies amd Session ID here????
	//
	Cookie c;
	c.setName(Configuration::getCookieIdentifier());
	c.setValue("");
	c.setPath(Configuration::getPath());
	c.setDomain(Configuration::getDomain());
	c.setPort(Configuration::getPort());
	c.setDiscard(Configuration::getDiscard());
	c.setComment(Configuration::getComment());
	c.setCommentURL(Configuration::getCommentURL());
	c.setSecure(Configuration::getSecure());
	
	cerr << c.cookieHeader();

	// Prevent resaving the file
	//
	d_metadata.isReadOnly(true);
	
	return true;
}

bool Implementation::save()
{
	if(!d_isreadonly)
	{
		if(d_metadata.isModified() || d_datastore.isModified())
		{
			if(! d_persistance->saveSession(d_metadata, d_datastore))
			{
				setError(d_persistance->getError());
				return false;
			}
			return true;
		}
		return true;
	}
	else
	{
		setError("Session is read only");
	}
	return false;
}

bool Implementation::update()
{
	if(!d_metadata.isNew())
	{
		d_metadata.update();
		return true;
	}
	else
	{
		setError("Cannot update new session");
		return false;
	}
}

bool Implementation::validate()
{
	const char *current=getenv("REMOTE_ADDR");
	
	if(!current)
	{
		current = "127.0.0.1";
	}

	if(IPValidator::validate(d_metadata.getOriginalIP(), current, d_metadata.getIPMask()))
	{
		long timenow = (long)time(0);

		// now validate the expiration thingy...
		//
		long interval = d_metadata.getMaxInactiveInterval();
		if(interval)
		{
			// convert minutes to seconds
			//
			interval *= 60;

			// timenow - lastactive cannot exceed interval
			//
			long difference = timenow - d_metadata.getLastAccessedTime();
			if(difference > interval)
			{
				setError("Session Timed Out");
				return false;
			}
		}

		// and validate session expiration
		// 
		long maxlength = d_metadata.getMaxSessionLength();
		if(maxlength)
		{
			// convert minutes to seconds
			//
			interval *= 60;

			// timenow - lastactive cannot exceed interval
			//
			long difference = timenow - d_metadata.getCreationTime();
			if(difference > maxlength)
			{
				setError("Session Expired");
				return false;
			}	
		}
		
		return true;
	}
	else
	{
		setError("Ip Mismatch");
		// Prevent saving any changes to session
		//
		return false;
	}
}

const char *Implementation::getError()
{
	return s_error.c_str();
}

//////////////////////////////////////////////////
/////  META-DATA METHODS
/////  ALL FUNCTIONS DEAL WITH OBJECT DATA-MEMBERS 
/////  AND UPDATE d_ismodified ACCORDINGLY
/////////////////////////////////////////////////

void Implementation::setMaxInactiveInterval(int minutes)
{
	d_metadata.setMaxInactiveInterval(minutes);
}

int Implementation::getMaxInactiveInterval()
{
	return d_metadata.getMaxInactiveInterval();
}

int Implementation::getIPMask()
{
	return d_metadata.getIPMask();
}

void Implementation::setIPMask(int maskbits)
{
	d_metadata.setIPMask(maskbits);
}

bool Implementation::isNew()
{
	return d_metadata.isNew();
}

long Implementation::getCreationTime()
{
	return d_metadata.getCreationTime();
}

long Implementation::getLastAccessedTime()
{
	return d_metadata.getLastAccessedTime();
}

const char *Implementation::getOriginalIP()
{
	return d_metadata.getOriginalIP();
}

const char *Implementation::getLastIP()
{
	return d_metadata.getLastIP();
}

int Implementation::getNumTimesActive()
{
	return d_metadata.getNumTimesActive();
}

const char *Implementation::getId()
{
	return d_metadata.getId();
}













//////////////////////////////////////////////////
/////  USER DATA METHODS
/////  ALL FUNCTIONS DEAL EXCLUSIVELY WITH DATA-MAP, 
/////  AND UPDATE d_ismodified ACCORDINGLY
/////////////////////////////////////////////////


void Implementation::setValue(const char *name, const char *value)
{
	d_datastore.setValue(name, value);
}


const char *Implementation::getValue(const char *name)
{
	return d_datastore.getValue(name);
}

void Implementation::addValue(const char *name, const char *value)
{
	d_datastore.addValue(name, value);
}

const char *Implementation::getValue(const char *name, int index)
{
	return d_datastore.getValue(name, index);
}

const char *  Implementation::removeValue(const char *name, int index)
{
	// Forward to implementation object
	//
	return d_datastore.removeValue(name, index);
}

int Implementation::getNumValues()
{
	return d_datastore.getNumValues();
}

int Implementation::getNumValues(const char *name)
{
	return d_datastore.getNumValues(name);
}

const char *Implementation::getNameAt(int index)
{
	return d_datastore.getNameAt(index);
}

const char *Implementation::getValueAt(int index)
{
	return d_datastore.getValueAt(index);
}

void Implementation::deleteValue(const char *name)
{
	d_datastore.deleteValue(name);
}

bool Implementation::exists(const char *name)
{
	return d_datastore.exists(name);
}

void Implementation::clear()
{
	d_datastore.clear();
}

}} // end namespaces

