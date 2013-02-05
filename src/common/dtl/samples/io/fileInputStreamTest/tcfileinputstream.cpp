#include <dtl.h>
#include <dtprec.h>

void 
test_read(void)
{
	FileInputStream in = FileInputStream("a.txt");
	String str = in.getFileName();
	cout << str.getCStr() << endl;
	char ptr[50];
	in.read(ptr,50);
	printf("%s\n",ptr);
	in.close();
}

void
test_seek(void)
{
	FileInputStream in = FileInputStream("b.txt");
	in.seek(3,SEEK_CUR);
	char ptr[30];
	in.read(ptr,5);
	printf("%s\n",ptr);
	in.close();
}

void 
test_available()
{
	FileInputStream in = FileInputStream("c.txt");
//	char ptr[50];
//	in.read(ptr,10);
	int64 left = in.available();
	cout << left << endl;
	in.close();
}

int main()
{
	test_read();
	test_seek();
	test_available();
	return 0;
}
