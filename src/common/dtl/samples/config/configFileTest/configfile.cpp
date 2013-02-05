/************************************************
configfile.cpp:
	copyright (c) Datatom Software, Inc.(2012)
Purpose:
	this is to test the configfile 
Auther:
	Zhang.Wencong

Createing Time:2012-7-27

*************************************************/


#include <dtprec.h>
#include <dtl/dtl.h>
#include <dtl/lang/string.h>
#include <dtl/io/file.h>
#include <dtl/io/path.h>
#include <dtl/config/configfile.h>


int main(void)
{
	const String path("a.txt");//define the file
	String strcontext("class");//
	
	ConfigFile configfile;

	configfile.setConfigFile(path); //set the file path
	
	configfile.setSection("name");
	configfile.setStringValue("name", "zhang");
	
	configfile.setSection("class");
	configfile.setValue("class", "tow");
	
	configfile.setSection("score");
	configfile.setIntValue("score", 100);
	
	configfile.save(); // save the file
	
	cout << "the section is:"<<configfile.getSectionNameAt(1).getCStr() << endl;
	
	cout << "the DataName is:"<<configfile.getDataNameAt(0).getCStr() << endl;
	
	cout << "the String is:"<<configfile.getStringValue("class").getCStr() << endl;
	
	cout << "this configfile is:" <<configfile.getConfigFile().getCStr() << endl;
		
	return 0;
}

