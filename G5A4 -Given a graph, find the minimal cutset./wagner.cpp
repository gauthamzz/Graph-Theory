/*
 * An implementation of Stoer-Wagner algorithm to find a global min-cut in UNDIRECTED GRAPHS with matrix representation.
 * The running time of this implementation is O(V^3).
 * See http://www.giaithuatlaptrinh.com/?p=553 for more details.
 * The program is not fully tested, use at your own risk.
 *
 *  Created on: Nov 30, 2016
 *      Author: hunglv
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define TRUE 1
#define FALSE 0
#define INFTY 1000000
#define MAX 1000



int W[MAX][MAX];	// the weight matrix
int Del[MAX];
int n;				// the number of veritces
int m;				// the number of edges

void read();
int StoerWagner();
int minCutPhase(int V);
int maxStickiness(int *T, int *L);
void merge(int s, int t);

int main(){
	read();
	printf("The global mincut value: %d\n", StoerWagner());
}

int minCutPhase(int V){
	int i = 0, j = 0;
	int s[2];
	if(V  == 2) {
		for( i = 0; i < n; i++){
			if(Del[i] == FALSE){
				s[j] = i; j++;
			}
		}
		return W[s[0]][s[1]];
	}
	int L[n], T[n];
	memset(L, 0, n*sizeof(int));
	memset(T, FALSE, n*sizeof(int));
	i = 1;	// the number of vertices in the tree T
	j = 0;
	int v,u;
	while( i <= V){
		v = maxStickiness(T,L);
		T[v] = TRUE;
		for(u = 0; u < n; u++){
			if(W[v][u] != 0 && Del[u] == FALSE && T[u] == FALSE){
				L[u] = L[u] + W[u][v];
			}
		}
		if( i >= V-1){
			s[j] = v; j++;
		}
		i++;
	}
	merge(s[0], s[1]);
	return L[s[1]];	
}

void merge(int s, int t){
	int v = 0;
	for(v = 0; v < n; v++){
		if(Del[v] == FALSE && v != s && v!= t){
			W[s][v] = W[s][v] + W[v][t];
			W[v][s] = W[s][v];
		}
	}
	Del[t] = TRUE;	
}

int maxStickiness(int *T, int *L){
	int i = 0;
	int v = 0;
	int max = 0;
	for(i = 0; i < n; i++){
		if(Del[i] == FALSE && T[i] == FALSE && max < L[i]){
			v = i;
			max = L[i];
		} 
	}
	return v;
}
int StoerWagner(){
	int V  = n;
	int C = INFTY;
	memset(Del, FALSE, n*sizeof(int));
	for(V = n; V > 1; V--){
		int cutValue = minCutPhase(V);
		C = (C < cutValue ? C: cutValue);	
	}
	return C;
}

// specify the input graph
void read(){
	n = 6, m = 9;
	int i = 0, j = 0;
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++) W[i][j] = 0;
	}
	W[0][1] = 1;
	W[1][0] = 1;
	W[0][3] = 3;
	W[3][0] = 3;
	W[0][4] = 1;
	W[4][0] = 1;
	W[0][5] = 2;
	W[5][0] = 2;
	W[1][2] = 5;
	W[2][1] = 5;
	W[1][4] = 2;
	W[4][1] = 2;
	W[2][4] = 1;
	W[4][2] = 1;
	W[3][4] = 2;
	W[4][3] = 2;
	W[3][5] = 2;
	W[5][3] = 2;
}

/* 
Other graphs to test
void read(){
	n = 6, m = 7;
	int i = 0, j = 0;
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++) W[i][j] = 0;
	}
	W[0][1] = 2;
	W[1][0] = 2;
	W[0][2] = 3;
	W[2][0] = 3;
	W[1][2] = 1;
	W[2][1] = 1;
	W[2][3] = 2;
	W[3][2] = 2;
	W[3][4] = 1;
	W[4][3] = 1;
	W[3][5] = 3;
	W[5][3] = 3;
	W[4][5] = 3;
	W[5][4] = 3;
}
void read(){
	n = 2, m = 1;
	int i = 0, j = 0;
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++) W[i][j] = 0;
	}
	W[0][1] = 2;
	W[1][0] = 2;
}*/
