#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <stack>
#include <list>
#include <vector>
using namespace std;

struct cell
{
	int _symbol;
	int _value;
};

enum Symbol
{
	OP_SYMBOL,
	OP_NUM,
	ADD,
	SUB,
	MUL,
	DIV,
};

void Test()
{
	cell arr[] =
	{
		{ OP_NUM, 12 },
		{ OP_NUM, 3 },
		{ OP_NUM, 4 },
		{ OP_SYMBOL, ADD },
		{ OP_SYMBOL, MUL },
		{ OP_NUM, 6 },
		{ OP_SYMBOL, SUB },
		{ OP_NUM, 8 },
		{ OP_NUM, 2 },
		{ OP_SYMBOL, DIV },
		{ OP_SYMBOL, ADD },
	};

	int i = 0;
	stack<cell> s;
	s.push(arr[0]);
	cell ret = s.top();
	for (i = 1; i<11; ++i)
	{
		cell cur = arr[i];
		if (cur._symbol == OP_NUM)
			s.push(cur);
		else if (cur._symbol == OP_SYMBOL)
		{
			int right = s.top()._value;
			s.pop();
			int left = s.top()._value;
			s.pop();
			switch (cur._value)
			{

			case ADD:
				ret._value = left + right;
				s.push(ret);
				break;
			case SUB:
				ret._value = left - right;
				s.push(ret);
				break;
			case MUL:
				ret._value = left*right;
				s.push(ret);
				break;
			case DIV:
				ret._value = left / right;
				s.push(ret);
				break;
			default:
				break;
			}
		}
	}
	cout << ret._value << endl;	
}



int main()
{
	//Test();
	//Testvector2();
	Testvector3();
	system("pause");
	return 0;
}