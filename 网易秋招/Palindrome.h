//#pragma once
//#include <cassert>
////���һ��������������֮���ԭ������һ���ľͳ���������������Ϊ�������С����磺
////{1, 2, 1}, {15, 78, 78, 15} , {112} �ǻ�������, 
//// {1, 2, 2}, {15, 78, 87, 51} ,{112, 2, 11} ���ǻ������С�
//// ���ڸ���һ���������У�����ʹ��һ��ת��������
//// ѡ�������������ڵ�����Ȼ��������Ƴ������������������������ֵĺͲ��뵽��������֮ǰ��λ��(ֻ����һ����)��
//// ���ڶ�����������Ҫ���������Ҫ���ٴβ������Խ����ɻ������С�
//
//
//������
//int comb(int* num,int head,int tail)
//{
//	
//	int left = num[head];
//	int right = num[tail];
//
//	int times = 0;
//	while(head != tail)
//	{
//		if(left<right)
//		{
//			left += num[++head];
//			++times;
//			if(head == tail)
//				return times;
//		}
//		else if(left > right)
//		{
//			right += num[--tail];
//			++times;
//			if(head == tail)
//				return times;
//		}
//		else if(left == right)
//		{
//			head++;
//			if(head != tail)
//				tail--;
//		}
//
//	}
//	return times;
//}
//void TestPalindrome()
//{
//	int n = 0;
//	int num[50] = {0};
//	cin>>n;
//
//	for(int i = 0; i<n; ++i)
//	{
//		cin>>num[i];
//	}
//
//	int ret = comb(num,0,n-1);
//	cout<<ret<<endl;
//}