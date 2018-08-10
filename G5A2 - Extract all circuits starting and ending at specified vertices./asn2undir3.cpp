#include<bits/stdc++.h>
using namespace std;
 
// Class for an undirected graph
class Graph
{
       // Pointer to an array containing adjacency lists
    void extractAllPathsUtil(int , int , bool [], int [], int &,vector< vector<int> > &crs,bool extracted[]);
public:
	int V;    // No. of vertices
    list<int> *adj; 
    Graph(int V);   // Constructor
    void addEdge(int v, int w);   // to add an edge to graph
    void extractAllPaths(int s, int d,vector< vector<int> > &crs,bool extracted[]);
};
 
Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}
 
void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w); // Add w to v’s list.
    adj[w].push_back(v); // Add v to w’s list.
}
void print(vector<int> v){
	for(int i=0;i<v.size();i++)
		cout<<v[i]<<" ";
	cout<<endl;
}
// Prints all paths from 's' to 'd'
void Graph::extractAllPaths(int s, int d,vector< vector<int> > &crs,bool extracted[])
{
    // Mark all the vertices as not visited
    bool *visited = new bool[V];
 
    // Create an array to store paths
    int *path = new int[V];
    int path_index = 0; // Initialize path[] as empty
 
    // Initialize all vertices as not visited
    for (int i = 0; i < V; i++)
        visited[i] = false;
 
    // Call the recursive helper function to print all paths
    extractAllPathsUtil(s, d, visited, path, path_index, crs,extracted);
}
 
// A recursive function to print all paths from 'u' to 'd'.
// visited[] keeps track of vertices in current path.
// path[] stores actual vertices and path_index is current
// index in path[]
void Graph::extractAllPathsUtil(int u, int d, bool visited[],
                              int path[], int &path_index,vector< vector<int> > &crs,bool extracted[])
{
    // Mark the current node and store it in path[]
    visited[u] = true;
    path[path_index] = u;
    path_index++;
 
    // If current vertex is same as destination, then print
    // current path[]
    if (u == d&&path_index>2)
    {	
    	vector<int> v;
    //	v.pus
        for (int i = 0; i<path_index; i++)
        	v.push_back(path[i]);
        crs.push_back(v);
         //   cout << path[i] << " ";
        //cout << endl;
    }
    else // If current vertex is not destination
    {
        // Recur for all the vertices adjacent to current vertex
        list<int>::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
            if (!visited[*i]&&!extracted[*i])
                extractAllPathsUtil(*i, d, visited, path, path_index,crs,extracted);
    }
 
    // Remove current vertex from path[] and mark it as unvisited
    path_index--;
    visited[u] = false;
}
void printCircuits(vector< vector<int> > crs,int s){
	if(crs.size()==0){
		cout<<"No circuits are there\n";
	}
	for(int i=0;i<crs.size();i++){
		vector<int> v= crs[i];
	
		cout<<s<<" ";
		for(int j=0;j<v.size();j++){
			cout<<v[j]<<" ";
		}
		cout<<endl;
	}
}
int binSearch(vector<int> arr, int l, int r, int x)
{
  while (l <= r)
  {
    int m = l + (r-l)/2;
    if (arr[m] == x) 
        return m;  
    if (arr[m] < x) 
        l = m + 1; 
    else
         r = m - 1; 
  }
  return -1; 
}
bool edgeRepeat(vector<int> v1, vector<int> v2){
	int n=v1.size(),m=v2.size(),ind;
	for(int i=0;i<n;i++){
		ind=binSearch(v2,0,m-1,v1[i]);
		if(ind!=-1&&i+1<n&&ind+1<m&&v1[i+1]==v2[ind+1]){
			return true;
		}
	}
	return false;
}
int main()
{
    Graph g1(6);
    g1.addEdge(0, 1);
    g1.addEdge(1, 2);
    g1.addEdge(3, 2);
    g1.addEdge(0, 3);
    g1.addEdge(2, 0);
    g1.addEdge(1, 4);
    g1.addEdge(4, 5);
    g1.addEdge(5, 2);
    
    int s,d;
    while(1){
	
	    cout<<"Enter a vertex:\n";
	    cin>>s;
	    vector< vector<int> > crs;
	    bool *extracted = new bool[g1.V];
    	for (int i = 0; i < g1.V; i++)
        	extracted[i] = false;
	    list<int>::iterator i;
	    for (i = g1.adj[s].begin(); i != g1.adj[s].end(); ++i){
	    	g1.extractAllPaths(*i,s,crs,extracted);
	    	extracted[*i]=true;
		}
	   	printCircuits(crs,s);
	}
    return 0;
}
