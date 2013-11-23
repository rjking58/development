// referenceTests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <iostream>


struct DeviceInfo
{
	int		HardwareIdLen;
	char *	HardwareId;
};


class AvailableDevices
{
public:
	
private:
	char * myStrA_1;
	char * myStrA_2;
	char * myStr3;
public:
	AvailableDevices()
	{
		myStrA_1 = new char[30];
		strcpy_s(myStrA_1,30,"first");
		myStrA_2 = new char[30];
		strcpy_s(myStrA_2,30,"second");
		myStr3 = new char[30];
		myStr3[0] = 0;
	}
	~AvailableDevices()
	{
		delete [] myStrA_1;
		delete [] myStrA_2;
		delete [] myStr3;
	}
	void GetDeviceInfoLen(DeviceInfo &rDevInfo)
	{
		rDevInfo.HardwareIdLen = strlen(myStrA_1) + 1;
	}
	void GetDeviceInfo(DeviceInfo &rDevInfo)
	{
		if( 0 != rDevInfo.HardwareId)
		{
			strcpy_s(rDevInfo.HardwareId,rDevInfo.HardwareIdLen,myStrA_1);
		}
	}

};

int _tmain(int argc, _TCHAR* argv[])
{
	DeviceInfo di;
	AvailableDevices ad;

	ad.GetDeviceInfoLen(di);
	di.HardwareId = new char[di.HardwareIdLen];
	ad.GetDeviceInfo(di);
	std::cout << di.HardwareId << std::endl;

	delete [] di.HardwareId;

	return 0;
}

