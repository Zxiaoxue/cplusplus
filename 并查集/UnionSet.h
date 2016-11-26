#pragma once

#include <iostream>
using namespace std;
#include <vector>
#include <cassert>
class UnionSet
{
public:
	UnionSet(int n)
		:_n(n)
	{
		_unionset = new int[n];

		//memset(_unionset,-1,sizeof(int)*n);memset按字节处理，只能初始化为0，1，-1

		for(int i = 0; i<n; ++i)
		{
			_unionset[i] = -1;
		}

	}

	int GetRoot(int root)
	{
		if(_unionset[root] >= 0)
		{
			root = _unionset[root];
		}

		return root;
	}

	void Union(int x1,int x2)
	{
		int root1 = GetRoot(x1);
		int root2 = GetRoot(x2);

		if(root1 != root2)
		{
			_unionset[root1] += _unionset[root2];
			_unionset[root2] = root1;
		}
	}

	bool Find(int x1,int x2)
	{
		int root1 = GetRoot(x1);
		int root2 = GetRoot(x2);

		return root1 == root2;
	}

	int Count()
	{
		int count = 0;
		for(int i = 0; i<_n; ++i)
		{
			if(_unionset[i] < 0)
				count++;
		}

		return count-1;
	}

	

protected:
	//vector<int> v;
	int* _unionset;
	int _n;
};

int Friend(int n,int m,int r[][2])
{
	assert(r);

	UnionSet u(n+1);//多开一个空间，0号位置不用
	for(int i = 0;i<m;++i)
	{
		int r1 = r[i][0];
		int r2 = r[i][1];

		u.Union(r1,r2);
	}
	return u.Count();
}

void Test1()
{
	int r[4][2] = {{1,2},{2,3},{4,5},{1,3}};//n=总人数，m=多少对好友关系
	cout<<"朋友圈？"<<Friend(5,4,r)<<endl;
}
void Test2()
{
	int r[][2] = {{1,2},{2,3},{4,5},{5,9},{6,2},{7,8}};//n=总人数，m=多少对好友关系
	cout<<"朋友圈？"<<Friend(9,6,r)<<endl;
}