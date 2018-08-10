#include <bits/stdc++.h>
using namespace std;
bool BFS(map<int,int> graph[],int src,int dest,int parent[],int n)
{
	bool visited[n];
	memset(visited,false,sizeof(visited));
	queue<int> q;
	q.push(src);
	visited[src] = true;
	parent[src] = -1;
	while(!q.empty())
	{
		int u = q.front();
		q.pop();
		if(u==dest)
		{
			return true;
		}
		map<int,int>::iterator it;
		for(it=graph[u].begin();it!=graph[u].end();it++)
		{
			int v = (*it).first;
			int capacity = (*it).second;
			if(!visited[v]&&capacity>0)
			{
				q.push(v);
				visited[v] = true;
				parent[v] = u;
			}
		}
	}
	return false;
}
int FordFulkerson(map<int,int> graph[],int src,int dest,int n)
{
	int parent[n];
	memset(parent,-1,sizeof(parent));
	map<int,int> residue[n];
	for(int i=0;i<n;i++)
	{
		residue[i] = graph[i];
	}
	int maxflow = 0;
	while(BFS(residue,src,dest,parent,n))
	{
		int pathflow = INT_MAX;
		for(int v=dest;v!=src;v=parent[v])
		{
			int u = parent[v];
			pathflow = min(residue[u][v],pathflow);
		}
		for(int v=dest;v!=src;v=parent[v])
		{
			int u = parent[v];
			residue[u][v] -= pathflow;
			residue[v][u] += pathflow;
		}
		maxflow += pathflow;
	}
	return maxflow;
}
int main()
{
	int n,m;
	cout << "Enter the number of vertices and edges\n"; 
	cin >> n >> m;
	map<int,int> graph[n];
	cout << "Enter the edges\n";
	for(int i=0;i<m;i++)
	{
		int u,v,c;
		cin >> u >> v >> c;
		graph[u-1][v-1] = c;
	}
	for(int i=0;i<n;i++)
	{
		map<int,int>::iterator it;
		for(it=graph[i].begin();it!=graph[i].end();it++)
		{
			int v = (*it).first;
			if(graph[v].find(i)==graph[v].end())
			{
				graph[v][i] = 0;
			}
		}
	}
	int src,dest;
	cout << "Enter the source and sink for maximum flow\n";
	cin >> src >> dest;
	int ans = FordFulkerson(graph,src-1,dest-1,n);
	cout << ans << "\n";
	return 0;
}