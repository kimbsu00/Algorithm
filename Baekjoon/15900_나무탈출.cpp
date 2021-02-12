/*
  url: https://www.acmicpc.net/problem/15900
  
  "Yes" 를 "YES"로,
  "No" 를 "NO" 로 출력해서 오답처리 받았던 문제.
*/

#include<iostream>
#include<vector>

using namespace std;

void makeGraph(int node);
int solve(int node, int level);

vector<vector<int>> tree;
vector<vector<int>> directedGraph;
vector<bool> visited;

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int N;
	cin >> N;

	tree = vector<vector<int>>(N, vector<int>());
	directedGraph = vector<vector<int>>(N, vector<int>());
	visited = vector<bool>(N, false);

	for (int i = 1; i < N; i++) {
		int a, b;
		cin >> a >> b;

		tree[a - 1].push_back(b - 1);
		tree[b - 1].push_back(a - 1);
	}

	makeGraph(0);

	int sum = solve(0, 0);
	if (sum % 2) {
		cout << "Yes\n";
	}
	else {
		cout << "No\n";
	}

	return 0;
}

void makeGraph(int node) {
	visited[node] = true;

	for (int next : tree[node]) {
		if (!visited[next]) {
			directedGraph[node].push_back(next);
			makeGraph(next);
		}
	}
}

int solve(int node, int level) {
	int ret = 0;

	for (int next : directedGraph[node]) {
		ret += solve(next, level + 1);
	}

	if (ret == 0)			return level;

	return ret;
}
