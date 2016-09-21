#pragma once
#include <iostream>
using namespace std;
#include <cstring>
#include "TypeTraits.h"

template<class T>
class VectorIterator
{
public:
	typedef T* Iterator;
	typedef const T* ConstIterator;
	VectorIterator()
		:_start(0)
		,_finish(0)
		,_endOfStorage(0)
	{}
	/*~Vector()
	{
		delete[] _start;
	}*/
	void PushBack(const T& x)
	{
		_CheckCapacity();
		new(_finish)T(x);

		//*(_finish) = x;
		++_finish;
	}
	void PopBack()
	{
		--_finish;
	}

	Iterator Begin()
	{
		return _start;
	}
	Iterator End()
	{
		return _finish;
	}

	ConstIterator Begin() const
	{
		return _start;
	}

	ConstIterator End() const
	{
		return _finish;
	}

	size_t Capacity()
	{
		return _endOfStorage-_start;
	}
	size_t Size()
	{
		return (size_t)(_finish-_start);
	}

	void _CheckCapacity()
	{
		if(_finish == _endOfStorage)
		{
			size_t size = Size();
			size_t capacity = 2*Capacity()+3;
			T* tmp = new T[capacity];

			Copy(_start,tmp,size,TypeTraits<T>::_IsPODType());

			/*for(size_t i = 0; i<size;++i)
			{
				tmp[i] = _start[i];
			}*/
			delete[] _start;
			_start = tmp;
			_finish = _start+size;
			_endOfStorage = _start+capacity;
		}
	}
	bool Empty()
	{
		return _start == _finish;
	}
	void Insert(Iterator pos,const T& x)
	{
		_CheckCapacity();
		size_t n = End() - pos;

		Iterator tmp = End();
		for(size_t i=0; i<n; ++i)
		{
			*(tmp-n) = *(tmp-n-1);
		}

		new(pos)T(x);
	}

	void Insert(Iterator pos,size_t n,const T& x)
	{
		_CheckCapacity();
		size_t count = End() - pos;

		Iterator tmp = End();
		_finish += n;
		for(size_t i=0; i<count; ++i)
		{
			*(tmp-i+n) = *(tmp-i);
		}

		for(size_t j=0; j<=n; ++j)
		{
			new(pos)T(x);
			++pos;
		}

	}


	void Display()
	{
		for(size_t i = 0;i<Size();++i)
		{
			cout<<_start[i]<<" ";
		}
		cout<<endl;
	}
private:
	Iterator _start;
	Iterator _finish;
	Iterator _endOfStorage;
};

template<class T>
void PrintVector(const VectorIterator<T>& v)
{
	VectorIterator<T>::ConstIterator it = v.Begin();
	while(it!=v.End())
	{
		cout<<*it<<" ";
		++it;
	}
	cout<<endl;
}

void TestVector()
{
	/*VectorIterator<int> v;

	v.PushBack(0);
	v.PushBack(1);
	v.PushBack(2);
	v.PushBack(3);
	v.PushBack(4);
	v.Insert(v.Begin(),3,0);*/

	/*PrintVector<int>(v);*/
	VectorIterator<string> v;

	v.PushBack("aaa");
	v.PushBack("bbb");
	v.PushBack("ccc");
	v.PushBack("ddd");
	v.PushBack("eee");
	v.Insert(v.Begin(),3,"ggg");

	//v.Display();

	/*PrintVector<string>(v);*/
}