/*
  url: https://codeforces.com/problemset/problem/486/E
*/

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

void LIS(vector<int>& list, vector<int>& save);

int N;
vector<int> sequence;
vector<int> L;
vector<int> RL;

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	// input
	cin >> N;
	sequence = vector<int>(N);
	L = vector<int>(N);
	for (int i = 0; i < N; i++)
		cin >> sequence[i];

	// 왼쪽에서부터 오른쪽으로 이동하면서,
	// index 번째에서 끝나는 LIS의 길이를 L[index] 에 저장한다.
	LIS(sequence, L);


	vector<int> reverse(N);
	for (int i = 0; i < N; i++) {
		reverse[i] = 1000000 - sequence[N - 1 - i];
	}
	vector<int> temp(N);
	// 오른쪽에서 왼쪽으로 이동하면서
	// index 번째에서 끝나는 Reverse LIS의 길이를 RL[index] 에 저장한다.
	LIS(reverse, temp);
	RL = vector<int>(temp.rbegin(), temp.rend());

	// LIS 의 길이를 maxValue 에 저장한다.
	int maxValue = 0;
	for (int i = 0; i < N; i++) {
		maxValue = max(maxValue, L[i]);
	}

	vector<int> answer(N, 1);
	for (int i = 0; i < N; i++) {
		// 아래 조건을 만족하는 경우에 대하여 전부다 3으로 설정해놓고
		if (L[i] + RL[i] == maxValue + 1) {
			answer[i] = 3;
		}
	}

	// sequence[index] 값이 모든 LIS에 포함되기 위한 조건으로는 다음과 같다.
	// [0, index-1] 에서의 최대값 < sequence[index]
	// [index+1, N-1] 에서의 최소값 > sequence[index]
	// 이 두 조건을 만족하는 경우에만 answer 값을 3으로 설정하면 된다.
	int leftMax = 0, rightMin = 987654321;
	for (int i = 0; i < N; i++) {
		if (answer[i] != 1) {
			if (leftMax >= sequence[i]) {
				answer[i] = 2;
			}
			leftMax = max(leftMax, sequence[i]);
		}
	}

	for (int i = N - 1; i >= 0; i--) {
		if (answer[i] != 1) {
			if (rightMin <= sequence[i]) {
				answer[i] = 2;
			}
			rightMin = min(rightMin, sequence[i]);
		}
	}

	for (int i = 0; i < N; i++) {
		cout << answer[i];
	}

	return 0;
}

// save 배열 -> index 번째 값으로 끝나는 LIS의 길이를 저장한다.
void LIS(vector<int>& list, vector<int>& save) {
	vector<int> temp;
	temp.push_back(-1);

	for (int i = 0; i < N; i++) {
		if (temp.back() < list[i]) {
			temp.push_back(list[i]);
		}
		// sequence[i] 값이 있으면, sequence[i] 값과 같은 위치의 iterator 를 반환
		// sequence[i] 값이 없으면, sequence[i] 값 보다 큰 값들 중에서 가장 작은 값의 iterator 를 반환
		auto it = lower_bound(temp.begin(), temp.end(), list[i]);
		*it = list[i];
		save[i] = it - temp.begin();
	}
}
