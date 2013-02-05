#include <iostream>
#include <dtl.h>
#include "filestream.h"
using namespace std;


int main()
{
	String name = "a.txt";	
	String name2 = "b.txt";
	//char buf[MAX_LENGTH];
	char *buf;
	
	FileStream openfile2(name2,CREATE_NEW_MODE,READ_WRITE_SHARE);
	int tmp1 = openfile2.getHandle();cout << tmp1 <<endl;
	int64 tmp2 = openfile2.getFileLength();cout << tmp2 <<endl;
	String tmp3;
	tmp3 = openfile2.getFileName();printf ("%s\n", tmp3.getCStr ());
	
	FileStream openfile(name,CREATE_NEW_MODE,READ_WRITE_SHARE);
	tmp1 = openfile.getHandle();cout << tmp1 <<endl;
	String tmp = "jack is a good man !";
	printf ("%s\n", tmp.getCStr ());
	
	/*
	int n;
	n = openfile.read(buf,MAX_LENGTH);
	while (n != -1)
	{		
		openfile2.write(buf,n);
		n = openfile.read(buf,MAX_LENGTH);
	}
	if(n == -1)
	{
		perror("fail  to write");
	}
	*/
	openfile2.close();
	openfile.close();
	
	return 0;
}