
#include<iostream>
#include<set>
using namespace std;

//�ȶ�����ȥ�̳���һ��ñ�ӣ��̳�����N��ñ�ӣ���Щñ�ӵļ۸������ͬ��
//�ȶ�������һ���۸�������˵�ñ�ӣ��ʵ������˵�ñ�Ӽ۸��Ƕ��٣�

//��������һ��������N��N <= 50��������������N������ʾÿ��ñ�ӵļ۸񣨼۸��������������С�ڵ���1000��
//�������:������ڵ������˵�ñ�ӣ����������۸��Ƕ��٣��������-1
//��������:
//10
//10 10 10 10 20 20 30 30 40 40


int BuyHand()
{
	int N;
	cin>>N;
	int pirce;
	set<int> pirces;
	for(int i = 0; i<N; i++)
	{
		cin>>pirce;
		pirces.insert(pirce);
	}
	int peace = 2;
	set<int>::iterator it = pirces.begin();
	while(peace--)
	{
		it++;
	}
	cout<<*it<<endl;
	return 0;
}

