/*
  url: https://algospot.com/judge/problem/read/ALLERGY
  
  비트마스크를 이용하여 해결함.
*/

#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<map>

using namespace std;

void ALLERGY(long long bits, int sum, int index);

int n, m;			// 친구의 수, 음식의 수
map<string, int> friends;
// index 번째 음식을 먹을 수 있는 사람들을 비트마스크 형식으로 저장함
long long food[50];

int best = 987654321;

int main(void) {
	int C;
	cin >> C;
	vector<int> answer(C);

	for (int i = 0; i < C; i++) {
		friends.clear();
		fill(&food[0], &food[50], 0);
		best = 987654321;

		cin >> n >> m;

		for (int k = 0; k < n; k++) {
			string str;
			cin >> str;
			friends.insert(make_pair(str, k));
		}

		for (int k = 0; k < m; k++) {
			int num;
			cin >> num;
			for (int j = 0; j < num; j++) {
				string name;
				cin >> name;
				food[k] |= ((long long)1 << friends.find(name)->second);
			}
		}

		ALLERGY(0LL, 0, 0);
		answer[i] = best;
	}

	for (int i = 0; i < C; i++)
		cout << answer[i] << endl;

	return 0;
}

void ALLERGY(long long bits, int sum, int index) {
	// 이전에 계산한 음식 수보다 많은 경우는 계산할 필요가 없다.
	if (sum > best)
		return;

	// 모든 사람들이 음식을 먹는경우
	if (bits == (1LL << n) - 1LL) {
		best = min(best, sum);
		return;
	}

	if (index == m)
		return;

	// index 번째 음식을 만드는 경우
	ALLERGY(bits | food[index], sum + 1, index + 1);
	// index 번째 음식을 만들지 않는 경우
	ALLERGY(bits, sum, index + 1);
}
