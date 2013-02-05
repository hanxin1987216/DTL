/***************************************************************************************************
File.cpp:	
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	the test for file operation

Author:
	yang.bing

Creating Time:
	2012-09-03
***************************************************************************************************/
#include <dtl/dtl.h>
#include <dtprec.h>
#include <dtl/io/file.h>
#include <stdio.h>
int main(void)
{
	/* create filepath */
	String strPath("/root/Desktop/file"); 
	/* init file */
	File file(strPath);
	
	/* if exists */
	if (file.exists()) {
		cout << "文件存在" << endl;
	} else {
		cout << "文件不存在" <<endl;
		return -1;
	}
	
	
	/* output len of file */
	cout << "len = " << file.getLength() << endl;
	
	/* readonmly  permission*/
	cout << "read only ? :" << file.isReadonly() <<endl;
	/* set Readonly */
	file.setReadonly(1);
	/* readonmly  permission*/
	cout << "read only ? :" << file.isReadonly() <<endl;
	
	/* create new name */
	cout << "oldname :" << file.getName().getCStr() << endl;
	String strName("/root/Desktop/newFileName");
	file.rename(strName);
	cout << "newname:"  << file.getName().getCStr() <<endl;
	
	/* copy  file */
	String strNewFileName("/root/Desktop/newFile");
	file.copy(strNewFileName, 1);  /* successful */
	/* 截断方法 */
	cout << "截断前长度" << file.getLength() << endl;
	int64  len = 2;
//	int64  num = truncate(len);
	cout << "截断后长度" << file.getLength() << endl;
	
	//create
//	file.create();
	//remove
	file.remove();
	
	return 0;
}
