#pragma once

#include <iostream>
using namespace std;
#include <string>
#include <cassert>
#include "Heap.h"
#include "UnionSet.h"


template<class V,class W>
class GraphMatrix
{
public:
	GraphMatrix(V* vertex,int size,bool isDriection = false,const W& invalid = W())
		:_vertex(new V[size])
		,_size(size)
		,_isDriection(isDriection)
	{
		_matrix = new W*[size];
		for(int i = 0; i<size; ++i)
		{
			_vertex[i] = vertex[i];
			_matrix[i] = new W[size];
		}
		for(int i = 0;i<_size;++i)
		{
			for(int j = 0; j<_size; ++j)
			{
				_matrix[i][j] = W();
			}
		}
	}

	int GetIndex(V src)
	{
		for(int i = 0; i<_size; ++i)
		{
			if(src == _vertex[i])
			{
				return i;
			}
		}
		//assert(false);
		//invalid_argument---参数异常
	}
	void AddEdg(V src,V dst,const W& w)
	{
		int index1 = GetIndex(src);
		int index2 = GetIndex(dst);

		_matrix[index1][index2] = w;
		if(_isDriection == false)
			_matrix[index2][index1] = w;
	}

	~GraphMatrix()
	{
		delete[] _vertex;
		for(int i = 0; i<_size; ++i)
		{
			delete[] _matrix[i];
		}
		delete[] _matrix;
	}
	void Print()
	{
		for(int i = 0; i<_size; ++i)
		{
			cout<<_vertex[i]<<"->";
			for(int j = 0;j<_size; ++j)
			{
				if(_matrix[i][j] != W())
				{
					cout<<_matrix[i][j];
					cout<<_vertex[j]<<"->";
				}
			}
			cout<<"NULL"<<endl;
		}
		cout<<endl;
	}
protected:
	V* _vertex;			//顶点
	W** _matrix;			//边

	int _size;			//顶点个数
	bool _isDriection;	//是有向图还是无向图
};

void TestGraphMatrix()
{
	string vertex[] = {"西安","咸阳","宝鸡","渭南","延安"};

	GraphMatrix<string,int> gm(vertex,5);

	gm.AddEdg("西安","宝鸡",300);
	gm.AddEdg("西安","咸阳",100);
	gm.AddEdg("西安","渭南",200);
	gm.AddEdg("宝鸡","延安",300);
	gm.AddEdg("渭南","宝鸡",200);

	gm.Print();

}

#include <vector>
#include <queue>

template<class V,class W>
class GraphLink
{
	struct Node
	{
		V _src;
		V _dst;
		W _w;
		Node* _next;

		Node(V src,V dst,const W& w)
			:_src(src)
			,_dst(dst)
			,_w(w)
			,_next(NULL)
		{}
	};

public:
	GraphLink(V* vertex,int size,bool isDirection = false)
		:_isDirection(isDirection)
	{
		_vertex.resize(size);
		_tables.resize(size);
		for(int i = 0; i<size; ++i)
		{
			_vertex[i] = vertex[i];
		}
	}

	int GetIndex(V src)
	{
		for(int i = 0; i<_vertex.size(); ++i)
		{
			if(src == _vertex[i])
			{
				return i;
			}
		}
		//assert(false);
		//invalid_argument---参数异常
	}

	void AddEdg(V src,V dst,const W& w)
	{
		int index1 = GetIndex(src);
		Node* tmp = new Node(src,dst,w);
		tmp->_next = _tables[index1];
		_tables[index1] = tmp;

		if(_isDirection == false)
		{
			int index2 = GetIndex(dst);
			Node* tmp = new Node(dst,src,w);
			tmp->_next = _tables[index2];
			_tables[index2] = tmp;
		}
	}

	void BFS(V src)//广度优先搜索
	{

		vector<bool> visited(_vertex.size(),false);
		_BFS(GetIndex(src),visited);

		for(int i = 0; i<_vertex.size(); ++i)
		{
			if(visited[i] == false)
				_BFS(GetIndex(_vertex[i]),visited);
		}
		cout<<"NULL"<<endl;
	}

	void _BFS(size_t index,vector<bool>& visited)
	{
		queue<size_t> q;
		q.push(index);

		while(!q.empty())
		{
			int front = q.front();
			q.pop();
			if(visited[front] == false)
			{
				cout<<_vertex[front]<<":"<<front<<"->";
				visited[front] = true;
			}
				
			Node* cur = _tables[front];
			while(cur)
			{
				if(visited[GetIndex(cur->_dst)] == false)
					q.push(GetIndex(cur->_dst));
				
				cur = cur->_next;
			}
		}
	}

	void DFS(V src)//深度优先搜索
	{
		vector<bool> visited(_vertex.size(),false);
		_DFS(GetIndex(src),visited);

		for(int i = 0; i<_vertex.size(); ++i)
		{
			if(visited[i] == false)
				_DFS(GetIndex(_vertex[i]),visited);
		}
		cout<<"NULL"<<endl;

	}
	void _DFS(size_t src,vector<bool>& visited)
	{
		cout<<_vertex[src]<<":"<<src<<"->";
		visited[src] = true;
		Node* cur = _tables[src];

		while(cur)
		{
			int index = GetIndex(cur->_dst);
			if(visited[index] == false)
			{
				_DFS(index,visited);
			}
			cur = cur->_next;
			
		}
	}

	void Print()
	{
		for(int i = 0; i<_tables.size(); ++i)
		{
			Node* cur = _tables[i];
			cout<<_vertex[i];
			while(cur)
			{
				cout<<"->"<<cur->_w<<" "<<cur->_dst;
				cur = cur->_next;
			}
			cout<<"->NULL"<<endl;
		}
	}


	//最小生成树
	bool Kruskal(GraphLink<V,W>& graph)
	{
		if(_isDirection)
			return false;

		graph._vertex = _vertex;
		graph._isDirection = _isDirection;
		size_t size = _tables.size();
		graph._tables.resize(size);

		UnionSet us(size);

		struct Compare
		{
			bool operator()(Node* l,Node* r)
			{
				return l->_w < r->_w;
			}
		};

		//建一个小堆
		Heap<Node*,Compare> minHeap;
		for(size_t i = 0; i<size; ++i)
		{
			Node* cur = _tables[i];
			while(cur)
			{
				minHeap.Push(cur);
				cur = cur->_next;
			}
		}

		int n = 0;

		while(n<size-1)
		{
			if(minHeap.Empty())
				return false;

			Node* top = minHeap.Top();
			minHeap.Pop();
			size_t root1 = us.GetRoot(top->_src);
            size_t root2 = us.GetRoot(top->_dst);

			if(root1 != root2)
			{
				graph.AddEdg(top->_src,top->_dst,top->_w);
				us.Union(top->_src,top->_dst);
				n++;
			}

		}

		return true;
	}

	//最小生成树---Prim算法
	/*bool Prim(GraphLink<V,W>& graph)
	{

	}*/

protected:
	vector<V> _vertex;	//顶点数组
	bool _isDirection;
	vector<Node*> _tables;	//邻接表
};

//void TestGraphLink()
//{
//	string vertex[6] = {"西安","咸阳","宝鸡","渭南","延安","汉中"};
//
//	GraphLink<string,int> gl(vertex,6);
//
//	gl.AddEdg("西安","宝鸡",300);
//	gl.AddEdg("西安","咸阳",100);
//	gl.AddEdg("西安","渭南",200);
//	gl.AddEdg("宝鸡","延安",300);
//	gl.AddEdg("渭南","宝鸡",200);
//
//	gl.Print();
//
//	gl.DFS("西安");
//	gl.BFS("西安");
//}


void TestKruskal()
{
	int vertex[] = {0,1,2,3,4};
	GraphLink<int,int> gl(vertex,5);
	gl.AddEdg(0,3,10);
	gl.AddEdg(0,4,20);
	gl.AddEdg(1,2,10);
	gl.AddEdg(1,3,20);
	gl.AddEdg(1,4,30);
	gl.AddEdg(2,4,40);

	gl.Print();

	cout<<gl.Kruskal(gl)<<endl;
	GraphLink<int,int> g2(vertex,5);
	cout<<gl.Kruskal(g2)<<endl;
	g2.Print();
}