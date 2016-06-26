#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;

class String
{
public:
	String(char* str = "")
		:_str(new char[strlen(str) + 1])
	{
		strcpy(_str, str);
	}
	String (const String& s)
		:_str(NULL)
	{
		/*_str = new char[strlen(s._str) + 1];
		strcpy(_str, s._str);*/
		String tmp(s._str);
		swap(_str, tmp._str);
	}
	String operator=(const String& s)
	{
	/*	if (this != &s)
		{
			delete[] _str;
			_str = new char[strlen(s._str) + 1];
			strcpy(_str, s._str);
		}
		return *this;*/
		if (this != &s)
		{
			String tmp(s._str);
			swap(_str, tmp._str);
		}
		return *this;
	}
	//String operator= (String s)//传值，会构造临时变量，将临时变量的_str和this的_str交换
	//{
	//	swap(_str, s._str);
	//}
	~String()
	{
		delete[] _str;
	}

	char* Cstr()
	{
		return _str;
	}
private:
	char* _str;
};
int main()
{
	system("pause");
	return 0;
}