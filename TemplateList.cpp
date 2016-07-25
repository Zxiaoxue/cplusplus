#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;

template<typename T>
struct ListNode
{
	T _data;
	ListNode<T>* _next;
	ListNode<T>* _prev;
	ListNode(const T& x)
		:_data(x)
		,_next(NULL)
		,_prev(NULL)
	{}
};

template<typename T>
class List
{
public:
	List()
		:_head(NULL)
		, _tail(NULL)
	{}

	void PushBack(const T& x)
	{
		if (_head == NULL)
		{
			_tail = _head = new ListNode<T>(x);
		}
		else
		{
			ListNode<T>* tmp = new ListNode<T>(x);
			_tail->_next = tmp;
			tmp->_prev = _tail;
			_tail = tmp;
		}
	}

	void PopBack()
	{
		_tail = _tail->_prev;
		_tail->_next = NULL;
	}

	void Unique()//去重
	{
		if (_head == NULL || _head->_next == NULL)
			return;
		ListNode<T>* slow = _head;
		ListNode<T>* fast = _head->_next;

		while (fast)
		{

			if (fast->_data == slow->_data)
			{
				fast = fast->_next;
				slow->_next = fast;
			}
			else
			{
				slow = slow->_next;
				fast = fast->_next;
			}

		}
	}

	void Print()
	{
		ListNode<T>* cur = _head;
		while (cur)
		{
			cout << cur->_data << " ";
			cur = cur->_next;
		}
	}


	void Merage(List<T> l)//合并
	{
		if (_head == NULL || l._head == NULL)
			return;

		ListNode<T>* cur1 = _head;
		ListNode<T>* cur2 = l._head;

		ListNode<T>* newhead = _head;
		if (l._head->_data < _head->_data)
			newhead = l._head;
		ListNode<T>* newtail = newhead;
		while (cur1&&cur2)
		{
			
			if (cur1->_data < cur2->_data)
			{
				ListNode<T>* tmp = cur1;
				cur1 = cur1->_next;
				newtail->_next = tmp;
				tmp->_prev = newtail;
				newtail = tmp;
			}
			else
			{
				ListNode<T>* tmp = cur2;
				cur2 = cur2->_next;
				newtail->_next = tmp;
				tmp->_prev = newtail;
				newtail = tmp;
			}
		}
		if (cur1)
		{
			newtail->_next = cur1;
			cur1->_prev = newtail;
		}
		if (cur2)
		{
			newtail->_next = cur2;
			cur2->_prev = newtail;
		}
	}

	void Reverse()//逆置
	{
		ListNode<T>* cur = _tail;
		while (cur != _head)
		{

			if (cur == _tail)
			{
				cur->_next = _tail->_prev;
				cur->_prev = NULL;
			}
			else
			{
				ListNode<T>* prev = cur->_prev;
				ListNode<T>* next = cur->_next;

				cur->_next = prev;
				cur->_prev = next;

			}
			cur = cur->_next;


		}
		cur->_next = NULL;
		cur->_prev = _head->_next;

		cur = _tail;
		_tail = _head;
		_head = cur;
	}
	void Sort()
	{
		ListNode<T>* cur = _head;
		ListNode<T>* next = cur->_next;
		ListNode<T>* tail = _tail;

		while (tail != _head)
		{
			cur = _head;
			next = cur->_next;
			while (cur!=tail)
			{
				if (cur->_data > next->_data)
				{
					T tmp = cur->_data;
					cur->_data = next->_data;
					next->_data = tmp;
				}
				cur = cur->_next;
				next = next->_next;
			}
			tail = tail->_prev;
		}
	}
	
protected:
	ListNode<T>* _head;
	ListNode<T>* _tail;
};

void Test()
{
	List<int> l;
	l.PushBack(1);
	l.PushBack(3);
	l.PushBack(5);
	l.PushBack(7);
	l.PushBack(9);
	l.PushBack(9);
	l.PushBack(9);


	List<int> l1;
	l1.PushBack(0);
	l1.PushBack(2);
	l1.PushBack(4);
	l1.PushBack(6);
	l1.PushBack(8);


	l.Merage(l1);//合并


	//l.PopBack();
	l.Print();

}

void Test1()
{
	List<int> l;
	l.PushBack(1);
	l.PushBack(3);
	l.PushBack(5);
	l.PushBack(7);
	l.PushBack(9);
	l.PushBack(9);
	l.PushBack(9);

	l.Reverse();//逆置

	l.Print();


}

void Test2()
{
	List<int> l;
	l.PushBack(7);
	l.PushBack(6);
	l.PushBack(4);
	l.PushBack(2);
	l.PushBack(1);
	l.PushBack(3);
	l.PushBack(5);
	l.PushBack(9);
	l.PushBack(8);
	l.PushBack(0);


	l.Sort();
	l.Print();
}


void Test3()
{
	List<int> l;
	l.PushBack(1);
	l.PushBack(3);
	l.PushBack(3);
	l.PushBack(3);
	l.PushBack(5);
	l.PushBack(7);
	l.PushBack(9);
	l.PushBack(9);
	l.PushBack(9);

	l.Unique();//去重

	l.Print();

}

int main()
{
	//Test();
	//Test1();
	//Test2();
	Test3();

	system("pause");
	return 0;
}