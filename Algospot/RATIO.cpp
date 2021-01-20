/*
  url: https://algospot.com/judge/problem/read/RATIO
*/

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

void RATIO(unsigned int left, unsigned int right);

vector<int> save;		// 승률이 1 이상 증가하게 되는 연승의 수를 저장하는 배열
double N, M;				// 플레이 횟수, 승리 횟수
int ratio;						// 승률
unsigned int range;		// 가능한 연승의 범위 [0, range]

/*
승률을 계산 할 때, 
1. ratio = (M / N) * 100 으로 하면 오답처리가 되는데
2. ratio = (M * 100 / N) 으로 하면 정답처리가 된다.
ex)
M = 58, N = 100 인 경우에 
1번 함수에서는 57, 2번 함수에서는 58 이 리턴되는데 이는 부동소수점 때문에 발생하는 오류라고 한다.
*/
int main(void) {
	int C;
	cin >> C;
	vector<int> answer(C);

	for (int i = 0; i < C; i++) {
		save.clear();
		cin >> N >> M;
		
		if (99 * N - 100 * M <= 0) {
			answer[i] = -1;
			continue;
		}
		ratio = M * 100 / N;
		// (N * N) / (99 * N - 100 * M) 의 결과가 자연수로 나누어 떨어지지 않는 경우에 예외가 발생할 수 있다고 생각해서 +1 을 해줌
		range = (N * N) / (99 * N - 100 * M) + 1;
		if (range <= 1) {
			answer[i] = 1;
			continue;
		}
		RATIO(0, range);
		sort(save.begin(), save.end(), less<int>());
		answer[i] = save[0];
	}

	for (int i = 0; i < C; i++)
		cout << answer[i] << endl;

	return 0;
}

void RATIO(unsigned int left, unsigned  int right) {
	if (right == left)
		return;

	unsigned int mid = ((double)right + left) / 2 + 0.5;

	int temp = (M + mid) * 100 / (N + mid);
	if (temp - ratio >= 1) {
		save.push_back(mid);
		if (left + 1 == right) 
			return;
		else
			return RATIO(left, mid);
	}
	else {
		return RATIO(mid, right);
	}
}
