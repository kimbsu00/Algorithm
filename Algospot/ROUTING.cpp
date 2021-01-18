/*
  url: https://algospot.com/judge/problem/read/ROUTING
  
  다익스트라 알고리즘을 조금 바꾸면 간단하게 해결되는 문제.
  임의의 노드에서 다른 노드로 이동할 때 값이 + 가 되는 일반적인 다익스트라 알고리즘과는 달리,
  이 문제에서는 임의의 노드에서 다른 노드로 이동할 때 값이 n배(n>=1 인 실수)가 되기 때문에 곱셈 연산을 수행해야 한다.
  따라서 56번째 줄에 초기 cost 값을 1로 설정함.
*/

#include<iostream>
#include<vector>
#include<queue>
#include<limits>

using namespace std;

vector<double> Dijkstra(int start);

const double INF = numeric_limits<double>::max();
// pair<double, int> = (cost, index)
vector<vector<pair<double, int>>> nearby;
// 컴퓨터 개수(노드). 회선 개수(엣지)
int N, M;

int main(void) {
	int C;
	cin >> C;
	vector<double> answer(C);

	for (int i = 0; i < C; i++) {
		cin >> N >> M;

		nearby = vector<vector<pair<double, int>>>(N, vector<pair<double, int>>());

		for (int k = 0; k < M; k++) {
			int a, b;
			double c;
			cin >> a >> b >> c;
			nearby[a].push_back(make_pair(c, b));
			nearby[b].push_back(make_pair(c, a));
		}

		answer[i] = Dijkstra(0)[N - 1];
	}

	for (int i = 0; i < C; i++)
		printf("%.10lf\n", answer[i]);

	return 0;
}

vector<double> Dijkstra(int start) {
	vector<double> ret(N, INF);

	priority_queue<pair<double, int>> pq;
	pq.push(make_pair(-1, start));

	while (!pq.empty()) {
		/* 
		priority_queue 는 내림차순 정렬이 디폴트임 
		오름차순으로 만들기 위해서 음의 부호를 붙여서 값을 넣었기 때문에 다시 양수로 바꿔줌.
		*/
		double cost = -pq.top().first;
		int here = pq.top().second;
		pq.pop();
		if (cost > ret[here])		continue;

		for (int i = 0; i < nearby[here].size(); i++) {
			double cost_to_there = cost * nearby[here][i].first;
			int there = nearby[here][i].second;
			
			if (ret[there] > cost_to_there) {
				ret[there] = cost_to_there;
				pq.push(make_pair(-cost_to_there, there));
			}
		}
	}

	return ret;
}
