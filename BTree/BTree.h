#pragma once

#include <iostream>
using namespace std;

template<class K,int M>
struct BTreeNode
{
	//多给一个空间，方便分裂的逻辑
	K _keys[M];					//关键字数组
	BTreeNode<K,M>* _subs[M+1];	//子节点指针数组

	BTreeNode<K,M>* _parent;
	size_t _size;				//记录关键字的个数

	BTreeNode()
		:_parent(NULL)
		,_size(0)
	{
		for(size_t i = 0; i<M; ++i)
		{
			_keys[i] = K();
			_subs[i] = NULL;
		}

		_subs[M] = NULL;
	}

};

template<class K, int M>
class BTree
{
	typedef BTreeNode<K,M> Node;
public:
	BTree()
		:_root(NULL)
	{}

	pair<Node*,int> Find(const K& key)
	{
		Node* cur = _root;
		Node* parent = NULL;
		while(cur)
		{
			size_t i = 0;
			while(i<cur->_size)
			{
				if(key > cur->_keys[i])
					++i;
				else if(key < cur->_keys[i])
				{
					break;
				}
				else
					return pair<Node*,int>(cur,i);
			}

			parent = cur;
			cur = cur->_subs[i];
		}

		return pair<Node*,int>(parent,-1);
	}

	bool Insert(const K& key)
	{
		//插入第一个节点
		if(_root == NULL)
		{
			_root = new Node;
			_root->_keys[0] = key;
			_root->_size = 1;
			return true;
		}
		//根节点不为空
		pair<Node*,int> ret = Find(key);

		if(ret.second != -1)
			return false;

		Node* cur = ret.first;
		Node* sub = NULL;
		K newkey = key;
		while(1)
		{
			_InsertKey(newkey,cur,sub);
			if(cur->_size == M)	//分裂
			{
				Node* tmp = new Node;
				int mid = cur->_size/2;
				int i = mid+1;
				int j = 0;
				for(; i<cur->_size; ++i,++j)
				{
					tmp->_keys[j] = cur->_keys[i];
					tmp->_subs[j] = cur->_subs[i];

					if(tmp->_subs[j])
						tmp->_subs[j]->_parent = tmp;

					cur->_keys[i] = K();
					cur->_subs[i] = NULL;

					tmp->_size++;
				}
				//把最后一个孩子节点也拷过来
				tmp->_subs[j] = cur->_subs[i];
				if(tmp->_subs[j])
					tmp->_subs[j]->_parent = tmp;
				cur->_subs[i] = NULL;

				newkey = cur->_keys[mid];
				cur->_keys[mid] = K();
				sub = tmp;
				cur->_size = mid;

				//如果分裂的是根节点
				if(cur == _root)
				{
					_root = new Node;
					_root->_keys[0] = newkey;
					_root->_subs[0] = cur;
					_root->_subs[1] = sub;
					cur->_parent = _root;
					sub->_parent = _root;
					_root->_size = 1;
					return true;
				}
				cur = cur->_parent;
			}
			else
				break;
		}
		return true;
	}

	void InOrder()
	{
		_InOrder(_root);
		cout<<endl;
	}

	bool Remove(const K& key)
	{
		//树为空树时删除失败
		if(_root == NULL)
			return false;

		//找不到，删除失败
		pair<Node*,int> ret = Find(key);
		if(ret.second == -1)
			return false;

		Node* cur = ret.first;
		int pos = ret.second;		//记录要删除的位置
		//判断将要删除的节点是否为叶子节点，如果不是叶子节点，就把他换到叶子节点处
		if(cur->_subs[pos+1]!= NULL)//cur节点的右孩子节点不为空，说明cur并非叶子节点
		{
			//找到将要删除关键码的右子树的最左关键码
			Node* minkey = cur->_subs[pos+1];
			while(minkey->_subs[0])
				minkey = minkey->_subs[0];
			//现在就可以转换成删除这个minkey关键码
			cur->_keys[pos] = minkey->_subs[0];
			cur = minkey;
			_MoveLeft(cur,0);
		}
		else
			_MoveLeft(cur,pos);

		//循环一层层判断是否满足B树的条件，如果不满足，进行调整

		int mid = (M+1)/2-1;//B树除根节点外关键码个数为([M/2]-1,M-1);[M/2]向上取整
		while(1)
		{
			if(cur->_size < mid)
			{
				if(cur == _root)
					break;
				Node* parent = cur->_parent;
				int pos = 0;
				while(parent->_subs[pos]!=cur && pos<parent->_size)
					++pos;
				if(pos == 0)//左调整
					_LeftAdjust(parent,cur,mid,pos);
				else
					_RightAdjust(parent,cur,mid,pos-1);
				
				cur = parent;
			}
			else			//不小于下限值的话，说明已经满足B树的条件，跳出循环
				break;
		}

		if(cur == _root)//处理根
		{

		}
	}

protected:

	void _InsertKey(const K& key,Node* node,Node* sub)
	{
		//挪动key和孩子节点
		int i = node->_size-1;
		while(i >= 0)
		{
			if(node->_keys[i] < key)
			{
				break;
			}
			else
			{
				node->_keys[i+1] = node->_keys[i];
				node->_subs[i+2] = node->_subs[i+1];
				--i;
			}
		}

		node->_keys[i+1] = key;
		node->_subs[i+2] = sub;

		if(sub)
			sub->_parent = node;

		node->_size++;
	}

	void _LeftAdjust(Node* parent,Node* cur,int mid,int pos)
	{
		//如果cur的右兄弟的关键码大于B树关键码个数下限，则通过收养解决
		Node* right = parent->_subs[pos+1];
		if(right->_size > mid)
		{
			//把父亲关键码下移
			cur->_size++;
			cur->_keys[cur->_size-1] = parent->_keys[pos];
			parent->_keys[pos] = right->_keys[0];//右孩子最小关键码上移
			//右兄弟的最左孩子给左兄弟的最右孩子
			cur->_subs[cur->_size] = right->_subs[0];//right的左孩子的最小关键码给cur的最右孩子
			if(right->_subs[0])
				right->_subs[0]->_parent = cur;

			right->_subs[0] = right->_subs[1];
			_MoveLeft(right,0);
		}
		else		//只能通过合并解决
			_Merage(parent,cur,right,pos);
	}

	void _RightAdjust(Node* parent,Node* cur,int mid,int pos)
	{
		//cur在parent的右边，则cur与它的左兄弟进行调整
		Node* left = parent->_subs[pos];
		//如果cur的左兄弟关键码大于B树关键码的下限
		if(left->_size > mid)
		{
			_MoveRight(cur,0);	//把最左边的位置空出来
			cur->_keys[0] = parent->_keys[pos];//parent下移
			//左兄弟关键码上移
			parent->_keys[pos] = left->_keys[left->_size-1];
			//左兄弟的最右孩子给当前节点的最左孩子
			cur->_subs[0] = left->_subs[left->_size];
			if(left->_subs[left->_size])
				left->_subs[left->_size]->_parent = cur;

			left->_keys[left->_size-1] = K();
			left->_subs[left->_size] = NULL;
			left->_size--;
		}
		else
			_Merage(parent,left,cur,pos);
	}
	//这里默认cur为左孩子，brother为其右兄弟
	void _Merage(Node* parent,Node* cur,Node* brother,int pos)//保留cur，合并兄弟节点
	{
		//要插入的位置
		int i = cur->_size;
		//把父亲节点的关键码移到左孩子节点
		cur->_keys[i] = parent->_keys[pos];
		//把右兄弟的最左孩子移动过来
		cur->_subs[i+1] = brother->_subs[0];
		if(brother->_subs[0])
			brother->_subs[0]->_parent = cur;
		i++;
		cur->_size++;

		//将兄弟指针拷贝过来
		for(int j = 0; j<brother->_size; ++j)
		{
			cur->_keys[i] = brother->_keys[j];
			cur->_subs[i+1] = brother->_subs[j+1];
			if(brother->_subs[j+1])
				brother->_subs[j+1]->_parent = cur;

			cur->_size++;
		}
		//将兄弟节点置空
		if(parent->_subs[pos] == brother)
			parent->_subs[pos] = NULL;
		else
			parent->_subs[pos+1] = NULL;

		_MoveLeft(parent,pos);
		delete brother;

	}

	void _MoveLeft(Node* cur,int pos)
	{
		if(cur == NULL)
		{
			return;
		}
		int i = pos;
		for(; i<cur->_size; ++i)
		{
			cur->_keys[i] = cur->_keys[i+1];
			cur->_subs[i+1] = cur->_subs[i+2];
		}
		cur->_size--;
	}

	void _MoveRight(Node* cur,int pos)
	{
		if(cur == NULL)
			return;
		int i = cur->_size-1;
		for(; i>=pos; --i)
		{
			cur->_keys[i+1] = cur->_keys[i];
			cur->_subs[i+2] = cur->_subs[i+1];
		}
		cur->_subs[1] = cur->_subs[0];

		cur->_size++;
	}


	void _InOrder(Node* root)
	{
		if(root == NULL)
			return;
		int i = 0;
		for(; i<root->_size; ++i)
		{
			_InOrder(root->_subs[i]);
			cout<<root->_keys[i]<<" ";
		}

		_InOrder(root->_subs[i]);
	}
protected:
	Node* _root;
};

void Test()
{
	int a[] = {53,75,139,49,145,36,101};

	BTree<int,3> bt;
	int size = sizeof(a)/sizeof(a[0]);
	for(int i = 0;i<size;++i)
	{
		bt.Insert(a[i]);
	}
	bt.InOrder();
}