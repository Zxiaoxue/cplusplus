#pragma once

#include <vector>
#include <iostream>
using namespace std;

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
//template<class K,class V>
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
//		return key%_tables.size();
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

template<class K,class V>
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
			  int index = _HashFunc(key);
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
		 
		   size_t index = _HashFunc(key);
		   if(_tables[index] == NULL)
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
		   }

		   return NULL;
	   }

	   bool Remove(const K& key)
	   {
		   if(_size == 0)
			   return false;

		   size_t index = _HashFunc(key);

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
					   _tables[index] = cur->_next;
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
	 size_t _HashFunc(const K& key)
	 {
		 return key%_tables.size();
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
						 Insert(cur->_key,cur->_value);
						 cur = cur->_next;
					 }
				 }
			 }

			 Swap(tmp);
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
	for(int i = 0; i<sizeof(a)/sizeof(a[0]);++i)
	{
		ht.Insert(a[i],i);
	}

	HashTable<int,int> ht1(ht);

	HashTable<int,int> ht2;
	ht2 = ht1;
}