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
str1和str2是两个字符串数组，我们会为它们在内存中分配两个长度为12个字节的空间，
并把“hello world”的内容分别复制到数组中去，这是两个初始地址不同的数组，因此str1和
str2的值也不相同。str3和str4是两个指针，我们无须为它们分配内存以存储字符串的内容。
而只需要把它们指向“hello world”在内存中的地址就可以了。因为“hello world”是常量字符串
它在内存中只有一个拷贝，因此str3和str4指向的是同一个地址。

*/