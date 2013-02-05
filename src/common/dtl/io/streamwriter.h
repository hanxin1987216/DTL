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
#ifndef __STREAMWRITER_HEAD_H__
#define __STREAMWRITER_HEAD_H__

#if PRAGMA_ONCE
#	pragma once
#endif

class DTL_DLLEXPORT StreamWriter
{
public:	
	/**
	* 打开文本文件写操作的构造函数
	* @param file 文件的名字
	* @param append 默认将原来文本抹掉重新写；append = true 紧接着文本写
	*/
	StreamWriter (const String &file, bool append = false);
	
	~StreamWriter (void) {
		close ();
	}
	
public:

	/**
	* 重新打开关闭的文件
	* @param append 默认append = true 紧接着文本写；false：将原来文本抹掉
	*/	
	int reopen (bool append = true);
	 
	/**
	* 强制写入磁盘
	* @return no 
	* @throw IOException If an I/O error occurs.
	*/
	void flush (void);
	 
	/**
	* 写入磁盘后关闭
	* @return ：no
	*/
	void close (void);
	 
	/**
	* 讲一个char类型写入到文本文件中
	* @param str : 要写入的字符
	* @return no
	* @throw IOException If an I/O error occurs.
	*/
	void writeChar (const tchar_t str);
	 
	/**
	* 将一个 c-style string 写入到文本文件中
	* @param str ：char类型的指针
	* @return ：no
	* @throw ArgumentException If the string pointer is null.
	* @throw IOException If an I/O error occurs.
	*/
	void writeChars (const tchar_t *str);
	 
	/**
	* 将一个指定长度的 c-style string 写入到文本文件中
	* @param str ：char类型的指针，指向string
	* @param size ：char* 的长度
	* @return ：no
	* @throw ArgumentException If the string pointer is null.
	* @throw IOException If an I/O error occurs.
	*/
	void writeChars (const tchar_t *str, size_t size);
	 
	/**
	* 将一个String类型的字符串添加到文件中
	*
	* @param str ：要添加的字符串
	* @return ：no 
	* @throw IOException If an I/O error occurs.
	*/
	void writeString (const String& str);
	
	
		 
	/**
	* 将一个字符串写入
	* @param str ：要写入的字符串
	* @param endChar ：当遇到字符endChar时停止写入到文本中
	* @return ：no
	* @throw IOException If an I/O error occurs.
	*/
	void writeString (const String& str, tchar_t endChar);  
	 
	/**
	* 写入一个字符并换行
	* @param str 要写入的字符串
	* @return no
	* @throw IOException If an I/O error occurs.
	*/
	void writeLine (const String& str);
	
	/**
	* 将多个String类型的字符串添加到文件中
	*
	* @param lines 要添加的字符串
	* @return no 
	* @throw IOException If an I/O error occurs.
	*/
	void writeLines (vector<String> &lines);
		
private:
	int			_file;
	String      _path;
};
#endif //  __STREAMWRITER_HEAD_H__
