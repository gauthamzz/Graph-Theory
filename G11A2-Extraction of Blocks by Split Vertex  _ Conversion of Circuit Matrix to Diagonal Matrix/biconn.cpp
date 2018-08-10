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

void dfs(ll u)
{
	visited[u]=true;
	disc[u]=low[u]=(tim++);

	ll i,child=0;
	for (i=0;i<(ll)adj[u].size();i++) {
		ll v=adj[u][i];

		if (!visited[v]) {

			parent[v]=u;
			child++;
			st.push(mp(u,v));
			
			dfs(v);

			if ((parent[u] && low[v]>=disc[u]) || (!parent[u] && child>1)) { //to get articulation point
				
				while (st.top()!=mp(u,v)) {
					biconn[conn].pb(st.top());
					st.pop();
				}
				biconn[conn].pb(st.top());
				st.pop();

				conn++;
			}

			low[u]=min(low[u],low[v]);   //update low time
		}

		else if (parent[u] != v && disc[v]<low[u]) {     // a back edge and not direct cycle
			low[u]=disc[v];
			st.push(mp(u,v));
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

	for (i=1;i<=n;i++) {
		if (!visited[i])
			dfs(i);

		bool flag=false;
		while (!st.empty()) {
			flag=true;
			biconn[conn].pb(st.top());
			st.pop();
		}

		if (flag)
			conn++;
	}

	ll diag[conn][M];
	memset(diag,0LL,sizeof(diag));

	pll ind[M];
	ll k=0;

	//convert to diagonal matrix:-
	for (i=0;i<conn;i++) {
		for (j=0;j<biconn[i].size();j++,k++) {
			ind[k]=biconn[i][j];
			diag[i][k]=1;
		}
	}

	//the order of edges are as follows:-
	cout<<"      ";
	for (i=0;i<k;i++)
		cout<<ind[i].F<<"-"<<ind[i].S<<"  ";
	cout<<endl;

	//the matrix is as:-
	for (i=0;i<conn;i++) {
		cout<<"C"<<i+1<<": ";
		for (j=0;j<k;j++)
			cout<<"   "<<diag[i][j]<<" ";
		cout<<endl;
	}

	return 0;
}