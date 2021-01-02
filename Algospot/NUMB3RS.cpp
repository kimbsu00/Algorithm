/*
  url: https://algospot.com/judge/problem/read/NUMB3RS
  
  별다른 어려움 없이 간단하게 풀 수 있었던 문제.
*/

#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;

double NUMB3RS(int start, int end, int day);

double cache[51][51][101];		// cache[start][end][day]
int n, d, p;		// 마을의 수, 탈출 후 지금까지 지난 일수, 교도소가 있는 마을 번호
vector<vector<int>> map;
vector<int> nearbyCity;		// index 번째 마을과 인접해있는 마을의 수

int main(void) {
	int C;
	cin >> C;
	vector<vector<double>> answer(C);

	for (int i = 0; i < C; i++) {
		fill(&cache[0][0][0], &cache[50][50][101], -1);
		map.clear();
		nearbyCity.clear();

		cin >> n >> d >> p;

		for (int row = 0; row < n; row++) {
			vector<int> vec(n);
			int count = 0;
			for (int col = 0; col < n; col++) {
				cin >> vec[col];
				count += vec[col];
			}
			map.push_back(vec);
			nearbyCity.push_back(count);
		}

		int T;
		cin >> T;
		vector<double> vec(T);
		for (int k = 0; k < T; k++) {
			int end;
			cin >> end;
			vec[k] = NUMB3RS(p, end, d);
		}
		answer[i] = vec;
	}

	for (int i = 0; i < C; i++) {
		for (int j = 0; j < answer[i].size(); j++) {
			printf("%.8lf ", answer[i][j]);
		}
		printf("\n");
	}

	return 0;
}

// day 일 동안에 start 에서 end 로 갈 수 있는 확률을 리턴함
double NUMB3RS(int start, int end, int day) {
	// 가저 사례 처리
	if (day == 0) {
		if (start == end)
			return 1;
		else
			return 0;
	}

	double& ret = cache[start][end][day];
	if (ret != -1)
		return ret;

	ret = 0.0;
	for (int i = 0; i < n; i++) {
		// start 번째 마을과 연결되어 있는 마을에 대해서만 재귀호출 수행
		if (map[start][i] == 1) {
			ret += (1 / (double)nearbyCity[start]) * NUMB3RS(i, end, day - 1);
		}
	}
	
	return ret;
}
