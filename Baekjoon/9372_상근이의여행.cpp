/*
  url: https://www.acmicpc.net/problem/9372
*/

#include<iostream>
#include<vector>

using namespace std;

int main(void) {
	int T;
	cin >> T;
	vector<int> answer(T, 0);

	for (int i = 0; i < T; i++) {
		int N, M;		// 국가의 수, 비행기의 수
		cin >> N >> M;

		for (int j = 0; j < M; j++) {
			int a, b;
			cin >> a >> b;
		}

		answer[i] = N - 1;
	}

	for (int output : answer) {
		cout << output << "\n";
	}

	return 0;
}
