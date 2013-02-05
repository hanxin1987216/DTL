/***************************************************************************************************
streamreader.h
 	Copyright (c) Datatom Co., Ltd.(2012 - 2013), All rights reserved.

Purpose:
	streamreader �ı���
	
Auther:
	����½ (liu.jialu@datatom.com)

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
    * ���ı���ÿ�ж���ŵ�һ��string��������
    * @param path: �ļ���
    * @param filelines: ���ı�ÿ�д���filelines��
    * @noreturn
    */
	void readLines(const string &path, vector<string> &filelines);
	
	/**
    * ���ı���ÿ�ж���ŵ�һ��string��������
    * @param lines: ���ı�ÿ�з���lines��������
    * @noreturn
    */	
    void readLines (vector<string> &lines);
	
    /**
    * ��ȡ�ı��е�һ���ֽ�
	* no param
    * @return ��һ��char����
    */
    char readChar (void); 
	
     /**
    * ��ȡ�ı���һ��
	* no param
    * @return :����һ��string�����ļ��ĵ�ǰһ��
    */	                
    string readLine (void); 
    
	/**
    * �����ļ���ǰָ��ָ������漸��
    * @param count :��Ҫ����������
    * @noreturn  ��
    */
	void skipLine (size_t &count);	

	/**
    * �ض�ĳһ�У��������ո��ʱ�ض�
    * @return �� ����������һ���ո�ǰ��string      
    */
	string readString (char endChar = ' ');

    /**
    * ֻҪ����ָ���ַ����������ַ��ͽض�
    * @param anyEndChars��ָ�����ַ����������ַ���
    * @return ��     ����������һ��ָ���ַ�ǰ��string  
    */
    string readString (const string& anyEndChars);  
	
    /**
    * �ж��ı��Ƿ񵽽�β��
	* @return ������һ��bool ����β������ false ���� true
    */
    bool hasMore (void);

    /**
    * �ر��ļ�
    */
    void close (void);	
	
private:
	fstream  	_file;
	string 		_path;
	int 		_localpos;

};