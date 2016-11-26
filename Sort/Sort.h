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

//快排---左右指针法
int PartSort1(int* a,int begin, int end)
{
	int left = begin;
	int right = end-1;
	//可采用三数取中法

	int key = a[end];

	while(left < right)
	{
		while(left<right && a[left] <= key)
		{
			++left;
		}
		while(left<right && a[right] >= key)
		{
			--right;
		}

		if(left < right)
			swap(a[left],a[right]);

		//处理两个数的情况
		if(a[left] < a[end])
			swap(a[left],a[end]);
	}

	swap(a[left],a[end]);

	return left;
}

//快排---挖坑法
int PartSort2(int*a,int begin,int end)
{
	assert(a);

	int left = begin;
	int right = end;
	//可采用三数取中法优化
	int key = a[end];

	while(left < right)
	{
		//从左往右找比key大的放到right位置上
		while(left < right && a[left] <= key)
		{
			++left;
		}

		if(left < right)
			a[right] = a[left];

		//从右往左找比key小的放到新的坑上
		while(left < right && a[right] >= key)
		{
			--right;
		}

		if(left < right)
			a[left] = a[right];
	}
	
	a[left] = key;

	return left;
}

//快排---前后指针法
int PartSort3(int* a,int begin,int end)
{
	assert(a);

	int prev = begin-1;
	int cur = begin;
	int key = a[end];

	if(begin < end)
	{
		while(cur < end)
		{
			if(a[cur] < key && ++prev!=cur)
			{
				swap(a[prev],a[cur]);
			}

			++cur;
		}

		swap(a[++prev],a[end]);
		return prev;
	}
	return -1;
}

#include <stack>
void QuickSortR(int* a,int begin,int end)
{
	if(begin < end)
	{
		stack<int> s;

		s.push(end);
		s.push(begin);

		while(!s.empty())
		{
			int left = s.top();
			s.pop();
			int right = s.top();
			s.pop();

			int div = PartSort3(a,left,right);

			if(left < div-1)
			{
				s.push(div-1);
				s.push(left);
			}
			if(right > div+1)
			{
				s.push(right);
				s.push(div+1);
			}
		}
	}
	
}

void QuickSort(int* a,int begin,int end)
{
	assert(a);

	if(begin >= end)
		return;

	//int div = PartSort1(a,begin,end);
	int div = PartSort2(a,begin,end);

	//QuickSort(a,begin,div-1);---PartSort2;
	QuickSort(a,begin,div-1);
	QuickSort(a,div+1,end);

}

void TestQuickSort()
{
	//int a[] = {2,5,4,9,3,6,8,7,1,0};
	int a[] = {2,0,4,9,3,6,8,7,1,5};
	int size = sizeof(a)/sizeof(a[0]);

	QuickSort(a,0,size-1);
	PrintArr(a,size);
}

void TestQuickSortR()
{
	//int a[] = {2,5,4,9,3,6,8,7,1,0};
	int a[] = {2,0,4,9,3,6,8,7,1,5};
	int size = sizeof(a)/sizeof(a[0]);

	QuickSortR(a,0,size-1);
	PrintArr(a,size);
}

void _merageArray(int* a,int begin,int mid,int end,int* tmp)
{
	int left = begin;
	int right = end;
	int j = mid+1;
	int k = mid;
	int m = left;

	//合并两个有序序列
	while(left <= k && j <= right)
	{
		if(a[left] < a[j])
			tmp[m++] = a[left++];
		else
			tmp[m++] = a[j++];
	}

	while(left <= k)
		tmp[m++] = a[left++];

	while(j <= right)
		tmp[m++] = a[j++];

	//再将tmp里的值赋给a
	for(int i = begin; i<=end;++i)
	{
		a[i] = tmp[i];
	}
}

//将两个有序序列合并
void _meragesort(int* a,int begin,int end,int* tmp)
{
	assert(a);

	if(begin < end)
	{
		int mid = (begin+end)/2;//防止溢出

		_meragesort(a,begin,mid,tmp);
		_meragesort(a,mid+1,end,tmp);

		_merageArray(a,begin,mid,end,tmp);
	}

}

void MerageSort(int* a,int begin,int end)
{
	assert(a);
	if(a == NULL)
		return;
	int size = end-begin;

	int* tmp = new int[size];
	_meragesort(a,begin,end,tmp);

	//delete[] tmp;放开会崩溃
}

void TestMerageSort()
{
	//int a[] = {2,5,4,9,3,6,8,7,1,0};
	int a[] = {2,0,4,9,3,6,8,7,1,5};
	int size = sizeof(a)/sizeof(a[0]);

	MerageSort(a,0,size-1);
	PrintArr(a,size);
}

//用hash表统计每个数出现的次数
void CountSort(int* a,int size)
{
	assert(a);
	int max = a[0];
	int min = a[0];
	for(int i = 0; i<size; ++i)
	{
		if(a[i]>max)
		{
			max = a[i];
		}
		
		if(a[i]<min)
		{
			min = a[i];
		}
	}
	int range = max-min+1;

	//统计每个数据出现的次数
	int* count = new int[range];
	memset(count,0,sizeof(int)*size);
	int index = 0;
	for(int i = 0; i<range;++i)
	{
		count[a[index++]]++;
	}
	 
	for(int i = 0; i<size; ++i)
	{
		while(count[i]--)
		{
			a[i++] = i+min;
		}
	}

	//delete count;
}

void TestCountSort()
{
	//int a[] = {2,5,4,9,3,6,8,7,1,0};
	int a[] = {2,0,4,9,3,6,8,7,1,5};
	int size = sizeof(a)/sizeof(a[0]);

	CountSort(a,size);
	PrintArr(a,size);
}

int _GetMaxDigit(int* a,int size)
{
	assert(a);
	int base = 10;
	int digit = 1;

	for(int i = 0; i<size; ++i)
	{
		while(a[i] >= base)
		{
			digit++;
			base *= 10;
		}
	}
	return digit;
}

//基数排序
void LSDSort(int* a,int size)
{
	assert(a);
	int* count = new int[10];
	int* tmp = new int[size];

	memset(tmp,0,sizeof(int)*size);

	int digit = _GetMaxDigit(a,size);
	int base = 1;
	while(digit--)
	{
		int num = 0;
		int index = 0;
		memset(count,0,sizeof(int)*10);//排完一次相应下标的索引就要把count数组清空，否则累加会出错

		//统计每个桶中数据个数,建立索引数组
		for(int i = 0; i<size; ++i)
		{
			num = (a[i]/base)%10;
			count[num]++;
		}

		//调整count数组，使count数组保存的是各个下标所对应的值的起始位置(索引位置)
		for(int i = 1; i<10; ++i)
		{
			count[i] += count[i-1];
		}

		//将每一次排序的结果放入tmp数组中
		for(int i = size-1; i>=0; --i)
		{
			index = (a[i]/base)%10;
			int j = --count[index];
			tmp[j] = a[i];
		}

		//将值拷回a数组
		for(int i = 0; i<size; ++i)
		{
			a[i] = tmp[i];
		}

		base *= 10;//控制位数，从个位开始到十位百位
	}

}

void TestLSDSort()
{
	//int a[] = {2,5,4,9,3,6,8,7,1,0};
	//int a[] = {2,0,41,92,3,6,8,711,1,5};
	int a[] = {81,22,73,93,43,14,55,65,28,39};
	int size = sizeof(a)/sizeof(a[0]);

	LSDSort(a,size);
	//cout<<"最大位数："<<_GetMaxDigit(a,size)<<endl;
	PrintArr(a,size);
}