#include <bits/stdc++.h>
using namespace std;


bool iscomplete( vector < vector <int> > graph , int n ,vector <int> sgr )
{
	if(sgr.size() <= 1)
		return false;
	
	
	for(int i = 0;i < sgr.size() - 1;i++)
	{
		for(int j=i+1;j<sgr.size();j++)
		{
			int a = sgr[i] , b = sgr[j];
			if( graph[a][b] == 0 || graph[b][a] == 0 )
			{
				return false;
			}
		}
	}
	
	return true;
	
}

void _lcc( vector < vector <int> > graph , int n ,vector <int> sgr , vector <int> &msgr , int no)
{
	if(no == n)
	{
		if(iscomplete(graph , n , sgr))
		{
			if(msgr.size() < sgr.size())
			{
				msgr = sgr;	
			}	
		}	
		return;			
	}
	
	_lcc(graph , n , sgr , msgr , no+1);
	sgr.push_back(no);
	_lcc(graph , n , sgr , msgr , no+1);
	
}

vector <int> lcc( vector < vector <int> > graph , int n)
{
	
	vector <int> sgr;
	vector <int> msgr;
	
	_lcc(graph,n,sgr,msgr,0);	
	
	return msgr;
}


int main()
{
	
	int n; 		
/*	cout<<"Enter No of vertices"<<endl;	
	cin>>n;		 // input no of vertices
	cout<<"Enter edges one by one press -1 -1 to terminate"<<endl;
*/
cout<<"brute force"<<endl;
for(n = 10 ; n <= 20 ; n = n + 2){

	vector < vector <int> > graph(n);
	
	for(int i=0;i<n;i++)
	{
		graph[i].resize(n,0);
	}	
	

 	// vertices starts from 0 to n-1
	
	
	/*while(true)
	{
		int a,b;
		cin>>a>>b;
		if(a == -1 || b == -1)
			break;
			
		graph[a][b] = 1;
		graph[b][a] = 1;
	}
	*/	
	/*cout<<endl<<"Adjacency matrix"<<endl<<endl;
	
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
			cout<<graph[i][j]<<" ";
		cout<<endl;
	}
	cout<<endl;*/
	
	clock_t start;
	double duration;
	start = clock();
	
	vector<int> res = lcc(graph,n);
	
	duration = (clock() - start ) / (double) CLOCKS_PER_SEC;
	
	cout<<"time taken for n = "<<n<<"is "<<duration<<endl;
	
	
	/*cout<<endl<<"Largest Complete Subgraph"<<endl<<endl;
	for(int i=0;i<res.size();i++)
	{
		cout<<res[i]<<" ";
	}
	cout<<endl;*/
}
	return 0;
}
