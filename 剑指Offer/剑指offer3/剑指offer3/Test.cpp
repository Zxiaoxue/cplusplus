#include<iostream>

using namespace std;
//��һ����ά�����У�ÿһ�ж����մ����ҵ�����˳������ÿһ�ж����մ��ϵ��µ�˳�����
//���һ����������������һ����ά�����һ���������ж��������Ƿ��и�����

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