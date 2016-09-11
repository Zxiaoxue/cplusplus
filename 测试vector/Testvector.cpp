#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <vector>
using namespace std;

void Testvector1()
{
	vector<int> v;
	for (int i = 0; i < 10; ++i)
	{
		v.push_back(i);
	}

	vector<int>::iterator it;
	//it = v.begin();
	//it = v.insert(it,100);

	//v.insert(it, 2, 300);

	//vector<int> v2(2,400);
	//v.insert(it + 2, v2.begin(), v2.end());

	//int myarr[] = { 501, 502, 503 };
	//v.insert(v.begin(), myarr, myarr + 3);

	for (it = v.begin(); it != v.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;
}
void Testvector2()
{
	vector<int> first(3, 100);
	vector<int> second(5, 200);

	first.swap(second);
	cout << "first contains:" << endl;
	for (int i = 0; i < first.size(); ++i)
	{
		cout << first[i] << " ";
	}
	cout << endl;
	cout << "second contins:" << endl;
	for (int i = 0; i < second.size(); ++i)
	{
		cout << second[i] << " ";
	}
	cout << endl;
}
void Testvector3()
{

	vector<int> myvector;

	for (int i = 1; i <= 10; i++)
		myvector.push_back(i);

	myvector.erase(myvector.begin() + 5);

	myvector.erase(myvector.begin(), myvector.begin() + 3);

	cout << "myvector contains:";
	for (int i = 0; i<myvector.size(); i++)
		cout << " " << myvector[i];
	cout << endl;

}