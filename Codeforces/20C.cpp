/*
  url: https://codeforces.com/problemset/problem/20/C
  
  메모리 초과가 발생하는데 어느 부분에서 메모리를 절약해야 할지 모르겠다..
*/

#include<cstdio>
#include<vector>
#include<queue>
#include<limits>

using namespace std;

void Dijkstra(int start);
void tracePath(int index);

const int INF = numeric_limits<int>::max();
int N, M;
vector<pair<int, int>> graph[100005];
int from[100005];
int dis[100005];

int main(void) {
	scanf("%d %d", &N, &M);
	for (int i = 0; i < M; i++) {
		int a, b, w;
		scanf("%d %d %d", &a, &b, &w);
		a--, b--;
		graph[a].push_back({ w,b });
		graph[b].push_back({ w,a });
	}

	Dijkstra(0);
	if (dis[N - 1] != INF) {
		tracePath(N - 1);
	}
	else {
		printf("-1");
	}

	return 0;
}

void Dijkstra(int start) {
	priority_queue<pair<int, int>> pq;
	fill(dis, dis + N, INF);
	pq.push({ 0,start });

	while (!pq.empty()) {
		int cost = -pq.top().first;
		int here = pq.top().second;
		pq.pop();

		if (dis[here] < cost)			continue;

		if (here == N - 1)			break;

		for (int i = 0; i < graph[here].size(); i++) {
			int cost_to_there = cost + graph[here][i].first;
			int there = graph[here][i].second;

			if (dis[there] > cost_to_there) {
				from[there] = here;
				dis[there] = cost_to_there;
				pq.push({ -cost_to_there, there });
			}
		}
	}
	return;
}

void tracePath(int index) {
	if (index == 0) {
		printf("1 ");
		return;
	}
	tracePath(from[index]);
	printf("%d ", index + 1);
	return;
}
