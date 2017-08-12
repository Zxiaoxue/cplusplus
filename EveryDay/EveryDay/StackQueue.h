#include <iostream>
#include <queue>
#include <stack>
#include <assert.h>
using namespace std;

//使用两个栈实现一个队列+使用两个队列实现一个栈 


template<class T> 
class Queue
{
public:
	void Push(int tmp)
	{
		s1.push(tmp);
	}

	void Pop()
	{
		if(!s2.empty())
		{
			s2.pop();
		}
		else
		{
			while(s1.size() >= 1)
			{
				int top = s1.top();
				s1.pop();
				s2.push(top);
			}
			s1.pop();
		}
	}

	int Front()
	{
		if(!s2.empty())
			break;
		else
		{
			while(!s1.empty())
			{
				int top = s1.top();
				s1.pop();
				s2.push(top);
			}
		}
		return s2.top();
	}

	int Size()
	{
		int size = 0;
		size=s1.size() + s2.size();
		
		return size;
	}


private:
	stack<int> s1;//入栈
	stack<int> s2;//出栈
};


template<class T>
class Stack
{
public:
	void Push(int tmp)
	{
		if(q1.empty() && q2.empty())
			q1.push(tmp);
		else if(!q1.empty())
			q1.push(tmp);
		else
			q2.push(tmp);
	}

	void Pop()
	{
		if(!q1.empty() && q2.empty())
		{
			while(q1.size() >= 1)
			{
				int tmp = q1.front();
				q1.pop();
				q2.push(tmp);
			}
			q1.pop();
		}
		else if(!q2.empty() && q1.empty())
		{
			while(q2.size() >= 1)
			{
				int tmp = q2..front();
				q2.pop();
				q1.push(tmp);
			}
			q2.pop();
		}

	}
	int Top()
	{
		if(!q1.empty())
		{
			while(q1.size() >= 1)
			{
				int tmp = q1.front();
				q1.pop();
				q2.push();
			}
			tmp = q1.front();
			q1.pop();
			q2.push();
			return tmp;
		}
		else
		{
			while(q2.size >= 1)
			{
				int tmp = q2.front();
				q2.pop();
				q1.push(tmp);
			}
			tmp = q2.front();
			q2.pop();
			q1.push(tmp);
			return tmp;
		}

	}
	int Size()
	{
		if(!q1.empty())
			return q1.size();
		else
			return q2.size();
	}

private:
	queue<int> q1;
	queue<int> q2;
};


//--替换字符串中的空格为$$$。要求时间复杂度为O(N) 
//将"talk is cheap show me the code"
//替换为"talk$$$is$$$cheap$$$show$$$me$$$the$$$code"。 

void Replace(char* str, int len)
{
	assert(str);

	int blank = 0;
	int i = 0;

	while(str[i] != '\0')
	{
		if(str[i] == ' ')
			blank++;
		i++;
	}

	int newlen =len + 2*blank;

	if(newlen < len)
		return;

	int oldIndex = len;
	int newIndex = newlen;

	while(oldIndex > 0 && oldIndex < newIndex)
	{
		if(str[oldIndex] == ' ')
		{
			str[newIndex--] = '$';
			str[newIndex--] = '$';
			str[newIndex--] = '$';
		}
		else 
			str[newIndex--] = str[oldIndex];

		oldIndex--;
	}

	printf("%s",str);
}


