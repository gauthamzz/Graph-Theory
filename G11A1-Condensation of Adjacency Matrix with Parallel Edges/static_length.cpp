#include <bits/stdc++.h>
using namespace std;
#define ull unsigned long long int

ull N,M,Base,Maxlen;

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

void bit_reduce(vector<ull> cond_vec[], vector<ull> &edge_db)
{
	//calculate bit lengths for each
	Maxlen=0;

	for (ull i=0;i<N;i++) {
		for (ull j=0;j<i;j++) {
			ull len=0,val=cond_vec[i][j];
			while (val) {
				len++;
				val>>=1LLU;
			}

			Maxlen=max(len,Maxlen);
		}
	}

	//considering 64-bit architecture and sizeof long long is 64;
	ull offset=0,e=-1;

	for (ull i=0;i<N;i++) {
		for (ull j=0;j<i;j++) {

			ull val=cond_vec[i][j];

			if (!edge_db.size() || (offset+Maxlen)>=64) {
				edge_db.push_back(0);
				offset=0;
				e++;				
			}

			val<<=offset;
			offset+=Maxlen;

			edge_db[e]|=val;
		}

	}
}

void bit_expand(vector<ull> cond_vec[], vector<ull> edge_db)
{
	ull j=0,k=0,u=1,v=0;

	while (j<edge_db.size()) {

		ull mask=(1LLU<<Maxlen)-1LLU;
		cond_vec[u][v++]=edge_db[j]&mask;

		if (v==u) {
			u++;
			v=0;
		}

		edge_db[j]>>=Maxlen;

		if (edge_db[j]==0) {
			j++;
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

	//print lower traingle matrix
	print(cond_vec);

	vector<ull> edge_db;

	bit_reduce(cond_vec,edge_db);

	vector<ull> decom_vec[N];
	init(decom_vec);

	bit_expand(decom_vec,edge_db);

	print(decom_vec);

	return 0;
}