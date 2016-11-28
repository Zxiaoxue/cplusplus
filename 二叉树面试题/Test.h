#pragma once

template<class T>
struct BinaryTreeNode
{
	T _data;
	int _maxleft;
	int _maxright;
	BinaryTreeNode* _left;
	BinaryTreeNode* _right;
	BinaryTreeNode* _parent;

	BinaryTreeNode(T data)
		:_data(data)
		,_maxleft(0)
		,_maxright(0)
		,_left(NULL)
		,_right(NULL)
		,_next(NULL)
	{}

};

template<class T>
class BinaryTree
{
	typedef BinaryTreeNode Node;
public:
	BinaryTree(T* a,size_t size,T& invalid = T())
	{
		size_t index = 0;
		Node* prev = NULL;
		_root = _Create(a,size,index,prev,invalid);
	}

	~BinaryTree()
	{
		_Delete(_root);
	}
	//1.求二叉树最远的两个节点距离
	
	//解法一
	int Depth()
	{
		return _Depth(_root);
	}
	int FindMaxLen1()
	{
		int num = 0;
		_FindMaxLen1(_root,num);
	}

	//解法二
	int FindMaxLen2()
	{
		int maxLen = 0;
		_FindMaxLen2(_root,maxLen);
		return maxLen;
	}

protected:
	Node* _Create(T* a,size_t size,size_t& index,Node*& prev,T& invalid = T())
	{
		Node* root = NULL;
		if(a[index]!=invalid && index<size)
		{
			root = new Node(a[index]);
			root->_parent = prev;
			root->_left = _Create(a,size,++index);
			root->_right = _Create(a,size,++index);
			prev = root;
		}

		return root;
	}

	int _Depth(Node* root)
	{
		if(root == NULL)
			return 0;
		int left = _Depth(root->_left);
		int right = _Depth(root->_right);

		return left > right ? left+1 : right+1;
	}

	void _FindMaxLen1(Node* root,int & maxLen)
	{
		if(root == NULL)
			return;

		int left = _Depth(root->_left);
		int right = _Depth(root->_right);

		if(maxLen < left+right)
			maxLen = left+right;

		_FindMaxLen(root->_left,maxLen);
		_FindMaxLen(root->_right,maxLen);
	}

	void _FindMaxLen2(Node* root,int& maxLen)
	{
		if(root == NULL)
			return;
		if(root->_left == NULL)
			root->_maxleft = 0;
		if(root->_right == NULL)
			root->_maxright = 0;
		if(root->_left != NULL)
		{
			int tmp = 0;
			if(root->_left->_maxleft > root->_left->_maxright)
				tmp = root->_left->_maxleft;
			else
				tmp = root->_left->_maxright;

			root->_maxleft = tmp+1;
		}
		
		if(root->_right != NULL)
		{
			int tmp = 0;
			if(root->_right->_maxleft > root->_right->_maxright)
				tmp = root->_right->_maxleft;
			else
				tmp = root->_right->_maxright;

			root->_maxright = tmp+1;
		}

		if(maxLen < root->_maxleft +root->_maxright)
			maxLen = root->_maxleft+root->_maxright;

	}


	void _Delete(Node* root)
	{
		if(root == NULL)
			return;
		if(root->_left == NULL &&root->_right == NULL)
			delete root;

		_Delete(root->_left);
		_Delete(root->_right);

	}
protected:
	Node* _root;
};