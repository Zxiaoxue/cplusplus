#pragma once

#include"BigData.h"
#include <iostream>

BigData::BigData(LONGTYPE value)
	:_value(value)
{
	if(value == 0xCCCCCCCCCCCCCCCC)
		return;
	int num = value;
	int count = 1;
	while(num != 0)
	{
		num /= 10;
		count++;
	}
	_strData.resize(count);
	num = value;
	int flag = 1;
	if(value >= 0)
		_strData[0] = '+';
	else if(value < 0)
	{
		_strData[0] = '-';
		flag = -1;
	}

	while(num)
	{
		_strData[--count] = num%10*flag +'0';
		num/=10;
	}
}

BigData::BigData(const char* strData)
{
	if(strData == NULL)
		return;

	int sign = strData[0];
	//"123245" "456dfghgjhk" "+" "		" "0000456778"	
	char *pStr = (char*)strData;

	//�������λ������������ţ�����ָ��������    
	if('+' == sign || '-' == sign)
		pStr++;
	else if(sign >= '0' && sign <= '9') //�����һ���ַ�Ϊ���֣��Ǿ�˵�����Ǹ�����
		sign = '+';
	else
		return;

	//����ʼΪ0��״̬	
	while(*pStr == '0')
		pStr++;

	//_strData
	_strData.resize(strlen(strData)+1);  //+1�ӵ��Ƿ���λ
	_strData[0] = sign;

	_value = 0;
	int count = 1;
	//����ת��
	while((*pStr >= '0' && *pStr <= '9'))
	{
		_value = _value*10 + *pStr-'0';
		_strData[count++] = *pStr;
		pStr++;
	}
	_strData.resize(count);//���¼����С�������˷�
	if(sign == '-')
		_value = 0-_value;
}

bool BigData::IsOverflow() const
{
	//9223372036854715807
	//-9223372036854715808

	string tmp = "9223372036854715807";
	if(_strData[0] == '-')
		tmp = "-9223372036854715808";

	int Ssize = _strData.size();
	int Tsize = tmp.size();

	if(Ssize < Tsize)
		return true;
	else if(Ssize == Tsize && _strData < tmp)
		return true;

	return false;
}

std::ostream& operator<<(std::ostream& _cout,const BigData& bigdata)
{
	if(bigdata.IsOverflow())
		_cout<<bigdata._value;
	else
	{
		char* pData = (char*)bigdata._strData.c_str();
		int i = 0;
		int j = 0;
		while('+' == bigdata._strData[i]||'-'==bigdata._strData[j+1]
		||'0'==bigdata._strData[i])
		{
			pData++;
			j++;
			i++;
		}
		cout<<pData;
	}
	return _cout;
}

