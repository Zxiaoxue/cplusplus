#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <string>
using namespace std;
//
//class Person
//{
//	friend ostream& operator<<(ostream& os, Person& p);
//public:
//	Person(string name = " ")
//		:_name(name)
//	{}
//	void Display()
//	{
//		cout << "Person::" << _name << endl;
//	}
//protected:
//	string _name;
//};
//ostream& operator<<(ostream& os, Person& p)
//{
//	os << p._name << " ";
//	cout << endl;
//	return os;
//}
//
//class Student : public Person
//{
//public:
//	Student(int num = 0)
//		:_num(num)
//	{}
//protected:
//	int _num;
//};
//
//void Test()
//{
//	Person p("zhangxue");
//	Student s;
//	s.Display();
//}

//class A
//{
//public:
//	A()
//	:_a(1)
//	{}
//
//	virtual void Display()
//	{
//		cout << "A::"<< _a << endl;
//	}
//protected:
//	int _a;
//};
//
//class B : virtual public A
//{
//public:
//	B()
//	:_b(2)
//	{}
//
//	void Display()//隐藏A类的Display函数
//	{
//		cout << "B::" << _b << endl;
//	}
//
//protected:
//	int _b;
//};
//
//class C :virtual public A
//{
//public:
//	C()
//		:_c(3)
//	{}
//
//	void Display()
//	{
//		cout << "C::" << _c << endl;
//	}
//
//protected:
//	int _c;
//}; 
//
//class D : public B,public C
//{
//public:
//	D()
//	:_d(4)
//	{}
//
//	void Display()
//	{
//		cout << "D::" << _d << endl;
//	}
//
//protected:
//	int _d;
//};
//
//void Test()
//{
//	A a;
//	B b;
//	C c;
//	D d;
//	//1.子类对象可以赋值给父类对象(切片)
//	a = b;
//	//2.父类对象不能赋值给子类对象
//	//b = a; NO
//	//3.父类对象的指针或引用可以指向子类对象
//	A* pa = &a;
//	B* pb = &b;
//	pa = &b;
//	//4.子类对象的指针（引用）不能指向父类对象(可强制类型转换)
//	//pb = &a;NO
//
//	a.Display();
//	b.A::Display();//调用的就是A类的Display函数
//	c.Display();
//	d.Display();
//
//}
//
//class Person
//{
//public:
//	Person(string name = "")
//		:_name(name)
//	{
//		cout << "Person()" << endl;
//	}
//	Person(const Person& p)
//		:_name(p._name)
//	{
//		cout << "Person(const Person& p)" << endl;
//	}
//	Person& operator=(const Person& p)
//	{
//		if (this != &p)
//		{
//			cout << "Persn& operator<<(const Person& p)" << endl;
//			_name = p._name;
//		}
//		return *this;
//	}
//	~Person()
//	{
//		cout << "~Person()" << endl;
//	}
//private:
//	string _name;
//};
//class Student : public Person
//{
//public:
//	Student(char* name,int num)
//		:Person(name)
//		,_num(num)
//	{
//		cout << "Student(char* name,int num)" << endl;
//	}
//	Student(const Student& s)
//		:Person(s)
//		, _num(s._num)
//	{
//		cout << "Student(const Student& s)" << endl;
//	}
//	Student& operator=(const Student& s)
//	{
//		cout << "Student& operator=(const Student& s)" << endl;
//		if (this != &s)
//		{
//			Person::operator=(s);
//			_num = s._num;
//		}
//		return *this;
//	}
//	~Student()
//	{
//		cout << "~Student()" << endl;
//	}
//private:
//	int _num;
//};
//
//void Test()
//{
//	Student s1("jake", 18);
//	Student s2(s1);
//	Student s3("rose", 17);
//	s3 = s1;
//}


////最好把基类的析构函数申明为虚函数
//class A
//{
//public:
//	A()
//		:_a(1)
//	{
//		cout << "A()" << endl;
//	}
//	virtual ~A()
//	{
//		cout << "~A()" << endl;
//	}
//private:
//	int _a;
//};
//
//class B : public A
//{
//public:
//	B()
//		:_b(new int[1])
//	{
//		cout << "B(int b)" << endl;
//		*_b = 2;
//	}
//	~B()
//	{
//		delete[] _b;
//		cout << "~B()" << endl;
//	}
//private:
//	int* _b;
//};
////eg：拿一个父类指针（引用）维护一个子类对象，释放时可能出现问题，
////非虚释放不到子类，此时若子类中开辟了空间，则造成内存泄漏
//void Test()
//{
//	A a;
//	B b;
//
//	A* pa = &b;
//}

//class Person
//{
//public:
//	virtual void BuyTickets()
//	{
//		cout << "买票" << endl;
//	}
//};
//class Student : public Person
//{
//public:
//	void BuyTickets()
//	{
//		cout << "买票-半价" << endl;
//	}
//};
//
//void Fun(Person& p)
//{
//	p.BuyTickets();
//}
//
//void Test()
//{
//	Person p;
//	Student s;
//	p.BuyTickets();
//	s.BuyTickets();
//
//	Fun(p);
//	Fun(s);
//
//}

//纯虚函数
class A
{
	virtual void Display() = 0;
};

class B : public A
{};

void Test()
{
	//A a; NO
	//B b; NO

}
int main()
{
	Test();
	system("pause");
	return 0;
}