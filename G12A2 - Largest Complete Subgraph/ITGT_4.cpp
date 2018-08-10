#include <bits/stdc++.h>

using namespace std;

vector <int> ans;

vector<int> FI(vector<int> a , vector<int> b,int n)
{
	vector<int> res;
	
	bool hash[n];
	
	for(int i=0;i<n;i++)
		hash[i] = false;
	
	
	for(int i=0;i<a.size();i++)
	{
		hash[a[i]] = true;
	}
	
	for(int i = 0 ; i<b.size();i++)
	{
		if(hash[b[i]])
		{
			res.push_back(b[i]);
		}
	}
	
	
	/*if(a.size() != 0 && b.size() != 0){
		res.resize( a.size() + b.size() );
		sort(a.begin(),a.end());
		sort(b.begin(),b.end());
		vector <int> :: iterator it;
		it = set_intersection (a.begin(), a.end(), b.begin(), b.end(), res.begin());
		res.resize(it - res.begin());
	}*/
	
	return res;
}

vector<int> FU(vector<int> a , int v)
{
	a.push_back(v);
	return a;
}


void fun( vector <int> P,vector <int> R,vector <int> X, vector < vector <int> > graph , int n , int depth)
{
	for(int i=0;i<depth;i++)
	{
		cout<<"\t";
	}
	
	cout<<"fun(";
	
	cout<<" { ";
	for(int i=0;i<R.size();i++)
		cout<<R[i]<<" ";
	cout<<" } ";
	
	cout<<" { ";
	for(int i=0;i<P.size();i++)
		cout<<P[i]<<" ";
	cout<<" } ";
	
	cout<<" { ";
	for(int i=0;i<X.size();i++)
		cout<<X[i]<<" ";
	cout<<" } ";
	
	cout<<") ";
	
	
	if(P.size() == 0 && X.size() == 0)
	{
		/*cout<<"Maximal Clique :"<<endl;
		for(int i=0;i<R.size();i++)
			cout<<R[i]<<" ";
		cout<<endl<<endl; */
		
		cout<<" -------->  Maximal Clique"<<endl;
		
		if(ans.size() < R.size())
			ans  = R;			
		return;
	}
	
	cout<<endl;
	
	vector <int > Pt = P;
	
	for(int i = 0;i<Pt.size();i++)
	{
		int v = Pt[i];
		fun( FI(P,graph[v],n) , FU(R , v) , FI( X ,  graph[v],n) , graph , n,depth+1);
		P.erase(P.begin());
		X = FU(X , v);
	}
}


int main()
{
	int n,a;
	cin>>n;
	vector < vector <int> > graph;
	
	cout<<"-1 to end"<<endl<<endl;
	
	for(int i=0;i<n;i++)
	{
		cout<<"Enter Neighbours of "<<i<<endl;
		vector <int> nb;
		while(true){
			cin>>a;
			
			if(a == -1)
				break;
				
			nb.push_back(a);
		}
		graph.push_back(nb);
	}
	
	/*for(int i=0;i<n;i++)
	{
		for(int j=0;j<graph[i].size();j++)
			cout<<graph[i][j]<<" ";
		cout<<endl;
	}
	*/
	
	vector <int> P,R,X;
	
	for(int i=0;i<n;i++)
	{
		P.push_back(i);
	}
	
	cout<<endl<<endl;
	
	
	fun(P,R,X,graph,n,0);	
	cout<<endl<<endl<<"Largest Complete Subgraph"<<endl<<endl;
	for(int i=0;i<ans.size();i++)
	{
		cout<<ans[i]<<" ";
	}
	cout<<endl;
	return 0;
}

 

