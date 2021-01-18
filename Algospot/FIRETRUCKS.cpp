/*
  url: https://algospot.com/judge/problem/read/FIRETRUCKS
*/

#include<iostream>
#include<vector>
#include<queue>
#include<limits>

using namespace std;

vector<int> Dijkstra(int start);

const int INF = numeric_limits<int>::max();
vector<vector<pair<int, int>>> nearby;
vector<int> firePlace;		// 화재 장소들의 인덱스
int v, e, n, m;		// 장소의 수, 도로의 수, 화재 장소의 수, 소방서의 수

int main(void) {
	int C;
	cin >> C;
	vector<int> answer(C);

	for (int i = 0; i < C; i++) {
		firePlace.clear();

		cin >> v >> e >> n >> m;
		nearby = vector<vector<pair<int, int>>>(v + 1, vector<pair<int, int>>());

		for (int k = 0; k < e; k++) {
			int a, b, t;
			cin >> a >> b >> t;
			nearby[a].push_back(make_pair(t, b));
			nearby[b].push_back(make_pair(t, a));
		}

		for (int k = 0; k < n; k++) {
			int num;
			cin >> num;
			firePlace.push_back(num);
		}

		for (int k = 0; k < m; k++) {
			int num;
			cin >> num;
			nearby[0].push_back(make_pair(0, num));
			nearby[num].push_back(make_pair(0, 0));
		}

		int sum = 0;
		vector<int> dijkstra = Dijkstra(0);
		for (int k = 0; k < n; k++)
			sum += dijkstra[firePlace[k]];
		answer[i] = sum;
	}

	for (int i = 0; i < C; i++)
		cout << answer[i] << endl;

	return 0;
}

vector<int> Dijkstra(int start) {
	vector<int> ret(v + 1, INF);

	priority_queue<pair<int, int>> pq;
	pq.push(make_pair(0, start));

	while (!pq.empty()) {
		int cost = -pq.top().first;
		int here = pq.top().second;
		pq.pop();

		if (cost > ret[here])		continue;

		for (int i = 0; i < nearby[here].size(); i++) {
			int there_to_cost = cost + nearby[here][i].first;
			int there = nearby[here][i].second;

			if (ret[there] > there_to_cost) {
				ret[there] = there_to_cost;
				pq.push(make_pair(-there_to_cost, there));
			}
		}
	}

	return ret;
}
