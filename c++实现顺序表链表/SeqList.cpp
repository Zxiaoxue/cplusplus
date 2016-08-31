//#define _CRT_SECURE_NO_WARNINGS 1
//
//#include <iostream>
//using namespace std;
//
//#define DataType int
//
//class SeqList
//{
//	friend ostream& operator<< (ostream& os, SeqList& seq);
//
//public:
//	SeqList()
//		:_capacity(0)
//		,_size(0)
//		,_pdata(NULL)
//	{}
//
//	SeqList(const SeqList& s)
//	{
//		_pdata = new DataType[_capacity];
//		memcpy(_pdata, s._pdata, s._size*sizeof(DataType));
//
//		/*for (int i = 0; i < l._size; i++)
//		{
//			tmp[i] = l._pdata[i];
//		}*/
//		//_pdata = tmp;
//		_size = s._size;
//		_capacity = s._capacity;
//
//	}
//
//	SeqList& operator=(const SeqList& s)
//	{
//		if (this != &s)
//		{
//			DataType* tmp = new DataType[_capacity];
//			memcpy(tmp, s._pdata, s._size*sizeof(DataType));
//			/*for (int i = 0; i < l._size; i++)
//			{
//				tmp[i] = l._pdata[i];
//			}*/
//			delete[] _pdata;
//			_pdata = tmp;
//			_size = s._size;
//			_capacity = s._capacity;
//		}
//		return *this;
//	}
//
//	~SeqList()
//	{
//		if (_pdata)
//		{
//			delete[] _pdata;
//			_pdata = NULL;
//
//		}
//		_size = 0;
//		_capacity = 0;
//	}
//public:
//	bool Empty()
//	{
//		return _size == 0;
//	}
//
//	int Size()
//	{
//		return _size;
//	}
//
//	void PushBack(const DataType& x)
//	{
//		_CheckCapacity();
//		_pdata[_size++] = x;
//	}
//
//	void PushFront(DataType x)
//	{
//		_CheckCapacity();
//		for (int i = _size; i > 0; --i)
//		{
//			_pdata[i] = _pdata[i-1];
//		}
//		_pdata[0] = x;
//		++_size;
//	}
//
//	void PopFront()
//	{
//		if (Empty())
//		{
//			return;
//		}
//		else
//		{
//			for (int i = 0; i < _size; i++)
//			{
//				_pdata[i] = _pdata[i + 1];
//			} 
//			--_size;
//		}
//		
//	}
//
//	void PopBack()
//	{
//		--_size;
//	}
//
//	void Sort()
//	{
//		int i = 0;
//		int j = 0;
//		for (i = 0; i < _size-1; i++)
//		{
//			for (j = 0; j < _size - i-1; j++)
//			{
//				if (_pdata[j]>_pdata[j+1])
//				{
//					DataType tmp = _pdata[j];
//					_pdata[j] = _pdata[j+1];
//					_pdata[j+1] = tmp;
//				}
//			}
//		}
//	}
//
//	void Insert(int pos, DataType x)
//	{
//		_CheckCapacity();
//
//		for (int i = _size; i > pos; i--)
//		{
//			_pdata[_size] = _pdata[_size - 1];
//		}
//		_pdata[pos] = x;
//	}
//
//	int Find(const DataType& data)
//	{
//		int i = 0;
//		for (i = 0; i < _size; i++)
//		{
//			if (_pdata[i] == data)
//			{
//				return i;
//			}
//		}
//
//		return -1;
//	}
//
//	void Erase(int pos)
//	{
//		if (Empty())
//		{
//			return;
//		}
//		else
//		{
//			for (int i = pos; i < _size; i++)
//			{
//				_pdata[i] = _pdata[i + 1];
//			}
//		}
//		
//	}
//
//	void Remove(DataType x)
//	{
//		if (Empty())
//		{
//			return;
//		}
//		else
//		{
//			for (int i = 0; i < _size; i++)
//			{
//				if (_pdata[i] == x)
//				{
//					for (int j = i; j < _size; j++)
//					{
//						_pdata[j] = _pdata[j + 1];
//					}
//					--_size;
//					return;
//				}
//			}
//		}
//	}
//
//	void RemoveAll(DataType x)
//	{
//		if (Empty())
//		{
//			return;
//		}
//		else
//		{
//			for (int i = 0; i < _size; i++)
//			{
//				while (_pdata[i] == x)
//				{
//					for (int j = i; j < _size; j++)
//					{
//						_pdata[j] = _pdata[j + 1];
//					}
//					--_size;
//				}
//			}
//		}
//	}
//
//	void _CheckCapacity()
//	{
//		
//		if (_size >= _capacity)
//		{
//			int newCapacity = _capacity * 2 + 3;
//			DataType* tmp = new DataType[newCapacity];
//			memcpy(tmp, _pdata, _size*sizeof(DataType));
//		/*	for (int i = 0; i < _size; i++)
//			{
//				tmp[i] = _pdata[i];
//			}*/
//			delete[] _pdata;
//			_pdata = tmp;
//			_capacity = newCapacity;
//		}
//	}
//
//private:
//	int _size;
//	int _capacity;
//	DataType* _pdata;
//
//};
//
//ostream& operator<<(ostream& os, SeqList& seq)
//{
//	for (int i = 0; i < seq._size; i++)
//	{
//		os << seq._pdata[i] << " ";
//	}
//	return os;
//}
//
//void Test1()
//{
//	SeqList seq;
//	seq.PushBack(0);
//	seq.PushBack(1);
//	seq.PushBack(2);
//	seq.PushBack(3);
//	seq.PushBack(4);
//	seq.PushBack(5);
//	seq.PushFront(1);
//	seq.PushFront(2);
//	seq.PushFront(3);
//	seq.PushFront(4);
//	seq.PushFront(5);
//
//	cout << seq << endl;
//}
//
//void Test2()
//{
//	SeqList seq;
//	seq.PushBack(0);
//	seq.PushBack(1);
//	seq.PushBack(2);
//	seq.PushBack(3);
//	seq.PushBack(4);
//	seq.PushBack(5);
//
//	//seq.PopBack();
//	//seq.PopBack();
//	//seq.PopBack();
//	//seq.PopBack();
//	//seq.PopBack();
//	//seq.PopBack();
//
//	seq.PopFront();
//	seq.PopFront();
//	seq.PopFront();
//	seq.PopFront();
//
//
//	cout << seq << endl;
//}
//
//void Test3()
//{
//	SeqList seq;
//	seq.PushBack(0);
//	seq.PushBack(2);
//	seq.PushBack(4);
//	seq.PushBack(6);
//	seq.PushBack(8);
//	seq.PushBack(10); 
//	seq.PushBack(2);
//	seq.PushBack(1);
//	seq.PushBack(3);
//	seq.PushBack(2);
//	seq.PushBack(5);
//	seq.PushBack(7);
//	seq.PushBack(9);
//	seq.PushBack(11);
//
//	seq.Sort();
//	cout << seq << endl;
//
//	seq.Remove(2);
//	cout << seq << endl;
//
//	seq.RemoveAll(2);
//	cout << seq << endl;
//
//}
//
//void Test4()
//{
//	SeqList seq;
//	seq.PushBack(0);
//	seq.PushBack(2);
//	seq.PushBack(4);
//	seq.PushBack(6);
//	seq.PushBack(8);
//	seq.PushBack(10);
//	seq.PushBack(1);
//	seq.PushBack(3);
//	seq.PushBack(5);
//	seq.PushBack(7);
//	seq.PushBack(9);
//	seq.PushBack(11);
//
//	cout << seq.Empty() << endl;
//	cout << seq.Size() << endl;
//
//	seq.Insert(3, 2);
//	cout << seq << endl;
//	seq.Erase(5);
//	cout << seq << endl;
//	cout << seq.Find(10)<< endl;
//}
//
//int main()
//{
//	Test4();
//	system("pause");
//	return 0;
//}