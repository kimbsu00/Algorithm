/*
  url: https://codeforces.com/problemset/problem/455/A
*/

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

vector<long long> cache(100005, 0);
vector<long long> cnt(100005, 0);

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int N;
	cin >> N;
	for (int i = 0; i < N; i++) {
		int input;
		cin >> input;
		cnt[input] += 1;
	}

	for (int i = 100000; i > 0; i--) {
		cache[i] = max(cache[i + 2] + i * cnt[i], cache[i + 3] + (i + 1) * cnt[i + 1]);
	}
	cout << cache[1] << "\n";

	return 0;
}
