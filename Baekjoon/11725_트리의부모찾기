/*
  url: https://www.acmicpc.net/problem/11725
  
  결과를 출력할 때, endl 을 이용하여 개행을 진행하면 시간초과가 발생하고, "\n" 문자를 출력해서 개행을 하면 시간초과가 나지 않는다.
  endl 함수가 느리다고는 알고 있었지만, 이렇게까지 느릴줄은 상상도 못했다..
*/

#include<iostream>
#include<vector>

using namespace std;

void solve(int node);

vector<vector<int>> tree;
vector<int> parent;
vector<bool> visited;

int main(void) {
	ios_base::sync_with_stdio(0); 
	cin.tie(0);

	int N;
	cin >> N;

	tree = vector<vector<int>>(N, vector<int>());
	parent = vector<int>(N);
	visited = vector<bool>(N, false);

	for (int i = 1; i < N; i++) {
		int a, b;
		cin >> a >> b;
		tree[a - 1].push_back(b - 1);
		tree[b - 1].push_back(a - 1);
	}

  // root 부터 부모를 찾기 시작한다.
	solve(0);

	for (int i = 1; i < N; i++) {
		cout << parent[i] + 1 << "\n";
	}

	return 0;
}

void solve(int node) {
	visited[node] = true;

  // dfs
	for (int i = 0; i < tree[node].size(); i++) {
		int next = tree[node][i];

		if (!visited[next]) {
			parent[next] = node;
			solve(next);
		}
	}
}
