#include<iostream>

using namespace std;
//在一个二维数组中，每一行都按照从左到右递增的顺序排序，每一列都按照从上到下的顺序递增
//完成一个函数，输入这样一个二维数组和一个整数，判断数组中是否含有该整数

bool Find(int *a,int rows,int cols,int num)
{
	if(a == NULL)
	{
		return false;
	}
	int flag = false;
	
	if(rows>0 && cols > 0)
	{
		int row = rows-1;
		int col = 0;
		while(row<rows && col<cols)
		{
			if(a[row*cols+col] == num)
			{
				flag = true;
				break;
			}
			else if(a[row*cols+col] > num)
			{
				row--;
			}
			else
				++col;
		}
	}
	return flag;
}


int main()
{
	int a[] = {1,2,8,9,2,4,9,12,4,7,10,13,6,8,11,15};
	int *b = NULL;
	int ret = Find(b,4,4,7);
	cout<<ret<<endl;
	system("pause");
	return 0;
}