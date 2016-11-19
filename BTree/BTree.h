#pragma once

#include <iostream>
using namespace std;

template<class K,int M>
struct BTreeNode
{
	//���һ���ռ䣬������ѵ��߼�
	K _keys[M];					//�ؼ�������
	BTreeNode<K,M>* _subs[M+1];	//�ӽڵ�ָ������

	BTreeNode<K,M>* _parent;
	size_t _size;				//��¼�ؼ��ֵĸ���

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
		//�����һ���ڵ�
		if(_root == NULL)
		{
			_root = new Node;
			_root->_keys[0] = key;
			_root->_size = 1;
			return true;
		}
		//���ڵ㲻Ϊ��
		pair<Node*,int> ret = Find(key);

		if(ret.second != -1)
			return false;

		Node* cur = ret.first;
		Node* sub = NULL;
		K newkey = key;
		while(1)
		{
			_InsertKey(newkey,cur,sub);
			if(cur->_size == M)	//����
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
				//�����һ�����ӽڵ�Ҳ������
				tmp->_subs[j] = cur->_subs[i];
				if(tmp->_subs[j])
					tmp->_subs[j]->_parent = tmp;
				cur->_subs[i] = NULL;

				newkey = cur->_keys[mid];
				cur->_keys[mid] = K();
				sub = tmp;
				cur->_size = mid;

				//������ѵ��Ǹ��ڵ�
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
		//��Ϊ����ʱɾ��ʧ��
		if(_root == NULL)
			return false;

		//�Ҳ�����ɾ��ʧ��
		pair<Node*,int> ret = Find(key);
		if(ret.second == -1)
			return false;

		Node* cur = ret.first;
		int pos = ret.second;		//��¼Ҫɾ����λ��
		//�жϽ�Ҫɾ���Ľڵ��Ƿ�ΪҶ�ӽڵ㣬�������Ҷ�ӽڵ㣬�Ͱ�������Ҷ�ӽڵ㴦
		if(cur->_subs[pos+1]!= NULL)//cur�ڵ���Һ��ӽڵ㲻Ϊ�գ�˵��cur����Ҷ�ӽڵ�
		{
			//�ҵ���Ҫɾ���ؼ����������������ؼ���
			Node* minkey = cur->_subs[pos+1];
			while(minkey->_subs[0])
				minkey = minkey->_subs[0];
			//���ھͿ���ת����ɾ�����minkey�ؼ���
			cur->_keys[pos] = minkey->_subs[0];
			cur = minkey;
			_MoveLeft(cur,0);
		}
		else
			_MoveLeft(cur,pos);

		//ѭ��һ����ж��Ƿ�����B������������������㣬���е���

		int mid = (M+1)/2-1;//B�������ڵ���ؼ������Ϊ([M/2]-1,M-1);[M/2]����ȡ��
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
				if(pos == 0)//�����
					_LeftAdjust(parent,cur,mid,pos);
				else
					_RightAdjust(parent,cur,mid,pos-1);
				
				cur = parent;
			}
			else			//��С������ֵ�Ļ���˵���Ѿ�����B��������������ѭ��
				break;
		}

		if(cur == _root)//�����
		{

		}
	}

protected:

	void _InsertKey(const K& key,Node* node,Node* sub)
	{
		//Ų��key�ͺ��ӽڵ�
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
		//���cur�����ֵܵĹؼ������B���ؼ���������ޣ���ͨ���������
		Node* right = parent->_subs[pos+1];
		if(right->_size > mid)
		{
			//�Ѹ��׹ؼ�������
			cur->_size++;
			cur->_keys[cur->_size-1] = parent->_keys[pos];
			parent->_keys[pos] = right->_keys[0];//�Һ�����С�ؼ�������
			//���ֵܵ������Ӹ����ֵܵ����Һ���
			cur->_subs[cur->_size] = right->_subs[0];//right�����ӵ���С�ؼ����cur�����Һ���
			if(right->_subs[0])
				right->_subs[0]->_parent = cur;

			right->_subs[0] = right->_subs[1];
			_MoveLeft(right,0);
		}
		else		//ֻ��ͨ���ϲ����
			_Merage(parent,cur,right,pos);
	}

	void _RightAdjust(Node* parent,Node* cur,int mid,int pos)
	{
		//cur��parent���ұߣ���cur���������ֵܽ��е���
		Node* left = parent->_subs[pos];
		//���cur�����ֵܹؼ������B���ؼ��������
		if(left->_size > mid)
		{
			_MoveRight(cur,0);	//������ߵ�λ�ÿճ���
			cur->_keys[0] = parent->_keys[pos];//parent����
			//���ֵܹؼ�������
			parent->_keys[pos] = left->_keys[left->_size-1];
			//���ֵܵ����Һ��Ӹ���ǰ�ڵ��������
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
	//����Ĭ��curΪ���ӣ�brotherΪ�����ֵ�
	void _Merage(Node* parent,Node* cur,Node* brother,int pos)//����cur���ϲ��ֵܽڵ�
	{
		//Ҫ�����λ��
		int i = cur->_size;
		//�Ѹ��׽ڵ�Ĺؼ����Ƶ����ӽڵ�
		cur->_keys[i] = parent->_keys[pos];
		//�����ֵܵ��������ƶ�����
		cur->_subs[i+1] = brother->_subs[0];
		if(brother->_subs[0])
			brother->_subs[0]->_parent = cur;
		i++;
		cur->_size++;

		//���ֵ�ָ�뿽������
		for(int j = 0; j<brother->_size; ++j)
		{
			cur->_keys[i] = brother->_keys[j];
			cur->_subs[i+1] = brother->_subs[j+1];
			if(brother->_subs[j+1])
				brother->_subs[j+1]->_parent = cur;

			cur->_size++;
		}
		//���ֵܽڵ��ÿ�
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