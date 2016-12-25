#pragma once
#include <list>
#include <vector>
//首次适应算法
//最佳适应算法

int ALLSIZE = 512;

struct WorkNode		//作业
{
	int _num;			//区号
	int _start;		//起始地址
	int _size;	//作业大小
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
	int _num;		//空闲分区区号
	int _size;		//空闲分区大小
	int _start;		//空闲分区始址
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
		cout<<"工作分区区号"<<"	"<<"大小"<<"	"<<"始址"<<endl;
		WorkNode* work = _work;
		while(work != NULL)
		{
			cout<<work->_num<<"	"<<work->_size<<"	"<<work->_start<<endl;
			work = work->_next;
		}
	}

	void FreePrint()
	{
		
		cout<<"空闲分区区号"<<"	"<<"大小"<<"	"<<"始址"<<endl;
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
		printf("输入1------装入新作业--------\n");
		printf("输入0------回收作业----------\n");
		printf("输入-1------结束-------------\n");

		while(scanf("%d",&t)!=EOF)
		{
			int freesize = _freesize;
			int worksize = _worksize;
			if(t == 1)
			{
				FreeNode* freetmp = _free;
				printf("请输入作业大小:\n");
				scanf("%d",&size);
				flag = 0; 
				
				while(freetmp != NULL)
				{  
					if(freetmp->_size >= size)  //首次适应算法  
					{  
						flag=1;					//找到了首次适应的空闲块
						break;  
					}	

					freetmp = freetmp->_next;
				}

				if(!flag)  //flag == 0的时候内存分配失败
				{  
					printf("内存分配失败\n");
					printf("请重新输入操作\n");
				} 
				else
				{
					//将该作业加入作业区里 
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

					if(freetmp->_size == size) //该分区全部用于分配，删除该空闲分区  
					{  
						if(freetmp->_next != NULL)
							freetmp->_next = freetmp->_next->_next;
						for(j = i; j<freesize; j++)
						{
							freetmp->_num--;
							freetmp = freetmp->_next;
						}

					}  
					else  //该空闲分区部分用于分配，剩余的留在空闲分区中  
					{  
						freetmp->_start += size;  
						freetmp->_size -= size;  
					}  
				}
			}
			else if(t==0)  
			{
				printf("输入要回收的作业ID ");  
				scanf("%d",&num); 

				Destory(num);
			}
			else 
			{
				printf("操作结束\n");
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

		//找出释放的工作分区的前后是不是空闲分区---四种情况
        for(int i=0; i < _freesize;i++)  
		{  
			if(freetmp->_start > (worktmp->_start+worktmp->_size)) 
				break;

			if((freetmp->_start+freetmp->_size) == worktmp->_start)  //待回收的作业上面有空闲分区  
			{  
				front=1;
				t1=i;  
			}  
			if(freetmp->_start == (worktmp->_start+worktmp->_size))  //待回收的作业下面有空闲分区  
			{  
				behind=1;  
				t2=i;  
			}  

			freetmp = freetmp->_next;
			number = freetmp->_num;
		} 

		if(!front && !behind)  //待回收的作业上下均没有空闲分区  
		{   
			//空闲分区增加一个  
			int start = worktmp->_start;
			int size = worktmp->_size;
			number++;
			tmp = new FreeNode(size,number,start);
			tmp->_next = freetmp->_next;
			freetmp->_next = tmp;

			//改变区号
			while(tmp->_next != NULL)
			{
				tmp = tmp->_next;
				tmp->_num++;
			}
			_freesize++;

			//在作业分区中删除该作业 
			if(worktmp == _work)//首节点就是要删除的节点
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

		//待回收的作业上下均有空闲分区  
		if(front && behind)  
			middle=1;  
		if(front && !middle)  //合并待回收的作业和上面的空闲分区  
		{  
			freetmp->_size += worktmp->_size;

			//在作业分区中删除该作业 
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

		if(middle)  //合并待回收的作业和上下的空闲分区  
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

			//删除空闲分区t2  
			tmp1->_next = freetmp;
			delete tmp2;
			tmp2 = NULL;

			while(tmp1->_next != NULL)
			{
				tmp1 = tmp1->_next;
				tmp1->_num++;
			}
			_freesize--;
			  
			//在作业分区中删除该作业
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
		if(behind &&!middle) //合并待回收的作业和下面的分区  
		{  
			freetmp->_start -= worktmp->_size;
			freetmp->_size += worktmp->_size;

			//在作业分区中删除该作业
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

	//以地址递增顺序连接
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

	//最佳分区分配
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