#pragma once
#include <iostream>
#include <stdio.h>
#include <cassert>
using namespace std;

enum Type
{
	HEAD,
	VALUE,
	SUB,
};

struct GeneralizedNode
{
	Type _type;            //����
	GeneralizedNode* _next;//ָ��ͬ����һ���ڵ��ָ��
	union
	{
		int _value;
		GeneralizedNode* _subLink; //ָ���ӱ��ָ��
	};
	GeneralizedNode(Type type = HEAD, int value = 0)//���캯��
		:_type(type)
		, _next(NULL)
	{
		if (_type == VALUE)
		{
			_value = value;
		}
		else if (_type == SUB)
		{
			_subLink = NULL;
		}
	}
};

class Generalized
{
public:
	Generalized()
		:_head(NULL)
	{}
	Generalized(const char* str)
		:_head(NULL)
	{
		_head = _CreateList(str);
	}
	Generalized(const Generalized& g)
	{
		_head = _Copy(g._head);
	}
	Generalized(const Generalized& g)
	{

	}
	~Generalized()
	{
		//Destory(_head);
	}
	size_t Size(const char* str)
	{

	}
	size_t Depth(const char* str)
	{
		int count = 0;
		assert(str);
		while (*str)
		{
			if (*str == '(')
			{
				count++;
			}
			*str++;
		}
		return count;
	}

protected:
	void Print(GeneralizedNode* head);
	GeneralizedNode* _CreateList(const char*& str);
	GeneralizedNode* _Copy(GeneralizedNode* head);


protected:
	GeneralizedNode* _head;
};

class Generalized
{
public:
	Generalized()
		:_head(NULL)
	{}
	Generalized(const char* str)
		:_head(NULL)
	{
		_head = _CreatList(str);
	}
	GeneralizedNode* _Copy(GeneralizedNode* head)
	{

	}
	bool _IsValue(char ch)
	{
		if ((ch >= '0'&&ch <= '9')
			|| (ch >= 'a'&&ch <= 'z')
			|| (ch >= 'A'&&ch <= 'A'))
		{
			return true;
		}
		return false;
	}
	GeneralizedNode* _CreatList(const char*& str)
	{
		assert(*str == '(');
		++str;
		GeneralizedNode* head = new GeneralizedNode(HEAD);//newһ���ڵ���Ϊͷ�ڵ�
		GeneralizedNode* cur = head;

		while (*str)
		{
			if (_IsValue(*str))//�ж��ַ����Ƿ��ǺϷ���
			{
				cur->_next = new GeneralizedNode(VALUE, *str);
				cur = cur->_next;
				++str;
			}
			else if (*str == '(')//��������������ʹ���һ���ӱ�
			{
				GeneralizedNode* subNode = new GeneralizedNode(SUB);//����һ���ӱ�ڵ�
				cur->_next = subNode;//��curָ���ӱ�ͷ�ڵ�
				cur = cur->_next;

				subNode->_subLink = _CreatList(str);//�ݹ�ʵ���ӱ�Ĵ���
			}
			else if (*str == ')')//��������������str++
			{
				++str;
				return head;
			}
			else
			{
				*str++;//�������ַ���ֱ������
			}
		}
		//�������ߵ�û��һ��������ߵ���һ������˵������Ĺ�������
		cout << "������ַ�������" << endl;
		assert(false);
		return head;
	}
protected:
	void PrintGeneralist(GeneralizedNode* head)//��ӡ�����
	{
		GeneralizedNode* cur = head;
		while (cur)
		{
			if (cur->_type == HEAD)//ͷ�ڵ�
			{
				cout << "(";
			}
			else if (cur->_type == VALUE)//ֱ�ڵ�
			{
				cout << cur->_value;
				if (cur->_next != NULL)
				{
					cout << ",";
				}
				else
				{
					PrintGeneralist(cur->_subLink);//�ݹ��ӡ�ӱ�ڵ�
					if (cur->_next != NULL)
						cout << ")";
				}
				cur = cur->_next;
			}
			cout << ")";
		}
	}

protected:
	GeneralizedNode* _head;
};


