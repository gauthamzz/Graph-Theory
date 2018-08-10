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
bool visited[MAX], AP[MAX];
vector<pll> bridges;
ll Acnt,Bcnt;

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
			
			dfs(v);

			if (parent[u] && low[v]>=disc[u]) { //to get articulation point
				AP[u]=true;
				Acnt++;
			}
			
			if (!parent[u] && child>1) {
			    AP[u]=true;
				Acnt++;
			}

			if (low[v]>disc[u]) { // to get bridges
			    if (u<v)
				    bridges.pb(mp(u,v));
				else
				    bridges.pb(mp(v,u));
				Bcnt++;
			}

			low[u]=min(low[u],low[v]);   //update low time
		}

		else if (parent[u] != v) {     // a back edge and not direct cycle
			low[u]=min(low[u],disc[v]);
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

	ll u,v,i;
	while (m--) {
		cin>>u>>v;
		adj[u+1].pb(v+1);
		adj[v+1].pb(u+1);
	}

	for (i=1;i<=n;i++) {
		if (!visited[i]) {
			dfs(i);
		}
	}

	//get all articulation points
	cout<<Acnt<<endl;
	for (i=1;i<=n;i++)
	    if (AP[i]) 
	        cout<<i-1<<" ";
    cout<<endl;

	//get all bridges
	cout<<Bcnt<<endl;
	sort(bridges.begin(),bridges.end());
	for (i=0;i<bridges.size();i++)
		cout<<bridges[i].F-1<<" "<<bridges[i].S-1<<endl;

	return 0;
}