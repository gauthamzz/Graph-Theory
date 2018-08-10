#include <bits/stdc++.h>
using namespace std;
#define N 6
bool BFS(int graph[N][N],int src,int dest,int parent[])
{
	bool visited[N];
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
		for(int v=0;v<N;v++)
		{
			if(!visited[v]&&graph[u][v]>0)
			{
				q.push(v);
				visited[v] = true;
				parent[v] = u;
			}
		}
	}
	return false;
}
int FordFulkerson(int graph[N][N],int src,int dest)
{
	int parent[N];
	memset(parent,-1,sizeof(parent));
	int residue[N][N];
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)
		{
			residue[i][j] = graph[i][j];
		}
	}
	int maxflow = 0;
	while(BFS(residue,src,dest,parent))
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
	int graph[N][N];
	cout << "Enter the adjacency matrix\n";
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)
		{
			cin >> graph[i][j];
		}
	}
	int src,dest;
	cout << "Enter the source and sink for maximum flow\n";
	cin >> src >> dest;
	int ans = FordFulkerson(graph,src-1,dest-1);
	cout << ans << "\n";
	return 0;
}