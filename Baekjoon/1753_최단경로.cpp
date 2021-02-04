/*
  url: https://www.acmicpc.net/problem/1753
*/

#include<iostream>
#include<vector>
#include<queue>
#include<limits>

using namespace std;

vector<int> Dijkstra(int start);

const int INF = numeric_limits<int>::max();
vector<vector<pair<int, int>>> graph;

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int V, E;
	cin >> V >> E;
	int start;
	cin >> start;

	graph = vector<vector<pair<int, int>>>(V, vector<pair<int, int>>());

	for (int i = 0; i < E; i++) {
		int u, v, weight;
		cin >> u >> v >> weight;
		graph[u - 1].push_back(make_pair(weight, v - 1));
	}

	vector<int> shortestPath = Dijkstra(start - 1);
	for (int output : shortestPath) {
		if (output == INF)
			cout << "INF\n";
		else
			cout << output << "\n";
	}

	return 0;
}

vector<int> Dijkstra(int start) {
	vector<int> ret(graph.size(), INF);
	ret[start] = 0;

	priority_queue<pair<int, int>> pq;
	pq.push(make_pair(0, start));

	while (!pq.empty()) {
		int cost = -pq.top().first;
		int here = pq.top().second;
		pq.pop();

		if (cost > ret[here])		continue;

		for (int i = 0; i < graph[here].size(); i++) {
			int there_cost = cost + graph[here][i].first;
			int there = graph[here][i].second;

			if (ret[there] > there_cost) {
				ret[there] = there_cost;
				pq.push(make_pair(-there_cost, there));
			}
		}
	}

	return ret;
}
