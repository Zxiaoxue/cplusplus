#define _CRT_SECURE_NO_WARNING  1
//引用做参数，1.swap--在函数内部改变参数，2.Bigdata提高效率
// 内联函数必须在定义处加上inline
//定义在类内部的函数默认为内联函数
//c++中尽量使用const，枚举，内联去替代宏
//宏没有类型安全的检查，在预处理的时候替换了所以无法调试，宏安全性不高

#include <iostream>
using namespace std;
	class Complex
	{
	public:
		Complex(double real = 0.0, double image = 0.0)
			:_real(real)
			, _image(image)
		{
			cout << "Complex()" << endl;
		}

		Complex(const Complex& c)
		{
			cout << "Complex(const Complex& c)" << endl;
			_real = c._real;
			_image = c._image;
		}

		~Complex()
		{
			cout << "~Complex()" << endl;
		}

		Complex& operator=(const Complex& c)// Complex返回值支持连续的赋值
		{
			cout << "Complex& operator=()" << endl;
			if (this != &c)
			{
				_real = c._real;
				_image = c._image;
			}

			return *this;
		}
		void Display()
		{
			cout << _real << "-" << _image << endl;
		}

		Complex& operator++()//前置++，返回加之后的值
		{
			this->_real++;
			this->_image++;
			return *this;
		}
		Complex operator++(int)//后置++，返回加之前的值，int用来占位，形成重载
		{
			Complex ret(*this);
			this->_real++;
			this->_image++;
			return ret;
		}

		bool operator== (const Complex& c)
		{
			IsEqual(c);
		}
		bool IsEqual(const Complex& c)
		{
			return _image == c._image&&_real == c._real;
		}

		bool operator> (const Complex& c)
		{
			MoreThan(c);
		}

		bool MoreThan(const Complex& c)
		{
			if (_real > c._real)
			{
				return true;
			}
			else if (_real == c._real
				&&_image > c._image)
			{
				return true;
			}
			return false;
		}

		Complex operator+ (const Complex& c)
		{
			/*Complex ret;
			ret._real = _real + c._real;
			ret._image = _image + c._image;*/

			Complex ret(*this);
			ret._real += c._real;
			ret._image += c._image;
			return ret;
		}

		Complex& operator+= (const Complex& c)
		{
			_real += c._real;
			_image += c._image;
			return *this;
		}

	private:
		double _real;
		double _image;
	};


	int main()
	{
		{
			Complex c3(1,2);
			Complex c1(1.0, 1.0);

		}
		
		//Complex c2(c1);  //c2 = c1; 两个都是拷贝构造,在创建中，赋值运算符的重载是已经存在的对象的赋值

		//Complex c3 = c1 + c2;

		//c1.Display();
		//c2.Display();
		//c3.Display();
		//c1 = c3;

		//c3.Display();
		//c1++;//-> c1.operator++(&c1,int())
		//++c1;//-> c1.opeartor++(&c1);
		system("pause");
		return 0;
	}


