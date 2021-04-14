/*
  url: https://codeforces.com/problemset/problem/839/C
  
  루트 노드에서 리프 노드까지의 모든 기대값을 더하면 되는 간단한 문제였지만,
  기대값을 계산하는 방법을 까먹어서 애를 먹었던 문제.
*/

#include<iostream>
#include<vector>

using namespace std;

double solve(int node);
void makeTree(int node);

int N;
vector<vector<int>> graph;
vector<vector<int>> tree;
vector<bool> visited;

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> N;
	graph = vector<vector<int>>(N, vector<int>());
	tree = vector<vector<int>>(N, vector<int>());
	visited = vector<bool>(N, false);
	for (int i = 1; i < N; i++) {
		int u, v;
		cin >> u >> v;
		graph[u - 1].push_back(v - 1);
		graph[v - 1].push_back(u - 1);
	}

	makeTree(0);
	double output = solve(0);
	printf("%.8lf\n", output);

	return 0;
}

double solve(int node) {
	double ret = 0;
	double ratio = (1.0 / tree[node].size());
	for (int next : tree[node]) {
		ret += ratio * (1 + solve(next));
	}

	return ret;
}

void makeTree(int node) {
	visited[node] = true;

	for (int next : graph[node]) {
		if (!visited[next]) {
			tree[node].push_back(next);
			makeTree(next);
		}
	}
}
