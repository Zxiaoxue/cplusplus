#define _CRT_SECURE_NO_WARNINGS 1


//一个数组实现两个栈 3
#include <iostream>
#include <assert.h>
using namespace std;

template<class T>
class DoubleStack2
{
public:
	DoubleStack2()
		:_array(NULL)
		, _capacity(0)
		, _top1(-2)
		, _top2(-1)
	{}

	DoubleStack2(const DoubleStack2& dstack)
	{
		_array = new T[dstack._capacity];
		_capacity = dstack._capacity;
		_top1 = dstack._top1;
		_top2 = dstack._yop2;
		int count = _top1 > _top2 ? _top1 : _top2;
		int index = 0;
		for (index = 0; index < count;++index)
		{
			_array[index] = dstack._array[index];
		}
	}

	~DoubleStack2()
	{
		if (_array)
		{
			delete[] _array;
			_array = NULL;
		}
	}
	void Push(int flag,T data)
	{
		if (flag != 1 && flag != 2)
		{
			return;
		}
		else
		{
			_CheckCapacity();
			if (flag == 1)
			{
				_top1 += 2;
				_array[_top1] = data;
			}
			else if (flag == 2)
			{
				_top2 += 2;
				_array[_top2] = data;
			}
		}
	}

	void Pop(int flag)
	{
		if (flag != 1 && flag != 2)
		{
			return;
		}
		else if (flag == 1)
		{
			if (_top1 == -2)
			{
				printf("the stack1 is empty!\n");
				return;
			}
			else
			{
				_top1 -= 2;
			}
		}
		else if (flag == 2)
		{
			if (_top2 == -2)
			{
				printf("the stack2 is empty!\n");
				return;
			}
			else
			{
				_top2 -= 2;
			}
		}

	}

	size_t Size(int flag)
	{
		//assert(flag != 1 && flag != 2);
		if (flag == 1)
		{
			return (_top1 / 2 + 1);
		}
		else
		{
			return (_top2 / 2 + 1);
		}
	}

	bool Empty(int flag)
	{
		if (flag != 1 && flag != 2)
		{
			return false;
		}
		else if (flag == 1)
		{
			if (_top1 == -2)
				return true;
		}
		else if (flag == 2)
		{
			if (_top2 == -1)
			{
				return true;
			}
		}
		return false;
	}

	T& Top(int flag)
	{
		//assert(flag != 1 && flag != 2);
		if (flag == 1)
		{
			return _array[_top1];
		}
		else if (flag == 2)
		{
			return _array[_top2];
		}
	}
protected:
	void _CheckCapacity()
	{
		int count = _top1 > _top2 ? _top1 : _top2;


		if (count < 0||_capacity == count)
		{
			size_t index = 0;
			_capacity = 2 * _capacity + 3;
			T* _tmp = new T[_capacity];
			if (_tmp && count>=0)
			{
				for (index = 0; index <= count; ++index)
				{
					_tmp[index] = _array[index];
				}
			}
			delete[] _array;
			_array = _tmp;
		}
		
	}
private:
	T* _array;
	T _capacity;
	T _top1;
	T _top2;
};

void Test()
{
	DoubleStack2<int> d;
	d.Push(1, 0);
	d.Push(1, 1);
	d.Push(1, 2);
	d.Push(1, 3);
	d.Push(1, 4);
	
	d.Push(2, 0);
	d.Push(2, 1);
	d.Push(2, 2);
	d.Push(2, 3);
	
	cout << d.Top(1) << endl;
	cout << d.Top(2) << endl;

	cout << d.Size(1) << endl;
	cout << d.Size(2) << endl;


	d.Pop(1);
	d.Pop(1);
	d.Pop(1);
	d.Pop(1);
	
	d.Pop(2);
	d.Pop(2);
	d.Pop(2);
	cout << d.Empty(1) <<endl;
	cout << d.Empty(2) << endl;


}


#define N 15
template<class T>
class DoubleStack
{
public:
	DoubleStack(size_t size = N)
		:_array(new T[N])
		, _capacity(N)
		, _top1(0)
		, _top2(N)
	{}

	DoubleStack(const DoubleStack& dstack)
	{
		_array = new T[dstack._capacity];
		_capacity = dstack._capacity;
		_top1 = dstack._top1;
		_top2 = dstack._top2;

		int count1 = 0;
		for (; count1 < _top1; ++count1)
		{
			_array[count1] = dstack._array[count1];
		}
		int count2 = _capacity - 1;
		for (count2 = _capacity - 1; count2>_top2; --count)
		{
			_array[count2] = dstack._array[count2];
		}

	}

	~DoubleStack()
	{
		if (_array)
		{
			delete[] _array;
			_array = NULL;
		}
	}

	void Push(int flag, const T data)
	{
		if (flag != 1 && flag != 2)
		{
			return;
		}
		if (flag == 1)
		{
			if (_top1 == _top2 - 1)
			{
				printf("the stack of one if full!\n");
				return;
			}
			else
			{
				_array[_top1++] = data;
			}
		}
		else if (flag == 2)
		{
			if (_top1 == _top2 - 1)
			{
				printf("the stack of two is full!\n");
				return;
			}
			else
			{
				_array[_top2--] = data;
			}
		}
	}


		void Pop(size_t flag)
		{
			if (flag != 1 && flag != 2)
			{
				return;
			}
			else
			{
				if (flag == 1)
				{
					--_top1;
				}
				else if (flag == 2)
				{
					++_top2;
				}
			}
		}

		size_t Size(size_t flag)
		{
			assert(flag != 1 && flag != 2);
			if (flag == 1)
			{
				return _top1;
			}
			else if (flag == 2)
			{
				return _capacity - _top2;
			}
		}
		size_t Top(size_t flag)
		{
			assert(flag != 1 && flag != 2);
			if (flag == 1)
				return _array[_top1];
			else if (flag == 2)
				return _array[_top2];
		}

		size_t Empty(size_t flag)
		{
			assert(flag != 1 && flag != 2);
			if (flag == 1)
				return _top1 == 0;
			else if (flag == 2)
				return _top2 == N;
		}

	private:
		T* _array;
		T _capacity;
		T _top1;
		T _top2;
	};

	void Test2()
	{
		DoubleStack<int> d;
		d.Push(1, 0);
		d.Push(1, 1);
		d.Push(1, 2);
		d.Push(1, 3);
		d.Push(1, 4);

		d.Push(2, 0);
		d.Push(2, 1);
		d.Push(2, 2);
		d.Push(2, 3);

		d.Pop(1);
		d.Pop(1);
		d.Pop(1);
		d.Pop(1);

		d.Pop(2);
		d.Pop(2);
		d.Pop(2);

	}

	int main()
	{
		Test();
		system("pause");
		return 0;
	}


//元素出栈入栈的合法性

//#include <iostream>
//#include <stack>
//#include <assert.h>
//using namespace std;
//
template<class T>
class IsLegality
{
public:
	bool Islegality(const T* str1, const T* str2,size_t size1,size_t size2)
	{
		assert(str1);
		assert(str2);
		if (size1 != size2)
		{
			return false;
		}
		/*size_t j = 0;
		for (size_t i = 0; i < size1; ++i)
		{
			s.push(str1[i]);
			if (s.top() == str2[j])
			{
				s.pop();
				j++;
				while (!s.empty() && s.top() == str2[j])
				{
					s.pop();
					j++;
				}
			}
		}
		while (!s.empty())
		{
			if (s.top() == str2[j])
			{
				s.pop();
				j++;
			}
			else
			{
				return false;
			}
			if (j == size1)
			{
				return true;
			}
			else
			{
				return false;
			}
		}*/
		while(*str1 != '\0'&&*str2 != '\0')
		{
			s.push(*str1++);
			if (s.top() != *str2)
			{
				s.push(*str1++);
			}
			while(!s.empty()&&s.top() == *str2)
			{
				s.pop();
				++str2;
			}
		}
		return s.empty() ? true : false;
	}
private:

	stack<T> s;
};


void Test3()
{
	char* str1 = "123456";
	char* str2 = "654321";

	IsLegality<char> i;
	cout << i.Islegality(str1,str2,7,7) << endl;

	//cout << Islegality(str1, str2) << endl;

}



////两个队列实现一个栈
//#include <iostream>
//#include <queue>
//using namespace std;
//
template<class T>
class Stack
{
public:
	void Push(const T& x)
	{
		qpush.push(x);
	}

	void Pop()
	{
		if (!qpush.empty())
		{
			while (qpush.size() > 1)
			{
				T tmp = qpush.front();
				qpop.push(tmp);
				qpush.pop();
			}

			qpush.pop();
			while (!qpop.empty())
			{
				T tmp = qpop.front();
				qpush.push(tmp);
				qpop.pop();
			}
		}
		else
		{
			qpop.pop();
		}
	}
protected:
	queue<T> qpush;
	queue<T> qpop;
};

void Test4()
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
	s1.Pop();
}


////两个栈实现一个队列
//#include <iostream>
//#include <stack>
//#include <queue>
//using namespace std;
//
template<class T>
class Queue
{
public:
	/*Queue()
		:spush(NULL)
		,spop(NULL)
	{}*/

	void Push(const T& x)
	{
		spush.push(x);
	}

	void Pop()
	{
		if (!spop.empty())
		{
			spop.pop();
		}
		else
		{
			while (spush.size() > 1)
			{
				T tmp = spush.top();
				spop.push(tmp);
				spush.pop();
			}
			spush.pop();

			while (!spop.empty())
			{
				T tmp = spop.top();
				spush.push(tmp);
				spop.pop();
			}
		}
	}

	size_t Size()
	{
		return spush.size();
	}

	bool Empty()
	{
		return spush.empty();
	}

protected:
	stack<T> spush;
	stack<T> spop;
};

void Test5()
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
}

//实现一个栈push,pop,min的时间复杂度都为O(1)
//#include <iostream>
//#include <stack>
//#include <assert.h>
//using namespace std;
//
typedef struct _stack
{
	int* _pElem;
	size_t _size;
	size_t _top;

	_stack(const int n)
		:_size(n)
	{
		_top = 0;
		_pElem = new int[n];
	}

	~_stack()
	{
		if (_pElem)
		{
			delete[] _pElem;
		}
	}
}_stack;

template<class T>
class Stack
{
public:
	Stack(int n)
		:s(n)
		,minstack(n)
	{}

	void Pop()
	{
		if (s._top == 0)
		{
			return;
		}

		int value = s._pElem[--s._top];
		--s._size;
		//判断将要出栈的是不是最小元素，
		if (value == minstack._pElem[minstack._top - 1])
		{
			--minstack._top;
			--minstack._size;
		}
	}

	void Push(const T value)
	{
		if (s._top == s._size)
		{
			return;
		}

		//如果当前最小元素栈为空或者要压入的元素小于等于当前最小元素 则压入
		//这里不需要担心最小栈溢出 因为前面已经判断并且top==0必须放在||前面 否则top==0时访问top-1会越界
		//注意这里必须是<=而不能是= 比如1 2 3 1 当1弹出时，最小元素仍然是1 因此minstack里面应该有两个1  
		if (minstack._top == 0 || value <= minstack._pElem[minstack._top - 1])
		{
			minstack._pElem[minstack._top++] = value;
		
		}
		s._pElem[s._top++] = value;
		

	}

	T& Min()
	{
		assert(minstack._size >= 0);
		return minstack._pElm[minstack._top];
	}
	
private:
	_stack s;
	_stack minstack;
};

void Test6()
{
	Stack<int> s(5);
	s.Push(9);
	s.Push(7);
	s.Push(10);
	s.Push(5);
	s.Push(8);

	s.Pop();
	s.Pop();
	s.Pop();
	s.Pop();
	s.Pop();
}
