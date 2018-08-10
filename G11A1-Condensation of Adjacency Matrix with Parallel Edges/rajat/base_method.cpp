#include <bits/stdc++.h>
using namespace std;
#define ull unsigned long long int
ull N,M,Base,Maxbits=0;

void init(vector<ull> cond_vec[])
{
	for (ull i=0;i<N;i++) {
		for (ull j=0;j<i;j++)
			cond_vec[i].push_back(0);
	}
}

void print(vector<ull> cond_vec[])
{
	for (ull i=0;i<N;i++) {
		for (ull j=0;j<i;j++)
			cout<<cond_vec[i][j]<<" ";
		cout<<endl;
	}
}

void condense(vector<ull> cond_vec[], ull cond_int[])
{
	int i,j;
	for (i=0;i<N;i++) {
		ull val=0;
		for (j=i-1;j>=0;j--) {
			val=val*Base+cond_vec[i][j];
		}
		// cout<<i<<" "<<val<<endl;
		cond_int[i]=val;
	}
}

void decondense(ull cond_int[], vector<ull> cond_vec[])
{
	for (ull i=0;i<N;i++) {
		ull val=cond_int[i];
		for (ull j=0;j<i;j++) {
			cond_vec[i].push_back(val%Base);
			val/=Base;
		}
	}
}

int main()
{
	if (fopen("input1.txt","r")) {
		freopen("input1.txt","r",stdin);
		freopen("output.txt","w",stdout);
	}

	ull i,u,v,j;
	cin>>N>>M;

	vector<ull> cond_vec[N];

	init(cond_vec);

	for (i=0;i<M;i++) {
		cin>>u>>v;
		if (u>v)
			cond_vec[u][v]++;
		else
			cond_vec[v][u]++;
	}

	cout<<"Input Matrix is:-\n";
	print(cond_vec);

	Base=0;
	for (i=0;i<N;i++)
		for (j=0;j<i;j++)
			Base=max(Base,cond_vec[i][j]);

	Base++;
	
	ull cond_int[N];

	cout<<"\nBase converted Matrix is:-\n";
	condense(cond_vec,cond_int);

	for (i=0;i<N;i++)
		cout<<cond_int[i]<<endl;

	vector<ull> decom_vec[N];

	cout<<"\nDecompressed Matrix\n";
	decondense(cond_int,decom_vec);

	print(decom_vec);

	return 0;
}
