#pragma once

template<class T>
class ObjectPool
{
	struct BlockNode
	{
		void* _memory;		//内存块
		size_t _objNum;		//内存对象个数
		BlockNode* _next;		//
		

		BlockNode(size_t objNum)
			:_objNum(objNum)
			,_next(NULL)
		{
			_memory = malloc(objNum*itemNum);
		}

		~BlockNode()
		{
			free _memory;
			_memory = NULL;
		}
	};

	size_t Init()
	{
		if(sizeof(T*) < sizeof(void*))
			return sizeof(void*);
		else
			return sizeof(T*);
	}

public:
	ObjectPool(size_t initNum = 32,size_t maxNum = 100000)
		:_countIn(0)
		,_maxNum(maxNum)
	{
		_first = _last = new BlockNode(initNum);
	}

	T* New()
	{
		//1.优先使用以前释放的空间
		//2.内存块里面申请
		//3.申请新的节点对象

		if(_lastDelete)
		{
			T* obj = _lastDelete;
			_lastDelete = *((T**)_lastDelete);
			return new(obj)T;
		}

		//2.内存块里面申请
		if(_countIn < last._objNum)
		{
			T* ptr = (T*)((char*)last._memory+_objNum*_itemSize);
			return ptr;
		}
	
		//3.申请新节点
		BlockNode* tmp = Allocate();

		return (T*)(tmp->_memory);
	}

	BlockNode* Allocate()
	{
		if(2*last._objNum >= maxNum)
			last._objNum = maxNum;

		BlockNode* tmp(last._objnum);
		last->_next = tmp;
		last = last->_net;
		_countIn = 0;
	}

	void Delete(T* ptr)
	{
		ptr->~T();
		if(ptr)
		{
			*(T**)ptr = _lastDelete;
			_lastDelete = ptr;
		}

		BlockNode* del = _first;
		while(del != _last)
		{
			_first = _first->_next;
			delete del;
			del = _first;
		}
	}

protected:
	size_t _countIn;			//当前节点在用的个数
	BlockNode* _first;		//
	BlockNode* _last;			//
	size_t _maxNum;			//节点申请内存块对象个数
	static size_t _itemSize;	//单个对象的大小
	T* _lastDelete;			//
};