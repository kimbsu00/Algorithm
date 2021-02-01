/*
  url: https://algospot.com/judge/problem/read/NERD2
  
  map 을 이용하여 해결함.
*/

#include<iostream>
#include<cstdio>
#include<vector>
#include<map>

using namespace std;

int NERD2(int x, int y);
bool checkNerd(int x, int y);
void removeNotNerd(int x, int y);

map<int, int> coordinates;

int main(void) {
	int C;
	cin >> C;
	vector<int> answer(C, 0);

	for (int i = 0; i < C; i++) {
		coordinates.clear();

		int N;
		scanf("%d", &N);

		for (int j = 0; j < N; j++) {
			int p, q;
			scanf("%d %d", &p, &q);

			answer[i] += NERD2(p, q);
		}
	}

	for (int output : answer) {
		printf("%d\n", output);
	}

	return 0;
}

int NERD2(int x, int y) {
	if (!checkNerd(x, y))		return coordinates.size();

	removeNotNerd(x, y);
	coordinates.insert(make_pair(x, y));
	return coordinates.size();
}

bool checkNerd(int x, int y) {
  // x 보다 큰 값들 중에서 가장 아래에 위치한 좌표를 반환
	map<int, int>::iterator it = coordinates.lower_bound(x);

  // x 보다 큰 값이 없는 경우 (x, y) 는 Nerd 이다.
	if (it == coordinates.end())		return true;

  // x 보다 큰 값들 중에서 가장 아래에 있는 좌표보다 커야만 너드가 될 수 있다.
	return y > it->second;
}

void removeNotNerd(int x, int y) {
  // x 보다 큰 값들 중에서 가장 아래에 위치한 좌표를 반환
	map<int, int>::iterator it = coordinates.lower_bound(x);

  // (x, y) 보다 왼쪽에 있는 좌표가 없는 경우
	if (it == coordinates.begin())		return;

	it--;
	while (true) {
		if (it->second > y)		break;

		if (it == coordinates.begin()) {
			coordinates.erase(it);
			break;
		}
		else {
			map<int, int>::iterator temp = it;
			temp--;
			coordinates.erase(it);
			it = temp;
		}
	}
}
