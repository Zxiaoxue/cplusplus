#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <string.h>
#include <assert.h>
using namespace std;
//自定义类型，显式写了析构函数，在new空间的时候会在所开空间的头上多开4个字节，
//存空间大小

//写时拷贝--->count 引用计数
class String
{
public:
	String(char* str = " ")
		:_str(new char[strlen(str)+1])
		, _pRefCount(new int(1))
	{
		strcpy(_str, str);
	}
	String(String& s)
		:_str(s._str)
		,_pRefCount(s._pRefCount)
	{
		++*_pRefCount;

	}
	String operator=(const String& s)
	{
		if (this != &s)
		{
			char* tmp = new char[strlen(s._str) + 1];
			strcpy(tmp, s._str);
			delete[] _str;
			_str = tmp;
			
		}
		return *this;
	}
	~String()
	{
		if (--(*_pRefCount) == 0)
		{
			cout << "~String()" << endl;

			delete[] _str;
			delete _pRefCount;
		}
	}
private:
	char* _str;
	int* _pRefCount;
};



void Test1()
{
	String s1("s1");
	String s2(s1);
	String s3(s2);

	String s4("s4");
	String s5(s4);

}

int main()
{
	Test1();
	system("pause");
	return 0;
}

//传统写法
//class String
//{
//public:
//	String(char* str = " ")
//		:_str(new char[strlen(str)+1])
//	{
//		strcpy(_str, str);
//	}
//	String(const String& s)
//		:_str(new char[strlen(s._str)+1])
//	{
//		strcpy(_str, s._str);
//	}
//	String operator=(const String& s)
//	{
//		if (this != &s)
//		{
//			char* tmp = new char[strlen(s._str) + 1];
//			strcpy(tmp, s._str);
//			delete[] _str;
//			swap(_str, tmp);
//		}
//
//		return *this;
//	}
//	~String()
//	{
//		if (_str)
//		{
//			delete[] _str;
//		}
//	}
//private:
//	char* _str;
//};
//
//void Test1()
//{
//	String s1("ssssssssss");
//	String s2(s1);
//	String s3("hello world!");
//
//	s2 = s3;
//}
//
//int main()
//{
//	Test1();
//
//	system("pause");
//	return 0;
//}

//class String
//{
//public:
//	/*String(const char* str)
//	:_str(new char[strlen(str)+1])
//	{
//	strcpy(_str, str);
//	}*/
//	String(const char* str)
//	{
//		_size = strlen(str);
//		_capacity = _size + 1;
//		_str = new char[_capacity];
//
//		strcpy(_str, str);
//	}
//
//	String(const String& s)
//		:_str(NULL)
//	{
//		/*_str = new char[strlen(s._str) + 1];
//		if (_str)
//		{
//			strcpy(_str, s._str);
//		}*/
//
//		String tmp(s._str);
//		swap(tmp._str, _str);
//		swap(tmp._capacity, _capacity);
//		swap(tmp._size, _size);
//
//
//	}
//
//	String& operator=(String s)
//	{
//		swap(_str, s._str);
//		swap(_capacity, s._capacity);
//		swap(_size, s._size);
//
//		return *this;
//	}
//
//	/*String& operator=(const String& s)
//	{
//		if (this != &s)
//		{
//			_str = NULL;
//			String tmp(s._str);
//			swap(tmp._str, _str);
//		}
//		return *this;
//	}*/
//
//	~String()
//	{
//		if (_str)
//		{
//			delete[] _str;
//			_str = NULL;
//			_size = 0;
//			_capacity = 0;
//		}
//	}
//public:
//	char* Cstr()
//	{
//		return _str;
//	}
//
//	char& operator[](size_t index)
//	{
//		return _str[index];
//	}
//
//	void PushBack(char c)
//	{
//		_CheckCapacity(_size + 2);
//
//		_str[_size++] = c;
//		_str[_size] = '\0';//字符串最后为0
//	}
//
//	void PopBack()
//	{
//		assert(_size > 0);
//		_size--;
//		_str[_size] = '\0';
//	}
//	void Insert(size_t pos, char c)
//	{
//		assert(pos < _size);
//		_CheckCapacity(_size + 2);
//
//		size_t index = _size;
//
//		while (pos <= index)
//		{
//			_str[index + 1] = _str[index];
//			--index;
//		}
//		_str[pos] = c;
//	}
//
//	void Insert(size_t pos, const char* str)
//	{
//		assert(pos <= _size);
//		assert(str);
//		size_t len = strlen(str);
//		size_t index = _size;
//
//		_CheckCapacity(_size + len + 1);
//
//		while (pos <= index)
//		{
//			_str[index + len] = _str[index];
//			--index;
//		}
//
//		int i = 0;
//		while (i <= len)
//		{
//			_str[pos + i] = str[i];
//			i++;
//		}
//		_size += len;
//	}
//
//	int Find(char c)
//	{
//		size_t index = 0;
//		for (; index < _size; index++)
//		{
//			if (_str[index] == c)
//				return index;
//		}
//
//		return -1;
//	}
//
//	int Find(const char* sub)
//	{
//		assert(sub);
//		size_t srcIndex = 0;
//		size_t subSize = strlen(sub);
//		while (srcIndex <= _size - subSize)
//		{
//			/*for (; subindex <= strlen(sub); subindex++)
//			{
//
//			}*/
//			size_t subIndex = 0;
//			size_t begin = srcIndex;
//
//			while (_str[begin] == sub[subIndex]
//				&& subIndex<subSize
//				&&begin<_size)
//			{
//				++begin;
//				++subIndex;
//			}
//			if (subIndex == subSize)
//			{
//				return srcIndex;
//			}
//			++srcIndex;
//		}
//		return -1;
//	}
//
//	void Erase(size_t pos)
//	{
//		assert(pos <= _size);
//		size_t index = pos;
//		while (index <= _size)
//		{
//			_str[index] = _str[index + 1];
//			++index;
//		}
//		_size--;
//	}
//
//	String& operator+=(const String& str)
//	{
//		this->Insert(_size, str._str);
//
//		return *this;
//		/*assert(str._str);
//		size_t size = strlen(str._str);
//		size_t i = 0;
//		_CheckCapacity(_size + size + 2);
//
//		while (*_str)
//		{
//		*_str++;
//		}
//
//		while (i++<size)
//		{
//		_str[_size + i] = str._str[i];
//		}
//
//		return *this;*/
//	}
//	bool operator==(const String& s)
//	{
//		if (s._str == NULL)
//			return false;
//		size_t size = strlen(s._str);
//		int i = 0;
//		while (_size == size&&_str[i++] == s._str[i++])
//		{
//			;
//		}
//		if (i == size)
//		{
//			return true;
//		}
//		return false;
//	}
//	bool operator!=(const String& s)
//	{
//		return !(*this == s);
//	}
//	bool operator>(const String& s)
//	{
//		size_t size = strlen(s._str);
//		size_t index = 0;
//		while (index < size || index<_size)
//		{
//			if (_str[index] > s._str[index])
//			{
//				return true;
//			}
//			++index;
//		}
//		return false;
//	}
//	bool operator>=(const String& s)
//	{
//		return ((*this == s) || (*this > s));
//	}
//	bool operator<(const String& s)
//	{
//		return !(*this >= s);
//	}
//	bool operator<=(const String& s)
//	{
//		return !(*this > s);
//	}
//private:
//	void _CheckCapacity(int needSize)
//	{
//		//3-->2
//		//3-->20
//		if (needSize >= _capacity)
//		{
//			_capacity = needSize > 2 * _capacity ? needSize : 2 * _capacity;
//			_str = (char*)realloc(_str, _capacity);
//		}
//		//if (_size + 1 >= _capacity)
//		//{
//		//	_capacity *= 2;
//		//	_str = (char*)realloc(_str, _capacity);
//		//	/*_capacity = 2 * _capacity + 3;
//		//	char* tmp = new char[_capacity];
//		//	strcpy(tmp, _str);
//		//	delete[] _str;
//		//	_str = tmp;*/
//		//}
//
//
//	}
//
//private:
//	char* _str;
//	size_t _size;
//	size_t _capacity;
//};
//
//void Test()
//{
//	String s1("hello ");
//
//	/*s1.PushBack('w');
//	s1.PushBack('o');
//	s1.PushBack('l');
//	s1.PushBack('d');
//	s1.Insert(8, 'r');*/
//
//	s1.Insert(6, "world");
//	s1.Erase(5);
//
//	String s2("abcdabcdefg");
//	int ret1 = s2.Find("abcde");
//	cout << ret1 << endl;
//	int ret = s1.Find("abc");
//	cout << ret << endl;
//
//	cout << s1.Cstr() << endl;
//}
//void Test1()
//{
//	String s1("hello ");
//	//String s2("world");
//
//	//s1 += s2;
//	s1 += "world";
//	cout << s1.Cstr() << endl;
//}
//void Test2()
//{
//	String s1("abcd");
//	String s2("abcf");
//	cout << (s1 > s2) << endl;
//}
//
//
//int main()
//{
//	Test2();
//
//	/*string s1("aaaaabbbbbccccc");
//	string s2("aaaaabbbbbcccc");
//	cout << (s1 > s2)<<endl;*/
//	system("pause");
//	return 0;
//}