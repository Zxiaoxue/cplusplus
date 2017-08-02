/*************************************************************************
	> File Name: List.h
	> Author: ZX
	> Mail: 18829897183@163.com 
	> Created Time: Mon 31 Jul 2017 08:15:03 PM PDT
 ************************************************************************/

#include <iostream>
#include <assert.h>
#include<stack>
using namespace std;

struct ListNode
{
	int _data;
	ListNode* _next;
	
	ListNode(const int& data = 0)
		:_data(data)
		 ,_next(NULL)
	{}
};
typedef struct ComplexNode
{
	int _data;
	ComplexNode* _next;
	ComplexNode* _random;

	ComplexNode(const int& data)
		:_data(data)
		 ,_next(NULL)
		 ,_random(NULL)
	{}
}ComplexNode;

ComplexNode* CopyComplexNode(ComplexNode* head)
{
	if(head == NULL)
		return NULL;
	//拷贝节点
	ComplexNode* cur = head;
	while(cur)
	{
		ComplexNode* next = cur->_next;
		ComplexNode* tmp = new ComplexNode(cur->_data);
		cur->_next = tmp;
		tmp->_next = next;

		cur = next;
	}						
	//置random指针
	cur = head;

	while(cur)
	{
		ComplexNode* next = cur->_next;
		
		if(cur->_random)
			next->_random = cur->_random->_next;
		
		cur = cur->_next->_next;
	}
	//	拆分源节点
	
		ComplexNode* newHead = head->_next;
		ComplexNode* newTail = newHead;	
		cur = head;
		while(cur)											
		{
			ComplexNode* next = cur->_next;
			cur->_next = next->_next;
		
			newTail->_next = next;
			newTail = next;
		
			cur = cur->_next;
		}
		return newHead;
}
class List
{
	typedef ListNode Node;
public:
	List()
		:_head(NULL)
	{}
	void Push(int data)
	{
		Node* tmp = new Node(data);
		if(_head == NULL)
			_head = tmp;
		else
		{
			Node* cur = _head;
			{
				cur = cur->_next;
			}
			cur->_next = tmp;
		}
	}

	void Print()
	{
		if(_head == NULL)
			return;
		Node* cur = _head;
		while(cur)
		{
			cout<<cur->_data<<" ";
			cur = cur->_next;
		}
		cout<<endl;
	}

	Node* Find(int data)
	{
		if(_head == NULL)
			return NULL;
		Node* cur = _head;
		while(cur != NULL)
		{
			if(cur->_data == data)
				return cur;
			cur = cur->_next;
		}
	}


	void Delete(Node* node)
	{
		if(_head == NULL)
			return NULL;

		Node* del = find(node);

		if(del == NULL)
			return;
		else
		{
			delete del;
			del = NULL;
		}

	}

