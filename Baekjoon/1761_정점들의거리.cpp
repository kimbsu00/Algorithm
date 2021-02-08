/*
  url: https://www.acmicpc.net/problem/1761
  
  트리는 어떤 노드를 루트로 하는지와 상관없이,
  두 정점 사이의 거리는 항상 일정하다.
  따라서 루트를 0번 노드로 설정해서 두 노드의 LCA 를 구해서 해결함.
*/

#include<iostream>
#include<vector>

using namespace std;

void makeGraph(int node);
int getDistance(int node1, int node2);
int getDepth(const int& node);

vector<vector<pair<int, int>>> tree;
vector<bool> visited;
vector<pair<int, int>> parent;

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int N;
	cin >> N;

	tree = vector<vector<pair<int, int>>>(N, vector<pair<int, int>>());
	visited = vector<bool>(N, false);
	parent = vector<pair<int, int>>(N, make_pair(-1, -1));

	for (int i = 1; i < N; i++) {
		int node1, node2, weight;
		cin >> node1 >> node2 >> weight;

		tree[node1 - 1].push_back(make_pair(node2 - 1, weight));
		tree[node2 - 1].push_back(make_pair(node1 - 1, weight));
	}

	makeGraph(0);

	int M;
	cin >> M;
	vector<int> answer(M);
	for (int i = 0; i < M; i++) {
		int node1, node2;
		cin >> node1 >> node2;
		answer[i] = getDistance(node1 - 1, node2 - 1);
	}

	for (int output : answer) {
		cout << output << "\n";
	}

	return 0;
}

void makeGraph(int node) {
	visited[node] = true;

	for (pair<int, int> next : tree[node]) {
		if (!visited[next.first]) {
			parent[next.first] = make_pair(node, next.second);
			makeGraph(next.first);
		}
	}
}

int getDistance(int node1, int node2) {
	int depth1 = getDepth(node1);
	int depth2 = getDepth(node2);

	int ret = 0;
	// node1 과 node2 의 depth 가 서로 다르면, 두 노드의 depth 를 먼저 맞춰주고
	if (depth1 < depth2) {
		while (depth1 != depth2) {
			ret += parent[node2].second;
			node2 = parent[node2].first;
			depth2 -= 1;
		}
	}
	else if (depth1 > depth2) {
		while (depth1 != depth2) {
			ret += parent[node1].second;
			node1 = parent[node1].first;
			depth1 -= 1;
		}
	}

	// 서로 한 칸씩 위로 올라가면 된다.
	while (node1 != node2) {
		ret += parent[node1].second;
		node1 = parent[node1].first;

		ret += parent[node2].second;
		node2 = parent[node2].first;
	}

	return ret;
}

int getDepth(const int& node) {
	int ret = 0;

	int next = node;
	while (next != -1) {
		next = parent[next].first;
		ret += 1;
	}

	return ret;
}
