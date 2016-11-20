#pragma once

#include <iostream>

using namespace std;
#include <cassert>


void PrintArr(int* a,int size)
{

	assert(a);

	for(int i = 0; i<size; ++i)
	{
		cout<<a[i]<<" ";
	}
	cout<<endl;
}

//插入排序
void InsertSort(int* a,int size)
{
	assert(a);
	
	for(int index = 1; index<size; ++index)
	{
		int pos = index-1;
		int tmp = a[index];
		while(pos>=0 && tmp<a[pos])
		{
			a[pos+1] = a[pos];
			--pos;
		}
		a[pos+1] = tmp;
	}

}
void TestInsertSort()
{
	int a[] = {2,5,4,9,3,6,8,7,1,0};
	int size = sizeof(a)/sizeof(a[0]);

	InsertSort(a,size);
	PrintArr(a,size);
}

//void InsertSort_OP(int* a,int size)
//{
//	assert(a);
//
//	for(int i = 1; i<size; ++i)
//	{
//		int j = i-1;
//		int tmp = a[i];
//		int left = 0;
//		int right = i-1;
//		int k = left;
//		while(left<=right)
//		{
//			int mid = (left+right)/2;
//			if(a[mid] > tmp)
//			{
//				right = mid-1;
//				k = mid;
//			}
//			else if(a[mid] <= tmp)
//			{
//				left = mid+1;
//				k = mid+1;
//			}			
//		}
//
//		for(int m = i; m>k ;--m)
//		{
//			a[m] = a[m-1];
//		}
//
//		a[j+1] = tmp;
//	}
//}
//void TestInsertSortOP()
//{
//	int a[] = {2,5,4,9,3,6,8,7,1,0};
//	int size = sizeof(a)/sizeof(a[0]);
//
//	InsertSort_OP(a,size);
//	PrintArr(a,size);
//}
void ShellSort(int* a,size_t size)
{
	assert(a);
	int  gap = size;
	while(gap>1)
	{
		gap = gap/3+1;
		for(int i = gap; i<size; ++i)
		{
			int pos = i-gap;
			int tmp = a[i];
			while(pos>=0 && tmp<a[pos])
			{
				a[pos+gap] = a[pos];
				pos -= gap;
			}
			a[pos+gap] = tmp;
		}
	}
	
}
void TestShellSort()
{
	int a[] = {2,5,4,9,3,6,8,7,1,0};
	int size = sizeof(a)/sizeof(a[0]);

	ShellSort(a,size);
	PrintArr(a,size);
}

//选择排序
void SelectSort(int* a,int size)
{
	assert(a);
	for(int i = 0; i<size; ++i)
	{
		int tmp = a[i];
		int pos = i;
		for(int j = i; j<size; ++j)
		{
			if(tmp > a[j])
			{
				tmp = a[j];
				pos = j;
			}
		}

		swap(a[i],a[pos]);
	}
}
void TestSelectSort()
{
	int a[] = {2,5,4,9,3,6,8,7,1,0};
	int size = sizeof(a)/sizeof(a[0]);

	SelectSort(a,size);
	PrintArr(a,size);
}


void SelectSortOP(int* a,int size)
{
	assert(a);

	int left = 0;
	int right = size-1;
	for( ; left<=right; ++left,--right)
	{
		int min = left;
		int max = right;
		for(int j = left; j<=right; ++j)
		{
			if(a[j] <= a[min])
				min = j;
			else if(a[j] >= a[max])
				max = j;
		}

		if(max == left)
		{
			max = min;
		}
		swap(a[left],a[min]);
		swap(a[right],a[max]);
	}
}
void TestSelectSortOP()
{
	int a[] = {2,5,4,9,3,6,8,7,1,0};
	int size = sizeof(a)/sizeof(a[0]);

	SelectSortOP(a,size);
	PrintArr(a,size);
}

void _AdjustDown(int* a,int size,int parent)
{
	assert(a);

	int child = parent*2+1;
	while(child < size)
	{
		//选出左右孩子中最大的
		if((child+1)<size && a[child] < a[child+1])
		{
			++child;
		}

		if(a[parent] < a[child])
		{
			swap(a[parent],a[child]);
			parent = child;
			child = parent*2+1;
		}
		else
			break;
	}
}

void HeapSort(int* a,int size)
{
	assert(a);
	//建堆
	for(int i=(size-2)/2; i>=0; --i)
	{
		_AdjustDown(a,size,i);
	}

	for(int j = size-1; j>=0; --j)
	{
		swap(a[0],a[j]);
		_AdjustDown(a,j,0);
	}

}
void TestHeapSort()
{
	int a[] = {2,5,4,9,3,6,8,7,1,0};
	int size = sizeof(a)/sizeof(a[0]);

	HeapSort(a,size);
	PrintArr(a,size);
}

//交换排序
void BubbleSort(int* a,int size)
{
	assert(a);

	for(int i = 0; i<size; ++i)
	{
		for(int j = 0; j<size-i-1; ++j)
		{
			if(a[j] > a[j+1]);
			{
				swap(a[j],a[j+1]);
			}
		}
	}
}

void TestBubbleSort()
{
	int a[] = {2,5,4,9,3,6,8,7,1,0};
	int size = sizeof(a)/sizeof(a[0]);

	BubbleSort(a,size);
	PrintArr(a,size);
}

//int PartSort(int* a,int begin, int end,int key)
//{
//	int left = begin;
//	int right = end-1;
//
//	while(left <= right)
//	{
//		while(a[left] <= key)
//		{
//			++left;
//		}
//		while(a[right] >= key)
//		{
//			--right;
//		}
//
//		swap(a[left],a[right]);
//	}
//
//
//}
//
//void QuickSort(int* a,int size)
//{
//	assert(a);
//
//
//}