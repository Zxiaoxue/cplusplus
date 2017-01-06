#pragma once

#include <iostream>
using namespace std;
#include"BigData.h"

void Test()
{
	BigData b1(-1234346);
	cout<<b1<<endl;
	BigData b2("-56789");
	cout<<b2<<endl;
	BigData b3("+ghksahfcei673802174");
	cout<<b3<<endl;
	BigData b4("         ");
	cout<<b4<<endl;
	BigData b5("-000000597584atykfsya");
	cout<<b5<<endl;
	BigData b6("623456789456123456789456123");
	cout<<b6<<endl;
	BigData b7("9456845327915463254621264780");

	//BigData res1(b2+b1);
	//BigData res2(b3+b5);
	BigData res3(b6+b7);

	//cout<<res1<<endl;
	//cout<<res2<<endl;
	cout<<res3<<endl;

}

int main()
{
	Test();
	system("pause");
	return 0;
}