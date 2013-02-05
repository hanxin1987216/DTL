/********************************************************************
  tcBand.cpp
  C++ Test Decoument
  Copyrigth (c) Datatom Co, Ltd (2013-2014),All rights reserved

  Purese:
      test the  band.cpp file

  Author:
      Wenxue Liu

  Creating Time
      2013-1-23
 **********************************************************************/

#include "tcBond.h"


/**
*       test bindingEthArry() function
*/
void 
TestBand::tcBindingEthArry ()
{
        cout << "多网卡绑定：" << endl;
	int bindType = 6;
	string ethNumber("1,2,3,4,5,6,");
	string strBondIp("www.datatom.com");
	string strBondMask("255.255.255.0");
	string strBondGateWay("192.168.1.5");
	int bindNumber = 10;
	int index = 5;
       	if (0 != bindingEthArry(bindType,
		       ethNumber,
		       strBondIp,
		       strBondMask,
		       strBondGateWay,
		       bindNumber,
		       index))
	{
                 cout << "多网卡绑定成功: " << enld;
	}
	else
	{
                 cout << "多网卡绑定失败: " << enld;
		 cout << "可能是ethNumber != bindNumber" << endl;
	}
}

/**
*       test cancleBindEthArry() function
*       
*       function: 删除band[index]的文件，找到对应文件中找到含有MASTER[strValue]的
        行，拷贝到strValue中。iCount记录了满足的行数目。
        删除Linux中的对于模块	
*/
void 
TestBand::tcCancleBindEthArry()
{
        cout << "取消多网卡绑定:" << endl;

	if (0 != cancleBindEthArry(10))
	{
               cout << "取消多网卡成功!!" << endl;	
	}
	else
	{
               cout << "取消多网卡成功!!" << endl;	
               cout << "可能是删除不存在的网卡" << endl;
	}

}

/**
*       test getBindEthStatus() function
*/
void
TestBand::tcGetBindEthStatus()
{
        cout << "得到网卡状态；" << endl;
        
	vector<string> bondName;
	vector<string> bondStatus;


	if (0 != getBindEthStatus(bondName, bondStatus))
	{
              cout << "得到网卡信息成功！" << endl;	
	     
	}
	else
	{
              cout << "得到网卡信息失败！" << endl;	
	}
}


/**
*       test integrationOfInfo() function
*/
void 
TestBand::tcIntegrationOfInfo()
{
       cout << "整合网卡名：" << endl; 

       size_t ethIndexNum = 0;
       if (0 != integrationOfInfo(ethIndexNum))
       {
              cout << "整合网卡名成功! " << endl; 
       }
       else
       {
              cout << "整合网卡名失败! " << endl; 
	      cout << "可能GetEthSpeedAndLink()有关" << endl;
       }
}

/**
*       test GetEthSpeedAndLink() function
*/
void
TestBand::tcrGetEthSpeedAndLink()
{
        cout << "获取网卡速度和链接：" << endl;

	cout << "正常测试: " << endl;
	string ethName("eth0");
        ethInfoList info; 
	if (0 != getEthSpeedAndLink(ethName, info))
	{
		cout << "获取网卡速度和链接成功！" << endl;
	}
	else
	{
		cout << "获取网卡速度和链接失败！" << endl;
                cout << "可能是对if的else情况没有处理" << endl;	
	}

	cout << "异常测试: " << endl;
	string ethName("000");
        ethInfoList info; 
	if (0 != getEthSpeedAndLink(ethName, info))
	{
		cout << "获取网卡速度和链接成功！" << endl;
	}
	else
	{
		cout << "获取网卡速度和链接失败！" << endl;
                cout << "可能是对if的else情况没有处理" << endl;	
	}

}

/**
*       test getEthIndex() function
*/
void
TestBand::tcGetEthIndex()
{
	cout << "获取网卡序号和数量：" << endl;

	vector<string> ethIndexLines;
	if (0 == getEthIndex(ethIndexLines))
	{
        	cout << "获取网卡序号和数量成功!" << endl;	
        	cout << "网卡信息：" << endl;	
		for(size_t i = 0; i < ethIndexNum.size(); ++i)
		{
                        cout << ethIndexLines.back() << endl;	
			ethIndexLines.pop_back();
		}
	}
	else
	{
        	cout << "获取网卡序号和数量失败!" << endl;	
	}
}

/**
*       test getEthInfoInBond() function
*/
void 
TestBand::tcGetEthInfoInBond()
{
        cout << "获取bond网卡包含的本地网卡信息：" << endl;

        string("band0");
	vector<string> ethName;
	vector<int> ethStatus;

	getEthInfoInBond(bondName, ethName, ethStatus);
        cout << "网卡信息：" << endl; 	
        for (size_t i = 0; i < ethName.size(); ++i)
	{
            	cout << ethName.back() << "  " <<　ethStatus <<  endl;	
		ethName.pop_back(); 
		ethStatus.pop_back();
	}
}
