/****************************************************************************************************
filetool.h
 	Copyright (c) Datatom, Inc.(2011 - 2012), All rights reserved.

Purpose:
    tools for get file type
	
Auther:
    fan.fei@datatom.com

Created Time:
	2012-06-11

Example:
    this is how filetool working 

    #include "filetool.h"

    // *NOTE*: filetool.rules is the default rule script of datrix
    //         check README to get more details of rule script
    if (0 != filetool_init("filetool.rules")) { 
        // do your expcetion here
    }

    ...

    char * filename = "yourfile_to_check";
    int typecode;
    if (0 != filetool_check(&typecode, filename)) {
        // do your exception here
    }
    printf("the type of %s is %d\n", filename, typecode);

    ...

    filetool_uninit();
****************************************************************************************************/
#ifndef __FILE_TOOL_19342
#define __FILE_TOOL_19342

#include "magic.h"

enum {
    FILETOOL_DOC = 1,
    FILETOOL_MEDIA,
    FILETOOL_IMAGE,
    FILETOOL_DATA,
    FILETOOL_AUDIO,
};

struct MapData
{
	String key;
	String value;
};

class FileTool
{
public:
	FileTool() {_gmagic = magic_open(MAGIC_NONE);}
	~FileTool() {magic_close(_gmagic);}

public:

	/**
	 * init libfiletool
	 *
	 * @filescript: name of rule file
	 *
	 * @return: if init success, return 0, otherwise return 1
	 *
	 */
	int filetool_init(const String &filescript);

	/**
	 * check file's type
	 *
	 * @typecode: a pointer to int, which contain the file's type by return.
	 *            it'll be FILE_DOC, FILE_MEDIA, FILE_IMAGE or FILE_DATA due to check result
	 *            if *typecode is -1, it means something unexpected during the check
	 *
	 * @filename: path of the file to examine the type
	 *
	 * @return: if success return 0, otherwise return 1;
	 */
	int filetool_check(int &typecode, const String &filename);

	int getFileTypeByExt(String &ext);
	
private:
	int fillmap(MapData &map, const String &line);
	
	int getFileType(const String &strtype);
	
//	int getFileTypeByExt(String &ext);
	
private:
	//////////////////////////////////////////////////
	// struct and global variables
	magic_t _gmagic;
	vector<MapData> _maps;
};

#endif
