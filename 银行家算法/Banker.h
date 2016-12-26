#pragma once

#define m 50
int resource;//资源数
int course;//进程数

class Banker
{
public:
	void Meun()
	{
		printf("请输入进程数:\n");
		cin>>course;
		printf("请输入资源种类数:\n");
		cin>>resource;

		printf("请输入最大需求矩阵(Max):\n");
		for(int i = 0; i<course; ++i)
		{
			for(int j = 0; j<resource; ++j)
			{
				cin>>Max[i][j];
			}
		}
		
		printf("请输入已分配矩阵(Allocation):\n");

		for(int i = 0; i<course; ++i)
		{
			for(int j = 0; j<resource; ++j)
			{
				cin>>Allocation[i][j];
			}
		}

		printf("请输入资源可用矩阵(Avaliable):\n");
		for(int i = 0; i<resource; ++i)
		{
			cin>>Avaliable[i];
		}

		//计算需求矩阵
		for(int i = 0; i<course; ++i)
		{
			for(int j = 0; j<resource; ++j)
			{
				Need[i][j] = Max[i][j]-Allocation[i][j];
			}
		}

		Print();
		Check();//检查该状态是否为安全状态，输出安全序列

		Alloc();
	}

	void Print()
	{
		cout<<"*****************************资源分配表**************************"<<endl;
		cout<<"进程号**********Max************Allocation************Avaliable***"<<endl;
		for(int i = 0; i<course; ++i)
		{
			cout<<i<<"		";
			for(int j = 0; j<resource; ++j)
			{
				cout<<Max[i][j]<<"  ";
			}
			cout<<"		";
			for(int j = 0; j<resource; ++j)
			{
				cout<<Allocation[i][j]<<"  ";
			}
			cout<<"		";
			for(int j = 0; j<resource; ++j)
			{
				cout<<Need[i][j]<<"  ";
			}
			cout<<endl;
		}

		cout<<"系统可用资源(Avaliable):"<<endl;
		for(int i = 0; i<resource; ++i)
		{
			cout<<Avaliable[i]<<endl;
		}

		cout<<"*****************************************************************"<<endl;
	}

	bool IsSalf(int* work,bool* finish,int& index)
	{
		for(int i = 0; i<course; ++i)
		{
			if(finish[i] == false)//该进程是否已经完成
			{
				int flag = 1;
				for(int j = 0; j<resource; ++j)
				{
					if(Need[i][j] > work[j])//需求大于可用，不可以分配
					{
						flag = 0;
					}
				}

				if(flag == 1)
				{
					index = i;
					return true;
				}
			}
		}
		return false;
	}

	bool Check()//检查是否为安全序列且打印计算过程
	{
		bool finish[m] = {false};
		int work[m];//不知道是否为安全序列之前不能改变Avaliable的值，
					//先用work矩阵修改判断
		for(int i = 0; i<resource; ++i)
			work[i] = Avaliable[i];

		int a[m] = {0};//用来存放安全序列的矩阵
		int salf = 0;
		int num = course;

		//while(num--)
		//{
		//	for(int i = 0; i<course; ++i)
		//	{
		//		if(finish[i] == false)//该进程是否已经完成
		//		{
		//			int flag = 1;
		//			for(int j = 0; j<resource; ++j)
		//			{
		//				if(Need[i][j] < work[j])//需求小于可用，可以分配
		//				{
		//					a[salf++] = i;

		//					for(int k = 0; k<resource; ++k)
		//						work[k] += Avaliable[k];

		//					finish[i] = true;
		//				}
		//			}

		//		}
		//	}
		//}

		int index = 0;
		while(IsSalf(work,finish,index) == true)
		{
			for(int j = 0; j<resource; ++j)
			{
				work[j] += Allocation[index][j];
			}		
			
			finish[index] = true;
			a[salf++] = index;
			//打印计算过程
			cout<<"找到进程:"<<index<<endl;
			cout<<"需要资源:";
			for(int i = 0; i<resource; ++i)
			{
				cout<<Need[index][i]<<" ";
			}
		}

		int flag = 1;
		for(int i = 0; i<course; ++i)
		{
			if(finish[i] == false)
				flag = 0;
		}

		if(flag == 1)
		{
			cout<<"安全序列为:";
			//打印安全序列
			for(int i = 0; i<salf; ++i)
			{
				cout<<"P"<<a[i]<<" ";
			}
			cout<<endl;
			return true;
		}
		else
		{
			Print();
			cout<<"该状态不安全!"<<endl;
			return false;
		}
		
	}

	void Alloc()
	{
		int AllocationT[m][m];
		int AvaliableT[m];
		int NeedT[m][m];

		//初始化三个矩阵的数据
		for(int i = 0; i<course; ++i)
		{
			for(int j = 0; j<resource; ++j)
			{
				AllocationT[i][j] = Allocation[i][j];
				NeedT[i][j] = Need[i][j];
			}
		}

		for(int i = 0; i<resource; ++i)
		{
			AvaliableT[i] = Avaliable[i];
		}

		char c;
		cout<<"是否还需要请求资源: Y or N"<<endl;
		while(cin>>c)
		{
			int requst[m];//请求资源矩阵
			int cou = 0;
			int res = 0;
			if(c != 'y' && c != 'Y')
			{
				cout<<"不再请求资源"<<endl;
				break;
			}
			cout<<"请输入请求的进程号:"<<endl;
			cin>>cou;

			if(cou > course)//进程号错误
			{
				cout<<"进程号错误"<<endl;
				continue;
			}

			cout<<"请输入请求的资源数:"<<endl;
			for(int i = 0; i<resource; ++i)
			{
				cin>>requst[i];
			}

			//修改三个矩阵的数据
			for(int i = 0; i<resource; ++i)
			{
				Allocation[cou][i] += requst[i];
				Need[cou][i] = Max[cou][i]-Allocation[cou][i];
				Avaliable[i] -= requst[i];
			}

			if(Check() == false)//不是安全状态，将数据改回来
			{
				for(int i = 0; i<course; ++i)
				{
					for(int j = 0; j<resource; ++j)
					{
						Allocation[i][j] = AllocationT[i][j];
						Need[i][j] = NeedT[i][j];
					}
				}

				for(int i = 0; i<resource; ++i)
				{
					Avaliable[i] = AvaliableT[i];
				}
			}

		}
	}

protected:
	int Max[m][m];
	int Allocation[m][m];
	int Avaliable[m];
	int Need[m][m];
};

void Test()
{
	Banker b;
	b.Meun();
}