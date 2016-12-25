#pragma once
#include <list>
#include <vector>
//�״���Ӧ�㷨
//�����Ӧ�㷨

int ALLSIZE = 512;

struct WorkNode		//��ҵ
{
	int _num;			//����
	int _start;		//��ʼ��ַ
	int _size;	//��ҵ��С
	WorkNode* _next;

	WorkNode(int size = 0,int num = 0,int start = 0)
		:_size(size)
		,_num(num)
		,_start(start)
		,_next(NULL)
	{}

};

struct FreeNode
{
	int _num;		//���з�������
	int _size;		//���з�����С
	int _start;		//���з���ʼַ
	FreeNode* _next;

	FreeNode(int size = ALLSIZE,int num = 0,int start = 0)
		:_size(size)
		,_num(num)
		,_start(start)
		,_next(NULL)
	{}
};

class PartAllocation
{
public:
	PartAllocation()	
		:_work(NULL)
		,_worksize(0)
		,_freesize(1)
	{
		_free = new FreeNode();
	}

	void WorkPrint()
	{
		int size = _worksize;
		cout<<"������������"<<"	"<<"��С"<<"	"<<"ʼַ"<<endl;
		WorkNode* work = _work;
		while(work != NULL)
		{
			cout<<work->_num<<"	"<<work->_size<<"	"<<work->_start<<endl;
			work = work->_next;
		}
	}

	void FreePrint()
	{
		
		cout<<"���з�������"<<"	"<<"��С"<<"	"<<"ʼַ"<<endl;
		FreeNode* free = _free;
		while(free != NULL)
		{
			cout<<free->_num<<"	"<<free->_size<<"	"<<free->_start<<endl;
			free = free->_next;
		}
	}

	void FF()
	{
		int i,j,k,t,size,flag,num;  
		 
		int t1,t2;    
		FreePrint();  
		printf("����1------װ������ҵ--------\n");
		printf("����0------������ҵ----------\n");
		printf("����-1------����-------------\n");

		while(scanf("%d",&t)!=EOF)
		{
			int freesize = _freesize;
			int worksize = _worksize;
			if(t == 1)
			{
				FreeNode* freetmp = _free;
				printf("��������ҵ��С:\n");
				scanf("%d",&size);
				flag = 0; 
				
				while(freetmp != NULL)
				{  
					if(freetmp->_size >= size)  //�״���Ӧ�㷨  
					{  
						flag=1;					//�ҵ����״���Ӧ�Ŀ��п�
						break;  
					}	

					freetmp = freetmp->_next;
				}

				if(!flag)  //flag == 0��ʱ���ڴ����ʧ��
				{  
					printf("�ڴ����ʧ��\n");
					printf("�������������\n");
				} 
				else
				{
					//������ҵ������ҵ���� 
					int start = 0;
					WorkNode* worktmp = _work;
					if(_work == NULL)
						 _work = new WorkNode(size,_worksize,start);
					else
					{
						while(worktmp->_next != NULL)
						{
							worktmp = worktmp->_next;
						}
						start = freetmp->_start;
						
						worktmp->_next = new WorkNode(size,_worksize,start);
					}
					_worksize++;

					if(freetmp->_size == size) //�÷���ȫ�����ڷ��䣬ɾ���ÿ��з���  
					{  
						if(freetmp->_next != NULL)
							freetmp->_next = freetmp->_next->_next;
						for(j = i; j<freesize; j++)
						{
							freetmp->_num--;
							freetmp = freetmp->_next;
						}

					}  
					else  //�ÿ��з����������ڷ��䣬ʣ������ڿ��з�����  
					{  
						freetmp->_start += size;  
						freetmp->_size -= size;  
					}  
				}
			}
			else if(t==0)  
			{
				printf("����Ҫ���յ���ҵID ");  
				scanf("%d",&num); 

				Destory(num);
			}
			else 
			{
				printf("��������\n");
				break;
			}

			SortFF();
			//SortBF();
		}
	}

	void Destory(int num)
	{
		int	front = 0;
		int middle = 0;
		int behind = 0; 
		int t1,t2;
		int worksize = _worksize;
		int freesize  = _freesize;
		FreeNode* tmp = NULL;
		WorkNode* worktmp = _work;
		FreeNode* freetmp = _free;
		int number = freetmp->_num;

		for(int i = 0; i<num; ++i)
		{
			worktmp = worktmp->_next;
		}

		//�ҳ��ͷŵĹ���������ǰ���ǲ��ǿ��з���---�������
        for(int i=0; i < _freesize;i++)  
		{  
			if(freetmp->_start > (worktmp->_start+worktmp->_size)) 
				break;

			if((freetmp->_start+freetmp->_size) == worktmp->_start)  //�����յ���ҵ�����п��з���  
			{  
				front=1;
				t1=i;  
			}  
			if(freetmp->_start == (worktmp->_start+worktmp->_size))  //�����յ���ҵ�����п��з���  
			{  
				behind=1;  
				t2=i;  
			}  

			freetmp = freetmp->_next;
			number = freetmp->_num;
		} 

		if(!front && !behind)  //�����յ���ҵ���¾�û�п��з���  
		{   
			//���з�������һ��  
			int start = worktmp->_start;
			int size = worktmp->_size;
			number++;
			tmp = new FreeNode(size,number,start);
			tmp->_next = freetmp->_next;
			freetmp->_next = tmp;

			//�ı�����
			while(tmp->_next != NULL)
			{
				tmp = tmp->_next;
				tmp->_num++;
			}
			_freesize++;

			//����ҵ������ɾ������ҵ 
			if(worktmp == _work)//�׽ڵ����Ҫɾ���Ľڵ�
			{
				_work = _work->_next;
			}
			else
			{
				if(worktmp->_next != NULL)
				{
					worktmp->_next = worktmp->_next->_next;
				}
				else
				{
					WorkNode* delfront = _work;
					while(delfront->_next != worktmp)
					{
						delfront = delfront->_next;
					}
					delfront->_next = worktmp->_next;
					delete worktmp;
					worktmp = NULL;

					while(delfront->_next != NULL)
					{
						delfront = delfront->_next;
						delfront->_num--;
					}

				}
			}
			_worksize--;
		} 

		//�����յ���ҵ���¾��п��з���  
		if(front && behind)  
			middle=1;  
		if(front && !middle)  //�ϲ������յ���ҵ������Ŀ��з���  
		{  
			freetmp->_size += worktmp->_size;

			//����ҵ������ɾ������ҵ 
			if(worktmp->_next != NULL)
			{
				worktmp->_next = worktmp->_next->_next;
			}
			else
			{
				WorkNode* delfront = _work;
				while(delfront->_next == worktmp)
				{
					delfront = delfront->_next;
				}
				delfront->_next = worktmp->_next;
				delete worktmp;
				worktmp = NULL;

				while(delfront != NULL)
				{
					delfront = delfront->_next;
					delfront->_num--;
				}

			}
			_worksize--;
		}  

		if(middle)  //�ϲ������յ���ҵ�����µĿ��з���  
		{  
			FreeNode* tmp1 = _free;
			FreeNode* tmp2 = _free;
			for(int i = 0; i<t1; ++i)
			{
				tmp1 = tmp1->_next;
			}
			for(int i = 0; i<t2; ++i)
			{
				tmp2 = tmp2->_next;
			}

			int size = tmp1->_size+tmp2->_size+worktmp->_size;
			tmp1->_size = size;

			//ɾ�����з���t2  
			tmp1->_next = freetmp;
			delete tmp2;
			tmp2 = NULL;

			while(tmp1->_next != NULL)
			{
				tmp1 = tmp1->_next;
				tmp1->_num++;
			}
			_freesize--;
			  
			//����ҵ������ɾ������ҵ
			if(worktmp->_next != NULL)
			{
				worktmp->_next = worktmp->_next->_next;
			}
			else
			{
				WorkNode* delfront = _work;
				while(delfront->_next == worktmp)
				{
					delfront = delfront->_next;
				}
				delfront->_next = worktmp->_next;
				delete worktmp;
				worktmp = NULL;

				while(delfront != NULL)
				{
					delfront = delfront->_next;
					delfront->_num--;
				}

			}
			_worksize--;
			  
		}  
		if(behind &&!middle) //�ϲ������յ���ҵ������ķ���  
		{  
			freetmp->_start -= worktmp->_size;
			freetmp->_size += worktmp->_size;

			//����ҵ������ɾ������ҵ
			if(worktmp->_next != NULL)
			{
				worktmp->_next = worktmp->_next->_next;
			}
			else
			{
				WorkNode* delfront = _work;
				while(delfront->_next == worktmp)
				{
					delfront = delfront->_next;
				}
				delfront->_next = worktmp->_next;
				delete worktmp;
				worktmp = NULL;

				while(delfront != NULL)
				{
					delfront = delfront->_next;
					delfront->_num--;
				}

			}
			_worksize--;
		}  
	}

	//�Ե�ַ����˳������
	void SortFF()
	{
		WorkNode* tmp = _work;
		WorkNode* next = tmp->_next;
		FreeNode* freetmp = _free;
		FreeNode* freenext = freetmp->_next;
		while(tmp != NULL)
		{
			next = tmp->_next;
			while(next != NULL)
			{
				if(tmp->_start > next->_start)
				{
					swap(tmp->_size,next->_size);
					swap(tmp->_start,next->_start);
				}
				next = next->_next;
			}
			tmp = tmp->_next;
		}

		while(freetmp != NULL)
		{
			freenext = freetmp->_next;
			while(freenext != NULL)
			{
				if(freetmp ->_start > freenext->_start)
				{
					swap(freetmp->_size,freenext->_size);
					swap(freetmp->_start,freenext->_start);
				}
				freenext = freenext->_next;
			}

			freetmp = freetmp->_next;
		}

	}

	//��ѷ�������
	void SortBF()
	{
		WorkNode* tmp = _work;
		WorkNode* next = tmp->_next;
		FreeNode* freetmp = _free;
		FreeNode* freenext = freetmp->_next;
		while(tmp != NULL)
		{
			next = tmp->_next;
			while(next != NULL)
			{
				if(tmp->_size > next->_size)
				{
					swap(tmp->_size,next->_size);
					swap(tmp->_start,next->_start);
				}
				next = next->_next;
			}
			tmp = tmp->_next;
		}

		while(freetmp != NULL)
		{
			freenext = freetmp->_next;
			while(freenext != NULL)
			{
				if(freetmp ->_size > freenext->_size)
				{
					swap(freetmp->_size,freenext->_size);
					swap(freetmp->_start,freenext->_start);
				}
				freenext = freenext->_next;
			}

			freetmp = freetmp->_next;
		}

	}

protected:
	WorkNode* _work;
	FreeNode* _free;
	int _worksize;
	int _freesize;
};

void TestFF()
{
	PartAllocation ff;

	ff.FF();
	ff.BF();

	ff.FreePrint();
	ff.WorkPrint();

}