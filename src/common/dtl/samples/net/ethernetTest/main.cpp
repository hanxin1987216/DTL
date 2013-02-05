/********************************************************************
  main.cpp 
  C++ Test Decoument
  Copyrigth (c) Datatom Co, Ltd (2013-2014),All rights reserved

  Purese:
      test the testing file

  Author:
      Wenxue Liu

  Creating Time:
      2013-1-23
 **********************************************************************/



int main()
{
     TestEthernet tcEther;

     tcEther.getEthernetInfo();     
     tcEther.getCloseEtherInfo();     
     tcEther.setEarthnet();     
     tcEther.setBrodcast();     
     tcEther.setDNS();     
     tcEther.getDNS();     
     tcEther.GetBindInfo();     
     tcEther.getNetworkInfo();     
     tcEther.get_ipaddar();     
     tcEther.get_mac();     
     tcEther.get_netmask();     
     tcEther.get_broadcast();     
     tcEther.get_nettype();     
     tcEther.ping();     
     tcEther.setDefGateWay();     
     tcEther.getAllEthInfo();     

}
