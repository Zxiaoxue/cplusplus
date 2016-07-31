#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <assert.h>
using namespace std;

template<typename T>
struct Node
{
	T _data;
	Node<T>* _next;

	Node(const T& x)
		:_data(x)
		, _next(NULL)
	{}
};

template<typename T>
class Queue
{
public:
	Queue()
		:_head(NULL)
		, _tail(NULL)
		, _size(0)
	{}

	~Queue()
	{}


	void Push(const T& x)
	{
		if (_head == NULL)
		{
			_head = _tail = new Node<T>(x);
		}
		else
		{
			/*Node<T>* _tmp = new Node<T>*(x);
			_tail->_next = _tmp;
			_tail = _tmp;*/
			_tail->_next = new Node<T>(x);
			_tail = _tail->_next;
		}
		_size++;
	}

	void Pop()
	{
		assert(_head);
		if (_head == _tail)
		{
			delete _head;
			_head = _tail = NULL;
		}
		else
		{
			Node<T>* del = _head;
			_head = _head->_next;
			delete del;
		}
		--_size;
	}

	bool Empty()
	{
		/*return _size == 0;*/
		return _head == NULL;
	}

	size_t Size()
	{
		return _size;
	}
	
	T& Front()
	{
		assert(_head);
		return _head->_data;
	}
	
	T& Back()
	{
		assert(_tail);
		return _tail->_data;
	}


private:
	Node<T>* _head;
	Node<T>* _tail;
	size_t _size;
};

void Test()
{
	Queue<int> q1;
	q1.Push(0);
	q1.Push(1);
	q1.Push(2);
	q1.Push(3);
	q1.Push(4);
	q1.Push(5);

	q1.Pop();
	q1.Pop();
	q1.Pop();

	size_t front = q1.Front();
	size_t back = q1.Back();

	size_t size = q1.Size();

	cout << q1.Empty() << endl;
}

int main()
{
	Test();
	system("pause");
	return 0;
}
//
//#define _CRT_SECURE_NO_WARNINGS 1
//#include <iostream>
//#include <assert.h>
//using namespace std;
//
//template<typename T>
//class Queue
//{
//public:
//	Queue()
//		:_a(NULL)
//		, _size(0)
//		, _capacity(0)
//	{}
//	
//	~Queue()
//	{
//		if (_a)
//		{
//			delete[] _a;
//		}
//	}
//
//	void Push(const T& x)
//	{
//		_CheckCapacity();
//		_a[_size++] = x;
//	}
//
//	void Pop()
//	{
//		assert(_size != 0);
//		size_t i = 0;
//		for (i = 0; i < _size; i++)
//		{
//			_a[i] = _a[i + 1];
//		}
//		--_size;
//	}
//
//	bool Empty()
//	{
//		return _size == 0;
//	}
//
//	size_t Size()
//	{
//		return _size;
//	}
//
//	T& Front()
//	{
//		return _a[0];
//	}
//	T& Back()
//	{
//		return _a[_size-1];
//	}
//
//protected:
//	void _CheckCapacity()
//	{
//		if (_capacity <= _size)
//		{
//			_capacity = 3;
//			_a = new T[_capacity];
//		}
//		else
//		{
//			_capacity *= 2;
//			T* tmp = new T[_capacity];
//
//			for (size_t i = 0; i < _size; i++)
//			{
//				tmp[i] = _a[i];
//			}
//
//			delete[] _a;
//			_a = tmp;
//		}
//	}
//
//private:
//	T* _a;
//	size_t _size;
//	size_t _capacity;
//};
//
//void Test()
//{
//	Queue<int> q1;
//	q1.Push(0);
//	q1.Push(1);
//	q1.Push(2);
//	q1.Push(3);
//	q1.Push(4);
//	q1.Push(5);
//
//	q1.Pop();
//	q1.Pop();
//	q1.Pop();
//
//	size_t front = q1.Front();
//	size_t back = q1.Back();
//
//	size_t size = q1.Size();
//
//	cout << q1.Empty() << endl;
//}
//
//int main()
//{
//	Test();
//	system("pause");
//	return 0;
//}