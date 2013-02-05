#include <dtprec.h>
#include <cppunit/tester.h>
#include <dtl/dtl.h>

#include "nettc.h"
#include <vector>

CPPUNIT_TEST_SUITE_REGISTRATION( NetTestCase );

void
NetTestCase::getAllEthernetInfo (void)
{
	EthernetMgm net;
	vector<EthernetInfo> eth;
	int size = 0;
	
	try
	{
		size = net.getAllEthernetInfo(eth);
	}
	catch (const Exception &e)
	{
		CPPUNIT_ASSERT_THROW_MESSAGE(e.getMessage().getCStr(), e, Exception);
	}
	CPPUNIT_ASSERT(size > 0);
	CPPUNIT_ASSERT(!eth.empty());
	
	//
	//	输出网卡信息
	//
	for (int i = 0; i < size; i ++)
	{
		EthernetInfo eInfo = eth.at(i);
		printf("\n\tDevice:\t%s\n", eInfo._device.getCStr());
		printf("\tIP:\t%s\n", eInfo._ip.getCStr());
		printf("\tNet mask:\t%s\n", eInfo._netmask.getCStr());
		printf("\tMAC:\t%s\n", eInfo._macAddress.getCStr());
		printf("\tBroadcast:\t%s\n", eInfo._broadcast.getCStr());
	}
}

void
NetTestCase::setEthernetInfo (void)
{
	/* EthernetMgm net;
	String Ip = "192.168.0.138";
	String Mask = "255.255.255.0";
	String Gateway = "192.168.0.1";
	String EthernetName = "eth2";

	//
	// 修改信息需重启网卡后生效
	//
	CPPUNIT_ASSERT_NO_THROW(net.setEthernetInfo(EthernetName, Ip, Mask, Gateway)); */
}

void
NetTestCase::getBroadCastByIP (void)
{
	EthernetMgm net;
	String IP = "192.168.1.131";
	String broadcast = net.getBroadCastByIP (IP);
	CPPUNIT_ASSERT(broadcast == String ("192.168.1.255"));
}

void
NetTestCase::getDNS (void)
{
	EthernetMgm net;
	String str1;
	String str2;
	
	try
	{
		net.getDNS(str1,str2);
	}
	catch (const Exception &e)
	{
		CPPUNIT_ASSERT_THROW_MESSAGE(e.getMessage().getCStr(), e, Exception);
	}
	
	//
	// 输出DNS信息
	//
	cout << "\n\tDNS1:\t" << str1.getCStr() << endl;
	cout << "\tDNS2:\t" << str2.getCStr() << endl;
}

void
NetTestCase::setDNS (void)
{
	EthernetMgm net;
	String strDNS1 = "8.8.8.8";
	String strDNS2 = "8.8.1.1";
	CPPUNIT_ASSERT_NO_THROW(net.setDNS(strDNS1, strDNS2));
	//
	// 判断DNS信息是否已被修改
	//
	String strFirstDNS("1.1.1.1");
	String strSecondDNS("1.1.1.1");
	CPPUNIT_ASSERT_NO_THROW(net.getDNS(strFirstDNS, strSecondDNS));
	CPPUNIT_ASSERT(strFirstDNS.compare("8.8.8.8") == 0);
	CPPUNIT_ASSERT(strSecondDNS.compare("8.8.1.1") == 0);
}


void
NetTestCase::bondMultiEthernet (void)
{
	EthernetMgm net;
	vector<int> vec;
	vec.push_back(0);
	vec.push_back(1);
	String ip = "192.168.1.37";
	String mask = "255.255.255.0";
	String gateway = "192.168.1.1";
	int type = 0;
	int id = 0;
	
	try
	{
		net.bondMultiEthernet(type,vec,ip,mask,gateway,id);
	}
	catch (const Exception &e)
	{
		CPPUNIT_ASSERT_THROW_MESSAGE(e.getMessage().getCStr(), e, Exception);
	}
}

void
NetTestCase::cancelBond (void)
{
	/*EthernetMgm net;
	String bond("bond0");
	CPPUNIT_ASSERT_NO_THROW(net.cancelBond(bond));*/
}

void 
NetTestCase::getBondInfos (void)
{
	EthernetMgm net;
	vector<BondInfo> vec;
	try
	{
		net.getBondInfos (vec);
	}
	catch (const Exception &e)
	{
		CPPUNIT_ASSERT_THROW_MESSAGE(e.getMessage().getCStr(), e, Exception);
	}
	
	
	//
	//	输出绑定多网卡信息
	//
	for (int i = 0; i < vec.size(); i ++)
	{
		BondInfo bInfo = vec.at(i);
		cout << "\nBond" << i << ":" << endl;
		cout << "\tIP:\t" << bInfo._bondIP.getCStr() << endl;
		cout << "\tName:\t" << bInfo._bondName.getCStr() << endl;
		cout << "\tBond nets:" << endl;

		//
		//	输出对应IP绑定的网卡名称
		//
		if (bInfo._bondEthernets.size() == 0)
		{
			cout << "\t\tNone" << endl;
			continue;
		}
		for (int j = 0; j < (bInfo._bondEthernets.size()); j ++)
		{
			cout << "\t\t" << bInfo._bondEthernets.at(j).getCStr() << endl;
		}
	}
}

void
NetTestCase::netRestart (void)
{
/*	EthernetMgm net;
	CPPUNIT_ASSERT_NO_THROW(net.netRestart());
*/
}

void
NetTestCase::reBoot (void)
{
/*	EthernetMgm net;
	net.reBoot ();
*/}




