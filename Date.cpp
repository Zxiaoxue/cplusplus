#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <assert.h>
using namespace std;

class Date
{
public:
	/*Date()
	{
	cout << "Date()" << endl;
	}*/
	Date(int year = 1900, int month = 1, int day = 1)//使用初始化列表更高效
		//必须使用初始化列表初始化的成员变量1.常量成员变量
		//2.引用类型成员变量
		//3.没有缺省的构造函数的类成员变量
	{
		//cout << "Date(int year = 1900, int month = 1, int day = 1)" << endl;
		if (year > 1900
			&& month > 0 && month<13
			&& day>0 && day <= GetMonthDay(year, month))
		{
			_year = year;
			_month = month;
			_day = day;
		}
		else
		{
			cout << "非法日期" << endl;
		}
	}

	Date(const Date& d)
	{
		//cout << "Date(const Date& d)" << endl;
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}

	Date& operator=(const Date& d)
	{

		//cout << "Date& operator=(const Date& d)" << endl;
		if (this != &d)
		{
			_year = d._year;
			_month = d._month;
			_day = d._day;
		}
		return *this;
	}

	~Date()
	{
		//cout << "~Date" << endl;
	}

	void Display()const//  -> const Date* this
	{
		cout << _year << "-" << _month << "-" << _day << endl;
	}

public:

	bool operator ==(const Date& d)
	{
		return _year == d._year
			&&_month == d._month
			&&_day == d._day;
	}

	bool operator !=(const Date& d)
	{
		return !(*this == d);
	}
	bool operator > (const Date& d)
	{
		//if (_year > d._year)
		//{
		//	return true;
		//}
		//else
		//{
		//	if (_year == d._year)
		//	{
		//		if (_month > d._month)
		//			return true;
		//		else
		//		{
		//			if (_month == d._month)
		//			{
		//				if (_day > d._day)
		//					return true;
		//			}
		//		}
		//	}
		//}
		//return false;
		return (_year > d._year)
			|| ((_year == d._year) && (_month > d._month))
			|| ((_year == d._year) && (_month == d._month) && (_day > d._day));
	}
	bool operator >= (const Date& d)
	{
		return (*this > d) || (*this == d);
	}
	bool operator <(const Date& d)
	{
		return !(*this >= d);
	}
	bool operator<=(const Date& d)
	{
		return !(*this > d);
	}
	//日期计算器
	Date operator+(int day)
	{

		if (day<0)
		{
			return *this - (-day);
		}
		Date tmp(*this);
		tmp._day += day;
		while (tmp._day > GetMonthDay(tmp._year, tmp._month))
		{
			tmp._day -= GetMonthDay(tmp._year, tmp._month);

			if (tmp._month == 12)
			{
				tmp._year++;
				tmp._month = 1;
			}
			else
			{
				++tmp._month;
			}
		}
		return tmp;
	}

	Date& operator+=(int day)
	{
		/*if (day < 0)
		{
		return *this - (-day);
		}

		_day += day;
		while (_day > GetMonthDay(_year, _month))
		{
		_day -= GetMonthDay(_year, _month);

		if (_month == 12)
		{
		_year++;
		_month = 1;
		}
		else
		{
		++_month;
		}
		}
		return *this;*/
		*this = *this + day;
		return *this;
	}


	Date operator-(int day)
	{
		if (day < 0)
		{
			return *this + (-day);
		}
		Date tmp(*this);
		tmp._day -= day;
		while (tmp._day <= 0)
		{

			if (tmp._month == 1)
			{
				tmp._year--;
				tmp._month = 12;
			}
			else
			{
				tmp._month--;
			}
			tmp._day += GetMonthDay(tmp._year, (tmp._month));
		}
		return tmp;
	}
	Date& operator-=(int day)
	{
		/*if (day < 0)
		{
		return *this + (-day);
		}
		_day -= day;
		while (_day < 0)
		{
		_day += GetMonthDay(_year, (--_month));
		if (_month == 1)
		{
		_year--;
		_month = 12;
		}
		else
		{
		_month--;
		}
		}
		return *this;*/
		*this = *this - day;
		return *this;
	}

	Date operator++() //前置++
	{
		*this += 1;
		return *this;
	}
	Date operator++(int)//后置++
	{
		/*
		Date tmp(*this);
		tmp._day += 1;

		while (_day > GetMonthDay(tmp._year, tmp._month))
		{
		tmp._day -= GetMonthDay(tmp._year, tmp._month);
		if (tmp._month == 12)
		{
		tmp._year++;
		tmp._month = 1;
		}
		else
		{
		tmp._month++;
		}
		}

		return tmp;*/
		Date tmp(*this);
		*this += 1;
		return *this;
	}

	Date operator--()//前置--
	{
		*this -= 1;
		return *this;
	}
	Date operator--(int)//后置--
	{
		/*Date tmp(*this);
		tmp._day -= 1;
		while (tmp._day < 0)
		{
		tmp._day += GetMonthDay(tmp._year, (--tmp._month));
		if (tmp._month == 1)
		{
		tmp._year--;
		tmp._month = 12;
		}
		else
		{
		tmp._month--;
		}
		}
		return tmp;*/
		Date tmp(*this);
		*this -= 1;
		return *this;
	}

	int operator-(const Date& d)
	{
		int flag = 1;
		Date max = *this;
		Date min = d;

		if (max < min)
		{
			swap(max._year, min._year);
			swap(max._month, min._month);
			swap(max._day, min._day);

			flag = -1;
		}
		int days = 0;
		while (min != max)
		{
			++min;
			++days;
		}
		return days*flag;
	}
private:
	bool _IsLeapyear(int year)
	{
		if ((year % 4 == 0 && year % 100 != 0)
			|| year % 400 == 0)
			return true;
	}

	int GetMonthDay(int year, int month)
	{
		int monthArray[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		int day = monthArray[month];
		if (month == 2 && _IsLeapyear(year))
		{
			day += 1;
		}
		return day;
	}

private:
	int _year;
	int _month;
	int _day;
};

void Test1()
{
	Date d1(2016, 4, 27);
	d1 += 13;
	d1.Display();

}
void Test2()
{
	Date d2(2015, 12, 31);
	d2 -= 10;
	d2 -= 30;
	d2.Display();
}

void Test3()
{
	Date d3(2016, 1, 1);
	d3 -= 10;
	d3.Display();
}
int main()
{
	//Test1();
	Test2();
	Test3();

	system("pause");
	return 0;
}