#pragma once
#include<cassert>
#include <queue>
#include <stack>

template<class T>
struct BinaryTreeNode
{
	BinaryTreeNode<T>* _left;
	BinaryTreeNode<T>* _right;
	T _data;

	BinaryTreeNode(const T& data)
		:_left(NULL)
		,_right(NULL)
		,_data(data)
	{}
};

template<class T>
class BinaryTree
{
	typedef BinaryTreeNode<T> Node;
public:
	BinaryTree(T* a,size_t size,const T& invalid)
	{
		size_t index = 0;
		_root = _Create(a,size,index,invalid);
	}

	BinaryTree()
		:_root(NULL)
	{}

	BinaryTree(const BinaryTree<T>& b)
	{
		_root = _Copy(b._root);
	}

	~BinaryTree()
	{
		_Clear(_root);
	}

	size_t Size()
	{
		return _Size(_root);
	}
	size_t LeafSize()
	{
		return _LeafSize(_root);
	}

	size_t Depth()
	{
		return _Depth(_root);
	}

	void PreOrder()
	{
		_PreOrder(_root);
		cout<<endl;
	}
	void PreOrder_NonR()
	{
		_PreOrder_NonR(_root);
		cout<<endl;
	}

	void InOrder()
	{
		_InOrder(_root);
		cout<<endl;
	}
	void InOrder_NonR()
	{
		_InOrder_NonR(_root);
		cout<<endl;
	}

	void PostOrder()
	{
		_PostOrder(_root);
		cout<<endl;
	}
	void PostOrder_NonR()
	{
		_PostOrder_NonR(_root);
		cout<<endl;
	}

	void LevelOrder()
	{
		_LevelOrder(_root);
		cout<<endl;
	}
protected:
	Node* _Create(T* a,size_t size,size_t& index,const T& invalid)
	{
		assert(a);
		
		Node* root = NULL;
		if(index<size && a[index]!=invalid)
		{
			root = new Node(a[index]);
			root->_left = _Create(a,size,++index,invalid);
			root->_right = _Create(a,size,++index,invalid);
		}
		return root;
	}
	Node* _Copy(Node* root)
	{
		
		if(root == NULL)
			return NULL;
		Node* newhead = new Node(root->_data);

		newhead->_left = _Copy(root->_left);
		newhead->_right = _Copy(root->_right);

		return newhead;
	}

	void _Clear(Node* root)
	{
		if(root == NULL)
			return;
		
		_Clear(root->_left);
		_Clear(root->_right);

		delete root;
		root = NULL;
	}

	size_t _Size(Node* root)
	{	
		size_t right = 0;
		size_t left  = 0;
		
		if(root == NULL)
			return 0;
		else
		{
			left = _Size(root->_left);
			right =  _Size(root->_right);
				
			return left+right+1;
		}
	}
	size_t _Depth(Node* root)
	{
		if(root == NULL)
			return 0;
		int left = _Depth(root->_left);
		int right = _Depth(root->_right);

		return left>right?(left+1):(right+1);
	}

	size_t _LeafSize(Node* root)
	{
		size_t leafsize = 0;
		if(root == NULL)
			return 0;
		if(root->_left == NULL && root->_right == NULL)
		{
			return 1;
		}
		leafsize += _LeafSize(root->_left);
		leafsize +=_LeafSize(root->_right);

		return leafsize;

	}
	void _PreOrder(Node* root)
	{
		if(root == NULL)
		{
			return;
		}
		cout<<root->_data<<" ";
		_PreOrder(root->_left);
		_PreOrder(root->_right);
	}

	void _InOrder(Node* root)
	{
		if(root == NULL)
		{
			return;
		}

		_InOrder(root->_left);
		cout<<root->_data<<" ";
		_InOrder(root->_right);

	}

	void _PostOrder(Node* root)
	{
		if(root == NULL)
		{
			return;
		}
		_PostOrder(root->_left);
		_PostOrder(root->_right);
		cout<<root->_data<<" ";
	}
	void _LevelOrder(Node* root)
	{
		queue<Node*> r;
		Node* parent = root;
		r.push(parent);

		if(parent == NULL)
		{
			return;
		}

		while(!r.empty())
		{
			parent = r.front();
			cout<<r.front()->_data<<" ";
			r.pop();

			if(parent != NULL)
			{
				if(parent->_left)
					r.push(parent->_left);
				if(parent->_right)
					r.push(parent->_right);
			}
		}
	}

	void _PreOrder_NonR(Node* root)
	{
		stack<Node*> s;
		Node* cur = root;
		if(root == NULL)
			return;

		s.push(cur);

		while(cur||!s.empty())
		{
			while(cur)
			{
				cout<<cur->_data<<" ";
				if(cur->_left)
					s.push(cur->_left);
				cur = cur->_left;
			}

			if(!s.empty())
			{
				cur = s.top();
				cur = cur->_right;
				s.pop();
				if(cur)
					s.push(cur);
			}	
		}
	}

	void _InOrder_NonR(Node* root)
	{
		if(root == NULL)
			return;
		stack<Node*> s;
		Node* cur= root;
		s.push(cur);

		while(cur||!s.empty())
		{
			while(cur)
			{
				if(cur->_left)
					s.push(cur->_left);
				cur = cur->_left;
			}

			if(!s.empty())
			{
				cur = s.top();
				s.pop();
				cout<<cur->_data<<" ";
				cur = cur->_right;
				if(cur)
					s.push(cur);	
			}
		}

	}
	void _PostOrder_NonR(Node* root)
	{
		stack<Node*> s;
		Node* cur = root;
		int Flag[20];

		if(root == NULL)
			return;
		
		while(cur||!s.empty())
		{
			while(cur)
			{
				s.push(cur);
				cur = cur->_left;
				Flag[s.size()] = 0;
			}
			while(!s.empty() && Flag[s.size()]==1)
			{
				cur = s.top();
				cout<<cur->_data<<" ";
				s.pop();
			}
			if(!s.empty())
			{
				cur = s.top();
				cur = cur->_right;
				Flag[s.size()] = 1;
			}
			else
				break;
		}
	}
protected:
	Node* _root;
};

void Test()
{
	int a[] = {1,2,3,'#','#',4,'#','#',5,6};
	BinaryTree<int> b(a,10,'#');
	BinaryTree<int> b1(b);
	b.PreOrder();
	b1.PreOrder();
	/*b.PreOrder();
	b.InOrder();
	b.PostOrder();
	b.LevelOrder();*/
	/*cout<<b.Depth()<<endl;*/
	//cout<<b.LeafSize()<<endl;
	//b.PreOrder_NonR();
	//b.InOrder_NonR();
	//b.PostOrder_NonR();
	//cout<<b.Size()<<endl;

	//int a[] = {1,2,'#',3,'#','#',4,5,'#',6,'#',7,'#','#',8};
	//BinaryTree<int> b(a,15,'#');
	//b.PreOrder();
	//b.InOrder();
	//b.PostOrder();
	//cout<<b.Size()<<endl;
	//b.LevelOrder();
	//cout<<b.Depth()<<endl;
	//cout<<b.LeafSize()<<endl;
	//b.PreOrder_NonR();

	/*b.InOrder_NonR();*/


}