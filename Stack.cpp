//#define _CRT_SECURE_NO_WARNINGS 
//
//#include <iostream>
//#include <assert.h>
//using namespace std;
//
//
//template<typename T>
//class Stack
//{
//public:
//	Stack()
//		:_a(NULL)
//		, _top(0)
//		, _capacity(0)
//	{}
//
//	~Stack()
//	{
//		if (_a)
//		{
//			delete[] _a;
//		}
//	}
//
//public:
//
//	void _CheckCapacity()
//	{
//		if (_a == NULL)
//		{
//			_capacity = 3;
//			_a = new T[_capacity];
//			return;
//		}
//
//		if (_top == _capacity)
//		{
//			_capacity *= 2;
//			T* tmp = new T[_capacity];
//			for (size_t i = 0; i < _top; i++)
//			{
//				tmp[i] = _a[i];
//			}
//
//			delete[] _a;
//			_a = tmp;
//		}
//
//	}
//
//	void Push(const T& x)
//	{
//		_CheckCapacity();
//		_a[_top++] = x;
//	}
//
//	void Pop()
//	{
//		assert(_top > 0);
//		--_top;
//	}
//
//	size_t Size()
//	{
//		return _top;
//	}
//
//	bool Empty()
//	{
//		return _top == 0;
//	}
//
//	T& Top()
//	{
//		return _a[_top];
//	}
//
//
//	
//private:
//	T* _a;
//	size_t _top;
//	size_t _capacity;
//};



#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <assert.h>
using namespace std;

template<typename T>
struct Node
{
	Node(const T& x)
		:_data(x)
		,_next(NULL)
	{}

	T _data;
	Node<T>* _next;
};

template<typename T>
class Stack
{
public:
	Stack()
		:_top(NULL)
		,_base(NULL)
		,_size(0)
	{}

	~Stack()
	{}

	void Push(const T& x)
	{
		if (_top == NULL)
		{
			_top = new Node<T>(x);
			_base = _top;
		}
		else
		{
			
			_top->_next = new Node<T>(x);
			_top = _top->_next;
		}
		++_size;
	}

	void Pop()
	{
		assert(_top);
		
		Node<T>* cur = _base;
		
		while (cur->_next != _top)
		{
			if (cur == NULL)
			{
				printf("Stack is empty!\n");
				return;
			}
			cur = cur->_next;
		}

		delete _top;
		_top = cur;
		--_size;
	}

	T& Top()
	{
		return _top->_data;
	}
	bool Empty()
	{
		return _top == NULL;
	}
	size_t Size()
	{
		return _size;
	}


private:
	Node<T>* _top;
	Node<T>* _base;
	size_t _size;
};


void Test()
{
	Stack<int> s1;
	s1.Push(0);
	s1.Push(1);
	s1.Push(2);
	s1.Push(3);
	s1.Push(4);
	s1.Push(5);

	s1.Pop();
	s1.Pop();
	s1.Pop();

	int top = s1.Top();
	size_t size = s1.Size();
	cout << s1.Empty() << endl;


}

int main()
{
	Test();
	system("pause");
	return 0;
}