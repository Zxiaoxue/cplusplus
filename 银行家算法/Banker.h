#pragma once

#define m 50
int resource;//��Դ��
int course;//������

class Banker
{
public:
	void Meun()
	{
		printf("�����������:\n");
		cin>>course;
		printf("��������Դ������:\n");
		cin>>resource;

		printf("����������������(Max):\n");
		for(int i = 0; i<course; ++i)
		{
			for(int j = 0; j<resource; ++j)
			{
				cin>>Max[i][j];
			}
		}
		
		printf("�������ѷ������(Allocation):\n");

		for(int i = 0; i<course; ++i)
		{
			for(int j = 0; j<resource; ++j)
			{
				cin>>Allocation[i][j];
			}
		}

		printf("��������Դ���þ���(Avaliable):\n");
		for(int i = 0; i<resource; ++i)
		{
			cin>>Avaliable[i];
		}

		//�����������
		for(int i = 0; i<course; ++i)
		{
			for(int j = 0; j<resource; ++j)
			{
				Need[i][j] = Max[i][j]-Allocation[i][j];
			}
		}

		Print();
		Check();//����״̬�Ƿ�Ϊ��ȫ״̬�������ȫ����

		Alloc();
	}

	void Print()
	{
		cout<<"*****************************��Դ�����**************************"<<endl;
		cout<<"���̺�**********Max************Allocation************Avaliable***"<<endl;
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

		cout<<"ϵͳ������Դ(Avaliable):"<<endl;
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
			if(finish[i] == false)//�ý����Ƿ��Ѿ����
			{
				int flag = 1;
				for(int j = 0; j<resource; ++j)
				{
					if(Need[i][j] > work[j])//������ڿ��ã������Է���
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

	bool Check()//����Ƿ�Ϊ��ȫ�����Ҵ�ӡ�������
	{
		bool finish[m] = {false};
		int work[m];//��֪���Ƿ�Ϊ��ȫ����֮ǰ���ܸı�Avaliable��ֵ��
					//����work�����޸��ж�
		for(int i = 0; i<resource; ++i)
			work[i] = Avaliable[i];

		int a[m] = {0};//������Ű�ȫ���еľ���
		int salf = 0;
		int num = course;

		//while(num--)
		//{
		//	for(int i = 0; i<course; ++i)
		//	{
		//		if(finish[i] == false)//�ý����Ƿ��Ѿ����
		//		{
		//			int flag = 1;
		//			for(int j = 0; j<resource; ++j)
		//			{
		//				if(Need[i][j] < work[j])//����С�ڿ��ã����Է���
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
			//��ӡ�������
			cout<<"�ҵ�����:"<<index<<endl;
			cout<<"��Ҫ��Դ:";
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
			cout<<"��ȫ����Ϊ:";
			//��ӡ��ȫ����
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
			cout<<"��״̬����ȫ!"<<endl;
			return false;
		}
		
	}

	void Alloc()
	{
		int AllocationT[m][m];
		int AvaliableT[m];
		int NeedT[m][m];

		//��ʼ���������������
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
		cout<<"�Ƿ���Ҫ������Դ: Y or N"<<endl;
		while(cin>>c)
		{
			int requst[m];//������Դ����
			int cou = 0;
			int res = 0;
			if(c != 'y' && c != 'Y')
			{
				cout<<"����������Դ"<<endl;
				break;
			}
			cout<<"����������Ľ��̺�:"<<endl;
			cin>>cou;

			if(cou > course)//���̺Ŵ���
			{
				cout<<"���̺Ŵ���"<<endl;
				continue;
			}

			cout<<"�������������Դ��:"<<endl;
			for(int i = 0; i<resource; ++i)
			{
				cin>>requst[i];
			}

			//�޸��������������
			for(int i = 0; i<resource; ++i)
			{
				Allocation[cou][i] += requst[i];
				Need[cou][i] = Max[cou][i]-Allocation[cou][i];
				Avaliable[i] -= requst[i];
			}

			if(Check() == false)//���ǰ�ȫ״̬�������ݸĻ���
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