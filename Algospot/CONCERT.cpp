/*
  url: https://algospot.com/judge/problem/read/CONCERT
  
  별다른 어려움 없이 해결한 문제.
*/

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int CONCERT(int volume, int count);

int N, VS, VM;
vector<int> V;
int cache[1001][51];

int main(void) {
	int C;
	cin >> C;
	vector<int> answer(C);

	for (int i = 0; i < C; i++) {
		cin >> N >> VS >> VM;
		
		V = vector<int>(N);
		fill(&cache[0][0], &cache[1000][51], -2);
		
		for (int k = 0; k < N; k++)
			cin >> V[k];

		answer[i] = CONCERT(VS, N);
	}

	for (int output : answer) {
		cout << output << endl;
	}

	return 0;
}

int CONCERT(int volume, int count) {
	// 기저 사례 처리
	if (volume <0 || volume > VM)			return -1;

	if (count == 0)			return volume;

	int& ret = cache[volume][count];
	if (ret != -2)			return ret;

	int diff = V[N - count];
	return ret = max(CONCERT(volume + diff, count - 1), CONCERT(volume - diff, count - 1));
}
