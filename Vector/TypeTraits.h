#pragma once

struct __TrueType
{
	bool Get()
	{
		return true;
	}
};

struct __FalseType
{
	bool Get()
	{
		return false;
	}
};

template<class _Tp>
struct TypeTraits
{
	typedef __FalseType _IsPODType;
};

template<>
struct TypeTraits<bool>
{
	typedef __TrueType _IsPODType;
};

template<>
struct TypeTraits<int>
{
	typedef __TrueType _IsPODType;
};

template<>
struct TypeTraits<short>
{
	typedef __TrueType _IsPODType;
};

template<>
struct TypeTraits<unsigned short>
{
	typedef __TrueType _IsPODType;
};

template<>
struct TypeTraits<double>
{
	typedef __TrueType _IsPODType;
};

template<>
struct TypeTraits<long>
{
	typedef __TrueType _IsPODType;
};

template<>
struct TypeTraits<long double>
{
	typedef __TrueType _IsPODType;
};
template<class T>
void Copy(const T* src,T* dst,size_t size,__FalseType)
{
	cout<<"_FalseType:"<<typeid(T).name()<<endl;

	for(size_t i = 0;i<size;++i)
	{
		dst[i] = src[i];
	}
}

template<class T>
void Copy(const T* src,T* dst,size_t size,__TrueType)
{
	cout<<"__TrueType:"<<typeid(T).name()<<endl;
	memcpy(dst,src,size*sizeof(T));
}

//使用Get函数判断是否是POD类型
template<class T>
void Copy(const T* src,T* dst,size_t size)
{
	cout<<"__trueType:"<<typeid(T).name()<<endl;

	if(TypeTraits<T>::__IsPODType().Get())
	{
		memcpy(dst,src,size*sizeof(T));
	}
	else
	{
		for(size_t i = 0;i<size;++i)
		{
			dst[i] = src[i];
		}
	}
}