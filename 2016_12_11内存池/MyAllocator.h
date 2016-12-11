#pragma once

using namespace std;

#include <vector>
#include <stdarg.h>


// Trace 跟踪
// 

#define __DEBUG__

FILE* fOut = fopen("trace.log", "w");

static string GetFileName(const string& path)
{
	char ch = '/';

#ifdef _WIN32
	ch = '\\' ;
#endif

	size_t pos = path. rfind(ch );
	if (pos == string:: npos)
		return path ;
	else
		return path .substr( pos + 1);
}
// 用于调试追溯的trace log
inline static void __trace_debug (const char* function,
								  const char * filename, int line , char* format , ...)
{
	// 读取配置文件
#ifdef __DEBUG__
	// 输出调用函数的信息
	fprintf(stdout , "【 %s:%d】%s" , GetFileName (filename). c_str(), line , function);
	fprintf(fOut, "【 %s:%d】%s" , GetFileName (filename). c_str(), line , function);

	// 输出用户打的trace信息
	va_list args ;
	va_start (args , format);
	vfprintf (stdout , format, args);
	vfprintf (fOut , format, args);
	va_end (args );
#endif
}

#define __TRACE_DEBUG(...)  \
	__trace_debug(__FUNCTION__ , __FILE__, __LINE__, __VA_ARGS__);


template<int inst>
class MallocAlloc
{
	
public:

	typedef void(*ALLOC_HANDLER)();
	static ALLOC_HANDLER MallocAllocOomHandler;


	static void* OomMalloc(size_t n)
	{
		void* ret;
		while(1)
		{
			if(MallocAllocOomHandler == NULL)
				throw bad_alloc();

			//期望释放的
			(*MallocAllocOomHandler)();
			ret = malloc(n);
			if(ret)
				return ret;
		}
	}

	static void* Allocate(size_t n)
	{
		__TRACE_DEBUG("一级空间配置器申请%uBytes\n", n);

		void* result = malloc(n);
		if(0 == result)
			return OomMalloc(n);

		return result; 
	}

	static void Deallocate(void* ptr,size_t n)
	{
		__TRACE_DEBUG("一级空间配置器释放0x%p,%uBytes\n", ptr,n);

		free(ptr);
	}


protected:
	static ALLOC_HANDLER SetMallocHandle(ALLOC_HANDLER f)
	{
		ALLOC_HANDLER old = MallocAllocOomHandler;
		MallocAllocOomHandler = f;

		return old;
	}

};


template<int inst>
typename MallocAlloc<inst>::ALLOC_HANDLER
	MallocAlloc<inst>::MallocAllocOomHandler = 0;


//template<int inst>
//void* MallocAlloc<inst>::OomMalloc(size_t n)
//{
//	void (*MyAllocHandle)();
//	void *result;
//
//	for(;;)
//	{
//		MyAllocHandle = MallocAllocOomHandle;
//		if(0 == MyAllocHandle)
//		{
//			__THROW_BAD_ALLOC; 
//		}
//
//		(*MyAllocHandle)();
//
//		result = malloc(n);
//		if(result)
//			return result;
//	}
//}


template<bool thread,int inst>
class DefaultAlloc
{
	union obj		//自由链表--空闲链表
	{
		obj* _freeListLink;
		char _clientdata[1];
	};

	enum {_ALIGN = 8};
	enum {_MAXBYTES = 128};
	enum {_NFREELISTS = 16};

private:
	static char* _startfree;
	static char* _endfree;
	static size_t _heapsize;
	static obj*_freelist[_NFREELISTS];//自由链表 volatile防止编译器优化

public:

	static void* Allocate(size_t n)
	{
		obj* volatile * MyFreeList;
		//obj* result;
		__TRACE_DEBUG("二级空间配置器申请%uBytes\n", n);

		
		//大于128就调用一级配置器
		if(n>(size_t) _MAXBYTES)
		{
			return (MallocAlloc<0>::Allocate(n));
		}

		//寻找16个freelist中适合的一个
		int index = FREELIST_INDEX(n);
		obj* ret = NULL;

		if(_freelist[index])
		{
			__TRACE_DEBUG("在自由链表第%d个位置取内存块\n", index);

			ret = _freelist[index];
			_freelist[index]->_freeListLink = ret;
			return ret;
		}
		else
		{
			return ReFill(ROUND_UP(n));
		}



		//MyFreeList = _freelist+FREELIST_INDEX(n);
		//result = *MyFreeList;
		//if(result == 0)
		//{
		//	//没找到可用的freelist，准备重新填充freelist
		//	void* r = ReFill(ROUND_UP(n));
		//	return r;
		//}

		////调整freelist
		//*MyFreeList = result->_freeListLink;
		//return (result);
	}

	static void Deallocate(void* p,size_t n)
	{
		obj* q = (obj*)p;
		obj* volatile * MyFreeList;
		__TRACE_DEBUG("二级空间配置器释放0x%p,%uBytes\n", p, n);


		if(n > (size_t) _MAXBYTES)//如果大于128，就是大块内存，调用一级空间配置器
		{
			MallocAlloc<0>::Deallocate(p,n);
			return;
		}

		//MyFreeList = freelist + FREELIST_INDEX(n);

		////调整freelist，回收区块
		//q->_freeListLink = *MyFreeList;
		//*MyFreeList = q;

		//将用过的内存块回收连接到空闲队列中去
		int index = FREELIST_INDEX(n);
		obj* first = (obj*)p;

		first->_freeListLink = _freelist[index];
		_freelist[index] = first;
	}

	static size_t FREELIST_INDEX(size_t bytes)
	{
		return (((bytes)+_ALIGN-1)/_ALIGN-1);
	}

	static size_t ROUND_UP(size_t bytes)
	{
		return (((bytes)+_ALIGN-1) & ~(_ALIGN-1));
	}
	

	//返回一个大小为n的对象，并且有时候会为适当的freelist增加节点
	//假设n已经适当上调至8的倍数
	static void* ReFill(size_t n)
	{
		int nobjs = 20;
		//调用ChunkAlloc(),尝试取得nobjs个区块作为freelist的新节点

		char* chunk = ChunkAlloc(n,nobjs);
		obj* volatile * MyFreeList;
		//如何只获得一个区块，这个区块就分配给调用者，freelist无新节点

		if(1 == nobjs)
			return (obj*)chunk;

		__TRACE_DEBUG("将剩余的生存块挂到自由链表上:%d\n", nobjs-1);

		//否则准备调整freelist,纳入新节点
		obj* result;
		obj* cur, *next;
		int index = FREELIST_INDEX(n);

		_freelist[index] = cur = (obj*)(chunk+n);
		///MyFreeList = next = (obj*)(chunk+n);
		//以下将Freelist的各节点串联起来
	/*	for(i = 1; ; i++)
		{ 
			next = (obj*)((char*)next+n);
			if(nobjs-1 == i)
			{
				cur->_freeListLink = 0;
				break;
			}
			else
				cur->_freeListLink = next;
		}*/

		for(size_t i = 1; i<nobjs-2; i++)
		{
			next = (obj*)((char*)cur+n);

			cur->_freeListLink = next;
			cur = next;
		}

		cur->_freeListLink = NULL;

		return chunk;

		//return (result);
	}

	static char* ChunkAlloc(size_t size, int& nobjs)
	{
		char* result;
		size_t totalBytes = size*nobjs;
		size_t leftBytes = _startfree-_endfree;//内存池剩余空间

		__TRACE_DEBUG("内存池剩余%ubytes,需要申请%uBytes\n",
			leftBytes,totalBytes);


		if(leftBytes >= totalBytes)//剩余空间足够申请所用
		{
			__TRACE_DEBUG("内存有足够%u个对象大小内存\n", nobjs);

			result = _startfree;
			_startfree += totalBytes;
			return (result);
		}
		else if(leftBytes >= size)//剩余空间足够一个对象(size)大小
		{

			//内存池剩余空间不能完全满足需求量，但足够供应一个以上区块
			nobjs = leftBytes/size;
			__TRACE_DEBUG("内存只能够分配%u个对象大小内存\n", nobjs);

			totalBytes = size*nobjs;

			result = _startfree;
			_startfree += totalBytes;
			return result;
		}
		else						//内存池中剩余空间连一个区块大小都无法提供
		{
			//需要得到的空间
			size_t bytesToGet = 2*totalBytes + ROUND_UP(_heapsize>>4);

			//内存池中有剩下的空间，还有利用价值
			if(leftBytes)
			{
				__TRACE_DEBUG("将剩余的%uBytes小片内存挂到自由链表上\n", leftBytes);

				//内存池内还有剩下的空间，先配给适当的freelist
				//首先寻找适当的freelist
				//obj* volatile *MyFreeList =  = _freelist + FREELIST_INDEX(leftBytes);
				size_t index = FREELIST_INDEX(leftBytes);

				//调整_freelist，将内存池中的残余空间编入
				//头插
				/*((obj*)_startfree)->_freeListLink = *MyFreeList;
				*MyFreeList = (obj*)_startfree;*/

				((obj*)_startfree)->_freeListLink = _freelist[index];
				_freelist[index] = (obj*)_startfree;
			}


			//配置heap空间，用来补充内存池
			//开辟所需空间，给startfree
			_startfree = (char*)malloc(bytesToGet);
			if(0 == _startfree)
			{
				//malloc失败，开辟失败
				/*int i;
				obj* volatile * MyFreeList,*p;*/
		
				//for(i = size;i<=_MAXBYTES;i += _ALIGN)
				//{
				//	MyFreeList = _freelist + FREELIST_IDEX(i);
				//	p = *MyFreeList;
				//	if(0 != p)
				//	{
				//		*MyFreeList = p->_freeListLink;
				//		_startfree = (char*)p;
				//		_endfree = _startfree+i;
				//		//递归调用自己，为了修正nobjs
				//		return (ChunkAlloc(size,nobjs));
				//	}
				//}

				for(int i = size; i<_MAXBYTES; i+=_ALIGN)
				{

					int index = FREELIST_INDEX(i);
					if(_freelist[index])
					{
						__TRACE_DEBUG("到更大的自由链表上申请内存\n");

						_startfree = (char*)_freelist[index];
						_freelist[index] = ((obj*)_startfree)->_freeListLink;
						_endfree = _startfree+i;
						return (ChunkAlloc(size,nobjs));
					}
				}
				_endfree = 0;	//防止异常，很重要，没有有可能会崩溃
				_startfree = (char*)MallocAlloc<0>::Allocate(bytesToGet);

				
			}
			//malloc成功，调整_heapsize大小
			_heapsize += bytesToGet;
			_endfree = _startfree + bytesToGet;
			return (ChunkAlloc(size,nobjs));
		}

	}

	
};


template <bool threads, int inst>
typename DefaultAlloc<threads,inst>::obj*
DefaultAlloc<threads,inst>::_freelist[_NFREELISTS] = {0};

template<bool thread,int inst>
char* DefaultAlloc<thread,inst>::_startfree = 0;

template<bool thread,int inst>
char* DefaultAlloc<thread,inst>::_endfree = 0;

template<bool thread,int inst>
size_t DefaultAlloc<thread,inst>::_heapsize = 0;


#ifdef __USE_MALLOC
	typedef MallocAlloc<0> Alloc;
#else
	typedef DefaultAlloc<0,0> Alloc;

#endif //__USE_MALLOC


template<class T,class _Alloc = Alloc>
class SimpleAlloc
{
public:
	static T* Allocate(size_t n)
	{
		return 0==n ? (T*)Alloc::Allocate(n*sizeof(T));
	}


	static T* Allocate(void)
	{
		return (T*)Alloc::Allocate(sizeof(T));
	}

	static void Deallocate(T* p,size_t n)
	{
		if(0 != n)
			Alloc::Deallocate(p,n*sizeof(T));
	}
	static void Deallocate(T* p)
	{
		Alloc::Deallocate(p,sizeof(T));
	}
};


void Test1()
{
	vector<pair<void*, size_t>> v;
	v.push_back(make_pair(DefaultAlloc<false, 0>::Allocate(129), 129));

	for (size_t i = 0; i < 21; ++i)
	{
		v.push_back(make_pair(DefaultAlloc<false, 0>::Allocate(12), 12));
	}

	while(!v.empty())
	{
		DefaultAlloc<false, 0>::Deallocate(v.back().first, v.back().second);
		v.pop_back();
	}
	
	for (size_t i = 0; i < 21; ++i)
	{
		v.push_back(make_pair(DefaultAlloc<false, 0>::Allocate(7), 7));
	}

	for (size_t i = 0; i < 10; ++i)
	{
		v.push_back(make_pair(DefaultAlloc<false, 0>::Allocate(16), 16));
	}

	while(!v.empty())
	{
		DefaultAlloc<false, 0>::Deallocate(v.back().first, v.back().second);
		v.pop_back();
	}
}


