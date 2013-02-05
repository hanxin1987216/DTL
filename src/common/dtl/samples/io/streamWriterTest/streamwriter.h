/***************************************************************************************************
streamwriter.h
 	Copyright (c) Datatom Co., Ltd.(2012 - 2013), All rights reserved.

Purpose:
	streamwriter 文本文件的写操作
	
Auther:
	刘佳陆 (liu.jialu@datatom.com)

Created Time:
	2012-02-02
***************************************************************************************************/

#include <iostream>
#include <fstream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
using namespace std;



class StreamWriter
{
public:	
	/**
	* 打开文本文件写操作的构造函数
	* @param file :文件的名字
	* @param append ：默认将原来文本抹掉重新写；append = true 紧接着文本写
	*/
	StreamWriter (const String &file, bool append = false);
	
	virtual ~StreamWriter (void) {}
	
public:
	 
	/**
	* 强制写入磁盘
	* @return ：no 
	* @throw IOException If an I/O error occurs.
	*/
	virtual void flush (void);
	 
	/**
	* 写入磁盘后关闭
	* @return ：no
	* After the method called, call other methods of this class should cause
	IOException.
	*/
	virtual void fclose (void);
	 
	/**
	* 讲一个char类型写入到文本文件中
	* @param str : 要写入的字符
	* @return ：no
	* @throw IOException If an I/O error occurs.
	*/
	virtual void writeChar (const tchar_t str);
	 
	/**
	* 将一个 c-style string 写入到文本文件中
	* @param str ：char类型的指针
	* @return ：no
	* @throw ArgumentException If the string pointer is null.
	* @throw IOException If an I/O error occurs.
	*/
	virtual void writeChars (const tchar_t *str);
	 
	/**
	* 将一个指定长度的 c-style string 写入到文本文件中
	* @param str ：char类型的指针，指向string
	* @param size ：char* 的长度
	* @return ：no
	* @throw ArgumentException If the string pointer is null.
	* @throw IOException If an I/O error occurs.
	*/
	virtual void writeChars (const tchar_t *str, size_t size);
	 
	/**
	* 将一个string类型的字符串添加到文件中
	*
	* @param str ：要添加的字符串
	* @return ：no 
	* @throw IOException If an I/O error occurs.
	*/
	virtual void writeString (const String& str);
		 
	/**
	* 将一个字符串写入
	* @param str ：要写入的字符串
	* @param endChar ：当遇到字符endChar时停止写入到文本中
	* @return ：no
	* @throw IOException If an I/O error occurs.
	*/
	virtual void writeString (const String& str, tchar_t endChar);  
	 
	/**
	* 写入一串字符并换行
	* @param str ：要写入的字符串
	* @return ：no
	* @throw IOException If an I/O error occurs.
	*/
	virtual void writeLine (const String& str);
	
	
private:
	int _file;
	String _path;
	

};