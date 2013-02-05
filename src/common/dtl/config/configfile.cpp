/***************************************************************************************************
configfile.cpp:	
	C++ Foundation Library header files
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	This file contain the impl of classes: configfile

Author:
	韩欣

Creating Time:
	2011-10-10
***************************************************************************************************/

#include "../prec.h"
#include "../lang/string.h"
#include "../sys/exception.h"

#include "configfile.h"


using namespace rude::config;




ConfigFile::ConfigFile()
{
	d_implementation = new ConfigImpl();
}

ConfigFile::~ConfigFile()
{
	delete d_implementation;
	d_implementation = 0;
}

void ConfigFile::setConfigFile(const String& filepath)
{
	d_implementation->setConfigFile(filepath.getCStr ());
}

String ConfigFile::getConfigFile()
{
	return String(d_implementation->getConfigFile());
}

void ConfigFile::setCommentCharacter(char commentchar)
{
	d_implementation->setCommentCharacter(commentchar);
}

void ConfigFile::preserveDeletedData(bool shouldPreserve)
{
	d_implementation->preserveDeletedData(shouldPreserve);
}

void ConfigFile::setDelimiter(char delimiter)
{
	d_implementation->setDelimiter(delimiter);
}

bool ConfigFile::load()
{
	return d_implementation->load();
}

bool ConfigFile::load(const String& filename)
{
	return d_implementation->load(filename.getCStr ());
}


bool ConfigFile::save()
{
	return d_implementation->save();
}

bool ConfigFile::save(const String& filepath)
{
	return d_implementation->save(filepath.getCStr ());
}


void ConfigFile::clear()
{
	d_implementation->clear();
}


//////////////////////////////////////////
// Section Methods
//////////////////////////////////////////
int ConfigFile::getNumSections() const
{
	return d_implementation->getNumSections();
}

String ConfigFile::getSectionNameAt(int index) const
{
	return d_implementation->getSectionNameAt(index);
}

bool ConfigFile::setSection(const String& sectionname, bool shouldCreate)
{
	return d_implementation->setSection(sectionname.getCStr (), shouldCreate);
}

bool ConfigFile::setSection(const String& sectionname)
{
	return d_implementation->setSection(sectionname.getCStr (), true);
}

bool ConfigFile::deleteSection(const String& sectionname)
{
	return d_implementation->deleteSection(sectionname.getCStr ());
}

//////////////////////////////////////////
// Data Methods
//////////////////////////////////////////
int ConfigFile::getNumDataMembers() const
{
	return d_implementation->getNumDataMembers();
}

String ConfigFile::getDataNameAt(int index) const
{
	return d_implementation->getDataNameAt(index);
}

bool ConfigFile::exists(const String& name) const
{
	return d_implementation->exists(name.getCStr ());
}

void ConfigFile::setBoolValue(const String& name, bool value)
{
	d_implementation->setStringValue(name.getCStr (), ConfigImpl::boolToString(value));
}

bool ConfigFile::getBoolValue(const String& name) const
{
	return ConfigImpl::stringToBool(d_implementation->getStringValue(name.getCStr ()));
}

void ConfigFile::setIntValue(const String& name, int value)
{
	d_implementation->setStringValue(name.getCStr (), ConfigImpl::intToString(value));
}

int ConfigFile::getIntValue(const String& name) const
{
	return ConfigImpl::stringToInt(d_implementation->getStringValue(name.getCStr ()));
}

void ConfigFile::setDoubleValue(const String& name, double value)
{
	d_implementation->setStringValue(name.getCStr (), ConfigImpl::doubleToString(value));
}

double ConfigFile::getDoubleValue(const String& name) const
{
	return ConfigImpl::stringToDouble(d_implementation->getStringValue(name.getCStr ()));
}

void ConfigFile::setStringValue(const String& name, const String& value)
{
	d_implementation->setStringValue(name.getCStr (), value.getCStr ());
}

String ConfigFile::getStringValue(const String& name) const
{
	return d_implementation->getStringValue(name.getCStr ());
}

void ConfigFile::setValue(const String& name, const String& value)
{
	d_implementation->setStringValue(name.getCStr (), value.getCStr ());
}

String ConfigFile::getValue(const String& name) const
{
	return d_implementation->getStringValue(name.getCStr ());
}

bool ConfigFile::deleteData(const String& name)
{
	return d_implementation->deleteData(name.getCStr ());
}