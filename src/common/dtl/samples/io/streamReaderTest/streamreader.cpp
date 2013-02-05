/***************************************************************************************************
streamreader.cpp
 	Copyright (c) Datatom Co., Ltd.(2012 - 2013), All rights reserved.

Purpose:
	streamreader ÎÄ±¾¶Á
	
Auther:
	Áõ¼ÑÂ½ (liu.jialu@datatom.com)

Created Time:
	2012-01-29
***************************************************************************************************/
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstddef>
#include <errno.h>
#include <string.h>
#include "streamreader.h"
using namespace std;

StreamReader::StreamReader (const string &file)
{
	_path = file;
	_file.open(_path.c_str());
	if(!_file)                                             
	{	cout <<_file;
		char * mesg = strerror(errno);              
		printf("Mesg:%s\n",mesg);
		return ;
	}
}

void 
StreamReader::close (void)
{
	if(_file.is_open())
	{
		_file.close();
		cout << "file close success!" << endl;
	}
}

void
StreamReader::readLines (vector<string> &lines)
{
	if(_file.is_open()) 
	{	
		string tmp_str;	
		while(!_file.eof())
		{
			getline(_file, tmp_str);
			lines.push_back(tmp_str);
		}
	}
}

char 
StreamReader::readChar (void)
{
	char tmp;
	if(_file.is_open())
	{		
		if(!_file.eof())
		{
			_file.get(tmp);
		}
		return tmp;	
	}
	else
	{
		cout << "file is closed!"<<endl;
	}
	
	return -1;
} 

string
StreamReader::readLine (void)
{	
	if(_file.is_open())
	{
		string tmp;
		getline(_file,tmp);
		return tmp;
	}
	
	return "";
}

void
StreamReader::skipLine (size_t &count)
{
	string tmp;
	if(_file.is_open())
	{
		for(size_t i = 0; i < count ; ++i)
		{	
			getline(_file,tmp);
		}
	}
}

bool
StreamReader::hasMore (void)
{
	if(_file.is_open())
	{
		if(_file.eof())
			return false;
		else
			return true;
	}
	else{
		return false;
	}
}

string
StreamReader::readString (const string& anyEndChars)
{
	string word;
	int count = 0;
	size_t loop = 1;
	int short_length = anyEndChars.size() - 1;
	int length = anyEndChars.size();
	char tmp_char;	
	char tmp_short;	
	do{
		_file.get(tmp_char);
		tmp_short = anyEndChars[0];

		if(tmp_char == tmp_short)
		{
			_file.seekg(-1,ios::cur);
			count = 0;
			do{
				_file.get(tmp_char);
				tmp_short = anyEndChars[count];
				count = count + 1;
			}while((tmp_char == tmp_short) && (count <= short_length) && (!_file.eof()));
			if((tmp_char == tmp_short) && (count == length))
			{
				loop = 0;
			}
			else{
				count = 0 - count;
				_file.seekg(count,ios::cur);
				_file.get(tmp_char);
				word.push_back(tmp_char);				
			}
		}
		else{
			word.push_back(tmp_char);
		}
	}while((!_file.eof()) && (loop == 1));

	return word;	
}




string
StreamReader::readString (char endChar)
{
	string word;
	
	char tmp_c;
	if(_file.is_open())
	{
			if(endChar == ' ')
			{
				do
				{
					_file.get(tmp_c);								
				}while((!_file.eof()) && (tmp_c == ' '));
				_file.seekg(-1,ios::cur);
				do
				{
					_file.get(tmp_c);
					word.push_back(tmp_c);
				}while((!_file.eof()) && (tmp_c != ' '));				
			}
			else{
				do
				{
					_file.get(tmp_c);
					if((tmp_c != endChar) )                                    //&& (tmp_c != '\n')
					{
						word.push_back(tmp_c);		
					}
				}while((!_file.eof()) && (tmp_c != endChar));
			}
		
	}	
	
	return word;
	
}
