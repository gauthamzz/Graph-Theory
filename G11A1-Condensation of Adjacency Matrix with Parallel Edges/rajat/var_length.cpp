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

void bit_reduce(vector<ull> cond_vec[], vector<ull> &len_db, vector<ull> &edge_db)
{
	//calculate bit lengths for each
	ull maxlen=0;
	vector<ull> len_all[N];
	init(len_all);

	for (ull i=0;i<N;i++) {
		for (ull j=0;j<i;j++) {
			ull len=0,val=cond_vec[i][j];
			while (val) {
				len++;
				val>>=1LLU;
			}

			len_all[i][j]=len;
			maxlen=max(len,maxlen);
		}
	}

	Maxbits=0;
	while (maxlen) {
		Maxbits++;
		maxlen>>=1LLU;
	}

	//considering 64-bit architecture and sizeof long long is 64;
	ull offset1=0,offset2=0,e=-1,l=-1;

	for (ull i=0;i<N;i++) {
		for (ull j=0;j<i;j++) {

			ull len=len_all[i][j];
			ull val=cond_vec[i][j];

			if (!edge_db.size() || (offset1+len)>=64) {
				edge_db.push_back(0);
				offset1=0;
				e++;				
			}

			if (!len_db.size() || (offset2+Maxbits)>=64) {
				len_db.push_back(0);
				offset2=0;
				l++;				
			}

			val<<=offset1;
			offset1+=len;

			len<<=offset2;
			offset2+=Maxbits;

			edge_db[e]|=val;
			len_db[l]|=len;
		}

	}
}

void bit_expand(vector<ull> cond_vec[], vector<ull> len_db, vector<ull> edge_db)
{
	ull i=0,j=0,k=0,u=1,v=0,cnt=0;

	while (i<len_db.size() && j<edge_db.size() && u<N) {

		ull mask=(1LLU<<Maxbits)-1LLU;
		ull shift=len_db[i]&mask;

		mask=(1LLU<<shift)-1LLU;
		cond_vec[u][v++]=edge_db[j]&mask;

		if (v==u) {
			u++;
			v=0;
		}

		len_db[i]>>=Maxbits;
		edge_db[j]>>=shift;

		cnt+=Maxbits;

		if (len_db[i]==0 && cnt+Maxbits>63) {
			i++;
			cnt=0;
		}

		if (edge_db[j]==0) {
			j++;
		}

	}
}

int main()
{
	if (fopen("input3.txt","r")) {
		freopen("input3.txt","r",stdin);
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

	//print lower triangle matrix
	cout<<"Input Matrix is:-\n";
	print(cond_vec);

	vector<ull> len_db;
	vector<ull> edge_db;

	bit_reduce(cond_vec,len_db,edge_db);

	cout<<"\nStatic Length Bit reduced Matrix is:-\n";
	for (i=0;i<edge_db.size();i++)
		cout<<edge_db[i]<<" ";

	vector<ull> decom_vec[N];
	init(decom_vec);

	bit_expand(decom_vec,len_db,edge_db);
	
	cout<<"\n\nDecompressed Matrix\n";
	print(decom_vec);

	return 0;
}
