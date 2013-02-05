/***************************************************************************************************
 MailSender.h
	C++ Network Library, Copyright (c) Datatom Software, Inc.(2012)

Author:
	chen.dawei@datatom.com
Creating Time:
	2012-11-5
***************************************************************************************************/
#ifndef __DTL_MAIL_SENDER_H__
#define __DTL_MAIL_SENDER_H__

#include <Poco/Net/MailRecipient.h>
#include <Poco/Net/SMTPClientSession.h>

using Poco::Net::MailRecipient;
using Poco::Net::SMTPClientSession;

enum RecevType
{
	//主收件人
	PRIMARY_RECEVIVER = MailRecipient::PRIMARY_RECIPIENT,
	
	//抄送收件人
	CC_RECEVIVER = MailRecipient::CC_RECIPIENT,
	
	//密件抄送接收者
	BCC_RECEVIVER = MailRecipient::BCC_RECIPIENT,
};


///接受者信息结构体 
struct Receiver
{
public:		
	//标准构造	
	Receiver(RecevType type
			,const String &addr
			,const String realname)
		: _realname(realname)
		, _addr(addr)
		, _type(type)
	{
	
	}	
	
	~Receiver(){}
	
public:
	String 			_realname;	//收件人备注名
	String 			_addr;		//收件人地址
	RecevType		_type;		//收件人类型 
};

///SMTP 配置文件信息结构体
struct SMTPConfig
{
public:
	SMTPConfig(const String &server, int port , int timeout)
		: _server(server)
		, _port(port)
		, _timeout(timeout)
	{
	
	}
	~SMTPConfig(){}
public:
	String		_server;
	int 		_port;
	int			_timeout;

};

////////////////////////////////////////////////////////////////////////
/// MailSender :一个简单的SMTP协议邮件发送类
//
class MailSender 
{
public:
	
	//设置发送者的邮箱地址和登录密码
	MailSender(const String &loginName, const String &loginPwd);
	
	~MailSender();
public:

	/**发送邮件，支持多附件
	*
	* @param subject  		邮件主题
	* @param recev  		收件人信息，支持多人抄送(CC_RECEVIVER)和密件抄送(BCC_RECEVIVER)
	* @param sendContent	发送内容
	* @param attachmentPath 附件本地路径，支持多个
	**/
	void sendMail(const String &subject,
					const vector<Receiver> &recev,
					const String &sendContent,
					std::vector<String>	&paths);
public:

	//设置全部配置信息
	void setSMTPConfig(const SMTPConfig &smtpconfig);

	
	//获得全部配置信息
	SMTPConfig getSMTPConfig(void);
	
private:
	String 				_senderAddr;
	String 				_senderPwd;
	SMTPClientSession	*_session;
	ConfigFile			_config;
	String 				_host;
	int 				_port;
	int 				_smtpTimeOut;
	
	
}; ///end MailSender

#endif 
