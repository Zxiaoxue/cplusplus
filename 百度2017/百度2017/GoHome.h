#include <iostream>
#include <algorithm>
using namespace std;

//һ�������Ϲ���N���㣬��һ����������Ƕȶ�������λ�ã���N-1�����Ƕȶ��ܵļҡ�
//��������Ҫ���εĴ�0�������ߵ�N-1�����ꡣ
//���ǳ���0�������N-1�����꣬�������������N-2��������ѡ��һ���㣬
//��ֱ�ӽ��������Ե����ʶȶ��ܻؼ������߶��پ��룿

/*��������:
����һ��������N, N <= 50��
������N��������ʾ���꣬������ʾX��������򣬸�����ʾX��ĸ����򡣾���ֵС�ڵ���100
�������:
���һ��������ʾ�ȶ���������Ҫ�ߵľ��롣
��������:
4
1 4 -1 3
�������:
4
*/
//����
//#define MAX_NAME 50
//int GoHome()
//{
//	int N;
//	cin>>N;
//	int n[MAX_NAME];			//����㼯��
//	int dist[MAX_NAME];		//��������ľ���
//	int deldist[MAX_NAME];	//
//	for(int i = 0; i<N; i++)
//	{
//		cin>>n[i];
//	}
//
//	int sum = 0;//��ɾ���κε���ܾ����Ƕ���
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
//	//��ɾ��ĳ������ٵľ���
//	for(int i = 1; i<N-1; i++)
//	{
//		int tmp = n[i+1]-n[i];
//		if(tmp < 0)
//			tmp *= -1;
//		deldist[i] = dist[i-1]+dist[i]-tmp;//ɾ��i����ٵľ���
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
		int tmp = abs(num[i]-num[i-1]) + abs(num[i+1]-num[i]);//���������ξ����

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