/*
  url: https://algospot.com/judge/problem/read/TSP1
*/

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

double TSP1(int start, int arrive);

vector<vector<double>> Distance;
vector<bool> visited;

int main(void) {
	int C;
	cin >> C;
	vector<double> answer(C);

	for (int i = 0; i < C; i++) {
		Distance.clear();
		visited.clear();

		int N;
		cin >> N;
		vector<bool> temp(N, false);
		visited.insert(visited.end(), temp.begin(), temp.end());

		for (int n = 0; n < N; n++) {
			vector<double> vec(N);
			for (int m = 0; m < N; m++) {
				cin >> vec[m];
			}
			Distance.push_back(vec);
		}

		double ret = 10000;
		for (int i = 0; i < visited.size(); i++)
			ret = min(ret, TSP1(i, i));
		answer[i] = ret;
	}

	for (int i = 0; i < C; i++)
		printf("%.10lf\n", answer[i]);

	return 0;
}

double TSP1(int start, int arrive) {
	bool end = true;
	for (int i = 0; i < visited.size(); i++) {
		if (!visited[i]) {
			end = false;
			break;
		}
	}
	if (end)		return 0;

	// 이미 방문한적 있는 마을인 경우
	if (visited[arrive])		return 10000;

	double ret = 10000;
	for (int i = 0; i < visited.size(); i++) {
		if (i == arrive)		continue;
		visited[arrive] = true;
		ret = min(ret, Distance[start][arrive] + TSP1(arrive, i));
		visited[arrive] = false;
	}

	return ret;
}
