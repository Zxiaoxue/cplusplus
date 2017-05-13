
#include <iostream>
#include <string.h>
#include "Str.h"
#include "ReplaceBlank.h"
using namespace std;

int main()
{
	//Str();
	char str[] = "hello world!";
	int len = strlen(str);
	ReplaceBlank(str,len);
	printf("new: %s\n", str);
	system("pause");
	return 0;
}