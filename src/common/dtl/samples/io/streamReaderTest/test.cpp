#include <iostream>
#include <vector>
#include <string.h>
#include <fstream>
#include <cstddef>
#include "streamreader.h"
using namespace std;

int main()
{
	string filepath = "a.txt";

	//StreamWriter writer(filePath);
	
	vector<string> lines;
    vector<string>::iterator it;
    char tmp_char;
    string test_string;

	StreamReader test(filepath);

    test.readlines(lines);
	for ( it=lines.begin(); it!=lines.end(); ++it)
	{
		cout<<*it<<endl;
	}

	test.close ();
	
	return 0;
}