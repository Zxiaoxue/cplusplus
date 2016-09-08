
#pragma once
#include <iostream>
#include <stack>
using namespace std;

template<class T>
struct BinaryTreeNode
{
	BinaryTreeNode(const T& data)
	:_left(NULL)
	,_right(NULL)
	,_data(data)
	{}

	BinaryTreeNode<T>* _left;
	BinaryTreeNode<T>* _right;
	T _data;
};

template <class T>
class BinaryTree
{
	typedef BinaryTreeNode<T> Node;
public:
	BinaryTree(int* a,size_t size,const T& invalid)
	{
		size_t i = 0;
		_root = _Create(a, size, i,invalid);
	}
	BinaryTree(const BinaryTree<T>& bt)
	{
		cout << "BinaryTree(const BinaryTree<T>& bt)" << endl;
		_root = _Copy(bt._root);
	}
	BinaryTree<T>& operator=(BinaryTree<T> bt)
	{
		cout << "BinaryTree<T>& operator=(BinaryTree<T> bt)" << endl;
		swap(_root, bt._root);
		return *this;
	}
	~BinaryTree()
	{
		cout << "~BinaryTree()" << endl;
		_Distory(_root);
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

	int Height()
	{
		return _Height(_root);
	}

	size_t Size()
	{
		return _Size(_root);
	}

	size_t LeafSize()
	{
		return _LeafSize(_root);
	}

	size_t GetkLevel(size_t k)
	{
		return _GetkLevel(root, k);
	}
	void PostOrder_NonR()
	{
		Node* cur = _root;
		Node* prev = NULL;
		stack<Node*> s;

		while (cur||!s.empty())
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

private:
	Node* _Create(int* a, size_t size, size_t& i,const T& invalid)
	{
		Node* root = NULL;
		if (a[i] != invalid && i < size)
		{
			root = new Node(a[i]);
			root->_left = _Create(a, size, ++i,'#');
			root->_right = _Create(a, size, ++i,'#');
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

	void _Distory(Node* root)
	{
		if (root == NULL)
			return;
		_Distory(root->_left);
		_Distory(root->_right);

		delete root;
	}

	void _InOrder(Node* root)//中序遍历
	{
		if (root == NULL)
			return;
		_InOrder(root->_left);
		cout << root->_data << " ";
		_InOrder(root->_right);
	}

	void _PrevOrder(Node* root)//前序遍历
	{
		if (root == NULL)
			return;
		cout << root->_data << " ";
		_PrevOrder(root->_left);
		_PrevOrder(root->_right);
	}

	void _PostOrder(Node* root)//后序遍历
	{
		if (root == NULL)
			return;
		_PostOrder(root->_left);
		_PostOrder(root->_right);
		cout << root->_data << " ";
	}

	int _Height(Node* root)//二叉树高度
	{
		if (root == NULL)
			return 0;

		return (_Height(root->_left)) > (_Height(root->_right)) ?
			(_Height(root->_left))+1 : (_Height(root->_right))+1;
	}

	size_t _Size(Node* root)//节点个数
	{
		if (root == NULL)
			return 0;
		return _Size(root->_left) + _Size(root->_right)+1;
	}

	size_t _LeafSize(Node* root)//叶子节点个数
	{
		if (root == NULL)
			return 0;
		if (root->_left == NULL&&root->_right == NULL)
			return 1;
		
		return _LeafSize(root->_left) + _LeafSize(root->_right);
	}

	size_t _GetkLevel(Node* root, size_t k)//第K层
	{
		if (root == NULL)
			return 0;
		if (k == 1)
			return 1;

	}
private:
	Node* _root;
};

void Test()
{
	int array[10] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6 };

	BinaryTree<int> b(array, 10,'#');
	BinaryTree<int>b2(b);
	BinaryTree<int>b3(array, 10, '#');
	b3 = b;
	b.InOrder();
	b.PrevOrder();
	b.PostOrder();
	cout << b.Height() << endl;
	cout << b.Size() << endl;
	cout << b.LeafSize() << endl;
}