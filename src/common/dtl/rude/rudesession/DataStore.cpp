// DataStore.cpp
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


#include "DataStore.h"
#include "Base64Encoder.h"
#include <stdio.h>

#include <iostream> // For DEBUG
using namespace std;

namespace rude{
namespace session{

DataStore::DataStore()
{
	d_ismodified = false;
	d_returnstring ="";
}

DataStore::~DataStore()
{

}

bool DataStore::isModified()
{
	return d_ismodified;
}

void DataStore::isModified( bool isit)
{
	d_ismodified = isit;
}

int DataStore::getNumValues()
{
	return d_datamap.size();
}

const char * DataStore::getValue(const char * name)
{
		return getValue(name, 0);
}

const char * DataStore::getValue(const char *name, int index)
{
	char buf[20];
	sprintf(buf, "%d", index);
	std::string myname= name? name : "";
		
	map<std::string, stringlist>::iterator iter = d_datamap.find(myname);

	if(iter != d_datamap.end())
	{
		int listsize = ((*iter).second).size();
		char buf[20];
		sprintf(buf, "%d", listsize);

		if(listsize <= index)
		{
			return "";
		}
		return ( ((*iter).second)[index].c_str() );
	}		
	return "";
}

void DataStore::setValue(const char *name, const char *value)
{
	std::string myname= name ? name : "";
	std::string myvalue= value ? value : "";
	
	stringlist mylist;
	mylist.push_back(myvalue);
	
	d_datamap[myname] = mylist;
	d_ismodified=true;
}

void DataStore::addValue(const char *name, const char *value)
{
	std::string myname= name ? name : "";
	std::string myvalue= value ? value : "";
	stringlist thelist = d_datamap[myname];
	if(thelist != (stringlist) 0)
	{
		thelist.push_back(myvalue);
		d_datamap[myname] = thelist;
	}
	else
	{
		setValue(name, value);
	}
	d_ismodified=true;
}

const char * DataStore::removeValue(const char *name, int index)
{
	std::string myname= name ? name : "";
	stringlist thelist = d_datamap[myname];
	if(thelist != (stringlist) 0)
	{
		if(thelist.size() > index)
		{
			d_returnstring = thelist[index];
			stringlist::iterator iter;
			int x=0;
			for(iter = thelist.begin(); iter != thelist.end(); iter++)
			{
				if(x == index)
				{
					thelist.erase(iter);
					d_datamap[myname] = thelist;
					d_ismodified=true;
					return d_returnstring.c_str();
				}
				x++;
			}

		}
	}
	return "";
}

int DataStore::getNumValues(const char *name)
{
	std::string myname= name ? name : "";

	map<std::string, stringlist>::iterator iter = d_datamap.find(myname);

	if(iter != d_datamap.end())
	{
		return ((*iter).second).size();
	}
	return 0;
}

const char *DataStore::getValueAt(int index)
{
	std::map<std::string, stringlist >::iterator iter;

	int pos=0;
	for(iter=d_datamap.begin(); iter != d_datamap.end(); iter++)
	{
		if(index == pos)
		{
			return (iter->second)[0].c_str();
		}
		pos++;
	}
	return "";
}

const char *DataStore::getNameAt(int index)
{
	std::map<std::string, stringlist>::iterator iter;

	int pos=0;
	for(iter=d_datamap.begin(); iter != d_datamap.end(); iter++)
	{
		if(index == pos)
		{
			return (iter->first).c_str();
		}
		pos++;
	}
	return "";
}

void DataStore::deleteValue(const char *name)
{
	std::string myname = name ? name : "";
	if(d_datamap.erase(myname))
	{
		d_ismodified=true;
	}
}

bool DataStore::exists(const char *name) const
{
	std::string myname = name ? name : "";
	return ( d_datamap.find(myname) != d_datamap.end() );
}

void DataStore::clear()
{
	if(d_datamap.size())
	{
		d_datamap.clear();
		d_ismodified=true;
	}
}

}} // end namespaces

