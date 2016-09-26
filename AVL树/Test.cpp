#pragma once
#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <math.h>
using namespace std;

template<class K, class V>
struct AVLTreeNode
{
	K _key;
	V _value;
	AVLTreeNode<K, V>* _left;
	AVLTreeNode<K, V>* _right;
	AVLTreeNode<K, V>* _parent;
	int _bf;

	AVLTreeNode(const K& key, const V& value)
		:_key(key)
		, _value(value)
		, _left(NULL)
		, _right(NULL)
		, _parent(NULL)
		, _bf(0)
	{}

};

template<class K, class V>
class AVLTree
{
	typedef AVLTreeNode<K, V> Node;
public:
	AVLTree()
		:_root(NULL)
	{}

	bool Insert(const K& key, const V& value)
	{
		if (_root == NULL)
		{
			_root = new Node(key, value);
			return true;
		}
		Node* cur = _root;
		Node* parent = NULL;
		while (cur)
		{
			if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
				return false;
		}

		cur = new Node(key, value);
		if (parent->_key < key)
		{
			parent->_right = cur;
			cur->_parent = parent;
		}
		else if (parent->_key > key)
		{
			parent->_left = cur;
			cur->_parent = parent;
		}

		//调整平衡因子
		bool isRotate = false;
		while (parent)
		{
			if (cur == parent->_right)
			{
				parent->_bf++;
			}
			else
				parent->_bf--;
			if (parent->_bf == 1 || parent->_bf == -1)
			{
				cur = parent;
				parent = cur->_parent;//往上寻找
			}
			else if (parent->_bf == 0)
			{
				break;
			}
			else//_bf == 2,_bf == -2
			{
				//调整AVL树的平衡因子

				if (parent->_bf == -2)
				{
					if (cur->_bf == -1)
					{
						_RotateR(parent);//右单旋
					}
					else
					{
						_RotateLR(parent);//左右双旋
					}
				}
				if (parent->_bf == 2)
				{
					if (cur->_bf == 1)
					{
						_RotateL(parent);//左单旋
					}
					else
					{
						_RotateRL(parent);//右左双旋
					}
				}

				isRotate = true;
				break;

			}
		}
		if (isRotate)
		{
			Node* ppNode = parent->_parent;
			if (ppNode == NULL)
			{
				_root = parent;
			}
			else if (ppNode->_key > parent->_key)
			{
				ppNode->_left = parent;
			}
			else
			{
				ppNode->_right = parent;
			}
		}
		return true;
	}

	void _RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		parent->_right = subRL;
		if (subRL)
			subRL->_parent = parent;
		subR->_left = parent;
		Node* ppNode = parent->_parent;
		parent->_parent = subR;

		if (ppNode == NULL)
		{
			_root = subR;
			_root->_parent = NULL;
		}
		else
		{
			if (ppNode->_left == parent)
				ppNode->_left = subR;
			else
				ppNode->_right = subR;

			subR->_parent = ppNode;
		}
		subR->_bf = parent->_bf = 0;
	}

	void _RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		parent->_left = subLR;
		if (subLR)
			subLR->_parent = parent;
		subL->_right = parent;
		Node* ppNode = parent->_parent;
		parent->_parent = subL;
		if (ppNode == NULL)
		{
			_root = subL;
			subL->_parent = NULL;
		}
		else
		{
			if (ppNode->_left == parent)
			{
				ppNode->_left = subL;
			}
			else
			{
				ppNode->_right = subL;
			}

			subL->_parent = ppNode;
		}

		subL->_bf = parent->_bf = 0;
	}

	void _RotateRL(Node* parent)
	{
		Node* pNode = parent;
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		int bf = subRL->_bf;
		_RotateR(parent->_right);
		_RotateL(parent);

		if (bf == 1)
		{
			subR->_bf = 0;
			pNode->_bf = -1;
		}

		else if (bf == -1)
		{
			subR->_bf = 1;
			pNode->_bf = 0;
		}
		else
		{
			pNode->_bf = subR->_bf = 0;
		}

		subRL->_bf = 0;
	}

	void _RotateLR(Node* parent)
	{
		Node* pNode = parent;
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		int bf = subLR->_bf;

		_RotateL(parent->_left);
		_RotateR(parent);

		if (bf == 1)
		{
			subL->_bf = 0;
			pNode->_bf = -1;
		}
		else if (bf == -1)
		{
			pNode->_bf = 0;
			subL->_bf = 1;
		}
		else
		{
			subL->_bf = pNode->_bf = 0;
		}
		subLR->_bf = 0;
	}

	int Height(Node* root)
	{
		if (root == NULL)
		{
			return 0;
		}

		int left = Height(root->_left);
		int right = Height(root->_right);

		return left > right ? (left + 1) : (right + 1);
	}

	bool IsBlance()
	{
		return _IsBlance(_root);
	}

	bool _IsBlance(Node* root)
	{
		if (root == NULL)
		{
			return true;
		}
		int left = Height(root->_left);
		int right = Height(root->_right);

		if (root->_bf != (left - right))
		{
			cout << "平衡因子异常：" << root->_key << endl;
			return false;
		}

		return abs(left - right) < 2
			&& (_IsBlance(root->_right))
			&& (_IsBlance(root->_left));
	}

	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}

	void _InOrder(Node* root)
	{
		if (root == NULL)
		{
			return;
		}
		_InOrder(root->_left);
		cout << root->_key << " ";
		_InOrder(root->_right);

	}

private:
	Node* _root;
};


void TestAVLTree()
{
	AVLTree<int, int> t;
	int a[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	for (size_t i = 0; i < sizeof(a) / sizeof(a[0]); ++i)
	{
		t.Insert(a[i], i);
	}

	t.InOrder();

	cout << "t是否平衡？" << t.IsBlance() << endl;

	/*AVLTree<int, int> t1;
	int a1[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
	for (size_t i = 0; i < sizeof(a1) / sizeof(a1[0]); ++i)
	{
		t1.Insert(a1[i], i);
	}

	t1.InOrder();

	cout << "t1是否平衡？" << t1.IsBlance() << endl;*/
}
//void Test()
//{
//	int arr[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
//	int size = sizeof(arr) / sizeof(arr[0]);
//
//	AVLTree<int, int> a;
//	int i = 0;
//
//	for (; i < size; i++)
//	{
//		a.Insert(arr[i], i);
//	}
//	cout << a.IsBlance() << endl;
//	a.InOrderSort();
//
//


int main()
{
	TestAVLTree();
	system("pause");
	return 0;
}