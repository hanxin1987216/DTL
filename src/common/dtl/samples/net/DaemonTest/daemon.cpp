#include <dtprec.h>
#include <dtl/dtl.h>

#include <stdio.h>
#include <time.h>

int main(void)
{
	InitDTLibrary();
	try
	{
	
		
	}catch (Exception &exc)
	{
		cout << exc.toString().getCStr() << endl;
	}
	
	return 0;
}