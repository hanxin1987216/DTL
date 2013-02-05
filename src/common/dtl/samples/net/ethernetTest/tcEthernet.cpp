/********************************************************************
  tcEthernet.cpp 
  C++ Test Decoument
  Copyrigth (c) Datatom Co, Ltd (2013-2014),All rights reserved

  Purese:
      test the  ethernet.cpp file

  Author:
      Wenxue Liu

  Creating Time
      2013-1-22
 **********************************************************************/
#include <dtprec.h>
#include <dtl/dtl.h>

#include <ethernet/ethernet.h>
#include <ethernet/bond.h>

#include "tcEthernet.h"

/*
*       print the Ethernet information
*/
void 
printEtherInfo(EthernetInfo strHostInfo[MAX_PATH])
{
	for (size_t i = 0; i < 3; ++i)
	{
		cout << "设备名：" << strHostInfo[i].DEVICE;
		cout << "ip地址：" << strHostInfo[i].IPADDR;
		cout << "子网掩码:" << strHostInfo[i].NETMASK;
		cout << "物理地址：" << strHostInfo[i].MAC;
		cout << "广播地址；" << strHostInfo[i].BROADCAST;
		cout << "网卡类型:" << strHostInfo[i].TYPE;
		cout << "网关:" << strHostInfo[i].GATEWAY;
		cout << "bond号：" << strHostInfo[i].MASTER;
		cout << "绑定类型：" << strHostInfo[i].iBindType;
		cout << "状态：" << strHostInfo[i].status;

	}
}


/*
 *       set the Ethernet information
 */
void 
setEthernetInfo(EthernetInfo strHostInfo[MAX_PATH])
{
	for (int i = 0; i < MAX_PATH; ++i) 
	{
		sprintf(strHostInfo[i].DEVICE, "Ethernet %d", i);
		sprintf(strHostInfo[i].IPADDR, "192.168.1.3");
		sprintf(strHostInfo[i].NETMASK, "255.255.255.0");
		sprintf(strHostInfo[i].MAC, "02x-02x-02x-02x-02x-02x");
		sprintf(strHostInfo[i].BROADCAST, "0.0.0.0");
		sprintf(strHostInfo[i].TYPE, "wlan0");
		sprintf(strHostInfo[i].GATEWAY, "192.234.1.1");
		sprintf(strHostInfo[i].MASTER, "123");
		strHostInfo[i].iBindType = 12;
		strHostInfo[i].status = 1;
	}
}


/**
 *      test case for getEthernetInfo() functions 
 */
void 
TestEthernet::tcGetEthernetInfo(void)
{
	cout << "获取网卡信息：" <<endl;

	EthernetInfo strHostInfo[MAX_PATH];
	setEthernetInfo(strHostInfo);
        int *iCount = NULL;
	cout << "正常测试:" << endl;
	cout << "当传入参数是不为空的时候: " << endl;
	if (0 != getEthernetInfo(strHostInfo,iCount))
	{
		cout << "获取网卡成功！" << endl;
		printEtherInfo(strHostInfo);
		cout << "iCount = " << iCount <<endl;
	}
	else
	{
		cout << "获取网卡失败！" << endl;
	}

	cout << "异常测试:" << endl;
	cout << "当传入参数是空的时候 :  " <<  endl;    
	if (0 != getEthernetInfo(NULL, 0))
	{
		cout << "获取网卡成功！" << endl;
		printEtherInfo(strHostInfo);
		cout << "iCount = " << iCount <<endl;
	}
	else
	{
		cout << "获取网卡失败！" << endl;
	}
}


/**
 *      test case for getCloseEtherInfo() functions 
 */
void 
TestEthernet::tcGetCloseEtherInfo(void)
{
	cout << "获取关闭网卡信息：" << endl;

	vector<EthernetInfo> strHostInfo;
	EthernetInfo strHost;

	cout << "正常测试：" << endl;
	cout << "当网卡信息不为空:" << endl;
	strHostInfo.push_back(strHost);	
	if (0 !=  getCloseEtherInfo(strHostInfo))	
	{
		cout << "关闭网卡信息成功！" << endl;	
		cout << "关闭网卡信息：" << endl;
		//printEtherInfo(strHostInfo);
	}
	else
	{
		cout << "关闭网卡信息失败！" << endl;	
	}

/*
	cout << "异常测试：" << endl;
	cout << "当网卡信息为空:" << endl;
	strHostInfo.push_back(strHost);	
	if (0 !=  getCloseEtherInfo(NULL))	
	{
		cout << "关闭网卡信息成功！" << endl;	
		cout << "关闭网卡信息：" << endl;
		printEtherInfo(strHostInfo.pop_back());
	}
	else
	{
		cout << "关闭网卡信息失败！" << endl;	
	}
*/
}


/**
 *      test case for setEarthnet() functions 
 */
void 
TestEthernet::tcSetEarthnet(void)
{
	cout << "修改网卡信息(IP地址，网关和网卡)：" << endl;

	cout << "正常性测试：" << endl;
	String strIP = "192.168.1.123";
	String strMask = "192.168.1.123";
	String strGateway = "192.168.1.123";
	String strEathName = "EarthName";
	if(0 != setEarthnet(strIP.getCStr(), strMask.getCStr(), strGateway.getCStr(), strEathName.getCStr()))
	{
		cout << "设置网卡信息成功！" << endl;	
	}
	else
	{
		cout << "设置网卡信息失败！" << endl;	
	}

	cout << "异常测试：IP重复" << endl;
	String strIP1 = "192.168.1.123";
	String strMask1 = "192.168.1.123";
	String strGateway1 = "192.168.1.123";
	String strEathName1 = "EarthName";
	if(0 != setEarthnet(strIP1.getCStr(), strMask1.getCStr(), strGateway1.getCStr(), strEathName1.getCStr()))
	{
		cout << "设置网卡信息成功！" << endl;	
	}
	else
	{
		cout << "设置网卡信息失败！" << endl;	
	}

	cout << "异常测试：地址异常" << endl;
	String strIP2 = "192.168.1.125";
	String strMask2 = "0.258.a.123";
	String strGateway2 = "192.168.1.123";
	String strEathName2 = "EarthName";
	if(0 != setEarthnet(strIP2.getCStr(), strMask2.getCStr(), strGateway2.getCStr(), strEathName2.getCStr()))
	{
		cout << "设置网卡信息成功！" << endl;	
	}
	else
	{
		cout << "设置网卡信息失败！" << endl;	
	}

}


/**
 *      test case for setBrodcast() functions 
 */
void 
TestEthernet::tcSetBrodcast(void)
{
	cout << "设置broadcast: " << endl;

	String strIP = "192.168.1.125";
	String strMask = "0.258.1.123";
	string strBroadcast = "Broadcast";
    
	cout << "如果string& 变量" << endl;
		if (0 != setBrodcast(strIP.getCStr(), strMask.getCStr(), strBroadcast))
		{
			cout << "设置broadcast成功!" << endl;	
		}
		else
		{
			cout << "设置broadcast失败!" << endl;	
		}

	cout << "如果string& 常量:" << endl;
		if (0 != setBrodcast(strIP.getCStr(), "0.258.1.123", strBroadcast))
		{
			cout << "设置broadcast成功!" << endl;	
		}
		else
		{
			cout << "设置broadcast失败!" << endl;	
		}
}


/**
 *      test case for setDNS() functions 
 */
void 
TestEthernet::tcSetDNS(void)
{
	cout << "设置DNS：" << endl;

	cout << "参数为空 ：" <<endl;
	String strPreferred = NULL;
	String strAfternative = NULL;
	if (0 != setDNS(strPreferred.getCStr(),strAfternative.getCStr()))
	{
		cout << "设置DNS服务成功！" << endl;
		cout << "strPreferred :" << endl;  
		cout << "strAfternative :" << endl;
	}
	else
	{
		cout << "获取DNS服务失败！" << endl;
	}

	cout << "参数不为空 ：" <<endl;
        String strPreferred1 = "Preferred";
	String strAfternative1 = "strAfternative";
	if (0 != setDNS(strPreferred1.getCStr(),strAfternative1.getCStr()))
	{
		cout << "设置DNS服务成功！" << endl;
		cout << "strPreferred :" << endl;  
		cout << "strAfternative :" << endl;
	}
	else
	{
		cout << "获取DNS服务失败！" << endl;
	}
}


/**
 *      test case for getDNS() functions 
 */
void 
TestEthernet::tcGetDNS(void)
{
	cout << "获取DNS服务：" << endl;

	cout << "参数为空时 ：" <<endl;
	char *strPreferred = NULL;
	char *strAfternative = NULL;
	if (0 != getDNS(strPreferred, strAfternative))
	{
		cout << "获取DNS服务成功！" << endl;
		cout << "strPreferred :" << endl;  
		cout << "strAfternative :" << endl;
	}
	else
	{
		cout << "获取DNS服务失败！" << endl;
	}


	cout << "参数不为空时 ：" <<endl;
	char strPreferred1[] = "Preferred";
	char strAfternative1[] = "strAfternative";

	cout << "before getDNS():" << endl;
	cout << "strPreferred :" << endl;  
	cout << "strAfternative :" << endl;

	cout << "After getDNS():" << endl;
	if (0 != getDNS(strPreferred1,strAfternative1))
	{
		cout << "获取DNS服务成功！" << endl;
		cout << "strPreferred :" << endl;  
		cout << "strAfternative :" << endl;
	}
	else
	{
		cout << "获取DNS服务失败！" << endl;
	}
}

/**
 *    set Bind information
 */
void 
setBindInfo(BindInfo strBindInfo[MAX_PATH])
{
	for (int i = 0; i < 5; ++i)
	{
		sprintf(strBindInfo[i].strBindIP,"182.134.112.2");
		sprintf(strBindInfo[i].strBindName, "Bond %d", i);
		sprintf(strBindInfo[i].strEathArray, "iWare");
		strBindInfo[i].iBindCount = 1;
	}

}

/**
 *    print Bind information
 */
void 
printBindInfo(BindInfo strBindInfo[MAX_PATH])
{
	for (int i = 0; i < 3; ++i)
	{
		cout << "IP ：" << strBindInfo[i].strBindIP << endl;
		cout << "BindName: " << strBindInfo[i].strBindName << endl;
		cout << "EathArry: " << strBindInfo[i].strEathArray << endl;
		cout << "iBindCount:" << strBindInfo[i].iBindCount << endl;
	}
}

/**
 *      test case for GetBindInfo() functions 
 */
void
TestEthernet::tcGetBindInfo(void)
{
	cout << "获取绑定信息 :" << endl; 

	BindInfo strBindInfo[MAX_PATH];
	setBindInfo(strBindInfo);
	if (0 != GetBindInfo(strBindInfo,0)) 
	{
		cout << "绑定成功!" << endl; 
		printBindInfo(strBindInfo);
	}
	else
	{
		cout << "绑定失败!" << endl; 
	}
}


/**
 *      test case for getNetworkInfo() functions 
 */
void 
TestEthernet::tcGetNetworkInfo(void)
{

	cout << "获取网卡信息：" << endl;
	EthernetInfo strHostInfo[MAX_PATH];

	if (0 != getNetworkInfo(strHostInfo,0))
	{
		cout << "获取网卡信息成功!" << endl;
	}
	else
	{
		cout << "获取网卡信息失败!" << endl;
	}
}

/**
 *      test case for get_ipaddr() functions 
 */
void 
TestEthernet::tcGet_ipaddr(void)
{
	cout << "获取IP地址：" << endl;

	char* interface_name = NULL;
	char* strRetValue = NULL;
	if(0 != get_ipaddr(interface_name, strRetValue))  
	{
		cout << "获取IP地址成功！" << endl;
		cout << "interface_name : " << interface_name << endl;
		cout << "strRetValue : " << strRetValue << endl;
	}
	else
	{
		cout << "获取IP地址失败！" << endl;
	}


	char interface_name1[] = "eth0";
	char *strRetValue1 = NULL;
	if(0 != get_ipaddr(interface_name1, strRetValue1))  
	{
		cout << "获取IP地址成功！" << endl;
		cout << "interface_name : " << interface_name1 << endl;
		cout << "strRetValue : " << strRetValue1 << endl;
	}
	else
	{
		cout << "获取IP地址失败！" << endl;
	}


	char interface_name2[] = "abc";
	char *strRetValue2 = NULL;
	if(0 != get_ipaddr(interface_name2, strRetValue2))  
	{
		cout << "获取IP地址成功！" << endl;
		cout << "interface_name : " << interface_name2 << endl;
		cout << "strRetValue : " << strRetValue2 << endl;
	}
	else
	{
		cout << "获取IP地址失败！" << endl;
	}

}


/**
 *      test case for get_mac() functions 
 */
void 
TestEthernet::tcGet_mac(void)
{
	cout << "获取硬件地址：" << endl;

	char *interface_name = NULL;
	char *strRetValue = NULL;

	if(0 != get_mac(interface_name,strRetValue))  
	{
		cout << "interface_name : " << interface_name << endl;
		cout << "strRetValue : " << strRetValue << endl;
	}
	else
	{
		cout << "获取硬件地址失败！" << endl;
	}


        char interface_name1[] = "eth0";
	char *strRetValue1 = NULL;

	if(0 != get_mac(interface_name1,strRetValue1))  
	{
		cout << "interface_name : " << interface_name1 << endl;
		cout << "strRetValue : " << strRetValue1 << endl;
	}
	else
	{
		cout << "获取硬件地址失败！" << endl;
	}


	char interface_name2[] = "lo";
	char *strRetValue2 = NULL;

	if(0 != get_mac(interface_name2,strRetValue2))  
	{
		cout << "interface_name : " << interface_name2 << endl;
		cout << "strRetValue : " << strRetValue2 << endl;
	}
	else
	{
		cout << "获取硬件地址失败！" << endl;
	}
}

/**
 *      test case for get_netmask() functions 
 */
void 
TestEthernet::tcGet_netmask(void)
{
	cout << "获取掩码：" << endl;

	char *interface_name = NULL;
	char *strRetValue = NULL;

	if (get_netmask(interface_name, strRetValue))  
	{
		cout << "interface_name : " << interface_name << endl;
		cout << "strRetValue : " << strRetValue << endl;
	}
	else
	{
		cout << "获取掩码失败！" << endl;       
	}


	char interface_name1[] = "eth0";
	char *strRetValue1 = NULL;

	if (get_netmask(interface_name1, strRetValue1))  
	{
		cout << "interface_name : " << interface_name1 << endl;
		cout << "strRetValue : " << strRetValue1 << endl;
	}
	else
	{
		cout << "获取掩码失败！" << endl;       
	}


	char interface_name2[] = "abc";
	char *strRetValue2 = NULL;

	if (get_netmask(interface_name2, strRetValue2))  
	{
		cout << "interface_name : " << interface_name2 << endl;
		cout << "strRetValue : " << strRetValue2 << endl;
	}
	else
	{
		cout << "获取掩码失败！" << endl;       
	}
}

/**
 *      test case for get_broadcast() functions 
 */
void 
TestEthernet::tcGet_broadcast(void)
{
	cout << "获取广播地址：" << endl;

	char *interface_name = NULL;
	char *strRetValue = NULL;

	if (get_broadcast(interface_name, strRetValue))  
	{
		cout << "获取广播地址成功!" << endl;     
		cout << "interface_name : " << interface_name << endl;
		cout << "strRetValue : " << strRetValue << endl;
	}
	else
	{
		cout << "获取广播地址失败!" << endl;     
	}


	char interface_name1[] = "abc";
	char *strRetValue1 = NULL;

	if (get_broadcast(interface_name1, strRetValue1))  
	{
		cout << "获取广播地址成功!" << endl;     
		cout << "interface_name : " << interface_name1 << endl;
		cout << "strRetValue : " << strRetValue1 << endl;
	}
	else
	{
		cout << "获取广播地址失败!" << endl;     
	}


	char interface_name2[] = "eth0";
	char *strRetValue2 = NULL;

	if (get_broadcast(interface_name2, strRetValue2))  
	{
		cout << "获取广播地址成功!" << endl;     
		cout << "interface_name : " << interface_name2 << endl;
		cout << "strRetValue : " << strRetValue2 << endl;
	}
	else
	{
		cout << "获取广播地址失败!" << endl;     
	}
}

/**
 *      test case for get_nettype() functions 
 */
void 
TestEthernet::tcGet_nettype(void)
{
	cout << "获取网卡类型：" << endl;

	char interface_name[] = "eth0";
	char *strRetValue = NULL;

	if (0 != get_nettype(interface_name,strRetValue)) 
	{
		cout << "获取网卡类型参数成功!" << endl;     
		cout << "interface_name : " << interface_name << endl;
		cout << "strRetValue : " << strRetValue << endl;
	}
	else
	{
		cout << "获取网卡类型参数失败!" << endl;     
	}


	char interface_name1[] = "abc";
	char *strRetValue1 = NULL;

	if (0 != get_nettype(interface_name1, strRetValue1)) 
	{
		cout << "获取网卡类型参数成功!" << endl;     
		cout << "interface_name : " << interface_name1 << endl;
		cout << "strRetValue : " << strRetValue1 << endl;
	}
	else
	{
		cout << "获取网卡类型参数失败!" << endl;     
	}
}
/**
 *      test case for ping() functions 
 */
void 
TestEthernet::tcPing(void)
{
	cout << "ping 测试 ：" << endl;

	char *strIP = NULL;       
	if (Ping(strIP))
	{
		cout << "Ping NULL  成功！" << endl;       
	}
	else
	{
		cout << "Ping NULL 失败!!" << endl;       
	}

	char strIP1[] = "www.datatom.com";       
	if (Ping(strIP1))
	{
		cout << "Ping www.datatom.com 成功！" << endl;       
	}
	else
	{
		cout << "Ping www.datatom.com 失败!!" << endl;       
	}
}

/**
 *      test case for setDefGateWay() functions 
 */
void 
TestEthernet::tcSetDefGateWay(void)
{
	cout << "设置默认网关：" << endl;

	string ethName1 = "iEthernet";
	if (0 == setDefGateWay(ethName1))
	{
		cout << "设置默认网关 iEthernet 成功！" << endl;
	}
	else
	{
		cout << "设置默认网关 iEthernet 异常！！" << endl;
	}

	string ethName2 = NULL;
	if (0 == setDefGateWay(ethName2))
	{
		cout << "设置默认网关 NULL 成功！" << endl;
	}
	else
	{
		cout << "设置默认网关 NULL 异常！！" << endl;
	}
}

/**
 *      test case for getAllEthInfo() functions 
 */
void 
TestEthernet::tcGetAllEthInfo(void)
{
	cout << "获取所有网卡：" << endl;

	vector<string> allEthInfo;
	if (0 == getAllEthInfo(allEthInfo))
	{
		cout << "获取所有网卡成功！" << endl;
		cout << "输出所有网卡信息: " << endl;
		for (size_t i = 0; i < allEthInfo.size(); ++i)
		{
			cout << "Ethernet " << i << " : " << allEthInfo[i].c_str() << endl;
		}
	}
	else
	{
		cout << "获取所有网卡失败!！" << endl;
	}
}

