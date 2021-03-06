/*
  url: https://www.acmicpc.net/problem/13511
  
  2021-03-06
  시간초과 발생하는 코드
  나중에 다시 풀어보자.
*/

#include<iostream>
#include<vector>
#include<stack>

using namespace std;

void makeGraph(int node, int _depth);
void calculateDist(int node, int weight);
int getLCA(int node1, int node2);
int getKthNode(int from, int to, int mid);

int N;
vector<vector<pair<int, int>>> tree;
vector<vector<pair<int, int>>> directedGraph;
vector<int> depth;
vector<int> parent;
vector<bool> visited;
vector<long long> dist;

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> N;
	tree = vector<vector<pair<int, int>>>(N, vector<pair<int, int>>());
	directedGraph = vector<vector<pair<int, int>>>(N, vector<pair<int, int>>());
	depth = vector<int>(N, 0);
	parent = vector<int>(N, -1);
	visited = vector<bool>(N, false);
	dist = vector<long long>(N, 0);
	for (int i = 1; i < N; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		tree[u - 1].push_back(make_pair(v - 1, w));
		tree[v - 1].push_back(make_pair(u - 1, w));
	}

	makeGraph(0, 0);
	calculateDist(0, 0);

	int M;
	cin >> M;
	vector<long long> answer;
	while (M--) {
		int q;
		cin >> q;
		if (q == 1) {
			int from, to;
			cin >> from >> to;
			answer.push_back(dist[from - 1] + dist[to - 1] - dist[getLCA(from - 1, to - 1)] * 2);
		}
		else if (q == 2) {
			int from, to, mid;
			cin >> from >> to >> mid;
			answer.push_back(getKthNode(from - 1, to - 1, mid - 1));
		}
	}

	for (long long output : answer) {
		cout << output << "\n";
	}

	return 0;
}

void makeGraph(int node, int _depth) {
	visited[node] = true;
	depth[node] = _depth;

	for (pair<int, int> p : tree[node]) {
		int next = p.first;
		int n_weight = p.second;

		if (!visited[next]) {
			directedGraph[node].push_back(p);
			parent[next] = node;
			makeGraph(next, _depth + 1);
		}
	}
}

void calculateDist(int node, int weight) {
	dist[node] = weight;

	for (pair<int, int> p : directedGraph[node]) {
		int next = p.first;
		int n_weight = p.second;

		calculateDist(next, weight + n_weight);
	}
}

int getLCA(int node1, int node2) {
	int depth1 = depth[node1];
	int depth2 = depth[node2];

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

int getKthNode(int from, int to, int mid) {
	int lca = getLCA(from, to);
	int depth1 = depth[from];
	int depth2 = depth[to];
	int depth3 = depth[lca];

	int ret = -1;
	if (depth1 - depth3 > mid) {
		ret = from;
		while (mid--) {
			ret = parent[ret];
		}
	}
	else {
		int count = (depth1 + depth2 - depth3 * 2) - mid;
		ret = to;
		while (count--) {
			ret = parent[ret];
		}
	}

	return ret + 1;
}
