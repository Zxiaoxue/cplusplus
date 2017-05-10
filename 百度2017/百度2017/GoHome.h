#include <iostream>
#include <algorithm>
using namespace std;

//一个数轴上共有N个点，第一个点的坐标是度度熊现在位置，第N-1个点是度度熊的家。
//现在他需要依次的从0号坐标走到N-1号坐标。
//但是除了0号坐标和N-1号坐标，他可以在其余的N-2个坐标中选出一个点，
//并直接将这个点忽略掉，问度度熊回家至少走多少距离？

/*输入描述:
输入一个正整数N, N <= 50。
接下来N个整数表示坐标，正数表示X轴的正方向，负数表示X轴的负方向。绝对值小于等于100
输出描述:
输出一个整数表示度度熊最少需要走的距离。
输入例子:
4
1 4 -1 3
输出例子:
4
*/
//有误
//#define MAX_NAME 50
//int GoHome()
//{
//	int N;
//	cin>>N;
//	int n[MAX_NAME];			//坐标点集合
//	int dist[MAX_NAME];		//相邻坐标的距离
//	int deldist[MAX_NAME];	//
//	for(int i = 0; i<N; i++)
//	{
//		cin>>n[i];
//	}
//
//	int sum = 0;//求不删除任何点的总距离是多少
//
//	for(int i = 0; i<N-1; i++)
//	{
//		dist[i] = n[i+1] - n[i];
//		if(dist[i] < 0)
//		{
//			dist[i] *= -1;
//		}
//		sum += dist[i];
//	}
//
//	//求删除某个点后少的距离
//	for(int i = 1; i<N-1; i++)
//	{
//		int tmp = n[i+1]-n[i];
//		if(tmp < 0)
//			tmp *= -1;
//		deldist[i] = dist[i-1]+dist[i]-tmp;//删除i点后少的距离
//	}
//
//	int max = deldist[1];
//
//	for(int i = 2; i<N-1; i++)
//	{
//		if(max < deldist[i])
//		{
//			max = deldist[i];
//		}
//	}
//
//	cout<<sum-max<<endl;
//
//	return 0;
//}

int GoHome()
{
	int N;
	cin>>N;
	int* num = new int[N];
	for(int i = 0; i<N; i++)
	{
		cin>>num[i];
	}

	int dealt = 0;
	int max = 0;
	int dis = 0;
	for(int i = 1; i<N-1; i++)
	{
		int tmp = abs(num[i]-num[i-1]) + abs(num[i+1]-num[i]);//三个点两段距离和

		int dealt = abs(tmp-abs(num[i+1]-num[i-1]));
		if(dealt > max)
		{
			max = dealt;
		}
	}

	for(int i = 0; i<N-1; i++)
	{
		dis += abs(num[i+1]-num[i]);
	}
	delete[] num;
	cout<<dis -max<<endl;
	return dis;
}