/*
  url: https://www.acmicpc.net/problem/11437
*/

#include<iostream>
#include<vector>

using namespace std;

void calculateParent(const int& node);
int solve(int node1, int node2);
int getDepth(const int& node);

vector<vector<int>> tree;
vector<int> parent;
vector<bool> visited;

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int N;
	cin >> N;

	tree = vector<vector<int>>(N, vector<int>());
	parent = vector<int>(N, -1);
	visited = vector<bool>(N, false);

	for (int i = 1; i < N; i++) {
		int a, b;
		cin >> a >> b;
		tree[a - 1].push_back(b - 1);
		tree[b - 1].push_back(a - 1);
	}

	calculateParent(0);

	int M;
	cin >> M;
	vector<int> answer(M);
	for (int i = 0; i < M; i++) {
		int node1, node2;
		cin >> node1 >> node2;
		answer[i] = solve(node1 - 1, node2 - 1) + 1;
	}

	for (int output : answer) {
		cout << output << "\n";
	}

	return 0;
}

void calculateParent(const int& node) {
	visited[node] = true;

	for (int next : tree[node]) {
		if (!visited[next]) {
			parent[next] = node;
			calculateParent(next);
		}
	}
}

int solve(int node1, int node2) {
	int depth1 = getDepth(node1);
	int depth2 = getDepth(node2);

	// node1 과 node2 의 depth 가 서로 다르면, 두 노드의 depth 를 먼저 맞춰주고
	if (depth1 < depth2) {
		while (depth1 != depth2) {
			node2 = parent[node2];
			depth2 -= 1;
		}
	}
	else if (depth1 > depth2) {
		while (depth1 != depth2) {
			node1 = parent[node1];
			depth1 -= 1;
		}
	}

	// 서로 한 칸씩 위로 올라가면 된다.
	while (node1 != node2) {
		node1 = parent[node1];
		node2 = parent[node2];
	}

	return node1;
}

int getDepth(const int& node) {
	int ret = 0;

	int next = node;
	while (next != -1) {
		next = parent[next];
		ret += 1;
	}

	return ret;
}
