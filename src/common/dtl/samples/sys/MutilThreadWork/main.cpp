/***************************************************************************************************
main.cpp:	
	C++ Foundation Library TestCase header files
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	客户端调用接口	

Author:
        liu.wenxue@datatom.com	

Creating Time:
	2013-01-31
***************************************************************************************************/


#include <dtprec.h>
#include <dtl/dtl.h>

#include "mail.h"
#include "mutilThread.h"
#include "MutilThreadRead.h"
#include "MutilThreadWrite.h"
#include "MutilThreadSendMail.h"
#include "strategy.h"
#include "tcJson.h"



int main()
{
	InitDTLibrary();

	try{
	/*
		tcJson json;
		cJSON *root;
		cJSON *pRoot;
		char *cStr;
		pRoot = json.createJson(root);
		//json.printFormat(pRoot);
		//json.printUnformat(pRoot);
		
		cJSON *pChild = pRoot->child;
		//json.printFormat(pChild);
		//json.printFormat(pChild->next);
		json.getValToStr(pChild->next, "name");
		json.getStrVal(pChild);
		json.getIntVal(pRoot);
		json.getDoubleVal(pRoot);
	*/	
	    
		//读文件线程
	    String threadName = "1";
		String pathName = "/mnt/hgfs/program/test.txt";
		String content;
				
		cout << "------------thread 1 start------------ " << endl;
		MutilThread *mThreadRead(new MutilThreadRead(threadName, pathName, content));
		TreadStartegy startegyThreadRead(mThreadRead);
		startegyThreadRead.threadRun();
		
			
		//写文件线程
		threadName = "2";
		pathName =  "/mnt/hgfs/program/test1.txt";
				
		cout << "----------thread 2 start------------ " << endl;
		MutilThread *mThreadWrite(new MutilThreadWrite(threadName, pathName, content));
		TreadStartegy startegyThreadWrite(mThreadWrite);
		startegyThreadWrite.threadRun();
		
		
		//发件人登录	
 		String loginName = "747411738@qq.com";
		String loginPwd = "654lwx@qq";
		//主题
		String subject = "问题";
		//接受者信息
		String addr = "747411738@qq.com";
		String realName = "liuwenxue";
		Receiver rec(PRIMARY_RECEVIVER, addr, realName);
		vector<Receiver> recv;
		recv.push_back(rec);
		//发件人内容
		String sendContent(content);	
		//附件
		pathName = "/mnt/hgfs/program/test1.txt";
		std::vector<String> attach;
		attach.push_back(pathName);
	        
	    threadName = "3";    	
		//发邮件线程
		cout << "--------thread 3 start---------- " << endl;
		MutilThread *mThreadSendMail(new MutilThreadSendMail(threadName,
															loginName,
															loginPwd,
															subject, 
															recv, 
															sendContent, 
															attach ));
		TreadStartegy startegyThreadSendMail(mThreadSendMail);
		startegyThreadSendMail.threadRun();

	
		
	}catch(Exception &exc)
	{
		cout << exc.toString().getCStr() << endl;
	}

	return 0;
}
