/***************************************************************************************************
tcdate.cpp:	
	C++ Foundation Library header files
	Copyright (c) Datatom Software, Inc.(2012)

Purpose:
test the date function

Author:
	应业敏

Creating Time:
	2012-2-9
***************************************************************************************************/
#include <dtprec.h>
#include <dtl.h>
#include <Python.h>
#include "../../../lang/uint.h"

int main() //调用python函数
{
Py_Initialize();
/*PyObje
ct * pModule = NULL;
PyObject * pFunc = NULL;
pModule =PyImport_ImportModule("pdf_carver_def");
PyObject* pDict = PyModule_GetDict(pModule);
PyObject* func = PyDict_GetItemString(pDict,"build_index");
PyObject* pArgs = PyTuple_New(2); 
PyTuple_SetItem(pArgs, 0, Py_BuildValue("s","pdf.index")); 
PyTuple_SetItem(pArgs, 1, Py_BuildValue("s","dfrws-2007-challenge.img")); 
//PyObject* pArgs = PyTuple_New(1); 
//PyTuple_SetItem(pArgs, 0, Py_BuildValue("s","pdf")); 
PyObject_CallObject(func,pArgs);
//Py_DECREF(pArgs); 
//Py_DECREF(pModule); 
Py_Finalize();
return 0;*/
}