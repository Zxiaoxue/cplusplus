#pragma once
#include <cassert>

#include <vector>

template<class T>
struct Less
{
	bool operator()(const T& l,const T& r)
	{
		return l < r;
	}
};

template<class T>
struct Greater
{
	bool operator()(const T& l,const T& r)
	{
		return l > r;
	}
};

template<class T,class Compear = Greater<T>>
class Heap
{
public:
	Heap()
	{}

	Heap(const T* a,size_t size)
	{
		for(int i = 0; i<size; ++i)
		{
			_root.push_back(a[i]);
		}

		for(int i =( _root.size()-2)/2; i>=0; --i)
		{
			_AdjustDown(i);
		}
		
	}

	void Push(const T& x)
	{
		_root.push_back(x);
		_AdjustUp(_root.size()-1);//向上调整
	}

	void Pop()
	{
		assert(_root.size() > 0);
		swap(_root[0],_root[_root.size()-1]);
		_root.pop_back();

		_AdjustUp(0);
	}

	const T& Top()
	{
		assert(_root.size() > 0);
		return _root[0];
	}

	bool Empty()
	{
		return _root.empty();

	}

	size_t Size()
	{
		return _root.size();
	}

	void Print()
	{
		for(int i = 0; i<Size(); ++i)
		{
			cout<<_root[i]<<" ";
		}

		cout<<endl;
	}

protected:
	void _AdjustDown(int root)//从根向下调整
	{
		int child = root*2 + 1;

		Compear com;
		while(child < _root.size())
		{
			//找出左右孩子中较大的那个
			//if((child+1<_root.size())&&(_root[child] < _root[child+1]))
			if((child+1<_root.size())&&
				com(_root[child+1],_root[child]))
			{
				++child;
			}

			//if(_root[child] > _root[root])
			if(com(_root[child],_root[root]))
			{
				swap(_root[child],_root[root]);
				root = child;
				child = root*2 + 1;
			}
			else
				break;
		}

	}

	void _AdjustUp(int child)
	{
		while(child > 0)
		{
			int parent = (child-1)/2;
			Compear com;

			//if(_root[child] > _root[parent])
			if(com(_root[child],_root[parent]))
			{
				swap(_root[child],_root[parent]);
				child = parent;
			}
			else
				break;
		}

	}
protected:
	vector<T> _root;
};

template<class T>
void _AdjustDown(T* a,size_t root,size_t size)
{
	size_t child = root*2+1;

	while(child < size)//小堆
	{
		//选出左右孩子中较小的那个
		if((a[child+1] < a[child]) && (child+1 < size))
		{
			++child;
		}
		
		if(a[child] < a[root])
		{
			swap(a[child],a[root]);
			root = child;
			child = root*2+1;
		}
		else
		{
			break;
		}
	}
}

template<class T>
void HeapSort(T* a,size_t size)
{
	assert(a);
	
	//建堆
	for(int i = (size-2)/2; i >= 0; --i)
	{
		_AdjustDown(a,i,size);
	}

	size_t End = size-1;
	while(End > 0)
	{	
		
		swap(a[0],a[End]);
		_AdjustDown(a,0,End);
	
		End--;
	}
	
}


//堆实现优先级队列
template<class T>
class PriorityQueue
{
public:
	PriorityQueue()
	{}

	PriorityQueue(T* a,size_t size)
		:_heap(a,size)
	{}

	void Push(const T& x)
	{
		_heap.Push(x);
	}

	void Pop()
	{
		_heap.Pop();
	}

	void Empty()
	{
		_heap.Empty();
	}

	size_t Size()
	{
		return _heap.Size();
	}

	const T& Top() const
	{
		return _heap.Top();
	}

	void Print()
	{
		_heap.Print();
	}

protected:
	Heap<T> _heap;
};



//N个数中最大的前k个数

template<class T>
void AdjustDown(T* a,size_t root,int k)
{
	size_t child = root*2+1;

	while(child < k)
	{
		//建小堆
		if(a[child+1] < a[child] && child+1 < k)
		{
			++child;
		}

		if(a[child] < a[root])
		{
			swap(a[child],a[root]);
			root= child;
			child = root*2+1;
		}
		else
			break;
	}
}

template<class T>
void GetKNum(T* a,T* max,int k,int n)
{
	assert(k < n);

	for(int i = 0; i<k; ++i)
	{
		max[i] = a[i];
	}

	for(int j = (k-2)/2; j>=0; --j)
	{
		AdjustDown(a,j,k);
	}

	for(int m = k; m<n; ++m)
	{
		if(a[m] > max[0])
		{
			swap(a[m],max[0]);
			AdjustDown(max,0,k);
		}
	}
}


void Test()
{
	int arr[] = {10,16,18,12,11,13,15,17,14,19};
	size_t size = sizeof(arr)/sizeof(arr[0]);

	Heap<int> h(arr,size);

}

template<class T>
void Print(T* a,size_t size)
{
	for(int i = 0; i<size; ++i)
	{
		cout<<a[i]<<" ";
	}

	cout<<endl;
}

void Test1()
{
	int arr[] = {10,16,18,12,11,13,15,17,14,19};
	size_t size = sizeof(arr)/sizeof(arr[0]);

	HeapSort<int>(arr,size);
	Print<int>(arr,size);
}

void Test2()
{
	int arr[] = {10,16,18,12,11,13,15,17,14,19};
	size_t size = sizeof(arr)/sizeof(arr[0]);

	PriorityQueue<int> pq(arr,size);

	pq.Print();
	pq.Push(9);
	pq.Print();
	pq.Push(20);
	pq.Print();

	pq.Pop();
	pq.Print();
}

#define n 1000
#define k 20
void Test3()
{
	int arr[n] = {0};
	int max[k] = {0};

	for(size_t i = 0; i<n; ++i)
	{
		arr[i] = i;
	}

	GetKNum<int>(arr,max,k,n);

	Print<int>(max,k);
}