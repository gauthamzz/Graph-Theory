#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAX 100005
#define pll pair<ll,ll>
#define F first
#define S second
#define pb push_back
#define mp make_pair

ll n,m,tim=1;
vector<ll> adj[MAX];
ll parent[MAX], disc[MAX], low[MAX];
bool visited[MAX];
stack<pll> st;
vector<pll> biconn[MAX];
ll conn;

void dfs(ll u, bool block[], bool visited[])
{
	visited[u]=true;

	ll i;
	for (i=0;i<adj[u].size();i++) {
		ll v=adj[u][i];
		if (block[v] && !visited[v])
			dfs(v,block,visited);
	}
}

bool conn_comp(bool block[])
{
	ll i;
	for (i=1;i<=n;i++) {
		if (block[i] && !visited[i])
			dfs()
	}

}

void recur(bool block[])
{
	bool isblock=true;

	for (i=1;i<=n;i++)
		if (block[i]) {
			block[i]=false;
			if (!connected(block)) {

			}
		} 

}

int main()
{
	if (fopen("input.txt","r")) {
		freopen("input.txt","r",stdin);
		freopen("output.txt","w",stdout);
	}

	cin>>n>>m;

	ll u,v,i,j,M=m;
	while (m--) {
		cin>>u>>v;
		adj[u].pb(v);
		adj[v].pb(u);
	}