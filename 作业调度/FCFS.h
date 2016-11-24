#include <iostream>
using namespace std;

//enum Statue
//{
//	READY,
//	RUNING,
//};
//
//typedef struct Node
//{
//	int _name;		//进程名
//	int _arrive;		//到达时间
//	int _serive;		//服务时间
//	int _start;		//开始执行时间
//	int _finish;		//完成时间
//	int _cycling;	//周转时间
//	int _wi;			//带权周转时间
//
//	struct Node* _next;
//	Statue _statue;//状态
//
//	Node(int name,int arrive = 0,int serive = 0,Statue statue = READY)
//		:_name(name)
//		,_arrive(arrive)
//		,_serive(serive)
//		,_start(0)
//		,_finish(_start+serive)
//		,_cycling(_finish-_arrive)
//		,_wi(_cycling/_start)
//		,_next(NULL)
//		,_statue(statue)
//	{}
//
//}Node;
//
//
//class Fcfs
//{
//public:
//	Fcfs()
//		:_head(NULL)
//		,_tail(NULL)
//	{}
//
//	void Print()
//	{
//		printf("进程名\t");
//		printf("进程状态\t");
//		cout<<endl;
//
//		Node* tmp = _head;
//		while(tmp)
//		{
//			printf("%d",tmp->_name);
//			printf("\t");
//			printf("%s",tmp->_statue);
//			cout<<endl;
//			tmp = tmp->_next;
//		}
//	}
//
//	void Push(int name,int arrive,int serive,Statue statue = READY)
//	{
//
//		if(_head == NULL)
//		{
//			_head = _tail = new Node(name,arrive,serive,statue);
//			return;
//		}
//		else
//		{
//			Node* tmp = new Node(name,arrive,serive,statue);
//			_tail->_next = tmp;
//			_tail = _tail->_next;
//		}
//	}
//
//	void Pop()
//	{
//		if(_head == NULL)
//			return;
//
//		Node* del = _head;
//		_head = _head->_next;
//
//		delete del;
//	}
//
//	void FcFs()
//	{
//
//	}
//
//protected:
//	Node* _head;
//	Node* _tail;
//};
//
//void Test()
//{
//	Fcfs f;
//	f.Push(1,0,1);
//
//	f.Print();
//	f.Pop();
//}

#include <queue>
#include <cassert>


int TIME = 40;	//时间(时间片轮转)
enum Statue
{
	READY,
	BLOCK,
	RUNING,
};

typedef struct Pcb
{
	int _name;	//进程名
	int _atime;		//到达时间
	int _runtime;	//服务时间
	int _start;		//开始执行时间
	int _finish;		//完成时间
	int _cycling;	//周转时间
	int _wi;			//带权周转时间
	Statue _statue;	//进程状态

	bool operator!=(Pcb f)
	{
		return _name!=f._name;
	}
	bool operator==(Pcb f)
	{
		return _name == f._name;
	}

	Pcb(int name = 0,int atime = 0,int runtime = 0,Statue statue = READY)
		:_name(name)
		,_atime(atime)
		,_runtime(runtime)
		,_start(0)
		,_finish(_start+_runtime)
		,_statue(statue)
		,_cycling(0)
		,_wi(0)
	{}

};

void Sort(vector<Pcb> f,int amount)
{
	int l,k;
	for(int i=0;i<amount;i++) //按进程到达时间的先后排序
	{                               //如果两个进程同时到达，按在屏幕先输入的先运行
		for(int j=0;j<amount-i-1;j++)
		{ 
			if(f[j]._atime>f[j+1]._atime)
			{
				l=f[j]._atime;
				f[j]._atime=f[j+1]._atime;
				f[j+1]._atime=l;

				k=f[j]._name;
				f[j]._name=f[j+1]._name;
				f[j+1]._name=k;
			}
		}
	}
}

class JobScheduling
{
public:

	JobScheduling()
	{
		int amount,i;
		printf("input a number:\n");
		scanf("%d",&amount);
		_f.resize(amount);
		for(i=0;i<_f.size();i++)
		{
			printf("请输入进程名，进程到达时间，进程运行时间:\n");
			scanf("%d",&_f[i]._name);
			scanf("%d",&_f[i]._atime);
			scanf("%d",&_f[i]._runtime);

		}

		Sort(_f,amount);
		for(i = 0; i<amount; ++i)	//修改进程的开始执行时间,周转时间，带权周转时间
		{
			if(i == 0)
				_f[i]._start = 0;
			else
				_f[i]._start = _f[i-1]._start+_f[i-1]._runtime;	

			_f[i]._finish = _f[i]._start+_f[i]._runtime;
			_f[i]._cycling = _f[i]._finish-_f[i]._atime;
			_f[i]._wi = _f[i]._cycling/_f[i]._runtime;
		}
	}

	void Print()
	{
		cout<<"进程名"<<"   "<<"到达时间"<<"   "<<"服务时间"<<"	"<<"开始执行时间"
			<<"   "<<"完成时间"<<"   "<<"周转时间"<<"   "<<"带权周转时间"
			<<"   "<<"进程状态"<<endl;
		for(int i = 0; i < _f.size();++i)
		{
			cout<<_f[i]._name<<"	  ";
			cout<<_f[i]._atime<<"	  ";
			cout<<_f[i]._runtime<<"	 ";
			cout<<_f[i]._start<<"	  ";
			cout<<_f[i]._finish<<"	  ";
			cout<<_f[i]._cycling<<"	  ";
			cout<<_f[i]._wi<<"	  ";
			if(_f[i]._statue == READY)
				cout<<"READY";
			else if(_f[i]._statue == RUNING)
				cout<<"RUNING";
			else
				cout<<"BLOCK";
			cout<<endl;
		}
	}

	void FcFs()//先来先服务
	{
		while(!_f.empty())
		{
			for(int i = 0; i<_f.size();++i)
			{	
				_f[i]._statue = RUNING;
				Print();
				_f.erase(_f.begin());
			}
		}
	}

	void RoundRobin(int slot)//时间片轮转
	{
		for(int i = 0; i<_f.size(); ++i)
		{
			_f[i]._statue = RUNING;
			Print();
			if(_f[i]._runtime == slot)
			{
				_f.erase(_f.begin());
			}
			else if(_f[i]._runtime > slot)
			{
				Pcb tmp = _f[i];
				tmp._runtime -= slot;
				tmp._statue = BLOCK;
				_f.erase(_f.begin());
				_f.push_back(tmp);
			}
			else
			{
				_f.erase(_f.begin());
				continue;
			}
		}
	}
protected:
	vector<Pcb> _f;
};

void Test()
{
	JobScheduling fc;
	//fc.FcFs();
	fc.RoundRobin(2);
}