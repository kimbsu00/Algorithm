/*
  url: https://codeforces.com/problemset/problem/158/A
*/

#include<iostream>
#include<vector>

using namespace std;

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int N, K;
	cin >> N >> K;

	vector<int> score(N);
	for (int i = 0; i < N; i++) {
		cin >> score[i];
	}

	int answer = 0;
	for (int i = 0; i < N; i++) {
		if (score[i] > 0 && score[i] >= score[K - 1]) {
			answer += 1;
		}
	}

	cout << answer << "\n";

	return 0;
}
