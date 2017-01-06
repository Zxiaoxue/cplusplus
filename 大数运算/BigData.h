#pragma once

#include <string>
#include <iostream>
using namespace std;

#define MAX_NUM 9223372036854715807
#define MIN_NUM -9223372036854715808

typedef long long LONGTYPE;
class BigData
{
public:
	BigData(LONGTYPE value = 0xCCCCCCCCCCCCCCCC);
	BigData(const char* strData);

	BigData operator+(const BigData& bigdata)
	{
		//��Ż�Ϊ����ʱ��ֱ�ӵ��ü���
		/*if(('+'==_strData[0]&&'-'==bigdata._strData[0])||('-'==_strData[0]&&'-'==bigdata._strData[0])
			||'-'==_strData[0]&&'+'==bigdata._strData[0])*/
		if(_strData[0]!=bigdata._strData[0])
			return *this-bigdata;
		//ȷ�������λ������λ����ߵ���λ����һ
		int size1 = _strData.size();
		int size2 = bigdata._strData.size();
		BigData res;
		res._value = 0;
		//res��_valueֵΪ����ֵ֮�ͣ����û�������ֱ�ӷ���
		if(IsOverflow()&&bigdata.IsOverflow()
			&&((_value>=0&&(_value <= MAX_NUM-bigdata._value))//+ +
			||(_value<0&&(_value >= MIN_NUM-bigdata._value))))//- -
		{
			res._value = _value+bigdata._value;
			return res;			
		}	
					
		int size = 0;
		//��res���ٿռ�
		if(size1>=size2)
		{
			res._strData.resize(size1+1,'0');
			size = size1;
		}
		else
		{
			res._strData.resize(size2+1,'0');
			size = size2;
		}
		int i = size1-1;
		int j = size2-1;
		int carry = 0;
		//��λ   -------forѭ���������п��ܻ��н�λ
		for(; (i>=0||j>=0)&&size>0; --i,--j,--size)
		{
			carry = 0;
			if(i<=0 && j>=0)
			{
				int tmp1 = 0;
				int tmp2 = res._strData[size]-'0';
				if(bigdata._strData[0]>='0'&&bigdata._strData[0]<='9')
				{
					tmp1 = bigdata._strData[j]-'0';
				}
				carry = tmp1+tmp2;				
			}
			else if(j<=0 && i>=0)
			{
				int tmp1 = 0;
				int tmp2 = res._strData[size]-'0';
				if(_strData[0]>='0'&&_strData[0]<='9')
				{
					tmp1 = _strData[i]-'0';
				}
				carry = tmp1+tmp2;
			}
			else if(i==0&&j==0)
			{
				break;
			}
			else
				carry = res._strData[size]-'0'+_strData[i]-'0'+bigdata._strData[j]-'0';
			//��λ
			if(carry>9)
			{
				int div = carry/10;
				int rem = carry%10;
				int tmp1 = res._strData[size-1]-'0';
				//int tmp2 = res._strData[size]-'0';
				res._strData[size-1] = div+tmp1+'0';
				res._strData[size] = rem+'0';
			}
			else
				res._strData[size] = carry +'0';
		}
		
		while(size >= 0)
			res._strData[size--] = _strData[0];
		return res;
	}

	BigData operator-(const BigData& bigdata)
	{
		if(('+'==_strData[0]&&'-'==bigdata._strData[0])
			||('-'==_strData[0]&&'+'==bigdata._strData[0]))
			return *this+bigdata;

		BigData tmp(bigdata);
		BigData res;
		res._value = 0;
		//ȷ������ķ���λ
		if('+'==tmp._strData[0])
			tmp._strData[0] = '-';
		else if('-'==tmp._strData[0])
			tmp._strData[0]='+';
		int size1 = _strData.size();
		int size2 = tmp._strData.size();
		int sign;
		if(size2>size1)//�ѳ��ķŵ����棬��ʱ������������,����
		{
			swap(_strData,tmp._strData);
			swap(_value,tmp._value);
			sign = _strData[0];	//ȷ������ķ���λ
		}
		else if(size2 == size1)	//λ����ͬ
		{
			//��ʱ��������ס���ǵķ���
			int tmpSymbol1 = _strData[0];
			int tmpSymbol2 = tmp._strData[0];
			tmp._strData[0] = tmpSymbol1;
			if(*this<tmp)
			{
				sign = tmpSymbol2;
			}
			else
			{
				sign = tmpSymbol1;
			}
		}

		//��������
		/*for()
		{

		}*/

		return res;
	}
	bool operator<(const BigData& bigdata)
	{
		if(_strData[0] != bigdata._strData[0])
		{
			if(_strData[0] == '+')
				return false;
			else
				return true;
		}
		else
		{
			char* pStr1 = (char*)_strData.c_str();
			char* pStr2 = (char*)bigdata._strData.c_str();
			pStr1++;
			pStr2++;
			if(_strData[0] == '+')
				return pStr1<pStr2;
			else
				return pStr1>pStr2;
		}
		return true;
	}

	friend ostream& operator<<(ostream& _cout,const BigData& bigdata);
private:
	bool IsOverflow() const; 
private:
	string _strData;
	LONGTYPE _value;
};


