#pragma once

template<T>
class Scopedptr
{
public:

	T* operator->()
	{
		return _ptr;
	}
	T& opeartor*()
	{
		return _ptr;
	}
protected:
	Scopedptr(Scopedptr<T>& sp);
	Scopedptr<T>& operator=(Scopedptr<T>& sp);
private:
	int* _ptr;
};

template <T>
class Autoptr
{
public:
	Autoptr(T* ap)
		:_ptr(new siseof(T))
	{
	}
	Autoptr(Autoptr<T>& ap)
		:_ptr(ap._ptr)
	{
		ap._ptr = NULL;
	}
	~Autoptr()
	{
		cout << "deleate" << endl;
	}
	Autoptr<T>& operator=(Autoptr<T>& ap)
	{
		if (this != &ap)
		{
			delete _ptr;
		}
	}
	T* operator->()
	{
		return _ptr;
	}
	T& operator*()
	{
		return _ptr;
	}
private:
	int* _ptr;
};



template<T>
class Sharedptr
{
public:
	Sharedptr(const sharedptr<T>& sp)
		:_ptr(sp._ptr)
		, _pCount(sp._pCount)
	{
		++(*_pCount);
	}
	Sharedptr<T>& operator=(const Sharedptr<T>& sp)
	{
		if (this != &sp)
		{
			if (--(*_pCount) == 0)
			{
				delete _ptr;
				delete _pCount;
			}
			_pCount = sp._pCount;
			_ptr = sp._ptr;
			++(*_pCount);
		}
		return *this;
	}
private:
	int* _ptr;
	int* _pCount;
};