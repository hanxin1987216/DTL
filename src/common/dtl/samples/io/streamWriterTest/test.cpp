#include <dtl.h>



#include "streamwriter.h"


int main()
{
	StreamWriter infile ("a.txt",false);
	
	infile.writeChar('e');
	String tmp = "tomorrow is sunday";
	infile.writeChar('\n');
	infile.writeChars(tmp.getCStr(),4);
	for(size_t i = 0; i <= 5; ++i)
	{
		infile.writeChars(tmp.getCStr(),i);
		infile.writeChar('\n');
	}
	infile.writeLine(tmp);
	infile.writeString("this is a aaa test");
	infile.writeChar('\n');
	infile.writeString("jack is a man",' ');
	infile.writeChar('\n');
	
	

	infile.fclose();





	return 0;
}