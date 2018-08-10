//============================================================================
// Name        : Benchmark.cpp
// Author      : Bikki Jaiwal (ISM2014001) and Tara Prasad Tripathy (IHM2014003)
// Version     : 1.0
// Description : Program for obtaining isolated vertices from
//				 adjacency matrix and incidence matrix.
//				 It also performs benchmark analysis.
//============================================================================

#include <bits/stdc++.h>
#include "printcpp.h"
using namespace std;

#define wi(x) cout << #x << " = " << x << endl;
#define what_is(x) cout << #x << " = " << x << endl;

typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vi> vvi;

void print_graph(vvi &g) {
	int n = g.size();
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < g[0].size(); ++j) {
			cout << g[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

vi adjacency(vvi& matrix, bool benchmarking) {
	int vertices = matrix.size();

	bool visited[vertices];
	memset(visited, 0, sizeof(visited));

	for (int i = 0; i < vertices; i++) {
		if (!visited[i]) {
			int flag = 0;
			for (int j = 0; j < vertices; j++) {
				if (matrix[i][j] == 1) {
					flag = 1;
					visited[j] = 1;
				}
			}
			if (flag) {
				visited[i] = 1;
			}
		}
	}

	vi isolated_vertices;
	if (not benchmarking) {
		for (int i = 0; i < vertices; i++) {
			if (visited[i] == 0) {
				isolated_vertices.push_back(i + 1);
			}
		}
	}
	return isolated_vertices;
}

vi incidence(vvi& matrix, bool benchmarking) {
	int vertices = matrix.size();
	int edges = matrix[0].size();

	bool isolated[vertices];
	memset(isolated, 0, sizeof(isolated));

	for (int i = 0; i < vertices; i++) {
		int j;
		for (j = 0; j < edges; j++) {
			if (matrix[i][j] == 1) {
				break;
			}
		}
		if (j == edges) {
			isolated[i] = true;
		}
	}

	vi isolated_vertices;
	if (not benchmarking) {
		for (int i = 0; i < vertices; i++) {
			if (isolated[i])
				isolated_vertices.push_back(i + 1);
		}
	}
	return isolated_vertices;
}
const int STEPS = 25;
const int MIN_N = 10;
const int MAX_N = 500;
const int SPARSE_THRESHOLD = 15;
const int DENSE_THRESHOLD = 50;
const int MAX_TRIALS = 10;

int get_random(int l, int r) {
	return l + (rand() % (int) (r - l + 1));
}

int get_one_with_probability(int min_prob, int max_prob) {
	int n = get_random(1, 100);
	if (n <= max_prob && n > min_prob) {
		return 1;
	}
	return 0;
}

vvi get_adjacency_sparse_directed(int n) {
	vvi g(n, vi(n, 0));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (i == j)
				continue;
			g[i][j] = get_one_with_probability(0, SPARSE_THRESHOLD);
		}
	}
	return g;
}

vvi get_adjacency_sparse_undirected(int n) {
	vvi g(n, vi(n, 0));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < i; ++j) {
			g[i][j] = get_one_with_probability(0, SPARSE_THRESHOLD);
			g[j][i] = g[i][j];
		}
	}
	return g;
}

vvi get_adjacency_dense_directed(int n) {
	vvi g(n, vi(n, 0));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (i == j)
				continue;
			g[i][j] = get_one_with_probability(DENSE_THRESHOLD, 100);
		}
	}
	return g;
}

vvi get_adjacency_dense_undirected(int n) {
	vvi g(n, vi(n, 0));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < i; ++j) {
			g[i][j] = get_one_with_probability(DENSE_THRESHOLD, 100);
			g[j][i] = g[i][j];
		}
	}
	return g;
}

bool is_safe(int v1, int v2, set<pii> &visited) {
	if (visited.find(make_pair(v1, v2)) != visited.end()
			|| visited.find(make_pair(v2, v1)) != visited.end()) {
		return false;
	}
	return true;
}

vvi get_incidence_dense(int n) {
	double percent = get_random(DENSE_THRESHOLD, 100) / 100.0;
	int e = percent * ((n * (n - 1)) / 2.0);
	//what_is(e)
	//what_is(n)
	vvi matrix(n + 1, vi(e + 1, 0));
	set<pii> visited;
	for (int i = 1; i <= e; i++) {
		int v1 = get_random(1, n);
		int v2 = get_random(1, n);
		while (v1 == v2 or not is_safe(v1, v2, visited)) {
			v1 = get_random(1, n);
			v2 = get_random(1, n);
		}
		matrix[v1][i] = 1;
		matrix[v2][i] = 1;
		visited.insert(make_pair(v2, v1));
		visited.insert(make_pair(v1, v2));
	}
//	print_graph(matrix);
	vvi g(n, vi(e));
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= e; j++) {
			g[i - 1][j - 1] = matrix[i][j];
		}
	}
//	print_graph(g);
	return g;
}

vvi get_incidence_sparse(int n) {
	double percent = get_random(0, SPARSE_THRESHOLD) / 100.0;
	int e = percent * ((n * (n - 1)) / 2.0);
	vvi matrix(n + 1, vi(e + 1, 0));
	set<pii> visited;
	for (int i = 1; i <= e; i++) {
		int v1 = get_random(1, n);
		int v2 = get_random(1, n);
		while (v1 == v2 or not is_safe(v1, v2, visited)) {
			v1 = get_random(1, n);
			v2 = get_random(1, n);
		}
		matrix[v1][i] = 1;
		matrix[v2][i] = 1;
		visited.insert(make_pair(v2, v1));
		visited.insert(make_pair(v1, v2));
	}
	vvi g(n, vi(e));
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= e; j++) {
			g[i - 1][j - 1] = matrix[i][j];
		}
	}
	return g;
}

vvi get_random_graph(int n, bool adjacency, bool sparse, bool directed) {
	if (adjacency) {
		if (sparse && directed)
			return get_adjacency_sparse_directed(n);
		if (sparse && !directed)
			return get_adjacency_sparse_undirected(n);
		if (!sparse && directed)
			return get_adjacency_dense_directed(n);
		if (!sparse && !directed)
			return get_adjacency_dense_undirected(n);
	} else {
		if (sparse)
			return get_incidence_sparse(n);
		else
			return get_incidence_dense(n);
	}
	return vvi(n, vi(n, 0));
}

void get_times(const char* file_name, vi (*f)(vvi&, bool), bool adjacency, bool sparse,
		bool directed) {
	FILE *fp = fopen(file_name, "w");
	if (fp == NULL) {
		cerr << "File " << file_name << " couldn't be opened for reading." << endl;
		return;
	}
	what_is(file_name);
	for (int n = MIN_N; n <= MAX_N; n+=STEPS) {
		what_is(n);
		double average_time = 0;
		for (int trial = 1; trial <= MAX_TRIALS; trial++) {
			//what_is(trial);
			vvi g = get_random_graph(n, adjacency, sparse, directed);
			//print_graph(g);
			int start = clock();
			vi isolated = (*f)(g, true);
			//what_is(isolated);
			int finish = clock();

			double elapsed_secs = (finish - start) / (double) (CLOCKS_PER_SEC) * 1000;
			//what_is(elapsed_secs);
//			printf("Elapsed = %.9lf\n", n, elapsed_secs); // in milli seconds
			average_time += elapsed_secs;
		}
		average_time /= MAX_TRIALS;
		fprintf(fp, "%d %.9f\n", n, average_time); // in milli seconds
		what_is(average_time);
//		printf("Average = %.9f\n", n, average_time); // in milli seconds
	}
	fclose(fp);
}

int main() {
	//get_times("sparse_adj_dir.txt", adjacency, true, true, true);
	//get_times("sparse_adj_undir.txt", adjacency, true, true, false);
	//get_times("dense_adj_dir.txt", adjacency, true, false, true);
	//get_times("dense_adj_undir.txt", adjacency, true, false, false);

	get_times("dense_inci.txt", incidence, false, false, true);
	get_times("sparse_inci.txt", incidence, false, true, true);
	return 0;
}
