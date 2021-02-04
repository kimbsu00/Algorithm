/*
  url: https://www.acmicpc.net/problem/2606
*/

#include<iostream>
#include<vector>

using namespace std;

void solve(int node);

vector<vector<int>> graph;
vector<bool> visited;
int infected = 0;

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int N, E;		// 컴퓨터의 수, 엣지의 수
	cin >> N >> E;

	graph = vector<vector<int>>(N, vector<int>());
	visited = vector<bool>(N, false);

	for (int i = 0; i < E; i++) {
		int a, b;
		cin >> a >> b;
		graph[a - 1].push_back(b - 1);
		graph[b - 1].push_back(a - 1);
	}

	solve(0);
	cout << infected - 1 << "\n";

	return 0;
}

void solve(int node) {
	if (visited[node])			return;

	infected += 1;
	visited[node] = true;
	for (int next : graph[node]) {
		solve(next);
	}
}
