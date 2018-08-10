#include <bits/stdc++.h>
using namespace std;
int N,M,Base,Maxbits=0;

void init(vector<int> cond_vec[])
{
	for (int i=0;i<N;i++) {
		for (int j=0;j<i;j++)
			cond_vec[i].push_back(0);
	}
}

void print(vector<int> cond_vec[])
{
	for (int i=0;i<N;i++) {
		for (int j=0;j<i;j++)
			cout<<cond_vec[i][j]<<" ";
		cout<<endl;
	}
}

void condense(vector<int> cond_vec[], int cond_int[])
{
	for (int i=0;i<N;i++) {
		int val=0;
		for (int j=i-1;j>=0;j--) {
			val=val*Base+cond_vec[i][j];
		}

		cond_int[i]=val;
	}
}

void decondense(int cond_int[], vector<int> cond_vec[])
{
	for (int i=0;i<N;i++) {
		int val=cond_int[i];
		for (int j=0;j<i;j++) {
			cond_vec[i].push_back(val%Base);
			val/=Base;
		}
	}
}

int main()
{
	if (fopen("input.txt","r")) {
		freopen("input.txt","r",stdin);
		freopen("output.txt","w",stdout);
	}

	int i,u,v,j;
	cin>>N>>M;

	vector<int> cond_vec[N];

	init(cond_vec);

	for (i=0;i<M;i++) {
		cin>>u>>v;
		if (u>v)
			cond_vec[u][v]++;
		else
			cond_vec[v][u]++;
	}

	print(cond_vec);

	Base=0;
	for (i=0;i<N;i++)
		for (j=0;j<i;j++)
			Base=max(Base,cond_vec[i][j]);

	Base++;

	int cond_int[N];

	condense(cond_vec,cond_int);

	vector<int> decom_vec[N];
	decondense(cond_int,decom_vec);

	print(decom_vec);

	return 0;
}