#pragma once

#include <vector>
#include <string>
#include <iostream>
using namespace std;

template<class K>
struct __HashFunc
{
	size_t operator()(const K& key)
	{
		return key;
	}
};

template<>
struct __HashFunc<string>
{
	size_t BKDRHash(const char* str)
	{
		int seed = 131;
		int hash = 0;

		while(*str++)
		{
			hash = hash*seed+(*str++);
		}

		return hash;
	}

	size_t operator()(const string& str)
	{
		return BKDRHash(str.c_str());
	}
};

//enum Status
//{
//	EMPTY,
//	EXITS,
//	DELETE,
//};
//
//template<class K, class V>
//struct KVNode
//{
//	K _key;
//	V _value;
//
//	Status _status;
//
//	KVNode(const K& key = K(),const V& value = V())
//		:_key(key)
//		,_value(value)
//		,_status(EMPTY)
//	{}
//};
//
//template<class K,class V,class HashFunc = __HashFunc<K,V>>
//class HashTable
//{
//	typedef KVNode<K, V> Node;
//public:
//	HashTable()
//		:_size(0)
//	{
//		_tables.resize(0);
//	}
//
//	bool Insert(const K& key, const V& value)
//	{
//		_CheckSize();
//		size_t index = _HashFunc(key);
//
//		while(_tables[index]._status == EXITS)
//		{
//			if(_tables[index]._key == key)
//				return false;
//
//			index++;
//			if(index == _tables.size())
//				index = 0;
//		}
//
//		_tables[index]._key = key;
//		_tables[index]._value = value;
//		_tables[index]._status = EXITS;
//
//		_size++;
//		return true;
//	}
//	Node* Find(const K& key)
//	{
//		size_t index = _HushFunc(key);
//		size_t num = index;
//
//		while(_table[index].status != EMPTY)
//		{
//			if(_tables[index]._key == key)
//			{
//				if(_tables[index].status == EXITS)
//					return _tables[index];
//				else
//					return NULL;
//			}
//
//			++index;
//			if(num == index)
//				return false;
//		}
//		return NULL;
//	}
//	bool Remove(const K& key)
//	{
//		if(_tables.size() == 0)
//			return false;
//
//		Node* del = Find(key);
//		if(del)
//		{
//			del._status = DELETE;
//			--_size;
//			return true;
//		}
//		else
//			return false;
//	}
//	size_t _HashFunc(const K& key)
//	{
//		return (HushFunc()(key))%_tables.size();
//	}
//	
//	size_t _GetNextPrime(size_t num)//素数表  
//    {  
//        const int _PrimeSize= 28;             
//        static unsigned long _PrimeList[28]=
//		{
//			53,   97,	193,		389,		769,		 1543,	 3079,  
//			6151, 12289, 24593, 49157, 98317, 196613, 393241,
//			786433ul,1572869ul,3145739,6291469,12582917,25165843,50331653,
//			100663319,201326611,402653189,805306457,1610612741,3221225473,4294967291
//		};  
//        
//		for(size_t i=0;i<_PrimeSize;++i)  
//        {  
//            if(_PrimeList[i]>num)  
//                return _PrimeList[i];  
//        }  
//
//        return _PrimeList[_PrimeSize-1];  
//    } 
//	void _CheckSize()
//	{
//		if(_tables.size() == 0|| _size*10/_tables.size() == 8)
//		{
//			size_t size = _tables.size();
//			int newSize = _GetNextPrime(_tables.size());
//
//			HashTable<K,V> tmp;
//			tmp._tables.resize(newSize);
//
//			for(int i = 0; i<size; ++i)
//			{
//				if(_tables[i]._status == EXITS)
//					Insert(_tables[i]._key,_tables[i]._value);
//			}
//
//			this->Swap(tmp);
//		}
//
//	}
//
//	void Swap(HashTable<K,V> hash)
//	{
//		swap(_tables,hash._tables);
//		swap(_size,hash._size);
//	}
//
//	HashTable<K,V>(const HashTable<K,V>& ht)
//	{
//		_tables.resize( ht._tables.size());
//		for(size_t i = 0; i<ht._tables.size(); ++i)
//		{
//			if(ht._tables[i]._status == EXITS)
//				Insert(ht._tables[i]._key,ht._tables[i]._value);
//		}
//		_size = ht._size;
//	}
//
//	HashTable operator=(const HashTable<K,V> ht)
//	{
//		if(this != &ht)
//		{
//			Swap(ht);
//		}
//		return *this;
//	}
//
//	~HashTable()
//	{}
//
//protected:
//	vector<Node> _tables;
//	size_t _size;
//};
//
//void Test()
//{
//	HashTable<int,int> ht;
//	int a[] = {89,18,49,58,9};
//	for(int i = 0; i<sizeof(a)/sizeof(a[0]);++i)
//	{
//		ht.Insert(a[i],i);
//	}
//
//	HashTable<int,int> ht1(ht);
//
//	HashTable<int,int> ht2;
//	ht2 = ht1;
//}

template<class K>
struct __HashFunc
{
	size_t operator()(const K& key)
	{
		return key;
	}
};
template<>
struct __HashFunc<string>
{
	static size_t BKDRHash(const char* str)
	{
		unsigned int seed = 131;
		unsigned int hash = 0;
		while(*str)
		{
			hash = hash*seed+(*str++);
		}
		return hash;
	}

	size_t operator()(const string& str)
	{
		return BKDRHash(str.c_str());
	}
};

template<class K,class V>
struct KVNode
{
	K _key;
	V _value;
	KVNode<K,V>* _next;

	KVNode(const K& key,const V& value)
		:_key(key)
		,_value(value)
		,_next(NULL)
	{}
};

template<class K,class V,class HashFunc = __HashFunc<K>>
class HashTable
{
	typedef KVNode<K,V> Node;
public:
	HashTable()
		:_size(0)
	{
		_tables.resize(_GetNextPrime(0));
	}

	HashTable(const HashTable<K,V>& ht)
	{
		_tables.resize(ht._tables.size());

		for(int i = 0; i<ht._tables.size(); ++i)
		{
			if(ht._tables[i])
			{
				Node* cur = ht._tables[i];
				while(cur)
				{
					Insert(cur->_key,cur->_value);
					cur = cur->_next;
				}
			}
		}
		_size = ht._size;
	}

	HashTable operator=(HashTable<K,V> ht)
	{
		if(this!=&ht)
		{
			Swap(ht);
		}
		return *this;
	}

	~HashTable()
	{
		//for(int i = 0; i<_tables.size(); ++i)
		//{
		//	Node* cur = _tables[i];
		//	Node* del = NULL;
		//	while(cur)
		//	{
		//		del = cur;
		//		cur = cur->_next;
		//		delete del;
		//	}
		//}
		//_size = 0;
		////只是把size减到0，并没有释放空间
		//_tables.clear();

		//如果想释放空间，构造一个空对象与他交换
		//HashTable<K,V> empty;
		//Swap(empty);

	}

	void Swap(HashTable<K,V>& ht)
	{
		swap(_tables,ht._tables);
		swap(_size,ht._size);
	}

	size_t _GetNextPrime(size_t num)//素数表
	   {
		   const int _PrimeSize= 28;
		   static unsigned long _PrimeList[28]=
		   {
			   53,   97,	193,		389,		769,		 1543,	 3079,  
			   6151, 12289, 24593, 49157, 98317, 196613, 393241,
			   786433ul,1572869ul,3145739,6291469,12582917,25165843,50331653,
			   100663319,201326611,402653189,805306457,1610612741,3221225473,4294967291
		   };
		   
		   for(size_t i=0;i<_PrimeSize;++i)  
		   {
			   if(_PrimeList[i]>num)
				   return _PrimeList[i];
		   }  

			return _PrimeList[_PrimeSize-1];  
	   }

	   bool Insert(const K& key,const V& value)
	   {
		   _CheckSize();

		   Node* tmp = Find(key);

		   if(tmp == NULL)
		   {
			  int index = _HashFunc(key,_tables.size());
			  Node* cur = new Node(key,value);
			  cur->_next = _tables[index];
			  _tables[index] = cur;
			  ++_size;

			  return true;
		   }

		   return false;
	   }

	   Node* Find(const K& key)
	   {
		   if(_size == 0)
			   return NULL;
		 
		   size_t index = _HashFunc(key,_tables.size());
		   if(index>=0)
		   {
			   Node* cur = _tables[index];
			   while(cur)
			   {
				   if(cur->_key == key)
					   return cur;

				   cur = cur->_next;
			   }
		   }
		 /*  if(_tables[index] == NULL)
			   return NULL;
		   else
		   {
			   Node* cur = _tables[index];
			   while(cur)
			   {
				   if(cur->_key == key)
					   return cur;
				   cur = cur->_next;
			   }
		   }*/

		   return NULL;
	   }

	   bool Remove(const K& key)
	   {
		   if(_size == 0)
			   return false;

		   size_t index = _HashFunc(key,_tables.size());

		   Node* prev = NULL;
		   Node* cur = _tables[index];

		   while(cur)
		   {
			   Node* del = NULL;
			   if(cur->_key == key)
			   { 
				   del = cur;
				   if(prev == NULL)
				   {
					   _tables[index] = cur->_next;//删除头节点
				   }
				   else
				   {
					   prev->_next = cur->_next;
				   }

				   delete del;
				   --_size;
				   return true;
			   }
			   prev = cur;
			   cur = cur->_next;
		   }

		   return false;
	   }
	 size_t _HashFunc(const K& key,int size)
	 {
		 return (HashFunc()(key))%size;
	 }

	 void _CheckSize()
	 {
		 if(_tables.size() == 0||_size*10/_tables.size() == 8)
		 {
			 int size = _tables.size();
			 int newSize = _GetNextPrime(_tables.size());
			 HashTable<K,V> tmp;
			 tmp._tables.resize(newSize);

			 for(int i = 0; i<size; ++i)
			 {
				 if(_tables[i])
				 {
					 Node* cur = _tables[i];
					 while(cur)
					 {
						 //插入时有开辟节点和释放节点的浪费，太低效
						 //Insert(cur->_key,cur->_value);
						 //cur = cur->_next;
						 Node* next = cur->_next;
						 //找到新标中插入key的位置
						 int index = _HashFunc(cur->_key,newSize);
						 cur->_next = tmp._tables[index];
						 tmp._tables[index] = cur;

						 cur = next;
					 }
				 }
			 }

			 Swap(tmp);
		 }
	 }

	 
	void Print()
	{
		 for(int i = 0; i<tmp._tables.size(); ++i)
		 {
			 printf("_tables[%d]->",i);
			 Node* cur = _tables[i];
			 while(cur)
			 {
				 printf("%d->",cur->_key);
				 cur = cur->_next;
			 }
			 printf("NULL\n");
		 }
	}

protected:
	vector<Node*> _tables;
	size_t _size;
};

void Test()
{
	HashTable<int,int> ht;
	int a[] = {89,18,49,58,9};
	for(int i = 0; i<sizeof(a)/sizeof(a[0]); ++i)
	{
		ht.Insert(a[i],i);
	}

	for(int i = 0; i<53; ++i)
	{
		ht.Insert(i,i);
	}


	ht.Remove(9);
	ht.Print();

	HashTable<int,int> ht1(ht);

	HashTable<int,int> ht2;
	ht2 = ht1;
}

void Test2()
{
	string a[] = {"sort","hehe","hello","haha","sort"};
	size_t size = sizeof(a)/sizeof(a[0]);

	HashTable<string,int> st;
	for(int i = 0; i<size; ++i)
	{
		st.Insert(a[i],i);
	}

}