/*
  url: https://algospot.com/judge/problem/read/NERD2
  
  (p. q) = (x, y) 로 두고 2차원 상의 좌표로 보면,
  Nerd 인 좌표들은 우하향인 형태로 나타나게 됨을 이용하여 해결함.
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
	// (x, y) 가 Nerd 가 아니면 바로 리턴
	if (!checkNerd(x, y))		return coordinates.size();

	// (x, y) 와 비교했을 때 Nerd 가 아니게 되는 기존 좌표들을 제거
	removeNotNerd(x, y);
	// (x, y) 를 추가해주고 리턴
	coordinates.insert(make_pair(x, y));
	return coordinates.size();
}

bool checkNerd(int x, int y) {
	// x 좌표가 x 값보다 큰 좌표들 중에서 x 값이 가장 작은 좌표를 it 에 저장
	map<int, int>::iterator it = coordinates.lower_bound(x);

	// it 가 end() 인 경우, x 좌표가 x 값보다 큰 좌표가 존재하지 않으므로 y 값과 상관없이 (x, y) 는 nerd 이다.
	if (it == coordinates.end())		return true;

	// it 가 가리키는 좌표는 x보다 오른쪽에 있는 좌표 중 가장 위에 있는 좌표이므로,
	// 이 점보다 y 좌표가 크면 nerd 이다.
	return y > it->second;
}

void removeNotNerd(int x, int y) {
	// x 좌표가 x 값보다 큰 좌표들 중에서 x 값이 가장 작은 좌표를 it 에 저장
	map<int, int>::iterator it = coordinates.lower_bound(x);

	// it 가 begin() 이라면 (x, y) 보다 왼쪽에 위치한 좌표가 존재하지 않음
	if (it == coordinates.begin())		return;

	// it 가 begin() 이 아니라면 (x, y) 보다 오른쪽에 있는 좌표들 중에서 가장 왼쪽에 있는 좌표를 가리키고 있으므로,
	// 한 칸 왼쪽으로 이동한다.
	it--;

	while (true) {
		// it 의 y 값이 y 보다 크다면 더 이상 비교할 필요가 없다.
		// -> it 보다 왼쪽에 있는 좌표들은 it 보다 위에 위치해 있기 때문이다.
		if (it->second > y)		break;

		// it 가 맨 왼쪽에 위치한 좌표라면 해당 좌표를 없애고 반복 종료
		if (it == coordinates.begin()) {
			coordinates.erase(it);
			break;
		}
		// 그 외의 경우, 해당 좌표 제거후 왼쪽으로 이동
		else {
			map<int, int>::iterator temp = it;
			temp--;
			coordinates.erase(it);
			it = temp;
		}
	}
}
