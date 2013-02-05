/***************************************************************************************************
main.cpp:	
	C++ Foundation Library TestCase source files
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	Test case for Thread class
    
	
	//qq 测试可以
	//公司邮箱测试不行，已放弃
Author:
       liu.wenxue@datatom.com	

Creating Time:
	2012-01-29
***************************************************************************************************/

#include <dtprec.h>
#include <dtl/dtl.h>


int main()
{
	//subject
	String subject = "文件";

	//recev
	String realName = "wenxueliu";
	String addr = "747411738@qq.com";
  	Receiver rec(PRIMARY_RECEVIVER, addr, realName);
	std::vector<Receiver> recev;
	recev.push_back(rec);
	
	//sendContent
	String sendContent = "hello mail";
    String pathName = "/mnt/hgfs/program/test.txt";
	
	//path
	std::vector<String> path;
    path.push_back(pathName);

	MailSender	mailTo("liu.wenxue@datatom.com","liuwenxue");
	
	mailTo.sendMail(subject, recev, sendContent, path);
}