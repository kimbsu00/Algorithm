/*
  url: https://codeforces.com/problemset/problem/449/B
*/

#include<iostream>
#include<queue>
#include<vector>

#define LL long long

using namespace std;

class Edge {
public:
	LL weight;
	// 도착 노드, 엣지 타입 { 1=normal, 2=train }
	int to, type;
	Edge(int to, LL weight, int type) : to(to), weight(weight), type(type) {}
};

class PKT {
public:
	int from, to, type;
	LL weight;
	bool operator < (const PKT& other) const {
		if (weight == other.weight)
			return type > other.type;
		return weight > other.weight;
	}
};

void Dijkstra(int start);

int N, M, K;
vector<Edge> graph[100005];
int edgeType[100005];
LL dist[100005];
bool visited[100005];

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> N >> M >> K;
	for (int i = 0; i < M; i++) {
		int u, v;
		LL x;
		cin >> u >> v >> x;
		graph[u].push_back(Edge(v, x, 1));
		graph[v].push_back(Edge(u, x, 1));
	}
	for (int i = 0; i < K; i++) {
		int s;
		LL y;
		cin >> s >> y;
		graph[1].push_back(Edge(s, y, 2));
		graph[s].push_back(Edge(1, y, 2));
	}

	Dijkstra(1);

	int temp = 0;
	for (int i = 2; i <= N; i++) {
		if (edgeType[i] == 2)
			temp += 1;
	}
	cout << K - temp << "\n";

	return 0;
}

void Dijkstra(int start) {
	memset(visited, false, sizeof(visited));

	priority_queue<PKT> pq;
	PKT p, q;
	p.from = 0, p.to = start, p.weight = 0, p.type = 0;
	pq.push(p);

	while (!pq.empty()) {
		p = pq.top();
		pq.pop();
		if (visited[p.to])			continue;

		visited[p.to] = true, dist[p.to] = p.weight, edgeType[p.to] = p.type;
		for (int i = 0; i < graph[p.to].size(); i++) {
			q.from = p.to;
			q.to = graph[p.to][i].to;
			q.type = graph[p.to][i].type;
			q.weight = dist[p.to] + graph[p.to][i].weight;
			pq.push(q);
		}
	}
	return;
}
