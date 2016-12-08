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
	union _obj		//��������--��������
	{
		_obj* _freeListLink;
		char _clientdata[1];
	}

private:
	static char* startfree;
	static char* endfree;
	static size_t _heapsize;
	static _obj* volatile _freelist[_NFREELISTS];//�������� volatile��ֹ�������Ż�

public:

	static void* Allocate(size_t n)
	{
		obj* volatile * MyFreeList;
		obj* result;
		
		//����128�͵���һ��������
		if(n>(size_t) _MAXBYTES)
		{
			return (MallocAlloc::Allocate(n));
		}

		//Ѱ��16��freelist���ʺϵ�һ��
		MyFreeList = _freelist+FREELIST_INDEX(n);
		result = *MyFreeList;
		if(result == 0)
		{
			//û�ҵ����õ�freelist��׼���������freelist
			void* r = ReFill(ROUND_UP(n));
			return r;
		}

		//����freelist
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

		//����freelist����������
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
	

	//����һ����СΪn�Ķ��󣬲�����ʱ���Ϊ�ʵ���freelist���ӽڵ�
	//����n�Ѿ��ʵ��ϵ���8�ı���
	void* ReFill(size_t n)
	{
		int nobjs = 20;
		//����ChunkAlloc(),����ȡ��nobjs��������Ϊfreelist���½ڵ�

		char* chunk = ChunkAlloc(n,nobjs);
		obj* volatile * MyFreeList;
		obj* result;
		obj* cur, *next;
		//���ֻ���һ�����飬�������ͷ���������ߣ�freelist���½ڵ�

		if(1 == nobjs)
			return (obj*)chunk;
		//����׼������freelist,�����½ڵ�
		MyFreeList = next = (obj*)(chunk+n);
		//���½�Freelist�ĸ��ڵ㴮������
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
