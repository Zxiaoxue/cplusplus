#include <iostream>
using namespace std;

void Str()
{
	char str1[] = "hello world";
	char str2[] = "hello world";

	char* str3 = "hello world";
	char* str4 = "hello world";

	if(str1 == str2)
		printf("str1 and str2 are same.\n");
	else
		printf("str1 and str2 are not same.\n");

	if(str3 == str4)
		printf("str3 and str4 are same.\n");
	else
		printf("str3 and str4 are not same.\n");
}
/*
str1��str2�������ַ������飬���ǻ�Ϊ�������ڴ��з�����������Ϊ12���ֽڵĿռ䣬
���ѡ�hello world�������ݷֱ��Ƶ�������ȥ������������ʼ��ַ��ͬ�����飬���str1��
str2��ֵҲ����ͬ��str3��str4������ָ�룬��������Ϊ���Ƿ����ڴ��Դ洢�ַ��������ݡ�
��ֻ��Ҫ������ָ��hello world�����ڴ��еĵ�ַ�Ϳ����ˡ���Ϊ��hello world���ǳ����ַ���
�����ڴ���ֻ��һ�����������str3��str4ָ�����ͬһ����ַ��

*/