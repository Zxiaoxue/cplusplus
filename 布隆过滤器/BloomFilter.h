#pragma once

#include <iostream>

#include "bitMap.h"
using namespace std;


struct __HashFunc1
{
	int operator()(const string& str)
	{
		return BKDRHash(str.c_str());
	}
 
	size_t BKDRHash(const char* str)  
	{  
		register size_t hash = 0;  
		while (size_t ch = (size_t)*str++)  
		{         
			hash = hash * 131 + ch;   // 也可以乘以31、131、1313、13131、131313..          
		}  
		return hash;  
	}  
};

struct __HashFunc2
{
	int operator()(const string& str)
	{
		return SDBMHash(str.c_str());
	}
 
	size_t SDBMHash(const char *str)  
	{  
		register size_t hash = 0;  
		while (size_t ch = (size_t)*str++)  
		{  
			hash = 65599 * hash + ch;         
			//hash = (size_t)ch + (hash << 6) + (hash << 16) - hash;  
		}  
		return hash;  
	}   
};

struct __HashFunc3
{
	int operator()(const string& str)
	{
		return RSHash(str.c_str());
	}
 
 
	size_t RSHash(const char *str)  
	{  
		register size_t hash = 0;  
		size_t magic = 63689;     
		while (size_t ch = (size_t)*str++)  
		{  
			hash = hash * magic + ch;  
			magic *= 378551;  
		}  
		return hash;  
	}   
};

struct __HashFunc4
{
	int operator()(const string& str)
	{
		return APHash(str.c_str());
	}

	size_t APHash(const char *str)  
	{  
		register size_t hash = 0;  
		size_t ch;  
		for (long i = 0; ch = (size_t)*str++; i++)  
		{  
			if ((i & 1) == 0)  
			{  
				hash ^= ((hash << 7) ^ ch ^ (hash >> 3));  
			}  
			else  
			{  
				hash ^= (~((hash << 11) ^ ch ^ (hash >> 5)));  
			}  
		}  
		return hash;  
	}   
};

struct __HashFunc5
{
	int operator()(const string& str)
	{
		return JSHash(str.c_str());
	}

	size_t JSHash(const char *str)  
	{  
		if(!*str)        // 这是由本人添加，以保证空字符串返回哈希值0  
			return 0;  
		register size_t hash = 1315423911;  
		while (size_t ch = (size_t)*str++)  
		{  
			hash ^= ((hash << 5) + ch + (hash >> 2));  
		}  
		return hash;  
	}  
};


//布隆过滤器，---不支持Reset
//
//template<class K = string,class HashFunc1 = __HashFunc1,
//class HashFunc2 = __HashFunc2,class HashFunc3 = __HashFunc3,
//class HashFunc4 = __HashFunc4,class HashFunc5 = __HashFunc5>
//class BloomFilter
//{
//public:
//	BloomFilter(int k)
//		:_range(k*5)
//		,_bitMap(k*5)
//	{}
//
//	void Set(const string& str)
//	{
//		int hash1 = HashFunc1()(str)%_range;
//		int hash2 = HashFunc2()(str)%_range;
//		int hash3 = HashFunc3()(str)%_range;
//		int hash4 = HashFunc4()(str)%_range;
//		int hash5 = HashFunc5()(str)%_range;
//
//		_bitMap.Set(hash1);
//		_bitMap.Set(hash2);
//		_bitMap.Set(hash3);
//		_bitMap.Set(hash4);
//		_bitMap.Set(hash5);
//
//		
//		cout<<hash1<<endl;
//		cout<<hash2<<endl;
//		cout<<hash3<<endl;
//		cout<<hash4<<endl;
//		cout<<hash5<<endl;
//
//		cout<<endl;
//
//	}
//
//Reset不准确，置0时会影响其他位
//	bool Reset(string&)
//	{
//		int hash1 = HashFunc1()(num)%k;
//		int hash2 = HashFunc2()(num)%k;
//		int hash3 = HashFunc3()(num)%k;
//		int hash4 = HashFunc4()(num)%k;
//		int hash5 = HashFunc5()(num)%k;
//
//		if(_bitMap.Test(hash1) == 0
//			||_bitMap.Test(hash2) == 0
//			||_bitMap.Test(hash3) == 0
//			||_bitMap.Test(hash4) == 0
//			||_bitMap.Test(hash5) == 0)
//		{
//			return false;
//		}
//
//		_bitMap.Reset(hash1);
//		_bitMap.Reset(hash2);
//		_bitMap.Reset(hash3);
//		_bitMap.Reset(hash4);
//		_bitMap.Reset(hash5);
//	}
//protected:
//	BitMap _bitMap;
//	size_t _range;
//};
//
//void Test1()
//{
//	string s1 = "Chazelle, Bernard; Kilian, Joe; Rubinfeld, Ronitt; Tal, Ayellet (2004),The Bloomier filter: an efficient data structure for static support lookup tables, Proceedings of the Fifteenth Annual ACM-SIMK Symposium on Discrete Algorithms, pp. 30–39";
//	string s2 = "Chazelle, Bernard; Kilian, Joe; Rubinfeld, Ronitt; Tal, Ayellet (2004),The Bloomier filter: an efficient data structure for static support lookup tables, Proceedings of the Fifteenth Annual ACM-SIDC Symposium on Discrete Algorithms, pp. 30–39";
//	string s3 = "Chazelle, Bernard; Kilian, Joe; Rubinfeld, Ronitt; Tal, Ayellet (2004),The Bloomier filter: an efficient data structure for static support lookup tables, Proceedings of the Fifteenth Annual ACM-SIAM Symposium on Discrete Algorithms, pp. 30–39";
//
//	BloomFilter<> b(50);
//
//	b.Set(s1);
//	b.Set(s2);
//	b.Set(s3);
//}

//支持引用计数的布隆过滤器
template<class K = string,class HashFunc1 = __HashFunc1,
class HashFunc2 = __HashFunc2,class HashFunc3 = __HashFunc3,
class HashFunc4 = __HashFunc4,class HashFunc5 = __HashFunc5>
class BloomFilter
{
public:
	BloomFilter(int range)
	{
		_bitMap.resize(range);
	}

	void Set(const string& str)
	{
		size_t size = _bitMap.size();

		int hash1 = HashFunc1()(str)%size;
		int hash2 = HashFunc2()(str)%size;
		int hash3 = HashFunc3()(str)%size;
		int hash4 = HashFunc4()(str)%size;
		int hash5 = HashFunc5()(str)%size;

		_bitMap[hash1]++;
		_bitMap[hash2]++;
		_bitMap[hash3]++;
		_bitMap[hash4]++;
		_bitMap[hash5]++;

		cout<<hash1<<" "<<_bitMap[hash1]<<endl;
		cout<<hash2<<" "<<_bitMap[hash2]<<endl;
		cout<<hash3<<" "<<_bitMap[hash3]<<endl;
		cout<<hash4<<" "<<_bitMap[hash4]<<endl;
		cout<<hash5<<" "<<_bitMap[hash5]<<endl;
		cout<<endl;
	}

	bool Reset(const string& str)
	{
		size_t size = _bitMap.size();

		int hash1 = HashFunc1()(str)%size;
		int hash2 = HashFunc2()(str)%size;
		int hash3 = HashFunc3()(str)%size;
		int hash4 = HashFunc4()(str)%size;
		int hash5 = HashFunc5()(str)%size;

		
		if(_bitMap[hash1])
			_bitMap[hash1]--;
		else
			return false;

		if(_bitMap[hash2])
			_bitMap[hash2]--;
		else
			return false;

		if(_bitMap[hash3])
			_bitMap[hash3]--;
		else
			return false;

		if(_bitMap[hash4])
			_bitMap[hash4]--;
		else
			return false;

		if(_bitMap[hash5])
			_bitMap[hash5]--;
		else
			return false;

		return true;
	}

protected:
	vector<size_t> _bitMap;
};

void Test2()
{
	string s1 = "Chazelle, Bernard; Kilian, Joe; Rubinfeld, Ronitt; Tal, Ayellet (2004),The Bloomier filter: an efficient data structure for static support lookup tables, Proceedings of the Fifteenth Annual ACM-SIMK Symposium on Discrete Algorithms, pp. 30–39";
	string s2 = "Chazelle, Bernard; Kilian, Joe; Rubinfeld, Ronitt; Tal, Ayellet (2004),The Bloomier filter: an efficient data structure for static support lookup tables, Proceedings of the Fifteenth Annual ACM-SIDC Symposium on Discrete Algorithms, pp. 30–39";
	string s3 = "Chazelle, Bernard; Kilian, Joe; Rubinfeld, Ronitt; Tal, Ayellet (2004),The Bloomier filter: an efficient data structure for static support lookup tables, Proceedings of the Fifteenth Annual ACM-SIAM Symposium on Discrete Algorithms, pp. 30–39";

	BloomFilter<> b(10);

	b.Set(s1);
	b.Set(s2);
	b.Set(s3);

	b.Reset(s1);
}
