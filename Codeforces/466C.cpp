/*
  url: https://codeforces.com/problemset/problem/466/C
  
  1. prefixSum[N-1] 이 3의 배수이어야만 한다.
  2. sum = prefixSum[N-1] / 3 라고 할 때,
     prefixSum 에서 sum, sum*2 인 지점을 알면 답을 계산할 수 있다.
*/

#include<iostream>
#include<vector>

using namespace std;

vector<long long> prefixSum;

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int N;
	cin >> N;
	prefixSum = vector<long long>(N, 0);

	cin >> prefixSum[0];
	for (int i = 1; i < N; i++) {
		long long num;
		cin >> num;
		prefixSum[i] = prefixSum[i - 1] + num;
	}

	long long answer = 0;
	if (prefixSum[N - 1] % 3 == 0) {
		long long sum = prefixSum[N - 1] / 3;
		long long count1 = 0, count2 = 0;
    // 3개의 모든 부분 집합은 최소 1개 이상의 원소를 가지고 있어야 하므로 (i < N-1) 이 for loop 의 탈출 조건이 된다.
		for (int i = 0; i < N - 1; i++) {
			if (prefixSum[i] == sum * 2)			count2 += count1;
			if (prefixSum[i] == sum)			count1 += 1;
		}
		answer = count2;
	}

	cout << answer << "\n";

	return 0;
}
