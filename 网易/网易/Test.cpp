#include<iostream>
using namespace std;


int main()
{
	int N,M;
	cin>>N>>M;
	int *arr = new int[N+2];
	int i = 0;
	for(;i<N+2; i++)
	{
		arr[i] = -1;
	}
	int j = 0;
	int a = 0,b = 0;
	for(; j<M; j++)
	{
		cin>>a;
		cin>>b;
		if(a == b)
		{
			return 1;
		}
		if(arr[a] == -1 && arr[b] == -1)
		{
			arr[a] = 0;
			arr[b] = 0;
		}
		else if((arr[a] == -1 && arr[b] != -1) || (arr[a] != -1 && arr[b] == -1))
		{
			if(arr[a] == -1)
				arr[a] = arr[b];
			if(arr[b] == -1)
				arr[b] = arr[a];
		}
	}
	int count = 0;
	for(i = 0; i<N+1; i++)
	{
		if(arr[i] == -1)
			count++;
	}
	cout<<count-1;
	system("pause");
	return 0;
}