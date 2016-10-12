#pragma once

enum Tag
{
	THREAD,
	LINK,
};

template<class T>
struct BinaryTreeThdNode
{
	BinaryTreeThdNode<T>* _left;
	BinaryTreeThdNode<T>* _right;
	T _data;
	Tag _leftTag;
	Tag _rightTag;

	BinaryTreeThdNode(const T& data)
		:_left(NULL)
		,_right(NULL)
		,_data(data)
		,_leftTag(LINK)
		,_rightTag(LINK)
	{}

};

template<class T,class Ref,class Ptr>
struct  __TreeIterator
{
	typedef BinaryTreeThdNode<T> Node;
	typedef __TreeIterator<T, Ref, Ptr> Self; 

	__TreeIterator(Node* node)
		:_node(node)
	{}

	Ref operator*()
	{
		return _node->_data;
	}

	bool operator==(const Self& x) const
	{
		return _node == x._node;
	}

	bool operator!=(const Self& x) const
	{
		return _node != x._node;
	}

	Self& operator++()
	{
		if(_node && (_node->_rightTag == THREAD))
		{
			_node = _node->_right;

		}
		else if(_node && (_node->_rightTag == LINK))
		{
			_node = _node->_right;
			while(_node && (_node->_leftTag == LINK))
			{
				_node = _node->_left;
			}
		}

		return *this;
	}

	Self& operator--()
	{
		if(_node && (_node->_leftTag == THREAD))
		{
			_node = _node->_left;
		}
		else if(_node && (_node->_leftTag == LINK))
		{	
			_node = _node->_left;
			while(_node && (_node->_rightTag == LINK))
			{
				_node = _node->_right;
			}
		}

		return *this;
	}


	Node* _node;
};



template<class T>
class BinaryTreeThd
{
public:
	typedef BinaryTreeThdNode<T> Node;
	typedef __TreeIterator<T, T&, T*> Iterator;
	typedef __TreeIterator<T, const T&, const T*> ConstIterator;

	BinaryTreeThd(T* a,size_t size,const T& invalid)
		:_root(NULL)
	{
		size_t index = 0;
		_root = _Create(a,size,index,invalid);
	}

	Iterator Begin()
	{
		Node* cur = _root;

		if(cur == NULL)
			return NULL;

		while(cur->_left)
		{
			cur = cur->_left;
		}

		return Iterator(cur);
	}

	Iterator End()
	{
		return Iterator(NULL);
	}

	void PrevOrderThreading()
	{
		Node* prev = NULL;
		_PrevOrderThreading(_root,prev);
	}

	void PrevOrderThd()
	{
		_PrevOrderThd(_root);
		cout<<endl;
	}

	void InOrderThreading()
	{
		Node* prev = NULL;
		_InOrderThreading(_root,prev);
	}

	void InOrderThd()
	{
		_InOrderThd(_root);
		cout<<endl;
	}
	
	void PostOrderThreading()
	{
		Node* prev = NULL;
		_PostOrderThreading(_root,prev);
	}
	void PostOrderThd()
	{
		_PostOrderThd(_root);
		cout<<endl;
	}

protected:
	Node* _Create(T* a,size_t size,size_t& index,const T& invalid)
	{
		Node* root = NULL;

		if((index < size) && (a[index] != invalid))
		{
			root = new Node(a[index]);

			root->_left = _Create(a,size,++index,invalid);
			root->_right = _Create(a,size,++index,invalid);
		}

		return root;
	}

	void _PrevOrderThreading(Node* root,Node*& prev)
	{
		if(root == NULL)
			return;

		if(root->_left == NULL)
		{
			root->_leftTag = THREAD;
			root->_left = prev;
		}

		if(prev && (prev->_right == NULL))
		{
			prev->_rightTag = THREAD;
			prev->_right = root;
		}
		prev = root;
		if(root->_leftTag == LINK)
			_PrevOrderThreading(root->_left,prev);
		
		if(root->_rightTag == LINK)
			_PrevOrderThreading(root->_right,prev);

	}

	void _PrevOrderThd(Node* root)
	{
		if(root == NULL)
			return;

		while(root)
		{
			while(root->_leftTag == LINK)
			{
				cout<<root->_data<<" ";
				root = root->_left;
			}

			cout<<root->_data<<" ";
			root = root->_right;
		}
	}

	void _InOrderThreading(Node* root,Node*& prev)
	{
		if(root == NULL)
			return;

		if(root->_leftTag == LINK)
			_InOrderThreading(root->_left,prev);

		if(root->_left == NULL)
		{
			root->_leftTag = THREAD;
			root->_left = prev;
		}

		if(prev&&(prev->_right == NULL))
		{
			prev->_rightTag = THREAD;
			prev->_right = root;
		}
		prev = root;

		if(root->_rightTag == LINK)
			_InOrderThreading(root->_right,prev);
	}
	void _InOrderThd(Node* root)
	{
		Node* cur = root;
		if(root == NULL)
			return;
		
		while(cur)
		{
			while(cur->_leftTag == LINK)
			{
				cur = cur->_left;
			}

			cout<<cur->_data<<" ";

			while(cur->_rightTag == THREAD)
			{
				cur = cur->_right;
				cout<<cur->_data<<" ";
			}
			cur = cur->_right;
		}
	}

	void _PostOrderThreading(Node* root,Node*& prev)
	{
		 if(root == NULL)
			 return;

		 if(root->_leftTag == LINK)
		 {
			 _PostOrderThreading(root->_left,prev);
		 }

		 if(root->_rightTag == LINK)
		 {
			 _PostOrderThreading(root->_right,prev);
		 }

		 if(root->_left == NULL)
		 {
			 root->_leftTag = THREAD;
			 root->_left = prev;
		 }

		 if(prev && (prev->_right == NULL))
		 {
			 prev->_rightTag = THREAD;
			 prev->_right = root;
		 }

		 prev = root;
	}

	//后序遍历线索化 1将树构建成三叉链 2写一个递归的find函数寻找当前节点的父节点(低效)
	//错误
	//void _PostOrderThd(Node* root)
	//{
	//	Node* cur = root;
	//	Node* prev = root;
	//	if(root == NULL)
	//		return;

	//	while(cur)
	//	{
	//		prev = cur;
	//		while(cur->_leftTag == LINK)
	//		{
	//			cur = cur->_left;
	//		}

	//		cout<<cur->_data<<" ";

	//		while(cur->_rightTag == THREAD)
	//		{
	//			cur = cur->_right;
	//			cout<<cur->_data<<" ";
	//		}

	//		if(cur->_rightTag == LINK)
	//			cur = prev;

	//		if(cur->_right == root)
	//			return;
	//		cur = cur->_right;
	//	}

	//}

protected:
	Node* _root;
};

void Test()
{
	 int arr[] = {1,2,3,'#','#',4,'#','#',5,6};  
	 BinaryTreeThd<int> b(arr,10,'#');

	/* b.PrevOrderThreading();
	 b.PrevOrderThd();*/

	// b.PostOrderThreading();
	// b.PostOrderThd();

	 b.InOrderThreading();
	 b.InOrderThd();

	BinaryTreeThd<int>::Iterator it = b.Begin();

	while (it != b.End())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
}