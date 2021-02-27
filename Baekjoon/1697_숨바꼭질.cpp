/*
  url: https://www.acmicpc.net/problem/1697
*/

#include<iostream>
#include<algorithm>
#include<queue>

using namespace std;

int solve();

int N, K;
bool visited[100001];

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	fill(&visited[0], &visited[100001], false);
	cin >> N >> K;

	cout << solve() << "\n";

	return 0;
}

int solve() {
	queue<pair<int, int>> q;
	q.push(make_pair(N, 0));

	int ret = -1;
	while (!q.empty()) {
		int pos = q.front().first;
		int sec = q.front().second;
		q.pop();

		if (pos == K) {
			ret = sec;
			break;
		}
		
		if (pos + 1 < 100001 && !visited[pos + 1]) {
			q.push(make_pair(pos + 1, sec + 1));
			visited[pos + 1] = true;
		}
		if (pos - 1 >= 0 && !visited[pos - 1]) {
			q.push(make_pair(pos - 1, sec + 1));
			visited[pos - 1] = true;
		}
		if (pos * 2 < 100001 && !visited[pos * 2]) {
			q.push(make_pair(pos * 2, sec + 1));
			visited[pos * 2] = true;
		}
	}

	return ret;
}
