#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <string>
using namespace std;

//1.��̬��ʵ��---���
//2.���̳кͶ�̳�
//3.��̬�󶨺Ͷ�̬��
//4.���μ̳к���������̳�

//1.������Ҫ��Ա���������������⣬���
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
//		printf("��%d���麯����ַ:%p\n", i, ppfun_t[i]);
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

//��̳У����μ̳к���������̳�
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

//��̬��̬�Ͷ�̬��̬
//��̬��̬��������(�����ھ������)������ʱȷ��������ַ
//��̬��̬����ͨ���̳���д������麯���Ķ�̬(����ʱ����ȷ��)����ʱ������Һ�����ַ

int main()
{
	Test();
	system("pause");
	return 0;
}