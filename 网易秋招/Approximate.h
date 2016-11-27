#pragma once
#include <vector>

void get_yue_shu(int k,vector<int> sub)
{
	for(int i = 2; i<k; ++i)
	{
		if(k%i == 0)
			sub.push_back(i);
	}
}
void Test()
{
	int m,n;

   while(cin>>n>>m){
        vector<int> res(m+1, 0);
        res[n] = 1;
        for(int i=n;i<=m;i++){
            vector<int>a;
            //位置i无法到达，跳过
            if(res[i]==0)
                continue;
            get_yue_shu(i, a);
            //记录从起点到i的最小步数
            for(int j=0;j<a.size();j++){
                //由点i出发能到达的点
                if((a[j]+i)<=m&&res[a[j]+i]!=0)
                    //其它点也能到达，比较大小，记录最小步数
                    res[a[j]+i] = min(res[a[j]+i], res[i] + 1);
                else if((a[j]+i)<=m)
                    //到达点i的最小步数加1
                    res[a[j]+i] = res[i] + 1;
            }
        }
        if(res[m]==0)
            cout<<-1<<endl;
        else
            cout<<res[m]-1<<endl;
    }
}

//void TestApproximate()
//{
//	int k = 0;
//	int m = 0;
//	cin>>k;
//	cin>>m;
//
//	vector<int> a(m+1,0);
//
//	TestAppr(k,a);
//	for(int i = 0; i<a.size(); ++i)
//	{
//
//	}
//}