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
//	int _name;		//������
//	int _arrive;		//����ʱ��
//	int _serive;		//����ʱ��
//	int _start;		//��ʼִ��ʱ��
//	int _finish;		//���ʱ��
//	int _cycling;	//��תʱ��
//	int _wi;			//��Ȩ��תʱ��
//
//	struct Node* _next;
//	Statue _statue;//״̬
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
//		printf("������\t");
//		printf("����״̬\t");
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


int TIME = 40;	//ʱ��(ʱ��Ƭ��ת)
enum Statue
{
	READY,
	BLOCK,
	RUNING,
};

typedef struct Pcb
{
	int _name;	//������
	int _atime;		//����ʱ��
	int _runtime;	//����ʱ��
	int _start;		//��ʼִ��ʱ��
	int _finish;		//���ʱ��
	int _cycling;	//��תʱ��
	int _wi;			//��Ȩ��תʱ��
	Statue _statue;	//����״̬

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
			printf("����������������̵���ʱ�䣬��������ʱ��:\n");
			scanf("%d",&_f[i]._name);
			scanf("%d",&_f[i]._atime);
			scanf("%d",&_f[i]._runtime);

		}

		Sort(amount);
		for(i = 0; i<amount; ++i)	//�޸Ľ��̵Ŀ�ʼִ��ʱ��,��תʱ�䣬��Ȩ��תʱ��
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
		cout<<"������"<<"   "<<"����ʱ��"<<"   "<<"����ʱ��"<<"	"<<"��ʼִ��ʱ��"
			<<"   "<<"���ʱ��"<<"   "<<"��תʱ��"<<"   "<<"��Ȩ��תʱ��"
			<<"   "<<"����״̬"<<endl;
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

	void FcFs()//�����ȷ���
	{
		while(!_f.empty())
		{
			int i = _f.size();

			while(i--)
			{	
				_f[0]._statue = RUNING;
				Print();
				_f.erase(_f.begin());
			}
		}

	}

	void RoundRobin(int slot)//ʱ��Ƭ��ת
	{
		for(int i = 0; i<_f.size(); ++i)
		{
			_f[i]._statue = RUNING;
			Print();
			if(_f[i]._runtime == slot)
			{
				_f.erase(_f.begin());
				i -= 1;
			}
			else if(_f[i]._runtime > slot)
			{
				Pcb tmp = _f[i];
				tmp._runtime -= slot;
				tmp._statue = BLOCK;
				_f.erase(_f.begin());
				_f.push_back(tmp);
				i-=1;
			}
			else
			{
				_f.erase(_f.begin());
				continue;
			}
		}
	}

	//����ҵ����(short job first)
	void SJF()
	{
		SortSJF();
		while(!_f.empty())
		{
			int i = _f.size();

			while(i--)
			{	
				_f[0]._statue = RUNING;
				Print();
				_f.erase(_f.begin());
			}
		}

	}
	void SortSJF()
	{
		int size = _f.size();
		for(int i = 0; i<size; ++i)
		{
			for(int j = 1; j<size-i-1; ++j)
			{
				if(_f[j]._atime <= _f[i]._finish
					&& _f[j+1]._atime <= _f[i]._finish
					&& _f[j+1]._runtime < _f[j]._runtime)
				{
					//Swap(_f[j],_f[j+1]);
					int atime =_f[j]._atime;
					_f[j]._atime=_f[j+1]._atime;
					_f[j+1]._atime=atime;

					int name=_f[j]._name;
					_f[j]._name=_f[j+1]._name;
					_f[j+1]._name=name;

					int runtime =_f[j]._runtime;
					_f[j]._runtime = _f[j+1]._runtime;
					_f[j+1]._runtime = runtime;

					int start = _f[j]._start;
					_f[j]._start = _f[j+1]._start;
					_f[j+1]._start = start;

					int finish = _f[j]._finish;
					_f[j]._finish = _f[j+1]._finish;
					_f[j+1]._finish = finish;

					Statue statue = _f[j]._statue;
					_f[j]._statue = _f[j+1]._statue;
					_f[j+1]._statue = statue;

					int cycling = _f[j]._cycling;
					_f[j]._cycling = _f[j+1]._cycling;
					_f[j+1]._cycling = cycling;

					int wi = _f[j]._wi;
					_f[j]._wi = _f[j+1]._wi;
					_f[j+1]._wi = wi;
				}
			}
		}
	}

	void Swap(Pcb pcb1,Pcb pcb2)
	{
		/*int atime = pcb1._atime;
		pcb1._atime = pcb2._atime;
		pcb2._atime = atime;*/
		swap(pcb1._atime,pcb2._atime);
		swap(pcb1._name,pcb2._name);
		swap(pcb1._runtime,pcb2._runtime);
		swap(pcb1._start,pcb2._start);
		swap(pcb1._finish,pcb2._finish);
		swap(pcb1._statue,pcb2._statue);
		swap(pcb1._cycling,pcb2._cycling);
		swap(pcb1._wi,pcb2._wi);

		//int name=pcb1._name;
		//pcb1._name=pcb2._name;
		//pcb2._name=name;
	
		//int runtime =pcb1._runtime;
		//pcb1._runtime = pcb2._runtime;
		//pcb2._runtime = runtime;

		//int start = pcb1._start;
		//pcb1._start = pcb2._start;
		//pcb2._start = start;

		//int finish = pcb1._finish;
		//pcb1._finish = pcb2._finish;
		//pcb2._finish = finish;

		//Statue statue = pcb1._statue;
		//pcb1._statue = pcb2._statue;
		//pcb2._statue = statue;

		//int cycling = pcb1._cycling;
		//pcb1._cycling = pcb2._cycling;
		//pcb2._cycling = cycling;

		//int wi = pcb1._wi;
		//pcb1._wi = pcb2._wi;
		//pcb2._wi = wi;
	}

	void Sort(int amount)
	{
		int l,k;
		int size = _f.size();
		for(int i=0;i<size;i++) //�����̵���ʱ����Ⱥ�����
		{                               //�����������ͬʱ���������Ļ�������������
			for(int j=0;j<size-i-1;j++)
			{ 
				if(_f[j]._atime>_f[j+1]._atime)
				{
					int atime =_f[j]._atime;
					_f[j]._atime=_f[j+1]._atime;
					_f[j+1]._atime=atime;

					int name=_f[j]._name;
					_f[j]._name=_f[j+1]._name;
					_f[j+1]._name=name;

					int runtime =_f[j]._runtime;
					_f[j]._runtime = _f[j+1]._runtime;
					_f[j+1]._runtime = runtime;

					int start = _f[j]._start;
					_f[j]._start = _f[j+1]._start;
					_f[j+1]._start = start;

					int finish = _f[j]._finish;
					_f[j]._finish = _f[j+1]._finish;
					_f[j+1]._finish = finish;

					Statue statue = _f[j]._statue;
					_f[j]._statue = _f[j+1]._statue;
					_f[j+1]._statue = statue;

					int cycling = _f[j]._cycling;
					_f[j]._cycling = _f[j+1]._cycling;
					_f[j+1]._cycling = cycling;

					int wi = _f[j]._wi;
					_f[j]._wi = _f[j+1]._wi;
					_f[j+1]._wi = wi;
				}
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
	//fc.RoundRobin(2);
	fc.SJF();
}