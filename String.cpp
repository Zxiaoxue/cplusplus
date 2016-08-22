#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <string>

using namespace std;

//深浅拷贝
class String
{
	friend ostream&operator<<(ostream& os, String& str);
public:
	String(char* str = "")
		:_size(strlen(str))
		, _capacity(strlen(str)+1)
		, _str(new char[strlen(str) + 1])
	{
		strcpy(_str, str);

	}

	//传统写法
	//String(const String& s)
	//	:_size(s._size)
	//{
	//	_str = new char[strlen(s._str) + 1];
	//	strcpy(_str, s._str);
	//	_capacity = strlen(s._str) + 1;
	//}

	//现代写法

	String(const String& s)
		:_size(strlen(s._str))
		,_capacity(strlen(s._str)+1)
		,_str(NULL)
	{
		String tmp(s._str);
		swap(_str, tmp._str);
		swap(_size, tmp._size);
		swap(_capacity, tmp._capacity);

	}
	//传统写法
	//String& operator=(const String& s)
	//{
	//	if (this != &s)
	//	{
	//		char* tmp = new char[strlen(s._str) + 1];
	//		delete[] _str;
	//		_str = tmp;
	//		strcpy(_str, s._str);
	//		_size = s._size;
	//		_capacity = strlen(s._str) + 1;
	//	}
	//	return *this;
	//}
	
	//现代写法
	String& operator=(String s)
	{
		swap(_size, s._size);
		swap(_capacity, s._capacity);
		swap(_str, s._str);
		return *this;
	}

	~String()
	{
		if (_str)
		{
			delete[] _str;
			_size = 0;
			_capacity = 0;
			_str = NULL;
		}
	}

	char* Cstr()
	{
		return _str;
	}

	void PushBack(char ch)
	{
		_CheckCapacity(1);
		char* tmp = _str;
		while (*tmp)
		{
			++tmp;
		}
		*tmp++ = ch;
		*tmp = '\0';
	}

	void PushBack(char* s)
	{
		_CheckCapacity(strlen(s));
		char* tmp = _str;
		while (*tmp)
		{
			++tmp;
		}
		while (*s)
		{
			*tmp++ = *s++;
		}
		*tmp = '\0';
	}

	void PushBack(String& s)
	{
		_CheckCapacity(strlen(s._str));
		char* tmp1 = _str;
		char* tmp2 = s._str;
		while (*tmp1)
		{
			++tmp1;
		}
		while (*tmp2)
		{
			*tmp1++ = *tmp2++;
		}
		*tmp1 = '\0';
	}

	String& Insert(size_t pos, const String& s)
	{
		int size1 = _size;
		_CheckCapacity(strlen(s._str));
		size_t step = size1 - pos;
		int size2 = s._size;
		_size = size1 + size2;
		while (step--)
		{
			_str[size1+size2 - 1] = _str[size1 - 1];
			--size1;
		}

		char* tmp = s._str;
		while (size2--)
		{
			_str[pos++] = *tmp++;
		}
		
		_str[_size] = '\0';
		return *this;

	}

	String& Insert(size_t pos1, const String& s, size_t pos2, size_t n)
	{
		size_t size1 = _size;
		size_t size2 = s._size;
		_CheckCapacity(n);
		size_t step1 = size1 - pos1;
		while (step1--)
		{
			_str[size1 + n - 1] = _str[size1 - 1];
			--size1;
		}
		char* tmp = s._str;
		while (pos2--)
		{
			tmp++;
		}
		while (n--)
		{
			_str[pos1++] = *tmp++;
		}
		_str[_size] = '\0';
		return *this;
	}

	String& Insert(size_t pos, const char* s, size_t n)
	{
		size_t size1 = _size;
		size_t size2 = strlen(s);
		size_t step = size1 - pos;
		_CheckCapacity(n);
		while (step--)
		{
			_str[size1 + n - 1] = _str[size1 - 1];
			--size1;
		}

		while (n--)
		{
			_str[pos++] = *s++;
		}
		_str[_size] = '\0';
		return  *this;
	}
	
	String& Insert(size_t pos, const char* s)
	{
		size_t size1 = _size;
		size_t size2 = strlen(s);
		size_t step = size1 - pos;
		_CheckCapacity(size2);
		while (step--)
		{
			_str[size1+size2-1] = _str[size1-1];
			--size1;
		}
		while (size2--)
		{
			_str[pos++] = *s++;
		}
		_str[_size] = '\0';
		return *this;
	}
	
	String& Insert(size_t pos, size_t n, char c)
	{
		int size1 = _size;
		int step = size1 - pos;
		_CheckCapacity(n);
		while (step--)
		{
			_str[size1 + n - 1] = _str[size1 - 1];
			--size1;
		}
		while (n--)
		{
			_str[pos++] = c;
		}
		_str[_size] = '\0';
		return *this;
	}


public:
	void _CheckCapacity(int count)
	{
	
		if ((_size + count) >= _capacity)
		{
			int newCapacity = (2 * _capacity) > (_capacity + count) ?
				(2 * _capacity) : (_capacity + count);
			char* tmp = new char[newCapacity];
			strcpy(tmp, _str);
			delete[] _str;
			_str = tmp;
			_size += count;
			_capacity = newCapacity;
		}
	}
private:
	int _size;
	int _capacity;
	char* _str;

};

ostream& operator<<(ostream& os, String& str)
{
	os << str._str;
	return os;
}

void Test1()
{
	String s1("abcde");
	String s2(s1); 
	String s3("hello ");
	//s3.PushBack('b');
	//s3.PushBack("bit");
	s3.PushBack(s1);
	/*s3 = s1;

	cout << s1 << endl;
	cout << s2 << endl;*/
	cout << s3 << endl;
}

void Test2()
{
	String s1("adefg");
	String s2("bc");
	s1.Insert(1, s2);
	cout << s1 << endl;
}

void Test3()
{
	String s1("abcfg");
	String s2("cde");
	s1.Insert(3, s2, 1, 2);
	//cout << s1 << endl;

	String s3("hello");
	char* s = "world";
	s3.Insert(2, s, 5);
	//cout << s3 << endl;

	String s4("hello ");
	char* str = "world";
	s4.Insert(3, str);
	cout << s4 << endl;

	String s5("hello");
	char c = 'k';
	s5.Insert(1, 5, c);
	cout << s5 << endl;
}
int main()
{
	Test3();
	system("pause");
	return 0;
}