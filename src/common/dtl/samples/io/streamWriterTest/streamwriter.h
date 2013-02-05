/***************************************************************************************************
streamwriter.h
 	Copyright (c) Datatom Co., Ltd.(2012 - 2013), All rights reserved.

Purpose:
	streamwriter �ı��ļ���д����
	
Auther:
	����½ (liu.jialu@datatom.com)

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
	* ���ı��ļ�д�����Ĺ��캯��
	* @param file :�ļ�������
	* @param append ��Ĭ�Ͻ�ԭ���ı�Ĩ������д��append = true �������ı�д
	*/
	StreamWriter (const String &file, bool append = false);
	
	virtual ~StreamWriter (void) {}
	
public:
	 
	/**
	* ǿ��д�����
	* @return ��no 
	* @throw IOException If an I/O error occurs.
	*/
	virtual void flush (void);
	 
	/**
	* д����̺�ر�
	* @return ��no
	* After the method called, call other methods of this class should cause
	IOException.
	*/
	virtual void fclose (void);
	 
	/**
	* ��һ��char����д�뵽�ı��ļ���
	* @param str : Ҫд����ַ�
	* @return ��no
	* @throw IOException If an I/O error occurs.
	*/
	virtual void writeChar (const tchar_t str);
	 
	/**
	* ��һ�� c-style string д�뵽�ı��ļ���
	* @param str ��char���͵�ָ��
	* @return ��no
	* @throw ArgumentException If the string pointer is null.
	* @throw IOException If an I/O error occurs.
	*/
	virtual void writeChars (const tchar_t *str);
	 
	/**
	* ��һ��ָ�����ȵ� c-style string д�뵽�ı��ļ���
	* @param str ��char���͵�ָ�룬ָ��string
	* @param size ��char* �ĳ���
	* @return ��no
	* @throw ArgumentException If the string pointer is null.
	* @throw IOException If an I/O error occurs.
	*/
	virtual void writeChars (const tchar_t *str, size_t size);
	 
	/**
	* ��һ��string���͵��ַ�����ӵ��ļ���
	*
	* @param str ��Ҫ��ӵ��ַ���
	* @return ��no 
	* @throw IOException If an I/O error occurs.
	*/
	virtual void writeString (const String& str);
		 
	/**
	* ��һ���ַ���д��
	* @param str ��Ҫд����ַ���
	* @param endChar ���������ַ�endCharʱֹͣд�뵽�ı���
	* @return ��no
	* @throw IOException If an I/O error occurs.
	*/
	virtual void writeString (const String& str, tchar_t endChar);  
	 
	/**
	* д��һ���ַ�������
	* @param str ��Ҫд����ַ���
	* @return ��no
	* @throw IOException If an I/O error occurs.
	*/
	virtual void writeLine (const String& str);
	
	
private:
	int _file;
	String _path;
	

};