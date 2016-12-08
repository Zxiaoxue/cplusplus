#pragma once

template<class T>
class MallocAlloc
{
public:
	typedef PF void(*f)();

private:
	static void *OomMalloc(size_t);
	static void (* MallocAllocOomHandler)();
public:

	static void* Allocate(size_t n)
	{
		void* result = malloc(n);
		if(0 == result)
			return OomMalloc(n);

		return result; 
	}

	void Deallocate(void* ptr,size_t n)
	{
		free(ptr);
	}


protected:
	static PF SetMallocHandle(PF f)
	{
		PF old = MallocAllocOomHandler;
		MallocAllocOomHandler = f;

		return old;
	}

};

template<int inst>
void (*MallocAlloc<inst>::OomMalloc)() = 0;

template<int inst>
void (*MallocAlloc<inst>::MallocAllocOomHandle)() = 0;


template<int inst>
void* MallocAlloc<inst>::OomMalloc(size_t n)
{
	void (*MyAllocHandle)();
	void *result;

	for(;;)
	{
		MyAllocHandle = MallocAllocOomHandle;
		if(0 == MyAllocHandle)
		{
			__THROW_BAD_ALLOC; 
		}

		(*MyAllocHandle)();

		result = malloc(n);
		if(result)
			return result;
	}
}


enum { _ALIGN = 8 };
enum { _MAXBYTES = 128 };
enum { _NFREELISTS = 6 };

template<bool thread,int inst>_NFREELISTS
class DefaultAlloc
{
	union _obj		//自由链表--空闲链表
	{
		_obj* _freeListLink;
		char _clientdata[1];
	}

private:
	static char* startfree;
	static char* endfree;
	static size_t _heapsize;
	static _obj* volatile _freelist[_NFREELISTS];//自由链表 volatile防止编译器优化

public:

	static void* Allocate(size_t n)
	{
		obj* volatile * MyFreeList;
		obj* result;
		
		//大于128就调用一级配置器
		if(n>(size_t) _MAXBYTES)
		{
			return (MallocAlloc::Allocate(n));
		}

		//寻找16个freelist中适合的一个
		MyFreeList = _freelist+FREELIST_INDEX(n);
		result = *MyFreeList;
		if(result == 0)
		{
			//没找到可用的freelist，准备重新填充freelist
			void* r = ReFill(ROUND_UP(n));
			return r;
		}

		//调整freelist
		*MyFreeList = result->_freeListLink;
		return (result);
	}

	static void* Deallocate(void* p,size_t n)
	{
		obj* q = (obj*)p;
		obj* volatile * MyFreeList;

		if(n > (size_t) _MAXBYTES)
		{
			MallocAlloc::Deallocate(p,n);
			return;
		}

		MyFreeList = freelist + FREELIST_INDEX(n);

		//调整freelist，回收区块
		q->_freeListLink = *MyFreeList;
		*MyFreeList = q;
	}

	static size_t FREELIST_INDEX(size_t bytes)
	{
		return (((bytes)+_ALIGN-1)/_ALIGN-1);
	}

	static size_t ROUNT_UP(size_t bytes)
	{
		return (((bytes)+_ALIGN-1) & ~(_ALGIN-1));
	}
	

	//返回一个大小为n的对象，并且有时候会为适当的freelist增加节点
	//假设n已经适当上调至8的倍数
	void* ReFill(size_t n)
	{
		int nobjs = 20;
		//调用ChunkAlloc(),尝试取得nobjs个区块作为freelist的新节点

		char* chunk = ChunkAlloc(n,nobjs);
		obj* volatile * MyFreeList;
		obj* result;
		obj* cur, *next;
		//如何只获得一个区块，这个区块就分配给调用者，freelist无新节点

		if(1 == nobjs)
			return (obj*)chunk;
		//否则准备调整freelist,纳入新节点
		MyFreeList = next = (obj*)(chunk+n);
		//以下将Freelist的各节点串联起来
		for(i = 1; ; i++)
		{
			cur = next;
			next = (obj*)((char*)next+n);
			if(nobjs-1 == i)
			{
				cur->_freeListLink = 0;
				break;
			}
			else
				cur->_freeListLink = next;
		}

		return (result);
	}

	
};

template<bool thread,int inst>
char* DefaultAlloc<thread,inst>::startfree = 0;

template<bool thread,int inst>
char* DefaultAlloc<thread,inst>::endfree = 0;

template<bool thread,int inst>
size_t DeafultAlloc<thread,inst>::_heapsize = 0;

template<bool thread,int inst>
DeadultAlloc<thread,inst>::_obj* volatile 
DeafultAlloc<thread,inst>::freelist[_NFREELISTS] = 
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
