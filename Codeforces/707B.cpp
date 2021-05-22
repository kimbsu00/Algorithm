/*
  url: https://codeforces.com/problemset/problem/707/B
  
  이전에 해결했었던 Algospot의 FIRETRUCK 문제와 유사한 문제라서 쉽게 해결했던 문제.
*/

#include<iostream>
#include<vector>
#include<queue>
#include<limits>
#include<algorithm>

#define LL long long

using namespace std;

vector<LL> Dijkstra(LL start);

const LL INF = numeric_limits<LL>::max();
LL N, M, K;
vector<vector<pair<LL, LL>>> graph;
vector<LL> storage;

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> N >> M >> K;
	graph.resize(N + 1, vector<pair<LL, LL>>());
	storage.resize(K);

	for (int i = 0; i < M; i++) {
		LL u, v, l;
		cin >> u >> v >> l;
		graph[u].push_back({ l,v });
		graph[v].push_back({ l,u });
	}
	for (int i = 0; i < K; i++) {
		cin >> storage[i];
		graph[0].push_back({ 0,storage[i] });
		graph[storage[i]].push_back({ 0,0 });
	}

	vector<LL> ret = Dijkstra(0);
	LL output = INF;
	for (int i = 0; i < ret.size(); i++) {
		if (ret[i] != 0)
			output = min(output, ret[i]);
	}
	cout << (output == INF ? -1 : output) << "\n";

	return 0;
}

vector<LL> Dijkstra(LL start) {
	vector<LL> ret(N + 1, INF);

	priority_queue<pair<LL, LL>> pq;
	pq.push({ 0,start });

	while (!pq.empty()) {
		LL cost = -pq.top().first;
		LL here = pq.top().second;
		pq.pop();

		if (ret[here] < cost)			continue;

		for (int i = 0; i < graph[here].size(); i++) {
			LL there_to_cost = cost + graph[here][i].first;
			LL there = graph[here][i].second;
			if (ret[there] > there_to_cost) {
				ret[there] = there_to_cost;
				pq.push({ -there_to_cost,there });
			}
		}
	}
	return ret;
}
