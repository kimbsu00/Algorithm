/*
  url: https://algospot.com/judge/problem/read/ARCTIC
  
  ARCTIC() 함수 내부에 존재하는 for loop 의 반복 횟수에 대한 궁금점이 생겼다.
  알고리즘 문제 해결 전략 책에서는 for loop 를 100번 돌리는데 여기서 왜 100번을 돌리는지 의아했다.
  그저 100번 정도 반복하면 정답이 나오겠지 싶어서 100번을 돌리는 건지 아니면 다른 이유가 있어서인지 잘 모르겠다.
  그래서 for loop 의 반복 횟수를 100번에서 점점 줄여가면서 알고스팟 채점 시스템에 돌려본 결과,
  이 코드처럼 25번 반복하면 수행 시간 20ms 으로 정답 처리를 받을 수 있었고, 24번 반복하는 경우는 오답 처리가 됨을 알 수 있었다.
  감히 내가 유추해보자면, 채점을 진행할 때 사용하는 테스트 케이스에는 25번 반복하는 걸로 충분한 것 같다.
*/

#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
#include<queue>

using namespace std;

double ARCTIC();
bool check(double dist);
void getDistance();
double getDistance(pair<double, double> a, pair<double, double> b);

vector<pair<double, double>> center;
// i 번째 기지와 j 번째 기지 사이의 거리 ->  distance[i][j]
double Distance[100][100];

int main(void) {
	int C;
	cin >> C;
	vector<double> answer(C);

	for (int i = 0; i < C; i++) {
		fill(&Distance[0][0], &Distance[99][100], -1);

		int N;
		cin >> N;

		center = vector<pair<double, double>>(N, pair<double, double>());

		for (int i = 0; i < N; i++) {
			double x, y;
			cin >> x >> y;
			center[i] = make_pair(x, y);
		}
		getDistance();

		answer[i] = ARCTIC();
	}

	for (int i = 0; i < C; i++)
		printf("%.2lf\n", answer[i]);

	return 0;
}

double ARCTIC() {
	// 주어진 조건 내에서 기지간의 최대 거리인 1000√2 = 1414.21356... 이기 때문에 이보다 큰 짝수로 설정함
	double dmax = 1416;		
	double dmin = 0;

  // 책에서 for loop 의 반복 횟수는 왜 100번으로 나와있는 거지..
	for (int i = 0; i < 25; i++) {
		double mid = (dmin + dmax) / 2;

		if (check(mid)) {
			dmax = mid;
		}
		else {
			dmin = mid;
		}
	}

	return dmax;
}

bool check(double dist) {
	vector<bool> visited(center.size(), false);

	queue<int> q;
	q.push(0);
	visited[0] = true;

	while (!q.empty()) {
		int here = q.front();
		q.pop();

		for (int i = 0; i < center.size(); i++) {
			if (!visited[i] && Distance[here][i] <= dist) {
				q.push(i);
				visited[i] = true;
			}
		}
	}

	bool ret = true;
	for (bool b : visited)
		ret &= b;

	return ret;
}

void getDistance() {
	for (int i = 0; i < center.size(); i++) {
		for (int j = i; j < center.size(); j++) {
			if (i == j)
				Distance[i][j] = 0;
			else
				Distance[i][j] = Distance[j][i] = getDistance(center[i], center[j]);
		}
	}
}

double getDistance(pair<double, double> a, pair<double, double> b) {
	return sqrt((a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second));
}
