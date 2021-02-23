/*
  url: https://www.acmicpc.net/problem/1260
*/

#include<iostream>
#include<vector>
#include<queue>

using namespace std;

void dfs(int node);
void bfs();

vector<vector<bool>> graph;
vector<bool> visited;
int N, M, V;

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> N >> M >> V;

	graph = vector<vector<bool>>(N, vector<bool>(N, false));
	visited = vector<bool>(N, false);

	for (int i = 0; i < M; i++) {
		int a, b;
		cin >> a >> b;
		graph[a - 1][b - 1] = true;
		graph[b - 1][a - 1] = true;
	}

	dfs(V - 1);
	visited = vector<bool>(N, false);
	cout << "\n";
	bfs();

	return 0;
}

void dfs(int node) {
	visited[node] = true;

	cout << node + 1 << " ";

	for (int i = 0; i < N; i++) {
		if (!visited[i] && graph[node][i]) {
			dfs(i);
		}
	}
}

void bfs() {
	queue<int> q;
	q.push(V - 1);
	visited[V - 1] = true;

	while (!q.empty()) {
		int node = q.front();
		q.pop();
		cout << node + 1 << " ";

		for (int i = 0; i < N; i++) {
			if (!visited[i] && graph[node][i]) {
				q.push(i);
				visited[i] = true;
			}
		}
	}
}
