#pragma once
#include <iostream>
#include <queue>
#include <stack>
using namespace std;
enum PointerTag
{
	THREAD,
	LINK
};

template<class T>
struct BinaryTreeNode_Thd
{
	T _data;
	BinaryTreeNode_Thd<T>* _left;
	BinaryTreeNode_Thd<T>* _right;
	PointerTag _leftTag;
	PointerTag _rightTag;

	BinaryTreeNode_Thd(const T& data)
		:_data(data)
		, _left(NULL)
		, _right(NULL)
		, _leftTag(LINK)
		, _rightTag(LINK)
	{}
};

template<class T>
class BinaryTree_Thd
{
	typedef  BinaryTreeNode_Thd<T> Node;
public:
	BinaryTree_Thd(T* array,size_t size,const T& invalid)
	{
		size_t index = 0;
		_root = _Create(array, size, invalid, index);
	}

	BinaryTree_Thd(const BinaryTree_Thd<T>& bt)
	{
		_root = _Copy(bt._root);
	}

	BinaryTree_Thd<T>& operator=(BinaryTree_Thd<T> bt)
	{
		swap(_root, bt._root);
		return *this;
	}

	~BinaryTree_Thd()
	{
		_Destory(_root);
		_root = NULL;
	}

	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}

	void PrevOrder()
	{
		_PrevOrder(_root);
		cout << endl;
	}

	void PostOrder()
	{
		_PostOrder(_root);
		cout << endl;
	}

	void LevelOrder()
	{
		queue<Node*> q;

		if (_root)
			q.push(_root);
		while (!q.empty())
		{
			Node* front = q.front();
			cout << front->_data << " ";
			q.pop();

			if (front->_left)
				q.push(front->_left);
			if (front->_right)
				q.push(front->_right);
		}

		cout << endl;
	}

	void PrevOrdre_NonR()
	{
		stack<Node*> s;
		if (_root)
			s.push(_root);
		while (!s.empty())
		{
			Node* top = s.top();
			cout << top._data << endl;

			if (top->_right)
				s.push(root->_right);
			if (top->_left)
				s.push(root->_left);
		}
		cout << endl;
	}

	void InOrder_NonR()
	{
		Node* cur = _root;
		stack<Node*> s;
		
		while (cur || !s.empty())
		{
			while (cur)
			{
				s.push(cur);
				cur = cur->_left;
			}
			if (!s.empty())
			{
				Node* top = s.top();
				s.pop();
				cout << top._data << " ";
				cur = top->_right;
			}

		}
		cut << endl;
	}

	void PostOrder_NonR()
	{
		Node* cur = _root;
		Node* prev = NULL;

		stack<Node*> s;

		while (cur || !s.empty())
		{
			while (cur)
			{
				s.push(cur);
				cur = cur->_left;
			}

			Node* top = s.top();

			if (top->_right == NULL||top->_right == prev)
			{
				cout << top->_data << " ";
				s.pop();
				prev = top;
			}
			else
			{
				cur = top->_right;
			}
		}
		cout << endl;
	}

	void InOrderThreading()
	{
		Node* prev = NULL;
		_InOrderThreading(_root, prev);
	}

	void PrevOrderThreading()
	{
		Node* prev = NULL;
		_PrevOrderThreading(_root, prev);
	}

	void InOrderThd()
	{
		Node* cur = _root;
		while (cur)
		{
			while (cur->_leftTag == THREAD)
			{
				cur = cur->_left;
			}

			cout << cur->_data << " ";

			while (cur->_rightTag == THREAD)
			{
				cur = cur->_right;
				cout << cur->_data << " ";
			}
			cur = cur->_right;
		}
		cout << endl;
	}

private:
	Node* _Create(T* array, size_t size, const T& invalid, size_t& index)
	{
		Node* root = NULL;
		if (index<size && array[index]!=invalid)
		{
			root = new Node(array[index]);
			root->_left = _Create(array, size, invalid, ++index);
			root->_right = _Create(array, size, invalid, ++index);
		}
		return root;
	}

	Node* _Copy(Node* root)
	{
		if (root == NULL)
			return NULL;
		Node* newRoot = new Node(root->_data);

		newRoot->_left = _Copy(root->_left);
		newRoot->_right = _Copy(root->_right);

		return newRoot;
	}

	void _Destory(Node* root)
	{
		if (root == NULL)
			return;
		_Destory(root->_left);
		_Destory(root->_right);

		delete root;
	}

	void _InOrder(Node* root)
	{
		if (root == NULL)
		{
			return;
		}
		_InOrder(root->_left);
		cout << root->_data << " ";
		_InOrder(root->_right);
	}

	void _PrevOrder(Node* root)
	{
		if (root == NULL)
		{
			return;
		}
		cout << root->_data << " ";
		_PrevOrder(root->_left);
		_PrevOrder(root->_right);
	}

	void _PostOrder(Node* root)
	{
		if (root == NULL)
		{
			return;
		}
		_PrevOrder(root->_left);
		_PostOrder(root->_right);
		cout << root->_data << " ";
	}

	void _InOrderThreading(Node* cur, Node*& prev)
	{
		if (cur == NULL)
			return;

		_InOrderThreading(cur->_left, prev);

		if (cur->_left == NULL)
		{
			cur->_leftTag = THREAD;
			cur->_left = prev;
		}

		if (prev && prev->_right == NULL)
		{
			prev->_rightTag = THREAD;
			prev->_right = cur;
		}

		prev = cur;

		_InOrderThreading(cur->_right, prev);
	}

	void _PrevOrderThreading(Node* cur, Node*& prev)
	{
		if (cur == NULL)
		{
			return;
		}

		if (cur->_left == NULL)
		{
			cur->_leftTag = THREAD;
			cur->_left = prev;
		}

		if (prev && prev->_right == NULL)
		{
			prev->_rightTag = THREAD;
			prev->_right = cur;
		}

		prev = cur;

		if (cur->_leftTag == LINK)
		{
			_PrevOrderThreading(cur->_left,prev)
		}
		if (cur->_right == LINK)
		{
			_PrevOrderThreading(cur->_left, prev);
		}

	}

	void _PostOrderThreading(Node* cur, Node*& prev)
	{
		if (cur == NULL)
			return;

		if (cur->_left == NULL)
		{
			cur->_leftTag = THREAD;
			cur->_left = prev;
		}	
		
		prev = cur;

		if (prev && prev->_right == NULL)
		{
			cur->_rightTag = THREAD;
			prev->_right = cur;
		}

	}
private:
	Node* _root;
};

void Test()
{
	int a1[10] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6 };
	int a2[15] = {1,2,'#',3,'#','#',4,5,'#',6,'#',7,'#','#',8};

	BinaryTree_Thd<int> bt(a1,10,'#');
	BinaryTree_Thd<int> bt2(a2,15,'#');

	/*bt.InOrder();
	bt2.InOrder();
	bt.PostOrder();
	bt2.PostOrder();
	bt.PrevOrder();
	bt2.PrevOrder();*/

	bt.InOrderThreading();
	bt.InOrderThd();

}