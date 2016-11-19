#include <iostream>
using namespace std;

int main()
{
	int n;
	int i,j;
	int a[20][20];
	int b[20][20];

	cin >> n;
	for(i = 0; i<n ; ++i)
	{
		for(j = 0; j<n; ++j)
		{
			cin >> a[i][j];
		}
	}
	
	for(i = 0; i<n; ++i)
	{
		for(j = 0; j<n; ++j)
		{
			b[i][j] = a[j][i];
			cout << b[i][j] << " ";
		}
		cout << endl;
	}
	return 0;
}

