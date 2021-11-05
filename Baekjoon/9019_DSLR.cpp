/*
  url: https://www.acmicpc.net/problem/9019
*/

#include <iostream>
#include <string>
#include <queue>

using namespace std;

bool is_used[10000];

int D(int input) {
	// #define MOD 10000 선언한 후에,
	// (input * 2) % MOD; 로 구현하면 실패처리 된다.
	// 이유가 뭐지?
	return (input * 2) % 10000;
}

int S(int input) {
	return input == 0 ? 9999 : input - 1;
}

int L(int input) {
	int a = input / 1000;
	int b = input % 1000;
	return b * 10 + a;
}

int R(int input) {
	int a = input % 10;
	int b = input / 10;
	return a * 1000 + b;
}

string solve(int& A, int& B) {
	fill(&is_used[0], &is_used[10000], false);

	queue<pair<int, string>> q;
	q.push({ A, "" });
	is_used[A] = true;

	string ret = "";
	while (!q.empty()) {
		int num = q.front().first;
		string cmd = q.front().second;
		q.pop();

		if (num == B) {
			ret = cmd;
			break;
		}

		int d = D(num);
		int s = S(num);
		int l = L(num);
		int r = R(num);
		if (!is_used[d]) {
			q.push({ d, cmd + "D" });
			is_used[d] = true;
		}
		if (!is_used[s]) {
			q.push({ s, cmd + "S" });
			is_used[s] = true;
		}
		if (!is_used[l]) {
			q.push({ l, cmd + "L" });
			is_used[l] = true;
		}
		if (!is_used[r]) {
			q.push({ r, cmd + "R" });
			is_used[r] = true;
		}
	}

	return ret;
}

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int T;
	cin >> T;

	for (int i = 0; i < T; i++) {
		int A, B;
		cin >> A >> B;

		cout << solve(A, B) << "\n";
	}

	return 0;
}
