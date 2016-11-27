//#pragma once
//#include <cassert>
////如果一个数字序列逆置之后跟原序列是一样的就称这样的数字序列为回文序列。例如：
////{1, 2, 1}, {15, 78, 78, 15} , {112} 是回文序列, 
//// {1, 2, 2}, {15, 78, 87, 51} ,{112, 2, 11} 不是回文序列。
//// 现在给出一个数字序列，允许使用一种转换操作：
//// 选择任意两个相邻的数，然后从序列移除这两个数，并用这两个数字的和插入到这两个数之前的位置(只插入一个和)。
//// 现在对于所给序列要求出最少需要多少次操作可以将其变成回文序列。
//
//
//有问题
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