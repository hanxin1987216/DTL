// Unit Test code for class net::EthernetMgm

#ifndef __NETTC_H__
#define __NETTC_H__

#include <cppunit/tester.h>


class NetTestCase : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE (NetTestCase);

		CPPUNIT_TEST_DESCRIPTION (getAllEthernetInfo,_T("测试net, getAllEthernetInfo 得到所有网卡的信息") );	
		CPPUNIT_TEST_DESCRIPTION (setEthernetInfo,_T("测试net, setEthernetInfo 设置网卡的信息") );
		CPPUNIT_TEST_DESCRIPTION (getBroadCastByIP,_T("测试net,getBroadCastByIP 通过IP得到广播地址") );
		CPPUNIT_TEST_DESCRIPTION (getDNS,_T("测试net,getDNS 获取DNS地址") );
		CPPUNIT_TEST_DESCRIPTION (setDNS,_T("测试 net,setDNS 设置DNS地址") );
		CPPUNIT_TEST_DESCRIPTION (bondMultiEthernet,_T("测试net, bondMultiEthernet 绑定网卡地址") );
		CPPUNIT_TEST_DESCRIPTION (cancelBond,_T("测试net,cancelBond 取消绑定") );
		CPPUNIT_TEST_DESCRIPTION (getBondInfos,_T("测试net，getBondInfos 获取绑定信息") );
		CPPUNIT_TEST_DESCRIPTION (netRestart,_T("测试net, netRestart 重启网卡") );

	CPPUNIT_TEST_SUITE_END ();
	
public:
	void setUp (void)
	{
	}
	
	void tearDown (void)
	{
	}
	
protected:
	void getAllEthernetInfo (void);
	void setEthernetInfo (void);
	void getBroadCastByIP (void);
	void getDNS (void);
	void setDNS (void);
	void bondMultiEthernet (void);
	void cancelBond (void);
	void getBondInfos (void);
	void netRestart (void);
}; // End class NETTestCase

#endif // __NETTC_H__

