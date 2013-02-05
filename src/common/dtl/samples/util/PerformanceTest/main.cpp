#include <dtprec.h>
#include <dtl/dtl.h>

void testfunc1 ()
{
	DTL_ADD_PROFILER_CODE_EX ("test1");
	
	cout << genMachineCode ().getCStr() << endl;
}

void testfunc2()
{
	DTL_ADD_PROFILER_CODE_EX ("test2");
	int64 a = 0;
	for (int i= 0; i< 100000000; i++)
		a += i;
	
	cout << "a = " << a << endl;
 }



int main ()
{	

	InitDTLibrary ();
	
	testfunc1 ();
	testfunc2 ();
	
	DTL_PROFILER_PRINT();

	return 0;
}

