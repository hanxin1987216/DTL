// MetaData.cpp
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


#include "MetaData.h"
#include <stdlib.h>

using namespace std;

namespace rude{
namespace session{


MetaData::MetaData()
{
	d_maxinactiveinterval=0;
	d_maxsessionlength=0;
	d_ismodified=false;
	d_isnew = true;
	d_isreadonly=false;
	d_sidfromcookie=false;


	d_creationtime=0;
	d_lastaccessed=0;
	d_original_ip="";
	d_last_ip="";
	d_numtimesactive=0;
	d_ipmask=0;
	d_sessionid="";
	
}

MetaData::~MetaData()
{

}

bool MetaData::update()
{
	d_last_ip=getenv("REMOTE_ADDR") ? getenv("REMOTE_ADDR") : "127.0.0.1";
	d_lastaccessed = (long)time(0);
	d_numtimesactive++;
	d_ismodified=true;
	return true;
}


void MetaData::setID( const char *id)
{
	d_sessionid = id ? id : "";
}

const char *MetaData::getId() const
{
	return d_sessionid.c_str();
}
	

void MetaData::setOriginalIP(const char *ip)
{
	d_original_ip = ip ? ip : "";
}

const char *MetaData::getOriginalIP() const
{
	return d_original_ip.c_str();
}
	
const char *MetaData::getLastIP() const
{
	return d_last_ip.c_str();
}
void MetaData::setLastIP(const char *ip)
{
	if(ip && ip[0])
	{
		d_last_ip = ip;
	}
	else
	{
		d_last_ip = "127.0.0.1";
	}
}	
	

bool MetaData::isNew() const
{
	return d_isnew;
}
void MetaData::isNew(bool isit)
{
	d_isnew = isit;
}	

bool MetaData::isModified() const
{
	return d_ismodified;
}
void MetaData::isModified(bool isit)
{
	d_ismodified = isit;
}

bool MetaData::isReadOnly() const
{
	return d_isreadonly;
}
void MetaData::isReadOnly(bool isit)
{
	d_isreadonly = isit;
}

int MetaData::getMaxInactiveInterval() const
{
	return d_maxinactiveinterval;
}

void MetaData::setMaxInactiveInterval(int minutes)
{
	if(d_maxinactiveinterval != minutes)
	{
		d_maxinactiveinterval=minutes;
		d_ismodified=true;
	}
}

int MetaData::getMaxSessionLength() const
{
	return d_maxsessionlength;
}
void MetaData::setMaxSessionLength(int minutes)
{
	if(d_maxsessionlength != minutes)
	{
		d_maxsessionlength=minutes;
		d_ismodified=true;
	}
}

int MetaData::getIPMask() const
{
	return d_ipmask;	
}

void MetaData::setIPMask(int maskbits)
{
	if(maskbits < 0 || maskbits > 32)
	{
		maskbits = 0;
	}
	
	if(d_ipmask != maskbits)
	{
		d_ipmask = maskbits;
		d_ismodified=true;
	}
}


long MetaData::getCreationTime() const
{
	return d_creationtime;
}
void MetaData::setCreationTime(long thetime)
{
	d_creationtime = thetime;
}

	
long MetaData::getLastAccessedTime() const
{
	return d_lastaccessed;
}
void MetaData::setLastAccessedTime(long thetime)
{
	d_lastaccessed = thetime;
}
	
int MetaData::getNumTimesActive() const
{
	return d_numtimesactive;
}
void MetaData::setNumTimesActive(int numtimes)
{
	d_numtimesactive = numtimes;
}

}} // end namespaces

