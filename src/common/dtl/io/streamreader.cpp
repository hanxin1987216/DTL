/***************************************************************************************************
streamreader.cpp
 	Copyright (c) Datatom Co., Ltd.(2012 - 2013), All rights reserved.

Purpose:
	streamreader 文本读
	
Auther:
	刘佳陆 (liu.jialu@datatom.com)

Created Time:
	2012-01-29
***************************************************************************************************/
#include "../prec.h"
#include "../lang/string.h"
#include "../sys/exception.h"
#include <stdio.h>
#include <fcntl.h>

#include "./streamreader.h"

#define CHECK_CLOSE(file)	\
	if (file == NULL)	\
		return;
				
#define MAX_LINE 256

StreamReader::StreamReader (const String &file)
{
	_path = file;
	_file = fopen(file.getCStr(), "r");
	if(_file == NULL)                                             
		THROW ("open file failed");
}

void 
StreamReader::close (void)
{
	CHECK_CLOSE(_file);
	
	int fd = fclose (_file);
	if(fd == EOF)
	{
		THROW ("close file failed");
	}

	_file = NULL;
}

void
StreamReader::readLines (vector<String> &lines)
{
	CHECK_CLOSE(_file);
	
	char *line = 0;
	size_t len;
	ssize_t result = 0;
	while ((result = getline(&line, &len, _file)) != -1) {
    	if (line == 0) 
    		continue;
    	if (strlen (line) == 0) 
    		continue;
		String tmp_str (line);
    	lines.push_back (tmp_str);
    }
}


String
StreamReader::readLine (void)
{
	if (_file == NULL)
		return "";
	
	char *line = 0;
	size_t len;
	ssize_t result = 0;
	String tmp;

	if((!feof(_file)) && ((result = getline(&line, &len, _file)) != -1))
	{
		String tmp_str (line);
		tmp = tmp_str;
	}
	
	return tmp;
}

char 
StreamReader::readChar (void)
{
	if (_file == NULL)
		return -1;
	
	char tmp = -1;		
	
	if(!feof(_file))
	{
		tmp = fgetc(_file);
	}

	return tmp;	
} 



void
StreamReader::skipLine (size_t &count)
{
	CHECK_CLOSE(_file);
	
	char *line = 0;
	size_t len;
	ssize_t result = 0;
	for(size_t i = 0; i < count ; ++i) {
		if((!feof(_file)) && ((result = getline(&line, &len, _file)) != -1))
		{
		}
	}
		
}

bool
StreamReader::hasMore (void)
{
	if (_file == NULL)
		return false;
	
	fgetc(_file);
	bool result = feof(_file);
	fseek(_file, -(sizeof(char)*1),SEEK_CUR);
	
	return (!result);
}


String
StreamReader::read ()
{
	String ret;
	while (hasMore ()) {
		ret += readChar ();
	}

	return ret;
}

String
StreamReader::readString (const String& anyEndChars)
{
	if (_file == NULL)
		return "";	
	
	String word;
	int count = 0;
	size_t loop = 1;
	int length = anyEndChars.getLength();
	char tmp_char;	
	char tmp_short;	
	do{
		tmp_char = fgetc(_file);
		tmp_short = anyEndChars[0];

		if(tmp_char == tmp_short)
		{
			fseek(_file, -(sizeof(char)*1),SEEK_CUR);
			count = 0;
			
			do{
				tmp_char = fgetc(_file);
				tmp_short = anyEndChars[count];
				count = count + 1;
			}while((tmp_char == tmp_short) && (count < length) && (!feof(_file)));
			
			if((tmp_char == tmp_short) && (count == length))
				loop = 0;				
			else{
				count = 0 - count;
				fseek(_file, (sizeof(char)*count), SEEK_CUR);
				tmp_char = fgetc(_file);
				word.append(tmp_char, 1);	
			}
		}
		else{
			word.append(tmp_char, 1);
		}
	}while((!feof(_file)) && (loop == 1));

	return word;	
}




String
StreamReader::readString (char endChar)
{
	if (_file == NULL)
		return "";	
	
	String word;	
	char tmp_c;

	if(endChar == ' ')
	{
		do
		{
			tmp_c = fgetc(_file);							
		}while((!feof(_file)) && (tmp_c == ' '));
		fseek(_file, -(sizeof(char)*1), SEEK_CUR);
		do
		{
			tmp_c = fgetc(_file);
			word.append(tmp_c, 1);
		}while((!feof(_file)) && (tmp_c != ' '));				
	}
	else{
		do
		{
			tmp_c = fgetc(_file);
			if((tmp_c != endChar) )  
			{
				word.append(tmp_c, 1);		
			}
		}while((!feof(_file)) && (tmp_c != endChar));
	}
		

	
	return word;
	
}
