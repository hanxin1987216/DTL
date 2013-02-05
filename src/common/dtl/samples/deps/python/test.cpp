#include <Python.h>
#include <stdio.h>


int main ()
{
	Py_Initialize();

	PyObject* pMod = NULL;
	PyObject* pFunc = NULL;
	
	PyRun_SimpleString("import sys");  
	PyRun_SimpleString("sys.path.append('./')");
	
	pMod = PyImport_ImportModule("testmod");
	if(pMod)
	{
  		pFunc = PyObject_GetAttrString(pMod, "func");
		if(pFunc) {
			PyObject *pResult = PyEval_CallObject(pFunc, NULL);
			char *result = PyString_AsString(pResult);
			printf ("result = %s", result);
		}
		
	}
	
	//Py_Finalize();
	return 0;
}
