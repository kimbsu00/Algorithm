/*
  url: https://codeforces.com/problemset/problem/1285/B
  
  tastiness 의 모든 합이 sum 일 때,
  x 또는 y 가 0 이하가 된다는 말은 
  x + z = sum 또는 
  y + z = sum 이 되는 z 값이 존재한다는 말이 된다.
  다시 말하면, x 와 y 가 0 이하가 되면 sum 이상의 z 라는 값이 존재할 수 밖에 없게 된다.
  
  이를 이용해서 해결함.
*/

#include<iostream>
#include<vector>

using namespace std;

vector<int> tastiness;

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int T;
	cin >> T;
	vector<bool> answer(T, true);

	for (int i = 0; i < T; i++) {
		int N;
		cin >> N;
		tastiness = vector<int>(N);

		bool check = true;
		for (int j = 0; j < N; j++) {
			cin >> tastiness[j];
		}

		long long x = tastiness[0];
		long long y = tastiness[N - 1];
		if (x <= 0 || y <= 0)			check = false;

		for (int j = 1; j < N; j++) {
			x += tastiness[j];
			y += tastiness[N - 1 - j];
			if (x <= 0 || y <= 0) {
				check = false;
				break;
			}
		}

		answer[i] = check;
	}

	for (bool output : answer) {
		cout << (output ? "YES" : "NO") << "\n";
	}

	return 0;
}
