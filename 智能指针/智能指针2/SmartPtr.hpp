#pragma once

#include <iostream>
using namespace std;

template<class T>
class AutoPtr
{
public:
	AutoPtr(T* ptr)
		:_ptr(ptr)
	{}

	AutoPtr(AutoPtr<T>& ap)
	{
		_ptr = ap._ptr;
		ap._ptr = NULL;
	}

	AutoPtr<T>& operator=(AutoPtr<T>& ap)
	{
		if (this != &ap)
		{
			delete _ptr;
			_ptr = ap._ptr;
			ap._ptr = NULL;
		}
		return *this;
	}

	~AutoPtr()
	{
		_Release();
	}

	T* operator->()
	{
		return _ptr;
	}

	T& operator*()
	{
		return *_ptr;
	}

	T* Get()
	{
		if (*this == NULL)
			return NULL;
		return _ptr;
	}

	bool operator==(const AutoPtr<T>& ap)
	{
		return _ptr == ap._ptr;
	}

	void Reset(T* p)
	{
		delete _ptr;
		_ptr = p;
	}

	void _Release()
	{
		delete _ptr;
	}

private:
	T* _ptr;
};

void Test1()
{
	AutoPtr<int> ap1(new int(1));
	AutoPtr<int> ap2(ap1);
	AutoPtr<int> ap3(new int(3));
	ap3 = ap2;
	cout << *ap3 << endl;

	cout<< ap1.Get() << endl;
	cout << ap2.Get() << endl;
	cout << ap3.Get() << endl;

	ap3.Reset(new int(5));
}


template<class T>
class ScopedPtr
{
public:
	ScopedPtr(T* ptr)
		:_ptr(ptr)
	{}

	~ScopedPtr()
	{
		return _Release();
	}

	T& operator*()
	{
		return *_ptr;
	}
	T* operator->()
	{
		return _ptr;
	}
	T* Get()
	{
		if (*this == NULL)
			return NULL;
		return *this;
	}

	bool operator==(ScopedPtr<T>& sp)
	{
		return _ptr == sp._ptr;
	}

	void _Release()
	{
		delete _ptr;
	}

	void Reset(T* p)
	{
		_ptr = p;
	}

protected:
	ScopedPtr(ScopedPtr<T>& ap);
	ScopedPtr& operator=(ScopedPtr<T>& sp);
private:
	T* _ptr;
};


void Test2()
{
	ScopedPtr<int> sp1(new int(1));
	ScopedPtr<int> sp2(new int(2));

}

template<class T>
class ScopedArray
{
public:
	ScopedArray(T* ptr)
		:_ptr(ptr)
	{}
	~ScopedArray()
	{
		delete[] _ptr;
	}
	T operator[](size_t index)
	{
		return _ptr[index];
	}
protected:
	ScopedArray(const ScopedArray<T>& sa);
	ScopedArray& operator=(const ScopedArray<T>& sa);
private:
	T* _ptr;
};

template<class T>
class SharedPtr
{
public:
	SharedPtr(T* ptr)
		:_ptr(ptr)
		,_pCount(new int(1))
	{}

	SharedPtr(const SharedPtr<T>& sp)
	{
		_ptr = sp._ptr;
		_pCount = sp._pCount;
		++(*_pCount);
	}
	/*SharedPtr<T>& operator=(SharedPtr<T>& sp)
	{
		if (this != &sp)
		{
			if (--*(_pCount) == 0)
			{
				delete _ptr;
			}
			
			_ptr = sp._ptr;
			_pCount = sp._pCount;
			++(*_pCount);
		}
		return *this;
	}*/
	SharedPtr<T>& operator=(SharedPtr<T> sp)
	{
		swap(_ptr, sp._ptr);
		swap(_pCount, sp._pCount);

		return *this;
	}

	
	~SharedPtr()
	{
		_Release();
	}

	T* Get()
	{
		if (*this == NULL)
			return NULL;
		return *this;
	}

	bool operator==(const SharedPtr<T>& sp)
	{
		return _ptr == sp._ptr;
	}

	T* operator->()
	{
		return _ptr;
	}

	T& operator*()
	{
		return *_ptr;
	}

	size_t UseCount()
	{
		return *_pCount;
	}

	void _Release()
	{
		if (--(*_pCount) == 0)
		{
			delete _ptr;
			delete _pCount;
		}
	}
private:
	T* _ptr;
	int* _pCount;
};

void Test3()
{
	SharedPtr<int> sp1(new int(1));
	SharedPtr<int> sp2(new int(2));
	SharedPtr<int> sp3(sp2);

	sp2 = sp1;
	cout << sp1.UseCount() << endl;
	cout << sp2.UseCount() << endl;
	cout << sp3.UseCount() << endl;


}