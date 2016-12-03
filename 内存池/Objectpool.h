#pragma once

template<class T>
class ObjectPool
{
	struct BlockNode
	{
		void* _memory;		//�ڴ��
		size_t _objNum;		//�ڴ�������
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
		//1.����ʹ����ǰ�ͷŵĿռ�
		//2.�ڴ����������
		//3.�����µĽڵ����

		if(_lastDelete)
		{
			T* obj = _lastDelete;
			_lastDelete = *((T**)_lastDelete);
			return new(obj)T;
		}

		//2.�ڴ����������
		if(_countIn < last._objNum)
		{
			T* ptr = (T*)((char*)last._memory+_objNum*_itemSize);
			return ptr;
		}
	
		//3.�����½ڵ�
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
	size_t _countIn;			//��ǰ�ڵ����õĸ���
	BlockNode* _first;		//
	BlockNode* _last;			//
	size_t _maxNum;			//�ڵ������ڴ��������
	static size_t _itemSize;	//��������Ĵ�С
	T* _lastDelete;			//
};