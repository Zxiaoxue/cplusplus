#pragma once

enum Colour
{
	RED,
	BLACK,
};

template<class K,class V>
struct RBTreeNode
{
	K _key;
	V _value;

	RBTreeNode<K,V>* _left;
	RBTreeNode<K,V>* _right;
	RBTreeNode<K,V>* _parent;

	Colour _colour;

	RBTreeNode(const K& key,const V& value,Colour colour = RED)
		:_key(key)
		,_value(value)
		,_left(NULL)
		,_right(NULL)
		,_parent(NULL)
		,_colour(RED)
	{}

};

template<class K,class V>
class RBTree
{
	typedef RBTreeNode<K,V> Node;

public:
	RBTree()
		:_root(NULL)
	{}

	RBTree(const K* a,size_t size)
	{
		_root = NULL;
		for(size_t i = 0;i<size;++i)
		{
			_Insert(a[i],i);
		}
	}

	bool _Insert(const K& key,const V& value)
	{
		if(_root == NULL)
		{
			_root = new Node(key,value);
			_root->_colour = BLACK;
			return true;
		}

		Node* parent = NULL;
		Node* cur = _root;

		while(cur)
		{
			if(cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if(cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				return false;
			}
		}

		cur = new Node(key,value);

		if(parent->_key > key)
		{
			parent->_left = cur;
			cur->_parent = parent;
		}
		else
		{
			parent->_right = cur;
			cur->_parent = parent;
		}

		while(cur != _root && parent->_colour == RED)
		{
			Node* grandfather = parent->_parent;

			if(parent == grandfather->_left)
			{
				Node* uncle = grandfather->_right;
				//1.uncle存在且为红
				if(uncle && uncle->_colour == RED)
				{
					grandfather->_colour = RED;
					uncle->_colour = BLACK;
					parent->_colour = BLACK;

					//向上调整，
					cur = grandfather;
					parent = cur->_parent;
				}
				else
				{
					//2.uncle不存在或3.uncle存在且为黑
					if(cur == parent->_right)
					{
						_RotateL(parent);
						swap(cur,parent);
					}

					_RotateR(grandfather);

					grandfather->_colour = RED;
					parent->_colour = BLACK;

					break;
				}
			}
			else //parent == grandfather->_right;
			{
				Node* uncle = grandfather->_left;

				//uncle存在且为红
				if(uncle && uncle->_colour == RED)
				{
					grandfather->_colour = RED;
					parent->_colour = BLACK;
					uncle->_colour = BLACK;

					//向上调整
					cur = grandfather;
					parent = cur->_parent;
				}
				else
				{
					if(cur == parent->_left)
					{
						_RotateR(parent);
						swap(cur,parent);
					}

					_RotateL(grandfather);
					grandfather->_colour = RED;
					parent->_colour = BLACK;

					break;
				}

			}
		}
		_root->_colour = BLACK;
		return true;
	}

	void _RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		parent->_right = subRL;
		if(subRL)
			subRL->_parent = parent;

		Node* ppNode = parent->_parent;
		subR->_left = parent;
		parent->_parent = subR;

		if(ppNode == NULL)
		{
			subR->_parent = NULL;
			_root = subR;
		}
		else
		{
			if(ppNode->_left == parent)
			{
				ppNode->_left = subR;
			}
			else
				ppNode->_right = subR;

			subR->_parent = ppNode;
		}

	}

	void _RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = parent->_right;

		parent->_left = subLR;
		if(subLR)
			subLR->_parent = parent;

		Node* ppNode = parent->_parent;
		subL->_right = parent;
		parent->_parent = subL;

		if(ppNode == NULL)
		{
			subL->_parent = NULL;
			_root = subL;
		}
		else
		{
			if(ppNode->_left == parent)
				ppNode->_left = subL;
			else
				ppNode->_right = subL;

			subL->_parent = ppNode;
		}
	}
	bool IsBlance()
	{
		if(_root == NULL)
			return true;

		if(_root->_colour == RED)
			return false;

		int count = 0;
		Node* cur = _root;
		while(cur)
		{
			if(cur->_colour == BLACK)
				++count;
			cur = cur->_left;
		}
		int k = 0;
		return _IsBlance(_root,count,k);

	}

	bool _IsBlance(Node* root,const int& count,int k)
	{
		if(root == NULL)
			return true;

		//连续红结点
		if(root->_colour == RED && root->_parent->_colour == RED)
		{
			cout<<"连续红节点："<<root->_key<<endl;
			return false;
		}
		//每条路径上黑节点个数
		if(root->_colour == BLACK)
			++k;

		if(root->_left == NULL && root->_right == NULL)
		{
			if(k != count)
			{
				cout<<"黑节点个数不同："<<root->_key<<endl;
				return false;
			}
		}

		return _IsBlance(root->_left,count,k)&&_IsBlance(root->_right,count,k);

	}
	void InOrder()
	{
		_InOrder(_root);
		cout<<endl;
	}

	void _InOrder(Node* root)
	{
		if(root == NULL)
			return;

		_InOrder(root->_left);
		cout<<root->_key<<" ";
		_InOrder(root->_right);

	}

protected:
	Node* _root;
};

void Test()
{
	int arr[] = {16,3,7,11,9,26,18,14,15};
	size_t size = sizeof(arr)/sizeof(arr[0]);

	RBTree<int,int> bt(arr,size);
	bt.InOrder();

	cout<<bt.IsBlance()<<endl;
}