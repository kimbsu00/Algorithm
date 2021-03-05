/*
  url: https://codeforces.com/problemset/problem/231/A
*/

#include<iostream>

using namespace std;

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int N;
	cin >> N;

	int answer = 0;
	for (int i = 0; i < N; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		if (a + b + c >= 2) {
			answer++;
		}
	}
	
	cout << answer << "\n";

	return 0;
}
