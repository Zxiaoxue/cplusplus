/*************************************************************************
	> File Name: Test1.cpp
	> Author: ZX
	> Mail: 18829897183@163.com 
	> Created Time: Tue 20 Jun 2017 02:56:50 AM PDT
 ************************************************************************/

#include<iostream>
#include<assert.h>
using namespace std;

int PartSort(int *a,int begin,int end)
{
       int left = begin;
       int right = end;
       while (left < right)
       {
              while (left < right&&a[left]<=a[end])     //找到一个大于基准值的值
              {
                     left++;
              }
              while (left < right&&a[right] >=a[end])    //找到一个小于基准值的值
              {
                     right--;
              }
              if (left<right)
                     swap(a[left],a[right]);
       }
       swap(a[left], a[end]);
       return left;
}

void QuickSort(int *a,int begin,int end)
{
       assert(a);
       int div=PartSort(a,begin,end);
       if (div-1>begin)                 //这个区间的元素个数大于一个的时候就要在进行划分排序
           QuickSort(a,begin,div-1);
       if (div+1<end)
              QuickSort(a,div+1,end);
}

int main()
{
	return 0;
}

