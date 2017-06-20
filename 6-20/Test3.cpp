/*************************************************************************
	> File Name: Test3.cpp
	> Author: ZX
	> Mail: 18829897183@163.com 
	> Created Time: Tue 20 Jun 2017 02:57:13 AM PDT
 ************************************************************************/

#include<iostream>
using namespace std;

int PartSort(int* a,int begin,int end)
{
       int prev = begin - 1;
       int cur = begin;
       while (cur<end)
       {
              if (a[cur] < a[end])
              {
                     prev++;
                     if (prev != cur)
                           swap(a[prev], a[cur]);
              }
              cur++;
       }
       prev++;
       swap(a[prev], a[end]);
       return prev;
}
//利用前后指针来快速的实现划分左右子区间
void QuickSort(int *a,int begin,int end)
{
       assert(a);
       if (end>begin)
       {
              int div = PartSort(a, begin, end);
              QuickSort(a, begin, div - 1);
              QuickSort(a, div + 1, end);
       }
}

