/****************************************************************************************************
filetool.c
 	Copyright (c) Datatom, Inc.(2012 - 2013), All rights reserved.

Purpose:
    tools for get file type
	
Auther:
    ying.yemin@datatom.com

Created Time:
	2013-01-07
****************************************************************************************************/
#include <dtprec.h>
#include "../prec.h"
#include "../mono_base/uglify.h"
#include "../lang/string.h"
#include "comdef.h"
#include "file.h"
#include "streamreader.h"
#include "path.h"
#include "../lang/string.h"
#include "../sys/exception.h"

#include "filetool.h"

const char* MEDIA_EXT[] = {".mpg",".wmv",".rmvb",".mxf", ".mov",".avi",".rm",".flv",".3gp",".ogg",".mp4",".mkv",".asf",".asx",".mpeg",".mpe",".dv",".vob",".ts"};
const char* DOC_EXT[] = {".doc",".docx",".ppt",".pptx",".xls",".xlsx",".pdf"};
const char* AUDIO_EXT[] = {".wma", ".flac", ".aac", ".mmf", ".amr", ".ogg", ".mp2", ".ape", ".pcm", ".tta", ".au", ".tak", ".wv", ".aiff", ".wav", ".mp3"};
const char* IMAGE_EXT[] = {".jpg", ".png", ".gif", ".tiff"};

int 
FileTool::filetool_init(const String &filescript) {
    // read from filescript
    StreamReader fileread(filescript);
	File file(filescript);
    if(!file.exists()){
		return -1;
	}
    if (_gmagic == NULL) {
		return -1;
	}
    int ret = magic_load(_gmagic, "magic");
    if (ret != 0) {
        magic_close(_gmagic);
        return -1;
    }
	String line;
	while ((line = fileread.readLine()) != ""){
		MapData map;
		fillmap(map, line);
	}
	return 0;
}

int 
FileTool::filetool_check(int &typecode, const String &filename) {
    String magictext;
    magictext = magic_file(_gmagic, filename.getCStr());
    if (magictext == "") {
		typecode = 4;
		return -1;
	}
	for (size_t i = 0; i < _maps.size(); ++i){
		if (magictext.find(_maps[i].value) != String::NO_POSITION){
			typecode = getFileType(_maps[i].key);
			return 0;
		}
	}
	typecode = 4;
	return -1;
}

int 
FileTool::fillmap(MapData &map, const String &line) {
    if ((line == "\n") || 
        (line == "\r\n") || 
        line[0] == '#') {
        return -1;
    }
    int64 pos = line.find("||");
	if (pos == String::NO_POSITION){
		return -1;
	}
    map.key = line.subString(0, pos);
    map.value = line.subString(pos+2, 50);
	_maps.push_back(map);
    return 0;
}

int
FileTool::getFileType(const String &strtype)
{
	if(strtype == "FILETOOL_DOC")
		return FILETOOL_DOC;
	else if (strtype == "FILETOOL_MEDIA")
		return FILETOOL_MEDIA;
	else if (strtype == "FILETOOL_IMAGE")
		return FILETOOL_IMAGE;
	else if (strtype == "FILETOOL_AUDIO")
		return FILETOOL_AUDIO;
	else
		return FILETOOL_DATA;
}
int
FileTool::getFileTypeByExt(String &ext)
{
	size_t i;
	ext.toLower();
	for (i=0; i< sizeof(MEDIA_EXT)/sizeof(char *); i++) {
		if (ext == MEDIA_EXT[i]){
			return FILETOOL_MEDIA;
		}
	}
	for (i=0; i< sizeof(DOC_EXT)/sizeof(char *); i++) {
		if (ext == DOC_EXT[i]){
			return FILETOOL_DOC;
		}
	}
	for (i=0; i< sizeof(AUDIO_EXT)/sizeof(char *); i++) {
		if (ext == AUDIO_EXT[i]){
			return FILETOOL_AUDIO;
		}
	}
	for (i=0; i< sizeof(IMAGE_EXT)/sizeof(char *); i++) {
		if (ext == IMAGE_EXT[i]){
			return FILETOOL_IMAGE;
		}
	}
	return FILETOOL_DATA;
}
