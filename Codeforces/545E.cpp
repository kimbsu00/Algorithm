/*
  url: https://codeforces.com/problemset/problem/545/E
*/

#include<iostream>
#include<vector>
#include<queue>

#define LL long long

using namespace std;

class TPL {
public:
	int b;
	int weight;
	int index;
	TPL(int b, int weight, int index) : b(b), weight(weight), index(index) {}
};

class PKT {
public:
	LL length;
	int a, b, w, index;
	bool operator < (const PKT& other) const {
		return length > other.length;
	}
};

void Dijkstra(int start);

int N, M, root;
vector<TPL> graph[300005];
LL dist[300005];
bool visited[300005];
int edgeIndex[300005];
int edgeWeight[300005];

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		graph[u].push_back(TPL(v, w, i + 1));
		graph[v].push_back(TPL(u, w, i + 1));
	}
	cin >> root;
	Dijkstra(root);
	
	LL sum = 0;
	for (int i = 1; i <= N; i++) {
		if (i == root)			continue;
		sum += edgeWeight[i];
	}
	cout << sum << "\n";
	for (int i = 1; i <= N; i++) {
		if (i == root)			continue;
		cout << edgeIndex[i] << " ";
	}

	return 0;
}

void Dijkstra(int start) {
	memset(visited, false, sizeof(visited));

	priority_queue<PKT> pq;
	PKT p, q;
	p.length = 0, p.a = 0, p.b = start, p.w = 0, p.index = 0;
	pq.push(p);

	while (!pq.empty()) {
		p = pq.top();
		pq.pop();

		if (visited[p.b]) {
			if (p.length == dist[p.b] && p.w < edgeWeight[p.b]) {
				edgeWeight[p.b] = p.w;
				edgeIndex[p.b] = p.index;
			}
			continue;
		}

		visited[p.b] = true, dist[p.b] = p.length, edgeIndex[p.b] = p.index, edgeWeight[p.b] = p.w;
		for (int i = 0; i < graph[p.b].size(); i++) {
			q.length = dist[p.b] + graph[p.b][i].weight;
			q.a = p.b;
			q.b = graph[p.b][i].b;
			q.w = graph[p.b][i].weight;
			q.index = graph[p.b][i].index;
			pq.push(q);
		}
	}

	return;
}
