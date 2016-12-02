#pragma once
#include <vector>
#include <string.h>
#include <queue>

bool flag = true;//3.解法一:队列加flag

template<class T>
struct BinaryTreeNode
{
	T _data;
	int _maxleft;
	int _maxright;
	BinaryTreeNode* _left;
	BinaryTreeNode* _right;
	BinaryTreeNode* _parent;

	BinaryTreeNode(const T& data = T())
		:_data(data)
		,_maxleft(0)
		,_maxright(0)
		,_left(NULL)
		,_right(NULL)
	{}

	bool operator!=(BinaryTreeNode* x1)
	{
		return _data != x2->_data;
	}

};

template<class T>
class BinaryTree
{
	typedef BinaryTreeNode<T> Node;
	//typedef BinaryTreeNode Node;
public:
	BinaryTree(const T* a,size_t size,const T& invalid = T())
	{
		size_t index = 0;
		Node* prev = NULL;
		_root = _GreateTree(a,size,index,prev,invalid);
	}

	BinaryTree(char* prev,char* order)
	{
		_root = _ReBuildTree(prev,order,order);
	}

	int Size()
	{
		return _Size(_root);
	}

	/*~BinaryTree()
	{
		_Delete(_root);
	}*/

	//ToList的析构函数
	~BinaryTree()
	{
		Node* head = _root;

		while(head)
			head = head->_left;

		_DeleteToList(head);
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
		return num;
	}

	//解法二
	int FindMaxLen2()
	{
		int maxLen = 0;
		_FindMaxLen2(_root,maxLen);
		return maxLen;
	}

	//2.由前序遍历和中序遍历重建二叉树
	/*Node* RebuildTree(string<int> prev,string<int> order)
	{
		int size = order.size();
		Node* root = NULL;
		return root = _ReBuildTree(prev,order[0],order[size-1]);
	}*/

	//3.判断一棵树是不是完全二叉树
	bool IsCompleteBinaryTree()
	{
		//return _IsCompleteBinaryTree(_root);
		return _IsCompleteBinaryTree1(_root);

	}

	//4.1
	Node* Find1(T data)
	{
		return _Find(_root,data);
	}

	//4.2
	bool Find2(T data)
	{
		return _Find2(_root,data);
	}

	//4.两个节点的最近公共祖先
	Node* GetCommRoot(Node* x1,Node* x2)
	{
		//三叉链找最近公共祖先
		//return _GetCommRoot(x1,x2);

		/*Node* ret = NULL;
		_GetCommRoot2(_root,x1,x2,ret);
		return ret;*/

		return _GetCommRoot3(_root,x1,x2);
	}

	//5.将一个二叉搜索树转换为一个排序二叉树，要求不能创建任何新节点，只能调整树中节点的指向
	Node* ToList()
	{
		Node* prev = NULL;
		_ToList(_root,prev);

		//找到链表的头，是最左节点
		Node* head = _root;
		while(head && head->_left != NULL)
			head = head->_left;

		return head;
	}

	void InOrder()
	{
		_InOrder(_root);
		cout<<endl;
	}

protected:
	Node* _GreateTree(const T* arr,size_t size,size_t& index,Node* prev,const T& invalid)
	{
		Node* root = NULL;

		if((index < size) && (arr[index] != invalid))
		{
			root = new Node(arr[index]);
			root->_parent = prev;
			prev = root;
			root->_left = _GreateTree(arr,size,++index,prev,invalid);		
			root->_right = _GreateTree(arr,size,++index,prev,invalid);
			
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

		_FindMaxLen1(root->_left,maxLen);
		_FindMaxLen1(root->_right,maxLen);
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
			_FindMaxLen2(root->_left,maxLen);
		}
		if(root->_right != NULL)
			_FindMaxLen2(root->_right,maxLen);

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

		if(maxLen < (root->_maxleft+root->_maxright))
			maxLen = root->_maxleft+root->_maxright;

	}

	Node* _ReBuildTree(char*& prev,char* in1,char* in2)
	{
		if(*prev == '\0')
			return NULL;

		Node* root = new Node(*prev);

		char* pos = in1;
		while(*pos != *prev)
			++pos;

		if(in1 <= in2)
			root->_left = _ReBuildTree(++prev,in1,--pos);
		if(pos < in2)
			root->_right = _ReBuildTree(++prev,pos+1,in2);

		return root;
	}

	//3.1队列加flag
	bool _IsCompleteBinaryTree(Node* root)
	{
		flag = true;
		if(root == NULL)
			return true;
		queue<Node*> q;
		q.push(root);

		while(!q.empty())
		{
			Node* front = q.front();
			q.pop();

			if(front->_left)
			{
				if(flag == false)
					return false;
				else
					q.push(front->_left);
			}
			else
				flag = false;

			if(front->_right)
			{
				if(flag == false)
					return false;
				else
					q.push(front->_right);
			}
			else
				flag = false;


			/*if(front->_left == NULL)
				flag = false;
			if(front->_right != NULL)
			{
				if(flag == false)
					return false;
			}
			if(front->_left)
				q.push(front->_left);
			if(front->_right)
				q.push(front->_right);*/
		}
		return true;
	}

	//3.2 入队列，遇到空判断队列是否已经空
	bool _IsCompleteBinaryTree1(Node* root)
	{
		queue<Node*> q;
		q.push(root);

		Node* front = q.front();

		while(front != NULL)
		{
			front = q.front();
			q.pop();
			if(front != NULL)
			{
				q.push(front->_left);
				q.push(front->_right);
			}
		}

		while(!q.empty())
		{
			front = q.front();
			q.pop();
			if(front != NULL)
				return false;
		}
		return true;
	}

	//3.3统计树的节点个数和应该是完全树的节点个数，看size是否相等
	bool _IsCompleteBinaryTree2(Node* root)
	{
		int size = _Size(root);
		//int completesize = 
	}

	size_t _Size(Node* root)
	{	
		size_t right = 0;
		size_t left  = 0;
		
		if(root == NULL)
			return 1;
		else
		{
			left = _Size(root->_left);
			right =  _Size(root->_right);
				
			return left+right+1;
		}
	}

	/*int _CompleteSize(Node* root)
	{
		queue<Node*> q;
		q.push(root);
		Node* prev = NULL;

		while()
		{
			if(root != NULL)
			{
				q.push(root->_left);
				q.push(root->_right);
			}
			else
			{
				q.push(NULL);
			}
		}

	}
*/
	Node* _Find(Node* root,T data)
	{
		if(root == NULL)
			return NULL;

		Node* left = _Find(root->_left,data);
		
		if(root->_data == data)
			return root;

		Node* right = _Find(root->_right,data);

		if(left != NULL)
			return left;
		else if(right != NULL)
			return right;
		else
			return NULL;
	}

	bool _Find2(Node* root,T data)
	{
		if(root == NULL)
			return false;

		if(root->_data == data)
			return true;
		bool left = _Find2(root->_left,data);
		bool right = _Find2(root->_right,data);

		if(left || right)
			return true;

	}

	//4.1三叉链找最近公共祖先
	Node* _GetCommRoot(Node* x1,Node* x2)
	{
		Node* parent1 = x1;
		Node* parent2 = x2;

		while(parent1 != NULL && parent2 != NULL &&parent1 != parent2)
		{
			parent1 = parent1->_parent;
			parent2 = parent2->_parent;
		}

		return parent1;
	}

	//4.2递归，在左子树Find node1，node2，右子树 Find node1，node2
	//有问题
	Node* _GetCommRoot2(Node* root,Node* x1,Node* x2,Node*& ret)
	{
		if(x1 == NULL || x2 == NULL)
			return NULL;
		if(root == NULL)
			return NULL;
		if(ret == NULL)
		{
			bool b1 = _Find2(root->_left,x1->_data);
			bool b2 = _Find2(root->_left,x2->_data);
			if(b1 && b2)
				_GetCommRoot2(root->_left,x1,x2,ret);
		}

		if(ret == NULL)
		{
			bool b3 = _Find2(root->_right,x1->_data);
			bool b4 = _Find(root->_right,x2->_data);
			if(b3 && b4)
				_GetCommRoot2(root->_right,x1,x2,ret);
		}

		if(ret == NULL)
		{
			bool b5 = _Find2(root->_left,x1->_data);
			bool b6 = _Find2(root->_right,x2->_data);
			if(b5 && b6)
			{
				ret = root;
				return root;
			}
		}

		if(ret == NULL)
		{
			bool b7 = _Find2(root->_left,x2->_data);
			bool b8 = _Find2(root->_right,x1->_data);
			if(b7 && b8)
			{
				ret = root;
				return root;
			}
		}
	}

	//4.3 递归
	Node* _GetCommRoot3(Node* root,Node* x1,Node* x2)
	{
		if(root == NULL)
			return NULL;

		//判断是否找到这个节点
		if(root == x1 ||root == x2)
		{
			return root;
		}
		//递归左右子树
		Node* left = _GetCommRoot3(root->_left,x1,x2);
		Node* right = _GetCommRoot3(root->_right,x1,x2);

		//判断是否在左右子树中找到
		if(left && right)
			return root;
		//否则返回找到的那个节点
		return left ? left : right;

	}
	Node* _ToList(Node* root,Node*& prev)
	{
		if(root == NULL)
			return root;
		_ToList(root->_left,prev);

		//root的左连接到前一个遍历过的节点上
		root->_left = prev;
		if(prev)
			prev->_right = root;
		prev = root;

		_ToList(root->_right,prev);
	}

	//void _Delete(Node* root)
	//{
	//	if(root == NULL)
	//		return;
	//	
	//	Node* del = root;

	//	_Delete(root->_left);
	//	_Delete(root->_right);
	//	
	//	delete root;
	//}

	//执行了ToList函数线索化后需要这样释放节点
	void _DeleteToList(Node* root)
	{
		Node* del = root;
		while(root != NULL)
		{
			root = root->_left;
			delete del;
		}
	}

	void _InOrder(Node* root)
	{
		if(root == NULL)
			return;
		_InOrder(root->_left);
		cout<<root->_data<<" ";
		_InOrder(root->_right);
	}

protected:
	Node* _root;
};

void Test()
{
	/*int arr[] = {1,2,3,'#','#',4,'#','#',5,6};
	int size = sizeof(arr)/sizeof(arr[0]);

	BinaryTree<int> bt(arr,size,'#');

	bt.InOrder();
	cout<<bt.FindMaxLen1()<<endl;
	cout<<bt.FindMaxLen2()<<endl;*/
	string s1;
	string s2;
	int a[] = {3,2,4,1,6,5};
	int size = sizeof(a)/sizeof(a[0]);
	for(int i = 1; i<7; ++i)
	{
		s1.push_back(i);
	}
	for(int i = 0; i<size; ++i)
	{
		s2.push_back(a[i]);
	}

	//BinaryTree bt(s1,s2);
	//bt.InOrder();
}

void TestToList()
{
	int a[] = {5,3,1,0,'#','#',2,'#','#',4,'#','#',7,6,'#','#',8};
	size_t size = sizeof(a)/sizeof(a[0]);

	BinaryTree<int> bt(a,size,'#');
	bt.InOrder();

	BinaryTreeNode<int>* head = bt.ToList();
	BinaryTreeNode<int>* last = NULL;

	while(head != NULL)
	{
		cout<<head->_data<<"->";
		last = head;
		head = head->_right;
	}
	cout<<"NULL";
	cout<<endl;

	while(last != NULL)
	{
		cout<<last->_data<<"->";
		last = last->_left;
	}
	cout<<"NULL";
	cout<<endl;
}

void TestIsCompleteTree()
{
	int a[] = {5,3,1,0,'#','#',2,'#','#',4,'#','#',7,6,'#','#',8};
	size_t size = sizeof(a)/sizeof(a[0]);

	BinaryTree<int> bt(a,size,'#');
	bt.InOrder();
	cout<<bt.Size()<<endl;

	cout<<bt.IsCompleteBinaryTree()<<endl;

	int arr[] = {1,2,3,'#','#',4,'#','#',5,6};
	int size1 = sizeof(arr)/sizeof(arr[0]);
	BinaryTree<int> bt1(arr,size1,'#');
	bt1.InOrder();
	cout<<bt1.Size()<<endl;

	cout<<bt1.IsCompleteBinaryTree()<<endl;
}

void TestfatherNode()
{
	int a[] = {5,3,1,0,'#','#',2,'#','#',4,'#','#',7,6,'#','#',8};
	size_t size = sizeof(a)/sizeof(a[0]);

	BinaryTree<int> bt(a,size,'#');
	bt.InOrder();

	BinaryTreeNode<int>* ret1 = bt.Find1(4);
	BinaryTreeNode<int>* ret2 = bt.Find1(3);
	if(ret1 != NULL)
		cout<<ret1->_data<<endl;
	if(ret2 != NULL)
		cout<<ret2->_data<<endl;
	BinaryTreeNode<int>* ret = bt.GetCommRoot(ret1,ret2);
	if(ret != NULL)
		cout<<ret->_data<<endl;

	//cout<<bt.Find2(10)<<endl;
}