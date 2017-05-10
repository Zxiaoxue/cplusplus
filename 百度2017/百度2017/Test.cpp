//#include "BuyHand.h"
//#include "GoHome.h"
//
//int main()
//{
//	//BuyHand();
//	GoHome();
//	system("pause");
//	return 0;
//}



#include <iostream>
#include <algorithm>
using namespace std;

int N;

class Solution {
public:
	int	min_dis(int* number, int nums)
	{
		int max_node,max_length=0,tmp,dis=0;
		for (int i = 1;i < nums - 1;i++)
		{
			tmp = abs(number[i] - number[i - 1]) + abs(number[i + 1] - number[i]); //�͸õ���ص�·������
			int delta = abs(tmp-abs(number[i+1]-number[i-1]));//ɾ���õ��� ����·������
			if (delta > max_length)
			{
				max_node = i;
				max_length = delta;  //ȡ�������ĵ�
			}
		}
	    
		for (int i = 0;i < nums-1;i++)
		{
			dis += abs(number[i+1]-number[i]); //ԭ��·������
		}

		dis = dis - max_length;
		return dis;
	}
		


};

int* get_number(void)
{
	cin >> N;
	int* cat = new int[N];

	for (int i = 0;i < N;i++)
	{
		cin >> cat[i];
	}

	return cat;
	//for (int i = 0;i < N;i++)
	//{
	//	cout<< cat[i]<<" ";
	//}
}

int main()
{
	int* number;
	int dis = 0;
	Solution s;
	number = get_number();

	dis = s.min_dis(number, N);

	delete[] number;
	cout << dis;
	system("pause");
    return 0;
}