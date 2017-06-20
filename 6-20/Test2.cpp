/*************************************************************************
	> File Name: Test2.cpp
	> Author: ZX
	> Mail: 18829897183@163.com 
	> Created Time: Tue 20 Jun 2017 02:57:06 AM PDT
 ************************************************************************/

#include<iostream>
using namespace std;

int PartSort(int *a,int begin,int end)
{
       int left = begin;
       int right = end;
       int key = a[end];
       int blank = end;
       while (left<right)
       {
              if (blank == right)        //从左边开始找一个比基准数大的值
              {
                     while (left<right&&a[left]<=key)
                     {
                           left++;
                     }
                     a[blank] = a[left];
                     blank = left;
              }
              else if (blank == left)    //从右边开始找一个比基准值小的值
              {
                     while (left<right&&a[right]>=key)
                     {
                           right--;
                     }
                     a[blank] = a[right];
                     blank = right;
              }
       }
       a[blank] = key;
       return blank;
}
void QuickSort(int *a,int begin,int end)
{
       assert(a);
       if (begin < end)
       {
              int div=PartSort(a,begin,end);
              QuickSort(a,begin,div-1);
              QuickSort(a,div+1,end);
       }
}

