#pragma once


#include <math.h>

//小易有一个圆心在坐标原点的圆，小易知道圆的半径的平方。
//小易认为在圆上的点而且横纵坐标都是整数的点是优雅的，
//小易现在想寻找一个算法计算出优雅的点的个数，请你来帮帮他。
// 例如：半径的平方如果为25
//优雅的点就有：(+/-3, +/-4), (+/-4, +/-3), (0, +/-5) (+/-5, 0)，一共12个点。


//选第一象限，判断i是整数的时候，j是不是整数就行了
void TestElegantPoint()
{
	int n = 0;
	cin>>n;

	int num = 0;	
	for(int i = 0;i<sqrt((double)n);++i)
	{
		double j = sqrt((double)n-i*i);	//a*a+b*b = n
		if((int)j >= j)
			num++;
	}
	num *= 4;
	
	cout<<num<<endl;
}