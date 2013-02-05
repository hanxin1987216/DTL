/****************************************************************************************************
util.cpp
 	Copyright (c) Datatom, Inc.(2011), All rights reserved.

Purpose:
	util
	
Auther:
	han.xin@datatom.com

Created Time:
	2011-10-08
****************************************************************************************************/
#include <dtprec.h>
#include "../prec.h"

#include "../lang/string.h"
#include "../sys/exception.h"
#include "../prec.h"
#include "../mono_base/uglify.h"
#include "../sys/exception.h"
#include "../io/comdef.h"
#include "../io/file.h"
#include "../io/streamreader.h"
#include "../security/md5.h"


#ifndef __WINDOWS__
	#include <arpa/inet.h>
	#include <netdb.h>
	#include <netinet/in.h>  
	#include <sys/socket.h>
	#include <net/if.h>  
	#include <sys/ioctl.h>  
	#include <sys/types.h>  
#endif


#define MAXINTERFACES   16



#include "util.h"


static String 
getSubCPUInfo (const String &cpuInfo, const String &infoName)
{
	size_t pos = 0;
	pos = cpuInfo.find (infoName);
	if (pos == String::NO_POSITION)
		return String::EMPTY;

	size_t posBegin = 0;
	for (posBegin = pos; posBegin < cpuInfo.getLength (); posBegin++)
		if (cpuInfo [posBegin] == ';')
			break;

	String infoStr = cpuInfo.subString (pos, posBegin - pos);

	return infoStr;
}

String generateCPUVendorInfo (void)
{
	String str ("");
	String filename ("/var/lib/cpuvendoreinfo.txt");

	//
	// open and read cpuinfo file
	//
	File file (filename);
	String cpuInfoStr;
	FILE * pFile;

	try {
		if (file.exists ())
			file.remove();

		file.create ();
		
		//使用linux系统命令cat  /proc/cpuinfo 获取生产厂商与硬件信息
		pFile = popen ( "cat /proc/cpuinfo >/var/lib/cpuvendoreinfo.txt", "r" );
		pclose (pFile);

		StreamReader fileread (filename);		
		while (fileread.hasMore ()) {
			cpuInfoStr += fileread.readLine ();
			cpuInfoStr += _T(";");
		}
		fileread.close ();
		file.remove();
	}
	catch (Exception& e) {
		cout << e.toString().getCStr() << endl;
	}

	//
	// get and cat cpu information
	//
	str += getSubCPUInfo (cpuInfoStr, _T("processor"));
	str	+= getSubCPUInfo (cpuInfoStr, _T("vendor_id"));
	str	+= getSubCPUInfo (cpuInfoStr, _T("cpu_family"));
	str	+= getSubCPUInfo (cpuInfoStr, _T("cpu family"));
	str	+= getSubCPUInfo (cpuInfoStr, _T("model"));
	str	+= getSubCPUInfo (cpuInfoStr, _T("cpu_model"));
	str	+= getSubCPUInfo (cpuInfoStr, _T("model_name"));
	str	+= getSubCPUInfo (cpuInfoStr, _T("model name"));
	str	+= getSubCPUInfo (cpuInfoStr, _T("stepping"));
	str	+= getSubCPUInfo (cpuInfoStr, _T("cache_size"));
	str	+= getSubCPUInfo (cpuInfoStr, _T("fdiv_bug"));
	str	+= getSubCPUInfo (cpuInfoStr, _T("hlt_bug"));
	str	+= getSubCPUInfo (cpuInfoStr, _T("sep_bug"));
	str	+= getSubCPUInfo (cpuInfoStr, _T("f00f_bug"));
	str	+= getSubCPUInfo (cpuInfoStr, _T("coma_bug"));
	str	+= getSubCPUInfo (cpuInfoStr, _T("fpu"));
	str	+= getSubCPUInfo (cpuInfoStr, _T("fpu_exception"));
	str	+= getSubCPUInfo (cpuInfoStr, _T("cpuid_level"));
	str	+= getSubCPUInfo (cpuInfoStr, _T("wp"));
	str	+= getSubCPUInfo (cpuInfoStr, _T("flags"));
	str	+= getSubCPUInfo (cpuInfoStr, _T("byte_order"));
	
 	return str;
}






String generateNetworkMAC (void)
{
#define MAC_LEN		(18)

	String macAddr("ff-ff-ff-ff-ff-ff");
	size_t maclen = MAC_LEN;
	int fd, interface;
	struct ifreq buf[MAXINTERFACES];
	struct ifconf ifc;

	char mac[MAC_LEN];
	memset (mac, 0, sizeof(mac));

#if !defined(__AIX__) && !defined(__HPPA__) && !defined(__SOLARIS__)
	if ((fd = socket (AF_INET, SOCK_DGRAM, IPPROTO_UDP)) >= 0) {
		ifc.ifc_len = sizeof buf;
		ifc.ifc_buf = (caddr_t) buf;
		if (!ioctl (fd, SIOCGIFCONF, (char *) &ifc)) {
			//获取接口信息
			interface = ifc.ifc_len / sizeof (struct ifreq);

			//根据接口信息循环获取设备MAC地址
			while (interface-- > 0) {
				if (!(ioctl (fd, SIOCGIFADDR, (char *) &buf[interface]))) {
					if (inet_ntoa(((struct sockaddr_in*)(&buf[interface].ifr_addr))->sin_addr) != "127.0.0.1") {
						//获取设备名称
#ifdef __64PLATFORM__
#error mac address format still not support x64, please port it.
#endif
						if (!(ioctl (fd, SIOCGIFHWADDR, (char *) &buf[interface]))) {
							snprintf ((char*)mac, maclen, "%02X-%02X-%02X-%02X-%02X-%02X",
										(buf[interface].ifr_hwaddr.sa_data[0] & 0xFF),
										(buf[interface].ifr_hwaddr.sa_data[1] & 0xFF),
										(buf[interface].ifr_hwaddr.sa_data[2] & 0xFF),
										(buf[interface].ifr_hwaddr.sa_data[3] & 0xFF),
										(buf[interface].ifr_hwaddr.sa_data[4] & 0xFF),
										(buf[interface].ifr_hwaddr.sa_data[5] & 0xFF));
							macAddr = mac;
							break;
						}
					}
				}
			}
		}

		close (fd);
	}
#endif 
	
#if defined(__AIX__) || defined(__HPPA__)

	char tmp[MAC_LEN];
	char macTmp[MAC_LEN];
	FILE* pFile;

#ifdef __AIX__
	String cmd = _T("lscfg|awk '{print $2}'|grep ^ent|while read MAC; do lscfg -vpl $MAC | awk -F. '/Network Address/ {print $14 }';done ");
#elif defined __HPPA__
	String cmd = _T("lanscan |awk '{print $2}'|grep -v Station|grep -v Address ");
#elif defined __SOLARIS__
	String cmd = _T("ifconfig -a | grep ether | awk '{print $2}'");
#endif

	//
	// 使用aix shell获取mac地址信息
	//	
	if ((pFile = popen (cmd.getCStr (), "r")) == NULL)  {
		throw SystemException (sysWrapLoader, 
								_T("IDS_ERROR_POPEN"), 
								errno, 
								SystemErrorHandler::getInstance ());
	}   
	
	fgets (tmp, sizeof(tmp), pFile);
	tmp[strlen (tmp)-1] = '\0';
	
	for (int i = 0; i < strlen (tmp); ++i) {
		//
		// 检查是否存在 \n 换行符，将换行符修改为 \0
		//
		if (tmp[i] == '\n') {
			tmp[i] = '\0';
			break;
		}
	}
	
	pclose (pFile);
	for (int i = 0,j = 0; i < strlen (tmp); i+=2) {
		macTmp[j] = tmp[i];
		macTmp[j+1] = tmp[i+1];
		macTmp[j+2] = '-';
		j+=3;
	}
	
	macTmp[strlen(macTmp)-1] = '\0';

	macAddr = macTmp;
#endif

	return macAddr;
}


String genMachineCode(void)
{
	String cpuInfo = generateCPUVendorInfo ();
	String macAddr = generateNetworkMAC ();

	if (cpuInfo.isEmpty () == true) {
		cpuInfo = generateCPUVendorInfo ();
		cpuInfo.toUpper ();
	}
	
	if (macAddr.isEmpty () == true) {
		macAddr = generateNetworkMAC ();
		macAddr.toUpper ();
	}
	
	String str = cpuInfo + macAddr;
	
	MD5Hash md5;
	unsigned char value[16];
	
	md5.update((unsigned char*)str.getCStr(), str.getLength());
	md5.final (value);
	
	return md5.toString(value, true);	
}
