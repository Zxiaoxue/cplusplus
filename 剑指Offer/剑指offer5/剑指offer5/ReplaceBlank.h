#include <iostream>
#include <assert.h>
using namespace std;

void ReplaceBlank(char str[],int len)
{
	if(str == NULL || len <= 0)
		return;

	int blank = 0;
	int i = 0;
	while(str[i] != '\0')
	{
		if(isspace(str[i]))
			++blank;
		++i;
	}

	int newlen = len + 2*blank;

	int Oindex = len;
	int Nindex = newlen;
	while(Oindex >= 0 && Nindex > Oindex)
	{
		if(str[Oindex] == ' ')
		{
			str[Nindex--] = '0';
			str[Nindex--] = '2';
			str[Nindex--] = '%';
		}
		else
		{
			str[Nindex--] = str[Oindex];
		}
		Oindex--;
	}
}