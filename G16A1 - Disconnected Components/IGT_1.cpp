#include <bits/stdc++.h>
using namespace std;


void bfs(int s , bool visited[] , vector < vector <int> > graph , int n)
{
	
	queue<int> q;
	q.push(s);
	visited[s] = true;
	while(!q.empty()){	
		s = q.front();
		q.pop();
	//	cout<<s<<" ";	
		for(int i=0;i<n;i++)
		{
			if(graph[s][i] == 1 && visited[i] == false)  // i is adjacent to s i.e. source
			{
				visited[i] = true;
				q.push(i);
			}
		}
	}
	//cout<<endl<<endl;
}

int main()
{
	
	int n; 		//no of vertices
	
	for(n = 500 ; n <= 1500 ; n = n+100){
	cout<<"no of vertices = "<<n<<" ";
	
	//cin>>n;		 // input no of vertices
//	cout<<"Enter edges one by one press -1 -1 to terminate"<<endl;
	
	vector < vector <int> > graph(n);
	
	for(int i=0;i<n;i++)
	{
		graph[i].resize(n,0);
	}	
	

 	// vertices starts from 0 to n-1
	
	srand((int)time(0));
	
	int edges = n + n/2 ;
	while(edges--)
	{
		int x = rand()%n;
		int y = rand()%n;
		
		if(x != y)
		{
			graph[x][y] = 1;
			graph[y][x] = 1;
		}
	}
	
	/*while(true)
	{
		int a,b;
		cin>>a>>b;
		if(a == -1 || b == -1)
			break;
			
		graph[a][b] = 1;
		graph[b][a] = 1;
	}*/
	
	/*cout<<endl<<"Adjacency matrix"<<endl<<endl;
	
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
			cout<<graph[i][j]<<" ";
		cout<<endl;
	}
	cout<<endl;*/
	
	bool visited[n];
	
	
	for(int i=0;i<n;i++)
		visited[i] = false; 
		
		// below code for bfs of graph
	int count = 0; // count for connected components
	
	//cout<<"Disconnected components are"<<endl<<endl;
	
	clock_t start;
	double duration;
	start = clock();
	
	for(int i = 0; i<n ;i++)
	{
		if(visited[i] == false)
		{
			bfs(i,visited , graph , n);
			count++;
		}
	}
	
	duration = (clock() - start ) / (double) CLOCKS_PER_SEC;
	
	cout<<"time taken = "<<duration<<" ";
	
	cout<<" "<<"No of components are = "<<count<<endl<<endl;
}
	
	return 0;
}
