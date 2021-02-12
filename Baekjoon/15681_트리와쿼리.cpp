/*
  url: https://www.acmicpc.net/problem/15681
*/

#include<iostream>
#include<vector>

using namespace std;

int makeGraph(int node);

vector<vector<int>> tree;
vector<bool> visited;
vector<int> childNum;

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int N, R, Q;
	cin >> N >> R >> Q;

	tree = vector<vector<int>>(N, vector<int>());
	visited = vector <bool>(N, false);
	childNum = vector<int>(N, 0);

	for (int i = 1; i < N; i++) {
		int a, b;
		cin >> a >> b;
		tree[a - 1].push_back(b - 1);
		tree[b - 1].push_back(a - 1);
	}

	makeGraph(R - 1);

	vector<int> answer(Q);
	for (int i = 0; i < Q; i++) {
		int query;
		cin >> query;
		answer[i] = childNum[query - 1] + 1;
	}

	for (int output : answer) {
		cout << output << "\n";
	}

	return 0;
}

int makeGraph(int node) {
	visited[node] = true;

	int ret = 0;
	for (int next : tree[node]) {
		if (!visited[next]) {
			ret += makeGraph(next) + 1;
		}
	}

	return childNum[node] = ret;
}
