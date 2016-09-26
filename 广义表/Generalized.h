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
	Type _type;            //类型
	GeneralizedNode* _next;//指向同层下一个节点的指针
	union
	{
		int _value;
		GeneralizedNode* _subLink; //指向子表的指针
	};
	GeneralizedNode(Type type = HEAD, int value = 0)//构造函数
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
		GeneralizedNode* head = new GeneralizedNode(HEAD);//new一个节点作为头节点
		GeneralizedNode* cur = head;

		while (*str)
		{
			if (_IsValue(*str))//判断字符串是否是合法的
			{
				cur->_next = new GeneralizedNode(VALUE, *str);
				cur = cur->_next;
				++str;
			}
			else if (*str == '(')//如果遇到“（”就创建一个子表
			{
				GeneralizedNode* subNode = new GeneralizedNode(SUB);//创建一个子表节点
				cur->_next = subNode;//让cur指向子表头节点
				cur = cur->_next;

				subNode->_subLink = _CreatList(str);//递归实现子表的创建
			}
			else if (*str == ')')//遇到‘）’就让str++
			{
				++str;
				return head;
			}
			else
			{
				*str++;//对其他字符都直接跳过
			}
		}
		//不可能走到没这一步，如果走到这一步，就说明传入的广义表错误
		cout << "广义表字符串错误" << endl;
		assert(false);
		return head;
	}
protected:
	void PrintGeneralist(GeneralizedNode* head)//打印广义表
	{
		GeneralizedNode* cur = head;
		while (cur)
		{
			if (cur->_type == HEAD)//头节点
			{
				cout << "(";
			}
			else if (cur->_type == VALUE)//直节点
			{
				cout << cur->_value;
				if (cur->_next != NULL)
				{
					cout << ",";
				}
				else
				{
					PrintGeneralist(cur->_subLink);//递归打印子表节点
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


