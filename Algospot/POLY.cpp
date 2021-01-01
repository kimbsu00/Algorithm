/*
  url: https://algospot.com/judge/problem/read/POLY
  
  문제 아웃풋 출력 조건으로 "폴리오미노의 수가 10,000,000 이상일 경우 10,000,000으로 나눈 나머지를 출력합니다." 라는 조건이 있었는데,
  아웃풋을 출력하기 직전에만 10,000,000으로 나누었을 때의 나머지를 출력해서 한참동안 헤맨 문제.
  그리고 "세로 단조 폴리오미노" 의 조건을 정확히 이해하지 못해서 상당히 어렵게 느껴졌던 문제.
*/

#include<iostream>
#include<algorithm>
#include<vector>

#define MOD 10000000

using namespace std;

int POLY(int blockNum, int count);

int cache[101][101];
int N;

int main(void) {
	int C;
	cin >> C;
	vector<long long> answer(C, 0);

	for (int i = 0; i < C; i++) {
		fill(&cache[0][0], &cache[100][101], 0);

		cin >> N;
		
		for (int k = 1; k <= N; k++) {
			answer[i] += POLY(N, k);
			answer[i] > MOD ? answer[i] %= MOD : answer[i];
		}
	}

	for (int i = 0; i < C; i++)
		cout << answer[i] << endl;

	return 0;
}

// 총 blockNum 개의 정사각형으로 만들 수 있는 폴리오미노 중에 첫 번째 줄의 정사각형 개수가 count 개인 경우를 리턴
int POLY(int blockNum , int count) {
	if (blockNum == 0)
		return 0;

	if (blockNum == count)
		return 1;

	int& ret = cache[blockNum][count];
	if (ret != 0)
		return ret;

	for (int i = 1; i <= blockNum - count; i++) {
		int temp = (count + i - 1) * POLY(blockNum - count, i);
		temp > MOD ? ret += temp % MOD : ret += temp;
		ret > MOD ? ret %= MOD : ret;
	}

	return ret;
}
