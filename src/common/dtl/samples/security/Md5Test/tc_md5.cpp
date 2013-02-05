#include <dtprec.h>
#include <dtl.h>

unsigned char input [16] = "012345678912345";
unsigned char output [33];
unsigned char digest [16];

void 
tc_md5 (void)
{
	int i = 0;
	int j = 0;
	MD5Hash zts;
	zts.update (input, 16);
	zts.final (output);
	for (i=0; i<31; i++)
	{
		printf ("%2x", output[i]);
		//cout << (unsigned char) output[i];
	}
	cout << endl;
	zts.toString (output, input);
	for (j=0; j<30; j++)
	{
		cout << output[j];
	}
	cout << endl;
}

int main()
{
	memset (output, 0, 33);
	memset (digest, 0, 16);
	cout << "the source is:" << input << endl;
	tc_md5();
	return 0;
}

