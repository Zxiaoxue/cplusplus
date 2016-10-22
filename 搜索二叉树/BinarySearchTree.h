#pragma once
#include <cassert>

template<class K>
struct BinarySearchTreeNode
{
	K _key;
	BinarySearchTreeNode<K>* _left;
	BinarySearchTreeNode<K>* _right;
	BinarySearchTreeNode<K>* _parent;

	BinarySearchTreeNode(const K& key)
		:_key(key)
		,_left(NULL)
		,_right(NULL)
		,_parent(NULL)
	{}

};

template<class K>
class BinarySearchTree
{
	typedef BinarySearchTreeNode<K> Node;
public:
	BinarySearchTree()
		:_root(NULL)
	{}

	BinarySearchTree(const K* arr,size_t size)
	{
		_root = NULL;
		for(int i = 0; i < size; ++i)
		{
			Insert(arr[i]);
		}
	}

	bool Insert(const K& key)
	{
		if(_root == NULL)
		{
			_root = new Node(key);
			return true;
		}
		
		Node* cur = _root;
		Node* parent = NULL;
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
				return false;
		}

		cur = new Node(key);
		
		if(key < parent->_key)
		{
			parent->_left = cur;
			cur->_parent = parent;
		}
		else
		{
			parent->_right = cur;
			cur->_parent = parent;
		}

		return true;
	}

	bool Find(const K& key)
	{
		if(_root == NULL)
		{
			return false;
		}

		Node* cur = _root;
		while(cur)
		{
			if(cur->_key > key)
			{
				cur = cur->_left;
			}
			else if(cur->_key < key)
			{
				cur = cur->_right;
			}
			else
				return true;

		}

		return false;
	}

	bool Remove(const K& key)
	{
		assert(_root);
		Node* cur = _root;
		Node* parent = NULL;

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
				Node* del = cur;
				if(cur->_left == NULL)
				{
					if(parent)
					{
						if(cur == parent->_left)
							parent->_left = cur->_right;
						else
							parent->_right = cur->_right;
					}
					else
					{
						_root = cur->_right;
					}
					
				}
				else if(cur->_right == NULL)
				{
					if(parent)
					{
						if(cur == parent->_left)
							parent->_left = cur->_left;
						else
							parent->_right = cur->_left;
					}
					else
					{
						_root = cur->_left;
					}
					
				}
				else
				{
					parent = cur;
					Node* minRight = cur->_right;

					while(minRight->_left)
					{
						parent = minRight;
						minRight = minRight->_left;
					}

					cur->_key = minRight->_key;

					del = minRight;
					if(parent->_left == minRight)
					{
						parent->_left = minRight->_right;
					}
					else
					{
						parent->_right = minRight->_right;
					}
				}
				
				delete del;
				return true;
			}
		}

		return false;
		
	}

	void InOrder()
	{
		_InOrder(_root);
		cout<<endl;
	}
protected:


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
	int arr[] = {5,3,4,1,7,8,2,6,0,9};

	size_t size = sizeof(arr)/sizeof(arr[0]);

	BinarySearchTree<int> bt(arr,size);

	bt.InOrder();

	bt.Remove(8);
	bt.Remove(3);
	bt.Remove(0);
	bt.Remove(1);
	bt.Remove(2);
	bt.Remove(3);
	bt.Remove(4);
	bt.Remove(5);
	bt.Remove(6);
	bt.Remove(7);
	bt.Remove(8);
	bt.Remove(9);

	bt.InOrder();
}