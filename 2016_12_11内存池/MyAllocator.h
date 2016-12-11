#pragma once

using namespace std;

#include <vector>
#include <stdarg.h>


// Trace ����
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
// ���ڵ���׷�ݵ�trace log
inline static void __trace_debug (const char* function,
								  const char * filename, int line , char* format , ...)
{
	// ��ȡ�����ļ�
#ifdef __DEBUG__
	// ������ú�������Ϣ
	fprintf(stdout , "�� %s:%d��%s" , GetFileName (filename). c_str(), line , function);
	fprintf(fOut, "�� %s:%d��%s" , GetFileName (filename). c_str(), line , function);

	// ����û����trace��Ϣ
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

			//�����ͷŵ�
			(*MallocAllocOomHandler)();
			ret = malloc(n);
			if(ret)
				return ret;
		}
	}

	static void* Allocate(size_t n)
	{
		__TRACE_DEBUG("һ���ռ�����������%uBytes\n", n);

		void* result = malloc(n);
		if(0 == result)
			return OomMalloc(n);

		return result; 
	}

	static void Deallocate(void* ptr,size_t n)
	{
		__TRACE_DEBUG("һ���ռ��������ͷ�0x%p,%uBytes\n", ptr,n);

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
	union obj		//��������--��������
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
	static obj*_freelist[_NFREELISTS];//�������� volatile��ֹ�������Ż�

public:

	static void* Allocate(size_t n)
	{
		obj* volatile * MyFreeList;
		//obj* result;
		__TRACE_DEBUG("�����ռ�����������%uBytes\n", n);

		
		//����128�͵���һ��������
		if(n>(size_t) _MAXBYTES)
		{
			return (MallocAlloc<0>::Allocate(n));
		}

		//Ѱ��16��freelist���ʺϵ�һ��
		int index = FREELIST_INDEX(n);
		obj* ret = NULL;

		if(_freelist[index])
		{
			__TRACE_DEBUG("�����������%d��λ��ȡ�ڴ��\n", index);

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
		//	//û�ҵ����õ�freelist��׼���������freelist
		//	void* r = ReFill(ROUND_UP(n));
		//	return r;
		//}

		////����freelist
		//*MyFreeList = result->_freeListLink;
		//return (result);
	}

	static void Deallocate(void* p,size_t n)
	{
		obj* q = (obj*)p;
		obj* volatile * MyFreeList;
		__TRACE_DEBUG("�����ռ��������ͷ�0x%p,%uBytes\n", p, n);


		if(n > (size_t) _MAXBYTES)//�������128�����Ǵ���ڴ棬����һ���ռ�������
		{
			MallocAlloc<0>::Deallocate(p,n);
			return;
		}

		//MyFreeList = freelist + FREELIST_INDEX(n);

		////����freelist����������
		//q->_freeListLink = *MyFreeList;
		//*MyFreeList = q;

		//���ù����ڴ��������ӵ����ж�����ȥ
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
	

	//����һ����СΪn�Ķ��󣬲�����ʱ���Ϊ�ʵ���freelist���ӽڵ�
	//����n�Ѿ��ʵ��ϵ���8�ı���
	static void* ReFill(size_t n)
	{
		int nobjs = 20;
		//����ChunkAlloc(),����ȡ��nobjs��������Ϊfreelist���½ڵ�

		char* chunk = ChunkAlloc(n,nobjs);
		obj* volatile * MyFreeList;
		//���ֻ���һ�����飬�������ͷ���������ߣ�freelist���½ڵ�

		if(1 == nobjs)
			return (obj*)chunk;

		__TRACE_DEBUG("��ʣ��������ҵ�����������:%d\n", nobjs-1);

		//����׼������freelist,�����½ڵ�
		obj* result;
		obj* cur, *next;
		int index = FREELIST_INDEX(n);

		_freelist[index] = cur = (obj*)(chunk+n);
		///MyFreeList = next = (obj*)(chunk+n);
		//���½�Freelist�ĸ��ڵ㴮������
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
		size_t leftBytes = _startfree-_endfree;//�ڴ��ʣ��ռ�

		__TRACE_DEBUG("�ڴ��ʣ��%ubytes,��Ҫ����%uBytes\n",
			leftBytes,totalBytes);


		if(leftBytes >= totalBytes)//ʣ��ռ��㹻��������
		{
			__TRACE_DEBUG("�ڴ����㹻%u�������С�ڴ�\n", nobjs);

			result = _startfree;
			_startfree += totalBytes;
			return (result);
		}
		else if(leftBytes >= size)//ʣ��ռ��㹻һ������(size)��С
		{

			//�ڴ��ʣ��ռ䲻����ȫ���������������㹻��Ӧһ����������
			nobjs = leftBytes/size;
			__TRACE_DEBUG("�ڴ�ֻ�ܹ�����%u�������С�ڴ�\n", nobjs);

			totalBytes = size*nobjs;

			result = _startfree;
			_startfree += totalBytes;
			return result;
		}
		else						//�ڴ����ʣ��ռ���һ�������С���޷��ṩ
		{
			//��Ҫ�õ��Ŀռ�
			size_t bytesToGet = 2*totalBytes + ROUND_UP(_heapsize>>4);

			//�ڴ������ʣ�µĿռ䣬�������ü�ֵ
			if(leftBytes)
			{
				__TRACE_DEBUG("��ʣ���%uBytesСƬ�ڴ�ҵ�����������\n", leftBytes);

				//�ڴ���ڻ���ʣ�µĿռ䣬������ʵ���freelist
				//����Ѱ���ʵ���freelist
				//obj* volatile *MyFreeList =  = _freelist + FREELIST_INDEX(leftBytes);
				size_t index = FREELIST_INDEX(leftBytes);

				//����_freelist�����ڴ���еĲ���ռ����
				//ͷ��
				/*((obj*)_startfree)->_freeListLink = *MyFreeList;
				*MyFreeList = (obj*)_startfree;*/

				((obj*)_startfree)->_freeListLink = _freelist[index];
				_freelist[index] = (obj*)_startfree;
			}


			//����heap�ռ䣬���������ڴ��
			//��������ռ䣬��startfree
			_startfree = (char*)malloc(bytesToGet);
			if(0 == _startfree)
			{
				//mallocʧ�ܣ�����ʧ��
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
				//		//�ݹ�����Լ���Ϊ������nobjs
				//		return (ChunkAlloc(size,nobjs));
				//	}
				//}

				for(int i = size; i<_MAXBYTES; i+=_ALIGN)
				{

					int index = FREELIST_INDEX(i);
					if(_freelist[index])
					{
						__TRACE_DEBUG("����������������������ڴ�\n");

						_startfree = (char*)_freelist[index];
						_freelist[index] = ((obj*)_startfree)->_freeListLink;
						_endfree = _startfree+i;
						return (ChunkAlloc(size,nobjs));
					}
				}
				_endfree = 0;	//��ֹ�쳣������Ҫ��û���п��ܻ����
				_startfree = (char*)MallocAlloc<0>::Allocate(bytesToGet);

				
			}
			//malloc�ɹ�������_heapsize��С
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


