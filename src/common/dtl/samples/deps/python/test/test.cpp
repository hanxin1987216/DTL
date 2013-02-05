#include <Python.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

#define MAX_PATH	256

struct EthernetInfo
{
	char DEVICE[MAX_PATH];
	char IPADDR[MAX_PATH];
	char NETMASK[MAX_PATH];
	char MAC[MAX_PATH];
	char BROADCAST[MAX_PATH];
	char TYPE[MAX_PATH];
	char GATEWAY[MAX_PATH];
	char MASTER[MAX_PATH];

	EthernetInfo()
	{
		memset(DEVICE,0,sizeof(DEVICE));
		memset(IPADDR,0,sizeof(IPADDR));
		memset(NETMASK,0,sizeof(NETMASK));
		memset(GATEWAY,0,sizeof(GATEWAY));
		memset(TYPE,0,sizeof(TYPE));
		memset(MASTER,0,sizeof(TYPE));
	}
};

int outPut (EthernetInfo &ethInfo)
{
	printf ("%s%s%s%s%s\n", ethInfo.BROADCAST,ethInfo.BROADCAST,ethInfo.IPADDR,ethInfo.NETMASK,ethInfo.GATEWAY);
	return 0;
}

int getEthernetInfo (EthernetInfo &ethInfo)
{
	Py_Initialize();
	Py_Initialize();

	PyObject* pMod = NULL;
	PyObject* pFunc = NULL;
	
	PyRun_SimpleString("import sys");  
	PyRun_SimpleString("sys.path.append('./')");
	
	pMod = PyImport_ImportModule("systemgm");
	if(pMod)
	{
  		pFunc = PyObject_GetAttrString(pMod, "getEnternetInfo");
		if(pFunc) {
			PyObject *pResult = PyEval_CallObject (pFunc, NULL);
			PyObject *Items = PyMapping_GetItemString (pResult, "BROADCAST");
			//PyObject *Item = PyList_GetItem (Items, 3);
			char *items = PyString_AsString (Items);
			//printf ("the items is %s\n", items);
			for (int i = 0;i < strlen(items); i++)
				ethInfo.BROADCAST[i] = items[i];
			//printf ("%s\n", ethInfo.BROADCAST);

			Items = PyMapping_GetItemString (pResult, "IPADDR");
			items = PyString_AsString (Items);
			for (int i = 0;i < strlen(items); i++)
				ethInfo.IPADDR[i] = items[i];
			//printf ("%s\n", ethInfo.IPADDR);

			Items = PyMapping_GetItemString (pResult, "DEVICE");
			items = PyString_AsString (Items);
			for (int i = 0;i < strlen(items); i++)
				ethInfo.DEVICE[i] = items[i];
			//printf ("%s\n", ethInfo.DEVICE);

			
			Items = PyMapping_GetItemString (pResult, "NETMASK");
			items = PyString_AsString (Items);
			for (int i = 0;i < strlen(items); i++)
				ethInfo.NETMASK[i] = items[i];
			//printf ("%s\n", ethInfo.NETMASK);

			Items = PyMapping_GetItemString (pResult, "GATEWAY");
			items = PyString_AsString (Items);
			for (int i = 0;i < strlen(items); i++)
				ethInfo.GATEWAY[i] = items[i];
			//printf ("%s\n", ethInfo.GATEWAY);
			return 1;
		}
	}
	//Py_Finalize();

	//outPut (ethInfo);
	return 0;
}


int getSystemRunTime (char*& strRuntime)
{
	Py_Initialize();

	PyRun_SimpleString ("import sys,os");  
	PyRun_SimpleString ("sys.path.append('./')");

	PyObject* pMod = NULL;
	PyObject* pFunc = NULL;

	pMod = PyImport_ImportModule ("systemgm");
	if (pMod)
	{
		pFunc = PyObject_GetAttrString(pMod, "getSystemRunTime");
		if (pFunc)
		{
			PyObject *pResult = PyEval_CallObject (pFunc, NULL);
			strRuntime = PyString_AsString (pResult);
			//printf("the time is %s.",strRuntime);
			//printf("hello");
			return 1;
		}
	}
	return 0;

}


int getSystemStartTime (char*& strStartTime)
{
	Py_Initialize ();
	PyRun_SimpleString ("import sys,os");
	PyRun_SimpleString ("sys.path.append ('./')");

	PyObject *pMod = NULL;
	PyObject *pFunc = NULL;

	pMod = PyImport_ImportModule ("systemgm");

	if (pMod)
	{
		pFunc = PyObject_GetAttrString (pMod,"getSystemStartTime");
		if (pFunc)
		{
			PyObject *pResult = PyEval_CallObject (pFunc, NULL);
			strStartTime = PyString_AsString (pResult);
			//printf ("%s\n", strStartTime);
			return 1;
		}
	}
	return 0;
}

int getDNS (vector<string> &vDns)
{
	Py_Initialize ();
	PyRun_SimpleString ("import sys,os");
	PyRun_SimpleString ("sys.path.append ('./')");

	PyObject *pMod = NULL;
	PyObject *pFunc = NULL;

	pMod = PyImport_ImportModule ("systemgm");
	if (pMod)
	{
		pFunc = PyObject_GetAttrString (pMod,"getDNS");
		if (pFunc)
		{
			PyObject *pResult = PyEval_CallObject (pFunc, NULL);
			char *dns = PyString_AsString (pResult);
			//printf("%s\n",dns);
			string str(dns);
			/*for (int i = 0; i < strlen(dns); i++)
			{
				str[i] = dns[i];
				//cout<<str[i]<<endl;
			}*/
			int k = str.find(' ');
			string str1 = str.substr(0, k);
			string str2 = str.substr(k + 1);
			vDns.push_back(str1);
			vDns.push_back(str2);
			return 1;
		}
	}

	//vector<string>::iterator it;
	//for (it = vDns.begin(); it != vDns.end(); it++)
		//cout<<*it<<endl;

	return 0;
}

int getApacheListenPort (int &port)
{
	Py_Initialize ();
	PyRun_SimpleString ("import sys,os");
	PyRun_SimpleString ("sys.path.append ('./')");

	PyObject *pMod = NULL;
	PyObject *pFunc = NULL;
	

	pMod = PyImport_ImportModule ("systemgm");
	if (pMod)
	{
		pFunc = PyObject_GetAttrString (pMod,"getApacheListenPort");
		if (pFunc)
		{
			PyObject *pResult = PyEval_CallObject (pFunc, NULL);
			char* strPort = PyString_AsString (pResult);
			port = atoi (strPort);
			//printf("port = %d\n",port);
			return 1;
		}
	}
	return 0;
}

int getServicesName(char*& strHostName)
{
	Py_Initialize ();
	PyRun_SimpleString ("import socket,sys");
	PyRun_SimpleString ("sys.path.append ('./')");

	PyObject *pMod = NULL;
	PyObject *pFunc = NULL;

	pMod = PyImport_ImportModule ("systemgm");
	if (pMod)
	{
		pFunc = PyObject_GetAttrString (pMod, "getServicesName");
		if (pFunc)
		{
			PyObject *pResult = PyEval_CallObject (pFunc, NULL);
			strHostName = PyString_AsString (pResult);
			//printf("%s\n",strHostName);
			return 1;
		}
	}
	return 0;
}

int getCpuNum (int& iNum)
{
	Py_Initialize ();
	PyRun_SimpleString ("import os,sys");
	PyRun_SimpleString ("sys.path.append ('./')");

	PyObject *pMod = NULL;
	PyObject *pFunc = NULL;

	pMod = PyImport_ImportModule ("systemgm");
	if (pMod)
	{
		//cout<<"HHH"<<endl;
		pFunc = PyObject_GetAttrString (pMod, "getCpuNum");
		if (pFunc)
		{
			//cout<<"HHH"<<endl;
			PyObject *pResult = PyEval_CallObject (pFunc, NULL);
			PyObject *Num = PyList_GetItem (pResult, 0);
			char *jNum = PyString_AsString (Num);
			iNum = atoi (jNum);
			//printf("%d\n",iNum);
			return 1;
		}
	}
	return 0;
}

int getCpuType (char*& strCpuType)
{
	Py_Initialize ();
	PyRun_SimpleString ("import os,sys");
	PyRun_SimpleString ("sys.path.append ('./')");

	PyObject *pMod = NULL;
	PyObject *pFunc = NULL;

	pMod = PyImport_ImportModule ("systemgm");
	if (pMod)
	{
		pFunc = PyObject_GetAttrString (pMod, "getCpuType");
		if (pFunc)
		{
			PyObject *pResult = PyEval_CallObject (pFunc, NULL);
			strCpuType = PyString_AsString (pResult);
			return 1;
		}
	}
	return 0;
}

int getCpuMHz (char*& strCpuMHz)
{
	Py_Initialize ();
	PyRun_SimpleString ("import os,sys");
	PyRun_SimpleString ("sys.path.append ('./')");

	PyObject *pMod = NULL;
	PyObject *pFunc = NULL;

	pMod = PyImport_ImportModule ("systemgm");
	if (pMod)
	{
		pFunc = PyObject_GetAttrString (pMod, "getCpuMHz");
		if (pFunc)
		{
			PyObject *pResult = PyEval_CallObject (pFunc, NULL);
			strCpuMHz = PyString_AsString (pResult);
			return 1;
		}
	}
	return 0;
}

int getCacheSize (char*& strCacheSize)
{
	Py_Initialize ();
	PyRun_SimpleString ("import os,sys");
	PyRun_SimpleString ("sys.path.append ('./')");

	PyObject *pMod = NULL;
	PyObject *pFunc = NULL;

	pMod = PyImport_ImportModule ("systemgm");
	if (pMod)
	{
		pFunc = PyObject_GetAttrString (pMod, "getCacheSize");
		if (pFunc)
		{
			PyObject *pResult = PyEval_CallObject (pFunc, NULL);
			strCacheSize = PyString_AsString (pResult);
			return 1;
		}
	}
	return 0;
}

int getMemTotal (char*& strMemTotal)
{
	Py_Initialize ();
	PyRun_SimpleString ("import os,sys");
	PyRun_SimpleString ("sys.path.append ('./')");

	PyObject *pMod = NULL;
	PyObject *pFunc = NULL;

	pMod = PyImport_ImportModule ("systemgm");
	if (pMod)
	{
		pFunc = PyObject_GetAttrString (pMod, "getMemTotal");
		if (pFunc)
		{
			PyObject *pResult = PyEval_CallObject (pFunc, NULL);
			strMemTotal = PyString_AsString (pResult);
			return 1;
		}
	}
	return 0;
}

int getMemFree (char*& strMemFree)
{
	Py_Initialize ();
	PyRun_SimpleString ("import os,sys");
	PyRun_SimpleString ("sys.path.append ('./')");

	PyObject *pMod = NULL;
	PyObject *pFunc = NULL;

	pMod = PyImport_ImportModule ("systemgm");
	if (pMod)
	{
		pFunc = PyObject_GetAttrString (pMod, "getMemFree");
		if (pFunc)
		{
			PyObject *pResult = PyEval_CallObject (pFunc, NULL);
			strMemFree = PyString_AsString (pResult);
			return 1;
		}
	}
	return 0;
}

int setServicesTime (int iDate, int iTime)
{
	Py_Initialize ();
	PyRun_SimpleString ("import os,sys,re");
	PyRun_SimpleString ("sys.path.append ('./')");

	PyObject *pMod = NULL;
	PyObject *pFunc = NULL;

	int i;

	pMod = PyImport_ImportModule ("systemgm");
	if (pMod)
	{
		pFunc = PyObject_GetAttrString (pMod, "setServicesTime");
		if (pFunc)
		{
			PyObject *pArgs = PyTuple_New(2);
			PyTuple_SetItem(pArgs, 0, Py_BuildValue("i",iDate));
			PyTuple_SetItem(pArgs, 1, Py_BuildValue("i",iTime));
			PyObject *pResult = PyEval_CallObject (pFunc, pArgs);
			PyArg_Parse(pResult, "i", &i);
			//cout<<"FFFFF"<<endl;
			//return 1;
		}
		//cout<<"TTTT"<<endl;
			
	}
	//cout<<"FFFFFGG"<<endl;
	return i;
}

int setServicesName (const char* strHostName)
{
	Py_Initialize ();
	PyRun_SimpleString ("import os,sys,re");
	PyRun_SimpleString ("sys.path.append ('./')");

	PyObject *pMod = NULL;
	PyObject *pFunc = NULL;

	pMod = PyImport_ImportModule ("systemgm");
	if (pMod)
	{
		pFunc = PyObject_GetAttrString (pMod, "setServicesName");
		if (pFunc)
		{
			PyObject *pArgs = PyTuple_New(1);
			PyTuple_SetItem(pArgs, 0, Py_BuildValue("s",strHostName));
			PyObject *pResult = PyEval_CallObject (pFunc, pArgs);
			return 1;
		}
	}
	return 0;
}

int setServerPort (int iPort)
{
	Py_Initialize ();
	PyRun_SimpleString ("import os,sys,re");
	PyRun_SimpleString ("sys.path.append ('./')");

	PyObject *pMod = NULL;
	PyObject *pFunc = NULL;

	pMod = PyImport_ImportModule ("systemgm");
	if (pMod)
	{
		pFunc = PyObject_GetAttrString (pMod, "setServerPort");
		if (pFunc)
		{
			PyObject *pArgs = PyTuple_New(1);
			PyTuple_SetItem(pArgs, 0, Py_BuildValue("i",iPort));
			PyObject *pResult = PyEval_CallObject (pFunc, pArgs);
			return 1;
		}
	}
	return 0;
}

int setEarthnet (const char* strIP,const char* strMask,const char* strGateway,const char* strEarthName)
{
	Py_Initialize ();
	PyRun_SimpleString ("import os,sys,re,socket");
	PyRun_SimpleString ("sys.path.append ('./')");

	PyObject *pMod = NULL;
	PyObject *pFunc = NULL;

	pMod = PyImport_ImportModule ("systemgm");
	if (pMod)
	{
		//cout<<"JJJJJJ"<<endl;
		pFunc = PyObject_GetAttrString (pMod, "setEarthnet");
		if (pFunc)
		{
			PyObject *pArgs = PyTuple_New(4);
			PyTuple_SetItem(pArgs, 0, Py_BuildValue("s",strIP));
			PyTuple_SetItem(pArgs, 1, Py_BuildValue("s",strMask));
			PyTuple_SetItem(pArgs, 2, Py_BuildValue("s",strGateway));
			PyTuple_SetItem(pArgs, 3, Py_BuildValue("s",strEarthName));
			PyObject *pResult = PyEval_CallObject (pFunc, pArgs);
			return 1;
		}
	}
	return 0;
}


int main ()
{
	EthernetInfo ethInfo;
	getEthernetInfo (ethInfo);
	outPut (ethInfo);

	char* strStartTime;
	getSystemStartTime (strStartTime);
	cout<<strStartTime<<endl;

	char* strRuntime;
	getSystemRunTime (strRuntime);
	cout<<strRuntime<<endl;

	vector<string>vDns;
	getDNS (vDns);
	for (int i = 0; i < vDns.size (); i++)
		cout<<vDns[i]<<endl;

	int port;
	getApacheListenPort (port);
	cout<<port<<endl;

	char *strHostName;
	getServicesName (strHostName);
	printf("%s\n",strHostName);

	int iNum;
	getCpuNum (iNum);
	printf("%d\n",iNum);

	char* strCpuType;
	getCpuType (strCpuType);
	printf ("%s\n",strCpuType);

	char* strCpuMHz;
	getCpuMHz (strCpuMHz);
	printf ("%s\n",strCpuMHz);

	char* strCacheSize;
	getCacheSize (strCacheSize);
	printf ("%s\n",strCacheSize);

	char * strMemTotal;
	getMemTotal (strMemTotal);
	printf ("%s\n",strMemTotal);

	char* strMemFree;
	getMemFree (strMemFree);
	printf ("%s\n",strMemFree);

	int iDate = 20120223;
	int iTime = 135959;
	cout<<setServicesTime(iDate, iTime)<<endl;

	const char* strHostNameSet = "nas";
	cout<<setServicesName(strHostNameSet)<<endl;

	int iPort = 80;
	cout<<setServerPort(iPort)<<endl;

	const char* strIP = "192.168.1.134";
	const char* strMask = "255.255.255.0";
	const char* strGateway = "192.168.1.1";
	const char* strEarthName = "eth0";
	cout<<setEarthnet(strIP, strMask, strGateway, strEarthName)<<endl;

	return 0;
}
