/***************************************************************************************************
streamreader.h
 	Copyright (c) Datatom Co., Ltd.(2012 - 2013), All rights reserved.

Purpose:
	streamreader 文本读
	
Auther:
	刘佳陆 (liu.jialu@datatom.com)

Created Time:
	2012-01-29
***************************************************************************************************/
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstddef>
using namespace std;

#define MAX_LENGTH 256
class StreamReader
{
public:	
	/**
	*open the file
	*@param file: the file name
	*/
	StreamReader (const string &file);
	
public:
	/**
    * 将文本中每行都存放到一个string的容器中
    * @param path: 文件名
    * @param filelines: 将文本每行存入filelines中
    * @noreturn
    */
	void readLines(const string &path, vector<string> &filelines);
	
	/**
    * 将文本中每行都存放到一个string的容器中
    * @param lines: 将文本每行放入lines的容器中
    * @noreturn
    */	
    void readLines (vector<string> &lines);
	
    /**
    * 读取文本中的一个字节
	* no param
    * @return ：一个char类型
    */
    char readChar (void); 
	
     /**
    * 读取文本的一行
	* no param
    * @return :返回一个string，是文件的当前一行
    */	                
    string readLine (void); 
    
	/**
    * 跳过文件当前指针指向的下面几行
    * @param count :想要跳过的行数
    * @noreturn  ：
    */
	void skipLine (size_t &count);	

	/**
    * 截断某一行，当遇到空格符时截断
    * @return ： 返回遇到第一个空格前的string      
    */
	string readString (char endChar = ' ');

    /**
    * 只要遇到指定字符串包含的字符就截断
    * @param anyEndChars：指定的字符，可以是字符串
    * @return ：     返回遇到第一个指定字符前的string  
    */
    string readString (const string& anyEndChars);  
	
    /**
    * 判断文本是否到结尾处
	* @return ：返回一个bool ，到尾部返回 false 否则 true
    */
    bool hasMore (void);

    /**
    * 关闭文件
    */
    void close (void);	
	
private:
	fstream  	_file;
	string 		_path;
	int 		_localpos;

};