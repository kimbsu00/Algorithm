/*
  url: https://codeforces.com/problemset/problem/607/A
*/

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int solve(int pos);
bool compare(const pair<int, int>& a, const pair<int, int>& b);

int N;
vector<pair<int, int>> beacon;
// index 번째 비콘을 활성화했을 때, 폭발하는 비콘들의 개수를 저장함
int cache[100002];

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	memset(cache, 0, sizeof(cache));
	cin >> N;
	beacon = vector<pair<int, int>>(N + 1, make_pair(0, 0));
	for (int i = 1; i <= N; i++) {
		cin >> beacon[i].first >> beacon[i].second;
	}
	sort(beacon.begin(), beacon.end(), compare);

  // i 번째 비콘으로 인해 터지지 않는 비콘들 중에서 맨 오른쪽에 위치한 비콘을 pos 번재 비콘이라 하면,
  // cache[i] = i - (pos + 1) + cache[pos] 가 된다.
	for (int i = 1; i <= N; i++) {
		int pos = solve(beacon[i].first - beacon[i].second) - 1;
		cache[i] = i - (pos + 1) + cache[pos];
	}

	int answer = 987654321;
  // for loop 내부에서 cache[i] + N - 1 과 비교하는 이유는
  // 어쩌피 i 가 작은 부분에서는 정답이 나오지 않을 것이고, i 가 N 이랑 가까운 부분에서 정답이 나올 것이기 때문에
  // i 값이 작은 경우에 (cache[i] + N - i) 가 실제 정답이 될 수는 없지만,
  // i 값이 어느정도 커지면 (N - i) 값이 작아지기 때문에 정답이 된다.
  // 따라서 for loop 가 종료될 때 answer 는 정답이 된다.
	for (int i = 1; i <= N; i++) {
		answer = min(answer, cache[i] + N - i);
	}
	cout << answer << "\n";

	return 0;
}

// pos 번째 비콘으로 인해 터지지 않는 비콘들 중에서 맨 오른쪽에 위치한 비콘의 인덱스를 리턴한다.
int solve(int pos) {
	int start = 1;
	int end = N;
	while (start < end) {
		int mid = (start + end) / 2;
		if (beacon[mid].first >= pos)
			end = mid;
		else
			start = mid + 1;
	}
	return start;
}

bool compare(const pair<int, int>& a, const pair<int, int>& b) {
	return a.first < b.first;
}
