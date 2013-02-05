/***************************************************************************************************
 MailSender.cpp
	C++ Network Library, Copyright (c) Datatom Software, Inc.(2012)

Author:
	chen.dawei@datatom.com
Creating Time:
	2012-11-5
***************************************************************************************************/
#include <dtprec.h>

#include "../prec.h"
#include "../lang/string.h"
#include "../sys/exception.h"
#include "../io/path.h"
#include "../config/configfile.h"


#include <Poco/Net/MailMessage.h>
#include <Poco/Net/MailRecipient.h>
#include <Poco/Net/SMTPClientSession.h>
#include <Poco/Net/StringPartSource.h>
#include <Poco/Net/FilePartSource.h>
#include "Poco/Net/NetException.h"


using Poco::Net::MailMessage;
using Poco::Net::MailRecipient;
using Poco::Net::SMTPClientSession;
using Poco::Net::StringPartSource;
using Poco::Net::FilePartSource;
using Poco::Net::SMTPException;
using Poco::Net::NetException;

#define DTL_CONFIG_FILE 	_T("dtl.config")
#define DTL_SMTP_SERVER		"server"
#define DTL_SMTP_PORT		"port"
#define DTL_SMTP_TIMEOUT	"timeouts"

#include "smtp.h"

MailSender::MailSender(const String &loginAddr, const String &loginPwd)
	: _senderAddr(loginAddr)
	, _senderPwd(loginPwd)
	, _host()
	, _port()
	, _smtpTimeOut()
{
	bool loadres = _config.load (DTL_CONFIG_FILE);
	if (!loadres) {
		String error;
		error.format ("Load %s DTL config file failed!", DTL_CONFIG_FILE);
		THROW (error);
	}		
	
	_config.setSection (_T("smtp"));
	
	_host = _config.getStringValue("server");
	_port = _config.getIntValue("port");
	_smtpTimeOut = _config.getIntValue("timeouts"); 	// 单位秒

	try
	{
		Poco::Timespan	timeouts(_smtpTimeOut, 0);
	
		_session = new SMTPClientSession(_host.getCStr(), _port);
		_session->setTimeout(timeouts);
		_session->login(SMTPClientSession::AUTH_LOGIN,
							loginAddr.getCStr(), 
							loginPwd.getCStr());
	}
	catch(SMTPException &smtpexc)
	{
		THROW(smtpexc.what());
	}
	catch(NetException &netexc)
	{
		THROW(netexc.what());
	}	
}
	
MailSender::~MailSender()
{
	if (_session) {
		_session->close();
		delete _session;
		_session = 0;
	}
	
	if(!_config.save())
		THROW("save smtp config failed");
}

	
/**发送带附件的邮件
*
* @param subject  		邮件主题
* @param recev  		收件人信息，支持多人抄送和密件抄送
* @param sendContent	发送内容
* @param attachmentPath 附件本地路径,支持多个
**/
void 
MailSender::sendMail(const String &subject,
						const vector<Receiver> &recev, 
						const String &sendContent, 
						std::vector<String>	&paths)
{
	if(recev.empty())
		THROW("not find receiver");
	
		
	try
	{	MailMessage message;
		message.setSubject(subject.getCStr());	
		message.setSender(_senderAddr.getCStr());
		for(size_t n = 0; n < recev.size(); n ++ )
		{		
			message.addRecipient(MailRecipient((MailRecipient::RecipientType)recev[n]._type,
								recev[n]._addr.getCStr(),			
								recev[n]._realname.getCStr()));			
		}
		message.addContent(new StringPartSource(sendContent.getCStr()));
		

		for(size_t i = 0; i < paths.size() ; i++)
		{
			if( Path::isAbsolutePath(paths[i]) && Path::isValidPath(paths[i]))
				message.addAttachment((Path::getFileName(paths[i])).getCStr(), new FilePartSource(paths[i].getCStr()));
			else 
			{
				String error;
				error.format("%s is an invalid path or not an absolute path",paths[i].getCStr());
				THROW(error);
			}
		}
			
		
		_session->sendMessage(message);
	}
	catch(SMTPException &exec)
	{
		THROW(exec.what());
	}
	catch( NetException &exec)
	{
		THROW(exec.what());
	}
}


///查询SMTP服务器相关配置项

//获得全部配置信息
SMTPConfig 
MailSender::getSMTPConfig(void)
{
	return SMTPConfig (_host, _port, _smtpTimeOut);
}



///设置SMTP服务器相关配置项

//设置全部配置信息
void 
MailSender::setSMTPConfig(const SMTPConfig &smtpconfig)
{
	_config.setStringValue(DTL_SMTP_SERVER,smtpconfig._server);
	_config.setIntValue(DTL_SMTP_PORT, smtpconfig._port);
	_config.setIntValue(DTL_SMTP_TIMEOUT, smtpconfig._timeout);
}
