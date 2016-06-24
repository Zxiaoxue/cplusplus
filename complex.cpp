#define _CRT_SECURE_NO_WARNING  1
//������������1.swap--�ں����ڲ��ı������2.Bigdata���Ч��
// �������������ڶ��崦����inline
//���������ڲ��ĺ���Ĭ��Ϊ��������
//c++�о���ʹ��const��ö�٣�����ȥ�����
//��û�����Ͱ�ȫ�ļ�飬��Ԥ�����ʱ���滻�������޷����ԣ��갲ȫ�Բ���

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

		Complex& operator=(const Complex& c)// Complex����ֵ֧�������ĸ�ֵ
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

		Complex& operator++()//ǰ��++�����ؼ�֮���ֵ
		{
			this->_real++;
			this->_image++;
			return *this;
		}
		Complex operator++(int)//����++�����ؼ�֮ǰ��ֵ��int����ռλ���γ�����
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
		
		//Complex c2(c1);  //c2 = c1; �������ǿ�������,�ڴ����У���ֵ��������������Ѿ����ڵĶ���ĸ�ֵ

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


