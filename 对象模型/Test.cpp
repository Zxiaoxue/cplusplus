#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <string>
using namespace std;

//1.多态的实现---虚表
//2.单继承和多继承
//3.静态绑定和动态绑定
//4.菱形继承和菱形虚拟继承

//1.子类需要成员变量，否则会出问题，虚表
//class Person
//{
//public:
//	Person()
//		:_num(1)
//	{}
//
//	virtual void Display()
//	{
//		cout << "Person::Display()" << endl;
//	}
//	virtual void Show()
//	{
//		cout << "Person::Show()" << endl;
//	}
//	virtual void Excibition()
//	{
//		cout << "Person::Excibition()" << endl;
//	}
//private:
//	int _num;
//};
//
//class Student : public Person
//{
//public:
//	Student()
//		:_num(2)
//	{}
//	virtual void Excibition()
//	{
//		cout << "Student::Excibition()" << endl;
//	}
//	virtual void Fun1()
//	{
//		cout << "Student::Fun()" << endl;
//	}
//private:
//	int _num;
//};
//
//typedef void(*pfun_t)();
//
//void PrintVTable(pfun_t* ppfun_t)
//{
//	for (int i = 0;ppfun_t[i]!= NULL; ++i)
//	{
//		printf("第%d个虚函数地址:%p\n", i, ppfun_t[i]);
//	}
//}
//void Test()
//{
//	//Person p;
//
//	//PrintVTable((pfun_t*)(*(int*)&p));
//
//	Student s;
//	PrintVTable((pfun_t*)(*(int*)&s));
//
//}

//多继承，菱形继承和菱形虚拟继承
class A
{
	public:
		A()
			:_num(1)
		{}
		virtual void Fun1()
		{
			cout << "A::Fun1()" << endl;
		}
	
private:
		int _num;
};
class B : public A
{
public:
	B()
	 :_num(2)
	{}
	virtual void Fun1()
	{
		cout << "B::Fun1()" << endl;
	}
	virtual void Fun2()
	{
		cout << "B::Fun2()" << endl;
	}
private:
	int _num;
};

class C : public A
{
public:
	C()
		:_num(3)
	{}
	virtual void Fun1()
	{
		cout << "C::Fun1()" << endl;
	}
	virtual void Fun3()
	{
		cout << "C::Fun3()" << endl;
	}
private:
	int _num;
};

class D : public B,public C
{
public:
	D()
		:_num(4)
	{}
	virtual void Fun2()
	{
		cout << "D::Fun2()" << endl;
	}
	virtual void Fun4()
	{
		cout << "D::Fun4()" << endl;
	}
private:
	int _num;
};

void Test()
{
	D d;
	d.B::Fun1();
	d.Fun2();
	d.Fun3();
	d.Fun4();

}

//静态多态和动态多态
//静态多态就是重载(编译期决议决定)，编译时确定函数地址
//动态多态就是通过继承重写基类的虚函数的多态(运行时决议确定)运行时到虚表找函数地址

int main()
{
	Test();
	system("pause");
	return 0;
}