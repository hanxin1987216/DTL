/****************************************************************************************************
cifsmgm.cpp
 	Copyright (python) Datatom, Inc.(2012), All rights reserved.

Purpose:
	define cifsmgm 
	
Auther:
	yingyemin (ying.yemin@datatom.com)

Created Time:
	2012-2-28
****************************************************************************************************/
#include <Python.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

struct cifsShareInfo
{
	string 		user; 		// 用户或者用户组
	int 		auth;	 
	bool 		isGroup;	// 是否为用户组	
};

int editDirShare (const string  origDirName, const string  shareDirName, vector<cifsShareInfo> shareInfo)
{
	Py_Initialize ();

	PyRun_SimpleString ("import sys,os,re");
	PyRun_SimpleString ("sys.path.append ('./')");

	PyObject *pMod = NULL;
	PyObject *pFunc = NULL;

	int k = 0;

	pMod = PyImport_ImportModule ("h21");
	if (pMod)
	{
		pFunc = PyObject_GetAttrString (pMod, "editDirShare");
		if (pFunc)
		{
			//cout<<"OOOOO"<<endl;

			PyObject *pArgs = PyTuple_New (3);
			int i = shareInfo.size();
			PyObject *list = PyList_New (i);
			int j = 0;

			for (;j < i; j++)
			{
				PyObject *Info = PyList_New(3);

				PyList_SetItem(Info, 0, Py_BuildValue("s", shareInfo[j].user.c_str()));
				PyList_SetItem(Info, 1, Py_BuildValue("i", shareInfo[j].auth));
				PyList_SetItem(Info, 2, Py_BuildValue("i", shareInfo[j].isGroup));

				PyList_SetItem(list, j, Info);
			}

			PyTuple_SetItem(pArgs, 0, Py_BuildValue("s", origDirName.c_str()));
			PyTuple_SetItem(pArgs, 1, Py_BuildValue("s", shareDirName.c_str()));
			PyTuple_SetItem(pArgs, 2, list);

			PyObject *pResult = PyEval_CallObject(pFunc, pArgs);
			PyArg_Parse(pResult, "i", &k);
			//cout<<"OOOOO"<<endl;
		}
	}
	//cout<<k<<endl;
	return k;
}

int getShareInfo (const string origDirName, string & shareDirName, vector<cifsShareInfo> & shareInfo)
{
	Py_Initialize ();

	PyRun_SimpleString ("import os,re,sys");
	PyRun_SimpleString ("sys.path.append ('./')");

	PyObject *pMod = NULL;
	PyObject *pFunc = NULL;

	pMod = PyImport_ImportModule ("h27");
	if (pMod)
	{
		pFunc = PyObject_GetAttrString (pMod, "getShareInfo");
		if (pFunc)
		{
			PyObject *pArgs = PyTuple_New(1);
			PyTuple_SetItem(pArgs, 0, Py_BuildValue("s",origDirName.c_str()));
			PyObject *pResult = PyEval_CallObject(pFunc, pArgs);

			PyObject *shDN = PyList_GetItem(pResult, 0);
			char *shdn = PyString_AsString(shDN);
			shareDirName.assign(shdn);

			PyObject *shIf = PyList_GetItem(pResult, 1);

			int i = PyList_Size(shIf);
			for(int j = 0; j < i; j++)
			{
				cifsShareInfo cifs;
				PyObject *shif = PyList_GetItem(shIf, j);

				PyObject *puser = PyList_GetItem(shif, 0);
				char *cuser = PyString_AsString(puser);
				cifs.user.assign(cuser);

				PyObject *pauth = PyList_GetItem(shif, 1);
				PyArg_Parse(pauth, "i", &cifs.auth);

				PyObject *pisGroup = PyList_GetItem(shif, 2);
				PyArg_Parse(pisGroup, "i", &cifs.isGroup);

				shareInfo.push_back (cifs);
			}
			return 1;
		}
	}
	return 0;
}

int getCifsShareDir (vector<string> & allSharedDir)
{
	Py_Initialize ();

	PyRun_SimpleString ("import os,re,sys");
	PyRun_SimpleString ("sys.path.append ('./')");

	PyObject *pMod = NULL;
	PyObject *pFunc = NULL;

	pMod = PyImport_ImportModule ("h28");
	if (pMod)
	{
		pFunc = PyObject_GetAttrString (pMod, "getCifsShareDir");
		if (pFunc)
		{
			PyObject *pResult = PyEval_CallObject(pFunc, NULL);
			
			int i = PyList_Size(pResult);
			for(int j = 0; j < i; j++)
			{
				PyObject *Dir = PyList_GetItem(pResult, j);
				char *shdir = PyString_AsString(Dir);
				allSharedDir.push_back(shdir);
			}
			return 1;
		}
	}
	return 0;
}

int addSambaUser (const string username)
{
	Py_Initialize ();

	PyRun_SimpleString ("import os,re,sys");
	PyRun_SimpleString ("sys.path.append ('./')");

	PyObject *pMod = NULL;
	PyObject *pFunc = NULL;

	pMod = PyImport_ImportModule ("h30");
	if (pMod)
	{
		pFunc = PyObject_GetAttrString (pMod, "addSambaUser");
		if (pFunc)
		{
			//cout<<"JJJJJJJJ"<<endl;
			PyObject *pArgs = PyTuple_New(1);
			//cout<<"JJJJ"<<endl;
			PyTuple_SetItem(pArgs, 0, Py_BuildValue("s",username.c_str()));
			PyObject *pResult = PyEval_CallObject(pFunc, pArgs);
			//cout<<"JJJJ"<<endl;
			return 1;
		}
	}
	return 0;
}

int changeSambaPwd (const string username,const string passwd)
{
	Py_Initialize ();

	PyRun_SimpleString ("import os,re,sys");
	PyRun_SimpleString ("sys.path.append ('./')");

	PyObject *pMod = NULL;
	PyObject *pFunc = NULL;

	pMod = PyImport_ImportModule ("h31");
	if (pMod)
	{
		pFunc = PyObject_GetAttrString (pMod, "changeSambaPwd");
		if (pFunc)
		{
			PyObject *pArgs = PyTuple_New(2);
			PyTuple_SetItem(pArgs, 0, Py_BuildValue("s", username.c_str()));
			PyTuple_SetItem(pArgs, 1, Py_BuildValue("s", passwd.c_str()));

			PyObject *pResult = PyEval_CallObject(pFunc, pArgs);
			return 1;
		}
	}
	return 0;
}

int delSambaUser (const string username)
{
	Py_Initialize ();

	PyRun_SimpleString ("import os,re,sys");
	PyRun_SimpleString ("sys.path.append ('./')");

	PyObject *pMod = NULL;
	PyObject *pFunc = NULL;

	pMod = PyImport_ImportModule ("h32");
	if (pMod)
	{
		pFunc = PyObject_GetAttrString (pMod, "delSambaUser");
		if (pFunc)
		{
			PyObject *pArgs = PyTuple_New(1);
			PyTuple_SetItem(pArgs, 0, Py_BuildValue("s", username.c_str()));

			PyObject *pResult = PyEval_CallObject(pFunc, pArgs);
			return 1;
		}
	}
	return 0;
}

int removeCifsShare (const string origDirName)
{
	Py_Initialize ();

	PyRun_SimpleString ("import os,re,sys");
	PyRun_SimpleString ("sys.path.append ('./')");

	PyObject *pMod = NULL;
	PyObject *pFunc = NULL;

	pMod = PyImport_ImportModule ("h33");
	if (pMod)
	{
		pFunc = PyObject_GetAttrString (pMod, "removeCifsShare");
		if (pFunc)
		{
			PyObject *pArgs = PyTuple_New(1);
			PyTuple_SetItem(pArgs, 0, Py_BuildValue("s", origDirName.c_str()));

			PyObject *pResult = PyEval_CallObject(pFunc, pArgs);
			return 1;
		}
	}
	return 0;
}

int removeVolumeShare (const string volumepath)
{
	Py_Initialize ();

	PyRun_SimpleString ("import os,re,sys");
	PyRun_SimpleString ("sys.path.append ('./')");

	PyObject *pMod = NULL;
	PyObject *pFunc = NULL;

	pMod = PyImport_ImportModule ("h34");
	if (pMod)
	{
		pFunc = PyObject_GetAttrString (pMod, "removeVolumeShare");
		if (pFunc)
		{
			PyObject *pArgs = PyTuple_New(1);
			PyTuple_SetItem(pArgs, 0, Py_BuildValue("s", volumepath.c_str()));

			PyObject *pResult = PyEval_CallObject(pFunc, pArgs);
			return 1;
		}
	}
	return 0;
}

int restartSMB ()
{
	Py_Initialize ();

	PyRun_SimpleString ("import os,re,sys");
	PyRun_SimpleString ("sys.path.append ('./')");

	PyObject *pMod = NULL;
	PyObject *pFunc = NULL;

	pMod = PyImport_ImportModule ("h35");
	if (pMod)
	{
		pFunc = PyObject_GetAttrString (pMod, "restartSMB");
		if (pFunc)
		{
			PyObject *pResult = PyEval_CallObject(pFunc, NULL);
			return 1;
		}
	}
	return 0;
}

int main ()
{
	/*vector<cifsShareInfo> shareInfo;
	cifsShareInfo cifs;
	cifs.user = "ab";
	cifs.auth = 0;
	cifs.isGroup = true;

	for(int i = 3; i >= 0; --i)
	{
		cifs.user += "c";
		cifs.auth = (cifs.auth+1)%2;
		cifs.isGroup = (~cifs.isGroup);
		shareInfo.push_back(cifs);
	}

	editDirShare("/adc/da", "share", shareInfo);

	string origDirName = "/adc/da";
	string shareDirName;
	vector<cifsShareInfo> gshareInfo;

	getShareInfo (origDirName, shareDirName, gshareInfo);
	for (int i = 0; i < gshareInfo.size(); ++i)
	{
		cout<<gshareInfo[i].user<<endl;
		cout<<gshareInfo[i].auth<<endl;
		cout<<gshareInfo[i].isGroup<<endl;
	}

	cout<<shareDirName<<endl;

	vector<string> allSharedDir;
	getCifsShareDir (allSharedDir);

	for (int i = 0; i < allSharedDir.size(); ++i)
	{
		cout<<allSharedDir[i]<<endl;
	}

	string username = "ss";
	addSambaUser (username);

	string cusername = "fff";

	string passwd = "345678";
	changeSambaPwd (cusername, passwd);

	string username = "df";
	delSambaUser (username);

	string origDirName = "3";
	removeCifsShare (origDirName);

	string volumepath = "da";
	removeVolumeShare (volumepath);*/

	restartSMB ();

}