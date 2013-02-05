/*******************************************************************************
main.cpp

Author:
	Huang.Xianming
Create time
	2012-4-25
*******************************************************************************/



#include <stdio.h>
#include "tc_thread.h"


int main(void)
{
	ThreadTestCase tcThread;
	char t[2] = "\0";
	tcThread.testStart();
	while (true)
	{
		printf("Please enter command:\n");
		printf("q-------------------quit\n");
		printf("s-------------------start\n");
		printf("p-------------------pause\n");
		printf("t-------------------stop\n");
		printf("j-------------------join\n");
		printf("r-------------------resume\n");
		printf("n-------------------get name\n");
		printf("a-------------------set name\n");
		printf("i-------------------get priority\n");
		printf("o-------------------set priority\n");
		printf("e-------------------get state\n");
		printf("l-------------------if alive\n");
		gets(t);
		if (t[0] == 'q' || t[0] == 'Q')
		{
			break;
		}
		else if (t[0] == 's' || t[0] == 'S')
		{
			tcThread.testStart();
		}
		else if (t[0] == 'p' || t[0] == 'P')
		{
			tcThread.testPause();
		}
		else if (t[0] == 't' || t[0] == 'T')
		{
			tcThread.testStop();
		}
		else if (t[0] == 'j' || t[0] == 'J')
		{
			tcThread.testJoin();
		}
		else if (t[0] == 'r' || t[0] == 'R')
		{
			tcThread.testResume();
		}
		else if (t[0] == 'n' || t[0] == 'N')
		{
			tcThread.testGetName();
		}
		else if (t[0] == 'a' || t[0] == 'A')
		{
			tcThread.testSetName();
		}
		else if (t[0] == 'i' || t[0] == 'I')
		{
			tcThread.testGetPriority();
		}
		else if (t[0] == 'o' || t[0] == 'O')
		{
			tcThread.testSetPriority();
		}
		else if (t[0] == 'e' || t[0] == 'E')
		{
			tcThread.testGetState();
		}
		else if (t[0] == 'l' || t[0] == 'L')
		{
			tcThread.testIsAlive();
		}
		else
		{
		}
		//printf("%s\n", t);
	}
	return 0;
}
