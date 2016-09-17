#pragma once

template<class T>
class _Vector
{
public:
	typedef T* Iterator;
	typedef T& Reference;

	Vector()
		:_Start(0)
		,_Finish(0)
		,_EndOfStorage
	{}

	void PushBack(const T& x)
	{
		if (_Finish != _EndOfStorage)
		{

		}
	}
	Iterator Begin()
	{
		return _Start;
	}
	Iterator End()
	{
		return _Finsh;
	}
	size_t Size()
	{
		return(size_t)(End()-Begin());
	}
	size_t Capacity()
	{
		return (size_t)(_EndOfStorage - Begin());
	}
	bool Empty() const
	{
		return Begin() == End();
	}

	Reference operator[](size_t n)
	{
		return *(Begin() + n);
	}

	Reference Front()
	{
		return *Begin();
	}
	Reference Back()
	{
		return *(End() - 1);
	}
private:
	T* _arr;

};