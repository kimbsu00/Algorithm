/*
  url: https://algospot.com/judge/problem/read/LIS
  
  풀잌 코드를 보지 않고 직접 구현한 코드.
  dp를 이용해서 구현할 때는 각각의 부분문제는 서로 독립이어야 함을 항상 잊지말자.
*/

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int LIS(int index);

int cache[501];
vector<int> sequence;

int main(void) {
	int C;
	cin >> C;
	vector<int> answer(C);

	for (int i = 0; i < C; i++) {
		sequence.clear();
		fill(&cache[0], &cache[501], -1);

		int N;
		cin >> N;

		for (int k = 0; k < N; k++) {
			int num;
			cin >> num;
			sequence.push_back(num);
		}
		int temp = 0;
		for (int k = 0; k < N; k++)
			temp = max(temp, 1 + LIS(k));
		answer[i] = temp;
	}

	for (int i = 0; i < C; i++)
		cout << answer[i] << endl;

	return 0;
}

// [index + 1, sequence.size) 의 범위 내에 존재하는 sequence[index] 보다 큰 숫자들 중에서 가장 큰 LIS의 길이를 리턴하는 함수
int LIS(int index) {
	int& ret = cache[index];
	if (ret != -1)		
		return ret;

	bool loopIn = false;
	for (int i = index+1; i < sequence.size(); i++) {
		if (sequence[index] < sequence[i]) {
			ret = max(ret, 1 + LIS(i));
			loopIn = true;
		}
	}

	if (!loopIn)
		ret = 0;

	return ret;
}
