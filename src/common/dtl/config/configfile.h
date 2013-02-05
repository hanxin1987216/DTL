/***************************************************************************************************
configfile.h:	
	C++ Foundation Library header files
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	This file contain the declaration of classes: configfile

Author:
	韩欣

Creating Time:
	2011-10-10
***************************************************************************************************/

#ifndef __DTL_CONFIGFILE_H__
#define __DTL_CONFIGFILE_H__

#if PRAGMA_ONCE
#	pragma once
#endif

#include "../rude/rudeconfig/ConfigImpl.h"

/**
 * This class represents a 32-bit signed int type.
 */
class DTL_DLLEXPORT ConfigFile
{
public:
	ConfigFile (void);
	~ConfigFile (void);
	
// static method
public:

	/**
	* Set's the default filepath to be used by the load() and save() methods
	* The default filepath is initially set to "./default.ini"
	* Affects the current instance only
	* @param filepath 设置配置文件路径
	*/
	void setConfigFile(const String& filepath);
	String getConfigFile ();

	/*
	* Sets whether or not deleted data will be preserved as comments.
	* If set to true, deleted data will be converted into comments when 
	* the save() method is called.  If set to false, deleted data
	* will not be compeltely discarded. Default is false (no preserve).
	* Affects the current instance only.
	*/
	void preserveDeletedData(bool shouldPreserve);

	/*
	* Set's the comment character ( initially set to '#' )
	* If the comment character is set to NULL (0), 
	* then comments will not be written when save() is called
	* Affects the current object only
	*/
	void setCommentCharacter(char commentchar);

	/*
	* Set's the delimiter for new config objects ( initially set to '=' )
	* If the delimiter is set to NULL, then it will be assumed that
	* the key and value are separated by whitespace.
	* Affects the current object only
	*/
	void setDelimiter(char kayvaluedelimiter);

	/*
	* 
	* When called before load(), saves the configuration to the default config file.
	* Initially, the default config file is "./default.ini".
	* 
	* If load was called with an argument:
	*     load(const String& filename)
	* then save() will use the same filename. 
	* 
	* The filename used by the instance can be changed by the setConfigFile() method.
	*/
	bool save();

	/*
	* Saves the configuration object to the specified file
	* The default config file path for the instance is not altered...
	* Use setConfigFile(const String& filename) or load(const String& filename) to set the default filename for the instance
	*/
	bool save(const String& filepath);

	/*
	* Removes the contents of the configuration file - completely wipes it out.
	* Does not preserve anything.  Afterwards, the current section is set
	* to the empty section (""), which is the unnamed section
	* at the beginning of the configuration file.
	*/
	void clear();
	
	/*
	* Loads the default file into the configuration object.
	* By default, the current file is 'default.conf', 
	* but can be overridden by calling the setConfigFile(const String& filename) method.
	* This method does not clear the config object before loading.
	* If you load two or more configuration files that have the same sections,
	* they are effectively merged.  In this case, data members that have the same
	* name will get the value of the last file loaded. This comes in handy if
	* you load a global config file first, and you want to override
	* some custom fields by subsequently loading a "preferences" file tailored to an individual.
	* Use clear() if the config object already has data that you want to completely discard before loading
	* a new file, or use another Config object instance.
	*/
	bool load();

	/*
	* Adds the file's configuration info to the current object.
	* Does not delete any existing data in the config object. 
	* The default config file path is not altered...
	* Use setConfigFile() to permanently set the default config file for load() and save()
	* This method does not clear the config object before loading.
	* Use clear() if the config object already has data that you want to discard.
	*/
	bool load(const String& filename);


	/*
	* Sets the current working [section], possibly creating a new section
	* The default section is "" (the untitled section at the beginning of the configuration file).  
	* If the new section cannot be found, and <b>shouldCreate</b> is <b>true</b>,
	*  then the section will be created and will exist at the end of all other sections.  
	* If the new section cannot be found, and <b>shouldCreate</b> is <b>false</b>,
	*  then the current section remains unchanged, and the method returns false.
	* Leading and trailing whitespace is not preserved when the file is written,
	*  and as such should be avoided when naming sections
	*/
	bool setSection(const String& sectionname, bool shouldCreate);

	/*
	* Sets the current working section, creating the section if it does not exist.
	* See <b><i>setSection(const String& sectionname, bool shouldCreate)</i></b> where <i>shouldCreate</i> = true.
	*/
	bool setSection(const String& sectionname);


	/*
	* Deletes the section identified by <i>sectionname</i> and all data associated with it
	* Returns false if the section does not exist or has already been deleted.
	* If the object is saved, the entire section will be commented out.
	* If, during the lifetime of this object, the section is re-created, then the section will be revived, but all
	* previous data members remain commented (as if deleted) unless/until recreated (see deleteData())
	*/
	bool deleteSection(const String& sectionname);


	/*
	* Returns the number of sections in the entire configuration file
	* This number includes the default section - ""  (the empty section at the beginning of the file) 
	* Sections within the configuration file are identifed by [Square Brackets] surrounding the name of the section.
	* Whitespace surrounding the section name is ignored. So [   This Section    ] and [This Section] are identical.
	* Section names <b>are</b> case sensitive.  
	* The default section is the empty section - the unnamed section at the beginning of the file that
	* exists before any other [named] sections. This section exists even if the first line of the file
	* contains a [named section].  The empty section will simply be void of any data.
	* As such, the return value will always be >= 1.
	*/
	int getNumSections() const;


	/*
	* Enumeration method to discover sections
	* Returns the section name at the given index,
	* or NULL if the index is out of range
	* If the section has no name, but is a valid index, then it will return the empty string ("")
	*/
	String getSectionNameAt(int index) const;


	/*
	* Returns the number of data elements for the current section
	*
	* <b>Example:</b>
	* 
	* Given the following configuration:
	*/
	int getNumDataMembers() const;

	/*
	* Enumeration method to discover data members within the current section
	* Returns the name of the data member at 
	* the specified index within the current
	* section, or NULL if the index is out of range.
	*
	*/
	String getDataNameAt(int index) const;

	/*
	* Returns true if a data member exists with the given 
	* name within the current section
	*/
	bool exists(const String& name) const;

	/*
	* Returns the boolean value of the data identified by <i>name</i> within the current section
	* This is a helper function that converts the string data stored in the config object to a boolean
	* Returns true if the current value is "on" or 1,
	* or if the value starts with the letter 't' or 'y'
	* ( all of the above are case insensitive )
	* returns false otherwise
	*/
	bool getBoolValue(const String& name) const;

	/*
	* Returns the integer value of the data identifed by <i>name</i> within the current section
	* This is a helper function that converts the string value stored in the config object to an int.
	* Returns 0 if the data does not exist or if an integer value cannot be determined.
	*/
	int getIntValue(const String& name) const;

	/*
	* Returns the double value, or 0 if a double value cannot be determined
	* Thie is a helper function that converts the string value stored in the config object to a double
	*/
	double getDoubleValue(const String& name) const;

	/*
	* Returns the string-character value.
	* Unless the value is quoted, leading and trailing whitespace is stripped.
	* If the value is quoted, the quotes are removed, and leading and trailing whitespace
	* within the quotes are preserved.
	*/
	String getValue(const String& name) const;

	/*
	* Same as <code>String getValue(const String& name)</code>
	* @deprecated
	*/
	String getStringValue(const String& name) const;

	/*
	* Sets the named value within the current section to "true" or "false"
	* This is a helper function that converts a bool to the string value
	* that the config object expects.
	* If the value is already set for the data item, the value is changed.
	* If the value is not already set, it is created
	*/
	void setBoolValue(const String& name, bool value);

	/*
	* Sets the named value within the current section to the specified integer
	* The config object stores values as strings- this is a helper method
	* that converts an integer to the expected string value.
	* If the value is already set for the data item, the value is changed.
	* If the value is not already set, it is created
	*/
	void setIntValue(const String& name, int value);

	/*
	* Sets the value for a data item within the current section to the specified double
	* The config object stores values as strings- this is a helper method
	* that converts an integer to a string value to be stored.
	* If the value is already set for the data item, the value is changed.
	* If the value is not already set, it is created
	* 
	*/
	void setDoubleValue(const String& name, double value);


	/*
	* Sets the value for a data item within the current section to the specified string
	* If the value is already set for the data item, the value is changed.
	* If the value is not already set, it is created.
	* If leading and/or trailing whitespace exists within the value, it will be preserved in
	* the config file.  The config object will automatically surround the value with quotes.
	* Likewise, if the value starts with a quote ("), then the value
	* will necessarily be surrounded by quotes to preserve it.  As such, programs do not have to, (and
	* in fact should not ) perform their own quoting of values.  You should provide you own
	* quotes only when you are modifying the config/ini file using a text editor or some other means
	* besides the RudeConfig object.
	*/
	void setValue(const String& name, const String& value);

	/*
	* Same as setValue(const String& name, const String& value);
	* @deprecated
	*/
	void setStringValue(const String& name, const String& value);

	/*
	* Deletes the data member identified by <i>name</i> (if it exists) in the current section.
	* If the configuration object is saved, 
	* then the data member will be preserved by being commented out.
	* If a new value is later assigned to this 
	* value (in the lifetime of the instance),
	* then it becomes undeleted (uncommented).
	* Values can only be revived this way using the same instance they were deleted with.
	* Otherwise, they become permanent comments.
	* See <code>preserveDeletedData(bool shouldPreserve)</code> to alter this behavior.
	*/
	bool deleteData(const String& name);


private:

	rude::config::ConfigImpl *d_implementation;	
	
}; // End class Int


#endif // __DTL_CONFIGFILE_H__
