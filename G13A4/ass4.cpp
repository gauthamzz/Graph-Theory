/*    
 *  eat_code    
 *  IIIT Allahabad
 */
#include <bits/stdc++.h>
// #include "pretty_print.h"
using namespace std;

#define mp make_pair
#define mt make_tuple
#define pb push_back
#define CONTAINS(a, x) (a.find(x) != a.end())
#define ALL(x) x.begin(), x.end()
#define SZ(x) (int)x.size()
#define nl cout << endl
#define F first
#define S second

#define what_is(x) cout << #x << " = " << x << endl
#define boost ios::sync_with_stdio(false);cin.tie(NULL)
#define CASET int ___T, case_n = 1; cin >> ___T; while (___T-- > 0) 


#define rep(it, st, en) for(ll it = st; it < en; it++)
#define rep1(it, st, en) for(ll it = st; it <= en; it++)
#define per(it, st, en) for(ll it = en - 1; it >= st; it--)

typedef long long ll;
typedef pair<int, int> ii;
typedef pair<ll,ll> pll;

typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<bool> vb;
typedef vector<ii> vii;
typedef vector<vi> vvi;

ll INF = 1E9;
ll M = 1E9 + 7;

inline ll power (ll a,ll p){
    ll res = 1, x = a;
    while ( p ) {
        if ( p & 1 ) res = ( res * x );
        x = ( x * x ); p >>= 1;
    }
    return res;
}
template <typename T> ostream& operator<<(ostream& os, const vector<T> &p){os << "[ "; for (T x: p) os << x << " "; os << "]" << endl; return os;}
template <typename T> ostream& operator<<(ostream& os, const set<T> &p){os << "{ "; for (T x: p) os << x << " "; os << "}" << endl; return os;}
template <typename Tk, typename Tv> ostream& operator<<(ostream& os, const map<Tk, Tv> &p){os << "{ "; for (pair<Tk, Tv> x: p) os << x << " "; os << "}" << endl; return os;}
template <typename Tk, typename Tv> ostream& operator<<(ostream& os, const pair<Tk, Tv> &p){os << "{" << p.first << ',' << p.second << "}";return os;}
int v, e;
vvi graph;
vi parent;
set<ii> graph_edges, branches, chords;
vb vis; 
vector< set<ii> > ciruits, cutsets;
void print_tree(){
    for(int i = 0;i < v;i++){
        if(vis[i]){
            cout << "parent of "<< i << " is " << parent[i] << ".\n";
        }
    }
}  
void get_input(){
    cin >> v >> e;
    graph.resize(v);
    for(int i = 0;i < e;i++){
        int x, y;
        cin >> x >> y;
        x--;y--;
        graph[x].pb(y);
        graph[y].pb(x);
        graph_edges.insert({x, y});
        graph_edges.insert({y, x});
    } 
}
void dfs(int u){
    vis[u] = true;
    for(int v : graph[u]){
        if(!vis[v]){
            parent[v] = u;
            branches.insert({u, v});
            branches.insert({v, u});
            dfs(v);
        }
    }
}
void build_spanning_tree(){
    vis.assign(v, false);
    parent.assign(v, -1);
    int cc = 0;
    for(int i = 0;i < v;i++){
        if(!vis[i]){
            dfs(i);
            cc++;
        }
    }
    if(cc > 1){
        puts("Graph is a forest, take another input");
        exit(0);
    }
}
void get_chords(){
    for(ii e : graph_edges){
        if(branches.find(e) == branches.end()){
            chords.insert(e);
        }
    }
}
set<ii> get_circuit(ii chord){
    set<ii> ret;
    set<int> s;
    int u = chord.F, lca;
    while(u != -1){
        s.insert(u);
        u = parent[u]; 
    }
    u = chord.S;
    while(u != -1){
        if(s.find(u) != s.end()){
            lca = u;
            break;
        }
        u = parent[u]; 
    }
    u = chord.F;
    while(u != lca){
        ret.insert({u, parent[u]});
        ret.insert({parent[u], u});
        u = parent[u]; 
    }
    u = chord.S;
    while(u != lca){
        ret.insert({u, parent[u]});
        ret.insert({parent[u], u});
        u = parent[u]; 
    }
    return ret;
}
void get_fundamental_circuits(){
    //a fundamental ciruit is determined by a unique chord
    for(ii chord : chords){
        ciruits.pb(get_circuit(chord));
    }
    what_is(ciruits);
}
int main() {
    boost;
    if(fopen("input.txt", "r")){
      freopen("input.txt", "r", stdin);
      freopen("output.txt", "w", stdout);
    }
    get_input();
    what_is(graph);
    build_spanning_tree();
    print_tree();
    get_chords();
    what_is(chords);
    // get_fundamental_circuits();
    // get_fundamental_cutsets();
    return 0;
}
//  Train Insane or Remain the same
 