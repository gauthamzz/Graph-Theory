#include<bits/stdc++.h>
using namespace std;
int v, n, gtype;
void makeGraph(vector < int > adjlist[], int indegree[]){
	for(int i=0; i<n; i++){
		int x, y;
		cin >> x >> y;
		adjlist[x].push_back(y);
		indegree[y]++;
		// for undirected graph
		if(gtype==1){
			adjlist[y].push_back(x);
		}
	}
}
void DFS(int src, int visited[], vector < int > adjlist[]){
	visited[src] = 1;
	for(int i=0; i<adjlist[src].size(); i++){
		if(!visited[adjlist[src][i]]){
			DFS(adjlist[src][i], visited, adjlist);
		}
	}
}
void reverseGraph(vector < int > adjlist[], vector < int > revgraph[]){
	for(int i=0; i<v; i++){
		for(int j=0; j<adjlist[i].size(); j++){
			revgraph[adjlist[i][j]].push_back(i);
		}
	}
}
bool isConnected(vector <int> adjlist[]){
	int visited[v];
	memset(visited, 0, sizeof(visited));
	int n;
	for(n=0; n<v; n++){
		if(adjlist[n].size()>0){
			break;
		}
	}
	// if no edges in graph
	if(n==v){
		return true;
	}
	DFS(n, visited, adjlist);
	for(int i=0; i<v; i++){
		if(adjlist[i].size()>0 && !visited[i]){
			return false;
		}
	}
	if(gtype==1){
		return true;
	}
	// strongly connected checking for directed graph
	vector < int > revgraph[v];
	reverseGraph(adjlist, revgraph);
	memset(visited, 0, sizeof(visited));
	DFS(n, visited, revgraph);
	for(int i=0; i<v; i++){
		if(adjlist[i].size()>0 && !visited[i]){
			return false;
		}
	}
	return true;
}
// Conditions checked for both directed and undirected to have Eulerian Circuit
bool checkGraph(vector < int > adjlist[], int indegree[]){
	if(!isConnected(adjlist)){
		return false;
	}
	if(gtype==0){
		for(int i=0; i<v; i++){
			if(indegree[i]!=adjlist[i].size()){
				return false;
			}
		}
	}else{
		for(int i=0; i<v; i++){
			if(adjlist[i].size() % 2 == 1){
				return false;
			}
		}
	}
	return true;
}
//Heirholzer's Algorithm
void printCycle(vector < int > adjlist[]){
	stack < int > currpath;
	vector < int > path;
	currpath.push(0);
	int temp = 0;
	while(!currpath.empty()){
		if(adjlist[temp].size()>0){
			currpath.push(temp);
			int next = adjlist[temp].back();
			adjlist[temp].pop_back();
			// Remove Both Edges from graph if graph is undirected eg: 0->1 and 1->0
			if(gtype==1){
				adjlist[next].erase(remove(adjlist[next].begin(), adjlist[next].end(), temp), adjlist[next].end());
			}
			temp = next;
		}else{
			path.push_back(temp);
			temp = currpath.top();
			currpath.pop();
		}
	}
	for(int i=path.size()-1; i>=0; i--){
		cout << path[i] << " ";
	}
}
int main(){
	int t;
	cin >> t;
	while(t--){
		cin >> v >> n >> gtype;
		//(Graphtype) gtype 1 -> undirected 
		//gtype 0 -> directed
		vector < int > adjlist[v];
		int indegree[v];
		memset(indegree, 0, sizeof(indegree));
		makeGraph(adjlist, indegree);
		bool valid = checkGraph(adjlist, indegree);
		if(valid){
			printCycle(adjlist);
			cout << "\n";
		}else{
			cout << "No Eulerian Circuit is Possible.\n";
		}
	}
	return 0;
}
