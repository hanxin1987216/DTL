/********************************************************************
  tcBand.h 
  C++ Test Decoument
  Copyrigth (c) Datatom Co, Ltd (2013-2014),All rights reserved

  Purese:
      test the  band.h file

  Author:
      Wenxue Liu

  Creating Time
      2013-1-23
 **********************************************************************/

#ifndef __TEST_BAND_H__
#define __TEST_BAND_H__
class TestBand
{
public:
/**
*       test bindingEthArry() function
*/
	void tcBindingEthArry ();

/**
*       test cancleBindEthArry() function
*/
	void tcCancleBindEthArry();

/**
*       test getBindEthStatus() function
*/
	void tcGetBindEthStatus();

/**
*       test integrationOfInfo() function
*/
	void tcIntegrationOfInfo();

/**
*       test tcGetEthSpeedAndLink() function
*/
	void getEthSpeedAndLink();

/**
*       test getEthIndex() function
*/
	void tcGetEthIndex();

/**
*       test getEthInfoInBond() function
*/
	void tcGetEthInfoInBond();
};

#endif //end __TEST_BAND_H__

