#pragma once

#define m 50
int resource;//��Դ��
int course;//������

class Banker
{
public:
	void Meun()
	{
		cout<<"�����������:"<<endl;
		cin>>course;
		cout<<"��������Դ������:"<<endl;
		cin>>resource;

		cout<<"����������������(Max):"<<endl;
		for(int i = 0; i<course; ++i)
		{
			for(int j = 0; j<resource; ++j)
			{
				cin>>Max[i][j];
				if(Max[i][j] < 0)
				{
					cout<<"�������������ݴ���!!"<<endl;
					return;
				}
			}

		}
		
		printf("�������ѷ������(Allocation):\n");

		for(int i = 0; i<course; ++i)
		{
			for(int j = 0; j<resource; ++j)
			{
				cin>>Allocation[i][j];
				if(Allocation[i][j] < 0)
				{
					cout<<"�ѷ���������ݴ���!!"<<endl;
					return;
				}
			}
		}

		cout<<"��������Դ���þ���(Avaliable):"<<endl;
		for(int i = 0; i<resource; ++i)
		{
			cin>>Avaliable[i];
			if(Avaliable[i] < 0)
			{
				cout<<"��Դ���þ������ݴ���!"<<endl;
				return;
			}
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
		cout<<"***********************************��Դ�����***********************************"<<endl;
		cout<<"���̺�            Max                 Allocation                   Need           "<<endl;
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
			cout<<Avaliable[i]<<" ";
		}

		cout<<endl<<"******************************************************************************"<<endl;
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
					if(Need[i][j] > work[j])//������ڿ��ã������Է���,ֱ������ѭ��
					{
						flag = 0;
						break;
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

		//Ч�ʵ�
		//-----------------------------------------------------------------------
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
		//}----------------------------------------------------------------------------

		int index = 0;
		while(IsSalf(work,finish,index) == true)
		{
			for(int j = 0; j<resource; ++j)
				work[j] += Allocation[index][j];		
			
			finish[index] = true;
			a[salf++] = index;

			//��ӡ�������
			cout<<"�ҵ�����:"<<index<<"	"<<"��Ҫ��Դ:";
			for(int i = 0; i<resource; ++i)
			{
				cout<<Need[index][i]<<" ";
			}
			cout<<"ϵͳ����:";
			for(int i = 0; i<resource; ++i)
			{
				cout<<work[i]<<" ";
			}
			cout<<endl;
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
			cout<<"��״̬����ȫ!"<<endl;
			return false;
		}
	}

	void Alloc()
	{
		int AllocationT[m][m];
		int AvaliableT[m];
		int NeedT[m][m];
		char c;
		cout<<"�Ƿ���Ҫ������Դ: Y or N"<<endl;
		while(cin>>c)
		{

			//��ʼ��������������ݣ������н��̵�0����Դ��ֵ��1����Դ��ֵ-----�޸�
			for(int j = 0; j<resource; ++j)
			{
				for(int i = 0; i<course; ++i)
				{
					AllocationT[j][i] = Allocation[j][i];
					NeedT[j][i] = Need[j][i];
				}
				AvaliableT[j] = Avaliable[j];
			}

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
			//�ж�������Դ���Ƿ�С��ϵͳ���ã������С�ڣ��Ǿ�ֱ�Ӵ�ӡ��������
			int x = 0;
			for(int i = 0; i<resource; ++i)
			{
				if(requst[i]>Avaliable[i])
				{
					x = 1;
					break;
				}
			}
			if(x == 1)
			{
				cout<<" "<<endl;
				continue;
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
				//������������ݣ������н��̵�0����Դ��ֵ��1����Դ��ֵ-----�޸�
				for(int j = 0; j<resource; ++j)
				{
					for(int i = 0; i<course; ++i)
					{
						Allocation[j][i] = AllocationT[j][i];
						Need[j][i] = NeedT[j][i];
					}
					Avaliable[j] = AvaliableT[j];
				}

			}
			//����ǰ�ȫ״̬����ӡ��������ǣ��ָ���ԭ��״̬
			Print();
			cout<<"�Ƿ���Ҫ������Դ: Y or N"<<endl;
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