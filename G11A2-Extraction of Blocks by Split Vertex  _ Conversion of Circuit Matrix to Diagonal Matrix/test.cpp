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
ll even,odd;

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

			if (parent[u] && low[v]>=disc[u]) { //to get articulation point
			    set<ll> vert;
				while (st.top()!=mp(u,v)) {
				    vert.insert(st.top().F);
				    vert.insert(st.top().S);
					st.pop();
				}
			    vert.insert(st.top().F);
			    vert.insert(st.top().S);
				st.pop();
				
				if (vert.size()&1)
				    odd++;
			    else if (vert.)
			        even++;
			}
			
			if (!parent[u] && child>1) {
                set<ll> vert;
				while (st.top()!=mp(u,v)) {
				    vert.insert(st.top().F);
				    vert.insert(st.top().S);
					st.pop();
				}
			    vert.insert(st.top().F);
			    vert.insert(st.top().S);
				st.pop();
				
				if (vert.size()&1)
				    odd++;
			    else
			        even++;
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

	ll u,v,i;
	while (m--) {
		cin>>u>>v;
		adj[u+1].pb(v+1);
		adj[v+1].pb(u+1);
	}

	for (i=1;i<=n;i++) {
		if (!visited[i]) {
			dfs(i);
			set<ll> vert;
			while (!st.empty()) {
			    vert.insert(st.top().F);
			    vert.insert(st.top().S);
				st.pop();
			}
			
			if (vert.size()&1)
			    odd++;
		    else
		        even++;
		}
	}

    cout<<even<<" "<<odd<<endl;
	return 0;
}