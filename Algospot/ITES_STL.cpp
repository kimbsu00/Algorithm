/*
  url: https://algospot.com/judge/problem/read/ITES
  
  cpp 에서 STL 로 제공하는 queue 자료구조를 사용해서 해결한 코드.
  수행 시간: 5140ms
*/

#include<iostream>
#include<vector>
#include<climits>
#include<queue>

#define X ((long long)UINT_MAX + 1)

using namespace std;

int ITES();

int K, N;

int main(void) {
	int C;
	cin >> C;
	vector<int> answer(C, 0);

	for (int i = 0; i < C; i++) {
		cin >> K >> N;

		answer[i] = ITES();
	}

	for (int i = 0; i < C; i++)
		cout << answer[i] << endl;

	return 0;
}

int ITES() {
	queue<int> q;

	long long value = 1983;
	int ret = 0;
	int sum = 0;
	for (int i = 0; i < N; i++) {
		int signal = value % 10000 + 1;
		q.push(signal);
		sum += signal;
		value = (value * 214013 + 2531011) % X;

		while (sum > K) {
			sum -= q.front();
			q.pop();
		}

		if (sum == K)		ret++;
	}

	return ret;
}
