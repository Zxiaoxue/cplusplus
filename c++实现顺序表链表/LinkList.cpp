#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;

#define DataType int

struct Node
{
	friend ostream& operator<<(ostream& os, Node& n);
	DataType _data;
	Node* _next;
	Node(DataType x = 0)
		:_data(x)
		,_next(NULL)
	{}
};
ostream& operator<<(ostream& os, Node& n)
{
	os << n._data << " ";
	return os;
}
class LinkList
{
	friend ostream& operator<<(ostream& os, LinkList& l);
public:
	LinkList()
		:_head(NULL)
		,_tail(NULL)
	{}

	~LinkList()
	{
		if (_head != NULL)
		{
			while (_head != NULL)
			{
				Node* tmp = _head;
				_head = _head->_next;
				delete tmp;
			}
		}
	}

	void PushBack(DataType x)
	{
		if (_head == NULL)
		{
			Node* tmp = new Node(x);
			_head = tmp;
			_tail = tmp;
		}
		else
		{
			Node* tmp = new Node(x);
			_tail->_next = tmp;
			_tail = tmp;
		}
	}
	void PushFront(DataType x)
	{
		Node* tmp = new Node(x);

		if (_head == NULL)//空
		{
			_head = tmp;
		}
		else
		{
			tmp->_next = _head;
			_head = tmp;
		}
	}
	void PopFront()
	{
		if (_head == NULL)//空
		{
			return;
		}
		else if (_head->_next == NULL)//只有一个节点
		{
			delete _head;
			_head = NULL;
		}
		else
		{
			Node* del = _head;
			_head = _head->_next;
			delete del;
		}
	}
	void PopBack()
	{
		if (_head == NULL)//空链表
		{
			cout << "空链表" << endl;
			return;
		}
		else if (_head->_next == NULL)//只有一个节点
		{
			delete _head;
			_head = NULL;
		}
		else
		{
			Node* del = _tail;
			_tail = _head;
			while (_tail->_next != del)
			{
				_tail = _tail->_next;
			}
			_tail->_next = NULL;
			delete del;
			del = NULL;
		}
	}

	void Sort()
	{
		Node* cur = NULL;
		Node* prev = NULL;
		Node* tail = NULL;
		while (_head != tail)
		{
			prev = _head;
			cur = prev->_next;
			while (cur != tail)
			{
					if (cur->_data < prev->_data)
					{
						DataType tmp = cur->_data;
						cur->_data = prev->_data;
						prev->_data = tmp;
					}

					prev = cur;
					cur = cur->_next;

			}
			tail = prev;
		}
	}

	void Insert(int pos,DataType x)
	{
		Node* tmp = new Node(x);
		Node* cur = _head;
		Node* prev = cur;
		int m = pos;

		while (m-- && cur)
		{
			prev = cur;
			cur = cur->_next;
		}
		tmp->_next = cur;
		prev->_next = tmp;
	}

	void Erase(int pos)
	{
		int m = pos;
		Node* prev = _head;
		Node* cur = _head;
		while (--m && cur)
		{
			prev = cur;
			cur = cur->_next;
		}

		prev->_next = cur->_next;
		delete cur;
		cur = NULL;
	}

	void Remove(DataType x)
	{
		Node* prev = _head;
		Node* cur = _head;

		while (cur)
		{
			if (cur->_data == x)
			{
				prev->_next = cur->_next;
				delete cur;
				cur = NULL;
				return;
			}
			prev = prev->_next;
			cur = prev->_next;
		}
	}

	void RemoveAll(DataType x)
	{
		Node* prev = _head;
		Node* tmp = _head;
		Node* cur = _head->_next;

		while (cur)
		{
			while (cur->_data == x)
			{
				tmp = prev;
				prev->_next = cur->_next;
				delete cur;
				cur = NULL;
				prev = tmp;
				cur = prev->_next;
			}
			prev = prev->_next;
			cur = prev->_next;
		}
	}
	
private:
	Node* _head;
	Node* _tail;
};

ostream& operator<<(ostream& os, LinkList& l)
{
	Node* tmp = l._head;
	while (tmp)
	{
		os << *tmp << " ";
		tmp = tmp->_next;
	}
	return os;
}

void Test1()
{
	LinkList l;
	l.PushBack(0);
	l.PushBack(1);
	l.PushBack(2);
	l.PushBack(3);
	l.PushBack(4);
	l.PushBack(5);
	l.PushFront(1);
	l.PushFront(2);
	l.PushFront(3);
	l.PushFront(4);
	l.PushFront(5);
	l.PushFront(6);

	l.PopBack();
	l.PopBack();
	l.PopBack();
	l.PopBack();
	l.PopBack();
	l.PopBack();

	l.PopFront();


	cout << l << endl;
}

void Test2()
{
	LinkList l;
	l.PushBack(0);
	l.PushBack(6);
	l.PushBack(2);
	l.PushBack(7);
	l.PushBack(8);
	l.PushBack(3);
	l.PushFront(1);


	l.Sort();
	cout << l << endl;
	l.Insert(4, 4);
	l.Insert(5, 5);
	cout <<l << endl;

	l.Erase(7);
	cout << l << endl;
}

void Test3()
{
	LinkList l;
	l.PushBack(0);
	l.PushBack(1);
	l.PushBack(2);
	l.PushBack(3);
	l.PushBack(4);
	l.PushBack(5);
	l.PushFront(1);
	l.PushFront(2);
	l.PushFront(3);
	l.PushFront(4);
	l.PushFront(5);
	l.PushFront(6);
	l.PushFront(4);
	l.PushFront(4);


	l.Sort();
	cout << l << endl;

	l.Remove(4);
	cout << l << endl;
	l.RemoveAll(4);
	cout << l << endl;

}
int main()
{
	//Test1();
	//Test2();
	Test3();
	system("pause");
	return 0;
}