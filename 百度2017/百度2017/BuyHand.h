
#include<iostream>
#include<set>
using namespace std;

//度度熊想去商场买一顶帽子，商场里有N顶帽子，有些帽子的价格可能相同。
//度度熊想买一顶价格第三便宜的帽子，问第三便宜的帽子价格是多少？

//首先输入一个正整数N（N <= 50），接下来输入N个数表示每顶帽子的价格（价格均是正整数，且小于等于1000）
//输出描述:如果存在第三便宜的帽子，请输出这个价格是多少，否则输出-1
//输入例子:
//10
//10 10 10 10 20 20 30 30 40 40


int BuyHand()
{
	int N;
	cin>>N;
	int pirce;
	set<int> pirces;
	for(int i = 0; i<N; i++)
	{
		cin>>pirce;
		pirces.insert(pirce);
	}
	int peace = 2;
	set<int>::iterator it = pirces.begin();
	while(peace--)
	{
		it++;
	}
	cout<<*it<<endl;
	return 0;
}

