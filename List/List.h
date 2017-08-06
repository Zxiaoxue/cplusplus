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

//14.��������ĸ��ơ�һ�������ÿ���ڵ㣬��һ��ָ��nextָ��ָ����һ���ڵ㣬
	//����һ��randomָ��ָ����������е�һ������ڵ����NULL������Ҫ��ʵ�ָ�������������ظ��ƺ��������
	


ComplexNode* MyCopyComplexNode(ComplexNode* head)
{
	if(head == NULL)
		return NULL;

	//�����ڵ�
	ComplexNode* cur = head;
	while(cur)
	{
		ComplexNode* tmp = new ComplexNode(cur->_data);
		tmp->_next = cur->_next;
		cur->_next = tmp;

		cur = cur->_next->_next;
	}

	//��randomָ��
	cur = head;
	while(cur)
	{
		ComplexNode* next = cur->_next;

		if(cur->_random)
			next->_random = cur->_random->_next;

		cur = next->_next;
	}

	ComplexNode* newHead = head->_next;
	ComplexNode* newTail = newHead;
	cur = head;

	//���Դ�ڵ�
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
	



ComplexNode* CopyComplexNode(ComplexNode* head)
	{
		if(head == NULL)
			return NULL;

		//�����ڵ�
		ComplexNode* cur = head;
		while(cur)
		{
			ComplexNode* next = cur->_next;
			ComplexNode* tmp = new ComplexNode(cur->_data);
			cur->_next = tmp;
			tmp->_next = next;

			cur = next;
		}

		//��randomָ��
		cur = head;

		while(cur)
		{
			ComplexNode* next = cur->_next;
			if(cur->_random)
				next->_random = cur->_random->_next;

			cur = cur->_next->_next;
		}	
		//���Դ�ڵ�

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
			while(cur != NULL && cur->_next != NULL)
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
	//�����������
	Node* Reverse()
	{
		if(_head == NULL)
			return NULL;
		Node* cur = _head;
		Node* newHead = NULL;
		Node* next = cur->_next;

		/*while(next != NULL)
		{
			cur->_next = newHead;
			newHead = cur;
			cur = next;
			next = cur->_next;
		}
		cur->_next = newHead;
		newHead = cur;*/
		while(cur != NULL)
		{
			cur->_next = newHead;
			newHead = cur;
			cur = next;
			if(cur != NULL)
			{
				next = cur->_next;
			}
		}
		return newHead;
	}


	//��β��ͷ��ӡ������---����stack

	void PrintTailToHead()
	{
		if(_head == NULL)
			return;
		stack<Node*> s;
		Node* cur = _head;
		while(cur)
		{
			s.push(cur);
			cur = cur->_next;
		}

		while(!s.empty())
		{
			cout<<s.top()->_data<<" ";
			s.pop();
		}
		cout<<endl;
	}
	//�ݹ�д��
	void PrintTailToHeadR()
	{
		_PrintTailToHeadR(_head);
		cout<<endl;
	}

	void _PrintTailToHeadR(Node* node)
	{
		if(node == NULL)
			return;
		_PrintTailToHeadR(node->_next);
		cout<<node->_data<<" ";
	}

	//ɾ��һ����ͷ������ķ�β�ڵ�
	void DeleteNonTail(Node* pos)
	{
		assert(pos && pos->_next);

		Node* cur = pos;
		Node* del = cur->_next;
		Node* next = del->_next;

		cur->_data = del->_data;
		cur->_next = next;
		delete del;
		del = NULL;
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


	//����ͷ�������һ����ͷ�ڵ�ǰ����һ���ڵ�
	void PushNodeNonHead(Node* pos, int data)
	{
		assert(pos);
		Node* tmp = new Node(data);
		Node* cur = pos;
		Node* next = pos->_next;
		
		//�ѽڵ㴮������
		tmp->_next = next;
		cur->_next = tmp;
		

		tmp->_data = cur->_data;
		cur->_data = data;
	}

	//������ʵ��Լɪ��
	//7.����������ð������&��������
	void ListSort()//Bubble
	{
		if(_head == NULL)
			return;
		Node* cur = _head;
		Node* next = NULL;
		Node* tail = NULL;

		while(_head != tail)
		{
			int flag = 0;
			cur = _head;
			next = cur->_next;
			while(next != tail)
			{
				if(cur->_data > next->_data)
				{
					int tmp = cur->_data;
					cur->_data = next->_data;
					next->_data = tmp;
					flag = 1;
				}
				cur = next;
				next = next->_next;
			}
			tail = cur;
			if(flag == 0)
				return;
		}
	}
	Node* Tail()
	{
		Node* tail = _head;
		while(tail->_next!= NULL)
		{
			tail = tail->_next;
		}
		return tail;
	}

	//QuickSort
	void QuickSortList()
	{
		_QuickSortList(_head,NULL);
	}

	void _QuickSortList(Node* head,Node* tail)
	{
		if(head == NULL || head == tail || head->_next == tail)//����ռ�ΪNULL������ֻ��һ���ڵ�
			return;

		Node* prev = head;
		Node* cur = head->_next;
		int key = head->_data;

		while(cur != tail)
		{
			if(cur->_data < key)
			{
				prev = prev->_next;
				if(cur != prev)
				{
					int data = cur->_data;
					cur->_data = prev->_data;
					prev->_data = data;
				}
			}
			cur = cur->_next;
		}

		int data = prev->_data;
		prev->_data = head->_data;
		head->_data = data;

		_QuickSortList(head,prev);
		_QuickSortList(prev->_next,tail);
	}

	/*void ListQuickSort()
	{
		Node* tail = Tail();
		 _ListQuickSort(_head,tail);
	}
	Node* Div(Node* head,Node* tail)
	{
		Node* left = NULL;
		Node* leftHead = NULL;
		Node* right = NULL;
		Node* rightHead = NULL;
		Node* cur = head->_next;
		Node* div = head;

		while(cur != NULL)
		{
			if(cur->_data < div->_data)
			{
				if(left)
				{
					left->_next = cur;
					left = cur;
				}
				else
				{
					left = cur;
					leftHead = cur;
				}
			}
			else
			{
				if(right)
				{
					right->_next = cur;
					right = cur;
				}
				else
				{
					right = cur;
					rightHead = cur;
				}
			}
			cur = cur->_next;
		}

		div->_next = NULL;
 		if(leftHead)
		{
			head = leftHead;
			left->_next = div;	
		}
		else
			head = div;

		if(leftHead && rightHead == NULL)
		{
			return div;
		}
		if(rightHead)
		{
			div->_next = rightHead;
			left->_next = div;
 
		}
	
		return div;
	}


	void _ListQuickSort(Node* head,Node* tail)
	{
		
		if(!head || !tail || head->_next == tail \
			|| !head->_next->_next || head->_next->_next == tail)
			return;
		Node* div = Div(head,tail);

		_ListQuickSort(head,div);
		_ListQuickSort(div,tail);
	}*/

	//8.�ϲ�������������,�ϲ�����Ȼ����
	List* Meragesort(List* l)
	{
		if(_head == NULL)
			return l;
		if(l->_head == NULL)
			return (List*)_head;

		Node* head1 = l->_head;
		Node* head2 = _head;

		if(head1->_data < head2->_data)
		{	
			_head = head1;
			head1 = head1->_next;
		}
		else
		{
			_head = head2;
			head2 = head2->_next;
		}

		Node* newTail = _head;
		while(head1 && head2)
		{
			if(head1->_data < head2->_data)
			{	
				newTail->_next = head1;
				head1 = head1->_next;
			}
			else
			{
				newTail->_next = head2;
				head2 = head2->_next;
			}
			newTail = newTail->_next;
		}

		if(head1)
			newTail->_next = head1;

		if(head2)
			newTail->_next = head2;

		return (List*)_head;
	}
	//9.���ҵ�������м�ڵ㣬Ҫ��ֻ�ܱ���һ������
	Node* FindMidList()
	{
		if(_head == NULL)
			return NULL;
		Node* fast = _head;
		Node* slow = _head;

		while(fast && fast->_next)
		{
			slow = slow->_next;
			fast = fast->_next->_next;
		}
		return slow;
	}
	//10.���ҵ�����ĵ�����k���ڵ㣬Ҫ��ֻ�ܱ���һ������
	Node* LastKNode(int k)
	{
		if(_head == NULL || k<=0)
			return NULL;
		
		int num = k;
		Node* fast = _head;
		Node* slow = _head;
		while(num-- && fast)
			fast = fast->_next;
		if(num > 0 || fast == NULL)
		{
			return NULL;
		}

		while(fast)
		{
			fast = fast->_next;
			slow = slow->_next;
		}
		return slow;
	}
	//11.�жϵ������Ƿ���������������󻷵ĳ��ȣ��󻷵���ڵ㣿
	//������ÿ���㷨��ʱ�临�Ӷ�&�ռ临�Ӷȡ�
	//�Ƿ����

	//Ϊʲôһ��ָ����һ��һ��ָ������������������һ����һ����һ���������ɲ�����
	//���軷�������ڵ㣬slow��һ��fast������������ѭ��


	//O(N)
	bool IsLoop()
	{
		bool flag = false;
		if(_head == NULL)
			return false;
		Node* slow = _head;
		Node* fast = _head->_next;

		while(slow && fast && fast->_next)
		{
			if(slow == fast)
			{
				flag = true;
				break;
			}
			slow = slow->_next;
			fast = fast->_next->_next;
		}

		return flag;
	
	}

	//���ĳ��� O(N)
	int LoopLength()
	{
		if(_head == NULL)
			return false;
		Node* slow = _head;
		Node* fast = _head->_next;

		while(slow && fast && fast->_next)
		{
			if(slow == fast)
			{
				break;
			}
			slow = slow->_next;
			fast = fast->_next->_next;
		}

		int length = 0;
		while(slow && fast && fast->_next)
		{
			length++;
			slow = slow->_next;
			fast = fast->_next->_next;

			if(slow == fast)
				break;
		}
		return length;
	}

	//������ڵ�O(N)
	Node* EntryLoop()
	{
		if(_head == NULL || _head->_next == NULL)
			return NULL;
		Node* slow = _head;
		Node* fast = _head->_next;

		while(slow && fast && fast->_next)
		{
			if(slow == fast)
			{
				break;
			}
			slow = slow->_next;
			fast = fast->_next->_next;
		}

		if(fast == NULL || fast->_next == NULL)
			return NULL;

	
		slow = _head;

		while(fast == slow)
		{
			fast = fast->_next;
			slow = slow->_next;
		}

		return slow;
	}


	//12.�ж����������Ƿ��ཻ�����ཻ���󽻵㡣����������������
	bool IsCross(List* l)
	{
		if(_head == NULL || l->_head == NULL)
			return NULL;

		Node* tmp1 = _head;
		Node* tmp2 = l->_head;
		
		while(tmp1->_next)
		{
			tmp1 = tmp1->_next;
		}

		while(tmp2->_next)
		{
			tmp2 = tmp2->_next;
		}
		
		if(tmp1 == tmp2)
			return true;

		return false;
	}
	//13.�ж����������Ƿ��ཻ�����ཻ���󽻵㡣������������ܴ������������桿
	//1.���ཻ��һ������һ��������
	//2.���ཻ������������
	//3.�ཻ���������������ཻ���ڻ���
	//4.�ཻ���������������ཻ�ڻ���
	

	Node* Head()
	{
		return _head;	
	}

	//15.��������������������ͬ�����ݡ�
	void UnionSet(Node* l1, Node* l2)
	{
		if(l1 == NULL || l2 == NULL)
			return;

		Node* tmp1 = l1;
		Node* tmp2 = l2;

		while(tmp1 && tmp2)
		{
			if(tmp1->_data == tmp2->_data)
			{
				cout<<tmp1->_data<<" ";
				tmp1 = tmp1->_next;
				tmp2 = tmp2->_next;
			}
			else if(tmp1->_data < tmp2->_data)
				tmp1 = tmp1->_next;
			else
				tmp2 = tmp2->_next;
		}
		cout<<endl;
	}


	//1.�ж����������Ƿ��ཻ�����ཻ���󽻵㡣����������������
	Node* MyIsCrossNonCircle(Node* head)
	{
		Node* first = _head;
		Node* second = head;
		int len1 = 0;
		int len2 = 0;

		while(first != NULL)
		{
			first = first->_next;
			++len1;
		}
		while(second != NULL)
		{
			second = second->_next;
			++len2;
		}
		if(first == second)
		{
			first = _head;
			second = head;
			if(len1 > len2)
			{
				int len = len1-len2;
				while(len--)
				{
					first = first->_next;
				}
			}
			else
			{
				int len = len2-len1;		
				while(len--)
				{
					second = second->_next;
				}
			}
			while(first != second)
			{
					
				first = first->_next;
				second = second->_next;
			}

			return first;
		}
		
		return NULL;
	}
	//2.�ж����������Ƿ��ཻ�����ཻ���󽻵㡣����������������������桿 
	bool MyIsCrossCircle(Node* head)
	{
		//�ж������Ƿ����
		Node* slow_ = _head;
		Node* fast_ = _head;
		int flag1 = 0;
		Node* slow = head;
		Node* fast = head;
		int flag2 = 0;

		while(fast_ && fast_->_next && slow_ && fast_ != slow_)
		{
			slow_ = slow_->_next;
			fast_ = fast_->_next->_next;
		}

		while(fast && fast->_next && slow && fast != slow)
		{
			slow = slow->_next;
			fast = fast->_next->_next;
		}

		//_head����
		if(slow_ == fast_ && slow_ != NULL)
			flag1 = 1;
		//head����
		if(slow == fast && slow != NULL)
			flag2 = 1;

		//�������������ƻ�һ�����������Ƿ񻹴���
		if(flag1 == flag2 == 1)
		{
			slow->_next = NULL;
			slow = fast = head;
			slow_ = fast_ = _head;
			flag1 = flag2 = 0;
		}
		//�ٴμ�����������Ƿ����
		//_head����
		if(slow_ == fast_ && slow_ != NULL)
			flag1 = 1;
		//head����
		if(slow == fast && slow != NULL)
			flag2 = 1;

		//һ������һ�����������϶����ཻ
		if(flag1 != flag2)
		{
			return NULL;
		}

		//������������
		if(flag1 == flag2 == 0)
		{
			//�����������һ���ڵ㲻ͬ���϶����ཻ
			if(slow_ != slow)
			{
				return NULL;
			}
			//���������ཻ���󽻵�
			slow = head;
			slow_ = _head;
			int len1 =0;
			int len2 = 0;
			while(slow_)
			{
				slow_ = slow_->_next;
				++len1;
			}
			while(slow)
			{
				slow = slow->_next;
				++len2;
			}
			int len = 0;
			if(len1 > len2)
			{
				len = len1-len2;
				while(len--)
				{
					slow_ = slow_->_next;
				}
			}
			else
			{
				len = len2-len1;
				while(len--)
				{
					slow = slow->_next;
				}
			}
			while(slow != slow_)
			{
				slow = slow->_next;
				slow_ = slow_->_next;
			}
			return slow;
		}
	}

	//ɾ����ͷ������ķ�β�ڵ�
	void DelNonHeadNonTail(Node* node)
	{
		if(node->_next == NULL)
			return;

		Node* del = node->_next;
		node->_data = del->_data;

		delete del;
		del = NULL;
	}

	//��β��ͷ��ӡ������
	void MyPrintTailToHead()
	{
		stack<Node*> s;
		s.push(_head);
		Node* cur = _head->_next;

		while(cur)
		{
			s.push(cur);
			cur = cur->_next;
		}

		while(!s.empty())
		{
			cur = s.top();
			cout<<cur->_data<<" ";
			s.pop();
		}
	}

	//MergeList �º���/����ָ�� ʵ������ͽ�����һ�ݴ���ʵ�ָ���

private:
	Node* _head;
};