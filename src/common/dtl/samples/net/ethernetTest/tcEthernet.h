/********************************************************************
  tcEthernet.h 
  C++ Test Decoument
  Copyrigth (c) Datatom Co, Ltd (2013-2014),All rights reserved

  Purese:
      test the  base file

  Author:
      Wenxue Liu

  Creating Time:
      2013-1-22
 **********************************************************************/

#ifndef _ETHERNET_TEST_H__
#define _ETHERNET_TEST_H__

class TestEthernet
{
public:
	/**
	 *      test case for getEthernetInfo() functions 
	 */
	void tcGetEthernetInfo();

	/**
	 *      test case for getCloseEtherInfo() functions 
	 */
	void tcGetCloseEtherInfo();

	/**
	 *      test case for setEarthnet() functions 
	 */
	void tcSetEarthnet();

	/**
	 *      test case for setBrodcast() functions 
	 */
	void tcSetBrodcast();

	/**
	 *      test case for setDNS() functions 
	 */
	void tcSetDNS();

	/**
	 *      test case for getDNS() functions 
	 */
	void tcGetDNS();

	/**
	 *      test case for GetBindInfo() functions 
	 */
	void tcGetBindInfo();

	/**
	 *      test case for getNetworkInfo() functions 
	 */
	void tcGetNetworkInfo();

	/**
	 *      test case for get_ipaddr() functions 
	 */
	void tcGet_ipaddr();

	/**
	 *      test case for get_mac() functions 
	 */
	void tcGet_mac();

	/**
	 *      test case for get_netmask() functions 
	 */
	void tcGet_netmask();

	/**
	 *      test case for get_broadcast() functions 
	 */
	void tcGet_broadcast();

	/**
	 *      test case for get_nettype() functions 
	 */
	void tcGet_nettype();

	/**
	 *      test case for ping() functions 
	 */
	void tcPing();

	/**
	 *      test case for setDefGateWay() functions 
	 */
	void tcSetDefGateWay();

	/**
	 *      test case for getAllEthInfo() functions 
	 */
	void tcGetAllEthInfo();

};
#endif//end _ETHERNET_TEST_H__
