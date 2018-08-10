#include <bits/stdc++.h>
using namespace std;
#define ull unsigned long long int

ull N,M,Base,Maxlen;
ull size_of_cond_vec=0;
ull size_of_edge_bd=0;
void init(vector<ull> cond_vec[])
{
	for (ull i=0;i<N;i++) {
		for (ull j=0;j<i;j++){
			cond_vec[i].push_back(0);
			size_of_cond_vec++;
		}
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
	size_of_edge_bd=e+1;
}

void bit_expand(vector<ull> cond_vec[], vector<ull> edge_db)
{
	ull j=0,k=0,u=1,v=0;
	ull offset=0;
	while (j<edge_db.size() && u<N) {

		ull mask=(1LLU<<Maxlen)-1LLU;
		offset=offset+Maxlen;
		if(offset>=64){
			j++;
			offset=Maxlen;
		}
		cond_vec[u][v++]=edge_db[j]&mask;
		if (v==u) {
			u++;
			v=0;
		}
		edge_db[j]>>=Maxlen;
	}
}

int main()
{
	if (fopen("input1.txt","r")) {
		freopen("input18.txt","r",stdin);
		freopen("static_size.txt","a",stdout);
	}
	/*FILE *f2;
	f2=fopen("static_decomp_tim.txt","a");*/
	ull i,u,v,j;
	clock_t begin1,begin2,end1,end2;
	double t1,t2;
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
	//print(cond_vec);

	vector<ull> edge_db;
	//begin1=clock();
	bit_reduce(cond_vec,edge_db);
	cout<<N<<" "<<sizeof(ull)*size_of_cond_vec<<" "<<sizeof(ull)*size_of_edge_bd<<" "<<edge_db.size()<<endl;
	/*end1=clock();
	t1=((double)(end1-begin1))/(double)CLOCKS_PER_SEC*1000;
	cout<<N<<" "<<t1<<endl;*/
	/*
	for(i=0;i<edge_db.size();i++){
		cout<<edge_db[i]<<endl;
	}*/
	/*
	vector<ull> decom_vec[N];
	
	init(decom_vec);
	begin2=clock();
	bit_expand(decom_vec,edge_db);
	end2=clock();
	t2=((double)(end2-begin2))/(double)CLOCKS_PER_SEC*1000;
	fprintf(f2,"%llu %lf\n",N,t2);
	fclose(f2);
	//cout<<N<<" "<<t2<<endl;
	//print(decom_vec);
	*/
	return 0;
}
