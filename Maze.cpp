#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <assert.h>
#include <stack>
using namespace std;

#define N 10

struct Pos
{
	int _row;
	int _col;
};

//void GetMaze(int a[][N],int n)
void GetMaze(int *a, int n)
{
	assert(a);
	FILE* fout = fopen("D:\\vc++6.0\\MyProjects\\迷宫\\Maze.txt", "r");
	assert(fout);

	for (int i = 0; i < n;i++)
	{
		for (int j = 0; j < n;)
		{
			char tmp = fgetc(fout);
			if (tmp == '0' || tmp == '1')
			{
				a[i*n+j] = tmp-'0';
				j++;
			}
		}

	}
}

void PrintMaze(int* a,int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << a[i*n + j] << " ";
		}

		cout << endl;
	}

	cout << endl;
}

bool CheckIsAccess(int* a, int n, Pos& next)
{
	int row = next._row;
	int col = next._col;

	if (row >= 0 && row < n
		&&col >= 0 && col < n
		&&a[row*n + col] == 0)
	{
		return true;
	}
	return false;
}


bool SearchMazePath(int* a, int n, Pos enrty,
	stack<Pos>& paths)
{
	assert(a);

	paths.push(enrty);
	
	while (!paths.empty())
	{
		Pos cur = paths.top();
		a[cur._row*n + cur._col] = 2;

		if (cur._row == n - 1)
		{
			return true;
		}
		//up
		Pos next = cur;
		next._row--;
		if (CheckIsAccess(a, n, next))
		{
			paths.push(next);
			if (cur._row == next._row
				&&cur._col == next._col)
			{
				a[cur._row*n + cur._col] = 3;
			}
			continue;
		}

		//down
		next = cur;
		next._row++;
		if (CheckIsAccess(a, n, next))
		{
			paths.push(next);
			if (cur._row == next._row
				&&cur._col == next._col)
			{
				a[cur._row*n + cur._col] = 3;
			}
			continue;
		}
		
		//left
		next = cur;
		next._col--;
		if (CheckIsAccess(a, n, next))
		{
			paths.push(next);
			if (cur._row == next._row
				&&cur._col == next._col)
			{
				a[cur._row*n + cur._col] = 3;
			}
			continue;
		}

		//right
		next = cur;
		next._col++;
		if (CheckIsAccess(a, n, next))
		{
			paths.push(next);
			if (cur._row == next._row
				&&cur._col == next._col)
			{
				a[cur._row*n + cur._col] = 3;
			}
			continue;
		}

		paths.pop();
	}
	return false;
}

void Test()
{
	int a[N][N] = {};
	PrintMaze((int *)a, N);
	GetMaze((int *)a, N);

	stack<Pos> paths;
	Pos entry = { 2, 0 };
	cout << "是否有通路？" << SearchMazePath((int*)a, N, entry, paths) << false << endl;

	PrintMaze((int*)a, N);
}

int main()
{
	Test();
	system("pause");
	return 0;
}