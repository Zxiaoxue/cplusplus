#pragma once

#include <iostream>
#include <vector>
using namespace std;

class BitMap
{
public:
	BitMap(int range)
	{
		bitMap.resize((range>>5)+1);
	}
	void Set(int num)
	{
		int index = num>>5;
		int pos = num%32;

		bitMap[index] |= (1<<pos);
	}

	void Reset(int num)
	{
		int index = num>>5;
		int pos = num%32;

		bitMap[index] &= (~(1<<pos));
	}

	bool Test(int num)
	{
		int index = num/32;
		int pos = num%32;

		if(bitMap[index]&(1<<pos))
			return true;
		else
			return false;
	}
protected:
	vector<size_t> bitMap;

};

void Test()
{
	BitMap bt(40);
	bt.Set(4);
	bt.Set(14);
	bt.Set(34);
	cout<<bt.Test(4)<<endl;
	cout<<bt.Test(14)<<endl;
	cout<<bt.Test(24)<<endl;
	cout<<bt.Test(34)<<endl;
	cout<<bt.Test(44)<<endl;


	bt.Reset(4);
	bt.Reset(14);
	bt.Reset(24);
	
	cout<<bt.Test(4)<<endl;
	cout<<bt.Test(14)<<endl;
	cout<<bt.Test(24)<<endl;
	cout<<bt.Test(34)<<endl;
	cout<<bt.Test(44)<<endl;
}