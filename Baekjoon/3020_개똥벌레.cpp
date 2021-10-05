/*
  url: https://www.acmicpc.net/problem/3020
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, H;
vector<int> input;

bool compare(const int& a, const int& b) {
	return a < b;
}

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> N >> H;
	input = vector<int>(H + 1, 0);
	for (int i = 0; i < N; i++) {
		int tmp;
		cin >> tmp;

		// 장애물이 석순인 경우 == 바닥에서 시작하는 경우
		if (i % 2 == 0) {
			input[0] += 1;
			input[tmp] -= 1;
		}
		// 장애물이 종유석인 경우 == 천장에서 시작하는 경우
		else {
			input[H - tmp] += 1;
			input[H] -= 1;
		}
	}

	vector<int> prefix_sum(H, 0);
	prefix_sum[0] = input[0];
	for (int i = 1; i < H; i++) {
		prefix_sum[i] = prefix_sum[i - 1] + input[i];
	}

	sort(prefix_sum.begin(), prefix_sum.end(), compare);
	int answer = 0;
	int tmp = prefix_sum[0];
	for (int i = 1; i < prefix_sum.size(); i++) {
		if (tmp == prefix_sum[i]) {
			continue;
		}
		else {
			answer = i;
			break;
		}
	}

	cout << tmp << " " << answer << "\n";

	return 0;
}
