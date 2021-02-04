/*
  url: https://algospot.com/judge/problem/read/COINS
  
  고등학교 재학중에 확률과 통계 과목에서 이 문제와 비슷한 문제가 있었던 것 같다.
  그때도 금액이 가장 큰 동전을 금액이 더 작은 다른 동전들로 환전해서 문제를 해결했는데,
  이 아이디어를 응용해서 해결한 문제.
*/

#include<iostream>
#include<vector>
#include<algorithm>

#define MOD 1000000007

using namespace std;

int COINS(int max, int sum);

vector<int> coin;
int cache[100][5001];

int main(void) {
	int T;
	cin >> T;
	vector<int> answer(T);

	for (int i = 0; i < T; i++) {
		int M, C;		// 환전할 금액, 동전 종류의 개수
		cin >> M >> C;

		fill(&cache[0][0], &cache[99][5001], -1);
		coin = vector<int>(C);

		for (int j = 0; j < C; j++) {
			cin >> coin[j];
		}

		sort(coin.begin(), coin.end(), less<int>());
		int max = -1;
		for (int j = C - 1; j >= 0; j--) {
			if (coin[j] <= M) {
				max = j;
				break;
			}
		}

		answer[i] = COINS(max, M);
	}

	for (int output : answer) {
		cout << output << "\n";
	}

	return 0;
}

// 가장 큰 동전의 인덱스가 max 이고, 환전할 금액이 sum 일 때, 가능한 경우의 수를 리턴하는 함수
int COINS(int max, int sum) {
	// 환전할 금액이 없는 경우 == 환전을 모두 끝낸 것이므로 return 1
	if (sum == 0)			return 1;
	
	// 더 이상 거슬러줄 동전의 종류가 남아있지 않은 경우
	if (max < 0)			return 0;

	int& ret = cache[max][sum];
	if (ret != -1)			return ret;

	ret = 0;
	// 금액이 가장 큰 동전을 0개 ~ 최대개수 까지 사용한 경우를 다 더해준다.
	for (int i = 0; sum - coin[max] * i >= 0; i++) {
		ret += (COINS(max - 1, sum - coin[max] * i) %MOD);
		ret %= MOD;
	}

	return ret;
}
