/***************************************************************************************************
mail.cpp:	
	C++ Foundation Library TestCase source files
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	Test case for Thread class

Author:
       liu.wenxue@datatom.com	

Creating Time:
	2012-01-29
***************************************************************************************************/
#include <dtprec.h>
#include <dtl/dtl.h>

#include "mail.h"

void 
Mail::sendMail()
{
	String subject = "文件";
	String realName = "wenxueliu";
	String addr = "747411738@qq.com";

  	Receiver rec(PRIMARY_RECEVIVER, addr, realName);
	std::vector<Receiver> recev;
	recev.push_back(rec);
	
	String sendContent = "hello mail";
    String pathName = "/mnt/hgfs/program/test.txt";
	
	std::vector<String> path;
    path.push_back(pathName);

 	MailSender mailTo("747411738@qq.com","654lwx@qq");
	mailTo.sendMail(subject, recev, sendContent, path);
	
}


