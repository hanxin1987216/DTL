// Session.h
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


#include "session.h"
#include "Implementation.h"
#include "Configuration.h"
#include "Converter.h"

using namespace rude::session;

namespace rude{

Session *Session::s_instance=0;

//////////////////////////////
// CONFIGRATION METHODS
//////////////////////////////

void Session::setPath(const char *path)
{
	Configuration::setPath(path);
}

const char *Session::getPath()
{
	return Configuration::getPath();
}
	
void Session::setDomain(const char *domain)
{
	Configuration::setDomain(domain);
}
const char *Session::getDomain()
{
	return Configuration::getDomain();
}

void Session::setDiscard(bool shouldDiscard)
{
	Configuration::setDiscard(shouldDiscard);
}

bool Session::getDiscard()
{
	return Configuration::getDiscard();
}

void Session::setMaxSessions(int num)
{
	Configuration::setMaxSessions(num);
}
int Session::getMaxSessions()
{
	return Configuration::getMaxSessions();
}

void Session::setMaxSessionLength(int seconds)
{
	Configuration::setMaxSessionLength(seconds);
}
int Session::getMaxSessionLength()
{
	return Configuration::getMaxSessionLength();
}

void Session::setMaxNewSessionLength(int seconds)
{
	Configuration::setMaxNewSessionLength(seconds);
}
int Session::getMaxNewSessionLength()
{
	return Configuration::getMaxNewSessionLength();
}

void Session::setDefaultMaxInactiveInterval(int seconds)
{
	Configuration::setMaxInactiveInterval(seconds);
}

int Session::getDefaultMaxInactiveInterval()
{
	return Configuration::getMaxInactiveInterval();
}

void Session::setPort(const char *port)
{
	Configuration::setPort(port);
}
const char *Session::getPort()
{
	return Configuration::getPort();
}

void Session::setSecure(bool isSecure)
{
	Configuration::setSecure(isSecure);
}
bool Session::getSecure()
{
	return Configuration::getSecure();
}

void Session::setComment(const char *comment)
{
	Configuration::setComment(comment);
}
const char *Session::getComment()
{
	return Configuration::getComment();
}

void Session::setCommentURL(const char *url)
{
	Configuration::setCommentURL(url);
}
const char *Session::getCommentURL()
{
	return Configuration::getCommentURL();
}

void Session::setSessionDirectory(const char *path)
{
	Configuration::setSessionDirectory(path);
}
const char *Session::getSessionDirectory()
{
	return Configuration::getSessionDirectory();
}

void Session::setDatabaseContext(const char *contextname)
{
	Configuration::setDatabaseContext(contextname);
}
const char *Session::getDatabaseContext()
{
	return Configuration::getDatabaseContext();
}

bool Session::setPersistanceMethod(const char *method)
{
	return Configuration::setPersistanceMethod(method);
}

const char *Session::getPersistanceMethod()
{
	return Configuration::getPersistanceMethod();
}

void Session::setCookieIdentifer(const char *name)
{
	Configuration::setCookieIdentifer(name);
}
const char *Session::getCookieIdentifier()
{
	return Configuration::getCookieIdentifier();
}

void Session::setURLIdentifier(const char *name)
{
	Configuration::setURLIdentifier(name);
}
const char *Session::getURLIdentifier()
{
	return Configuration::getURLIdentifier();
}

void Session::useCookies(bool useCookies)
{
	Configuration::useCookies(useCookies);
}
bool Session::useCookies()
{
	return Configuration::useCookies();
}


void Session::setDefaultIPMask(int maskbits)
{
	Configuration::setDefaultIPMask(maskbits);
}
	
int Session::getDefaultIPMask()
{
	return Configuration::getDefaultIPMask();
}

void Session::setDebugMode(bool mode)
{
	Configuration::setDebugMode(mode);
}

bool Session::getDebugMode()
{
	return Configuration::getDebugMode();
}

////////////////////////////////
// Static Methods
////////////////////////////////

Session *Session::getSession()
{
	if(! s_instance )
	{
		s_instance = new Session(new Implementation());
	}
	return s_instance;
}
	
Session * Session::getSession(const char *id)
{
	return getSession();
}

bool Session::generateNewSessionID()
{
	return d_implementation->generateNewSessionID();
}
	


Session * Session::getSession(bool shouldCreate)
{
	return getSession();
}

const char *Session::getError()
{
	return Implementation::getError();
}

///////////////////////////////
// CONSTRUCTOR & DESTRUCTOR
///////////////////////////////

Session::Session(Implementation * implementation)
{
	d_implementation = implementation;
}

Session::~Session()
{
	delete d_implementation;
}


// INSTANCE METHODS


bool Session::terminate()
{
	// Forward to implementation object
	//
	return d_implementation->terminate();
}

bool Session::save()
{
	// Forward to implementation object
	//
	return d_implementation->save();
}

long Session::getCreationTime()
{
	// Forward to implementation object
	//
	return d_implementation->getCreationTime();
}

long Session::getLastAccessedTime()
{
	// Forward to implementation object
	//
	return d_implementation->getLastAccessedTime();
}


const char *Session::getOriginalIP()
{
	// Forward to implementation object
	//
	return d_implementation->getOriginalIP();
}

const char *Session::getLastIP()
{
	// Forward to implementation object
	//
	return d_implementation->getLastIP();
}

int Session::getNumTimesActive()
{
	// Forward to implementation object
	//
	return d_implementation->getNumTimesActive();
}

const char *Session::getSessionID()
{
	// Forward to implementation object
	//
	return d_implementation->getId();
}

const char *Session::getId()
{
	return getSessionID();
}

void Session::setMaxInactiveInterval(int minutes)
{
	// Forward to implementation object
	//
	d_implementation->setMaxInactiveInterval(minutes);
}


int Session::getMaxInactiveInterval()
{
	// Forward to implementation object
	//
	return d_implementation->getMaxInactiveInterval();
}

int Session::getIPMask()
{
	// Forward to implementation object
	//
	return d_implementation->getIPMask();
}

void Session::setIPMask(int maskbits)
{
	// Forward to implementation object
	//
	d_implementation->setIPMask(maskbits);
}


bool Session::isNew()
{
	// Forward to implementation object
	//
	return d_implementation->isNew();
}









//////////////////////////////////////////////
//   DATA METHODS
//////////////////////////////////////////////

bool Session::exists(const char *name)
{
	// Forward to implementation object
	//
	return d_implementation->exists(name);
}

int Session::getNumValues()
{
	// Forward to implementation object
	//
	return d_implementation->getNumValues();
}

int Session::getNumValues(const char *name)
{
	return d_implementation->getNumValues(name);
}	

const char *Session::getNameAt(int index)
{
	// Forward to implementation object
	//
	return d_implementation->getNameAt(index);
}

const char *Session::getValueAt(int index)
{
	// Forward to implementation object
	//
	return d_implementation->getValueAt(index);
}


void Session::setValue(const char *name, const char *value)
{
	// Forward to implementation object
	//
	d_implementation->setValue(name, value);
}

const char *Session::getValue(const char *name)
{
	// Forward to implementation object
	//
	return d_implementation->getValue(name);
}


void Session::addValue(const char *name, const char *value)
{
	// Forward to implementation object
	//
	d_implementation->addValue(name, value);
}

const char *Session::getValue(const char *name, int index)
{
	// Forward to implementation object
	//
	return d_implementation->getValue(name, index);
}


void Session::setStringValue(const char *name, const char *value)
{
	// Forward to implementation object
	//
	d_implementation->setValue(name, value);
}
const char *Session::getStringValue(const char *name)
{
	// Forward to implementation object
	//
	return d_implementation->getValue(name);
}


void Session::setIntValue(const char *name, int value)
{
	// Convert and forward to implementation object
	//
	d_implementation->setValue(name, Converter::intToString(value));
}

int Session::getIntValue(const char *name)
{
	// Forward to implementation object and convert results
	//
	return Converter::stringToInt(d_implementation->getValue(name));
}


void Session::setDoubleValue(const char *name, double value)
{
	// Convert and forward to implementation object
	//
	d_implementation->setValue(name, Converter::doubleToString(value));
}

double Session::getDoubleValue(const char *name)
{
	// Forward to implementation object and convert results
	//
	return Converter::stringToDouble(d_implementation->getValue(name));
}


void Session::setBoolValue(const char *name, bool value)
{
	// Forward to implementation object
	//
	d_implementation->setValue(name, Converter::boolToString(value));
}

bool Session::getBoolValue(const char *name)
{
	// Forward to implementation object and convert results
	//
	return Converter::stringToBool(d_implementation->getValue(name));
}


void Session::setBinaryValue(const char *name, const char *data, int length)
{
	// Convert and forward to implementation object
	//
	d_implementation->setValue(name, Converter::binaryToString(data, length));
}

char *Session::getBinaryValue(const char *name, int &outlength)
{
	// Forward to implementation object and convert results
	//
	return Converter::stringToBinary(d_implementation->getValue(name), outlength);
}

void Session::deleteValue(const char *name)
{
	// Forward to implementation object
	//
	d_implementation->deleteValue(name);
}

const char *  Session::removeValue(const char *name, int index)
{
	// Forward to implementation object
	//
	return d_implementation->removeValue(name, index);
}

void Session::clear()
{
	// Forward to implementation object
	//
	d_implementation->clear();
}


} // end namespace


