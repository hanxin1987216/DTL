#include <dtprec.h>
#include <dtl/dtl.h>


int main ()
{
	try {

		// 
		InitDTLibrary ();

		DoResourceReader res ("dtl.do", true);
		String msg = res.loadString ("IDS_TO_STRING_TEST");

		cout << msg.getCStr () << endl;

	}
	catch (Exception &e) {
		cout << e.toString ().getCStr () << endl;
	}
	return 0;
}

