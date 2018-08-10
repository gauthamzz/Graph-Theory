#include <bits/stdc++.h>
using namespace std;


void dfs(int s , bool visited[] , vector< vector<int> > graph , int n)
{
	visited[s] = true;
//	cout<<s<<" ";
	for(int i=0;i<n;i++)
	{
		if(graph[s][i] == 1 && !visited[i])
		{
			dfs(i , visited ,graph , n);
		}
	}
}

void reverse_edges(vector < vector<int> > &graph , int n)
{
	vector< vector<int> > tra = graph;
	
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
			graph[i][j] = tra[j][i];
	}
}

void fun(int i,bool visited[] , vector < vector <int> > graph ,int  n , stack<int> &Stack)
{
	visited[i] = true;
 
    // Recur for all the vertices adjacent to this vertex
    
    for(int j = 0 ; j<n; j++){
        
		if(graph[i][j] == 1 && !visited[j])
            fun(j,visited,graph,n,Stack);
	
	}
	
    // All vertices reachable from v are processed by now, push v 
    
    Stack.push(i);
}


int main()
{
	
	int n; 		//no of vertices
	
	for(n = 600 ; n <= 1500 ; n = n+100){
	
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
	
	int edges = n + n;
	while(edges--)
	{
		int x = rand()%n;
		int y = rand()%n;
		
		if(x != y)
		{
			graph[x][y] = 1;
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
	
/*	cout<<endl<<"Adjacency matrix"<<endl<<endl;
	
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
			cout<<graph[i][j]<<" ";
		cout<<endl;
	}
	cout<<endl;
*/	
	bool visited[n];
	
	
	for(int i=0;i<n;i++)
		visited[i] = false; 
		
		// below code for bfs of graph
	int count = 0; // count for connected components
	
	//cout<<"Disconnected components are"<<endl<<endl;
	
	stack<int> Stack;
	
	clock_t start;
	double duration;
	start = clock();
	
	
	for(int i = 0; i < n ;i++)
	{
		if(visited[i] == false)
		{
			fun(i,visited , graph , n , Stack);
		}
	}
	
	reverse_edges(graph,n);
	
	for(int i=0;i<n;i++)
		visited[i] = false; 
		
	while (!Stack.empty())
    {
        // Pop a vertex from stack
        int v = Stack.top();
        Stack.pop();
 
        // Print Strongly connected component of the popped vertex
        if (visited[v] == false)
        {
           dfs(v, visited,graph,n);
          // cout << endl;
            count++;
        }
    }	
	
	duration = (clock() - start ) / (double) CLOCKS_PER_SEC;
	
	cout<<"time taken = "<<duration<<" ";
	
	cout<<" "<<"No of components are = "<<count<<endl<<endl;
}
	
	return 0;
}
