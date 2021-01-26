/*
  url: https://algospot.com/judge/problem/read/LUNCHBOX
  
  처음에 문제를 읽었을 때, 한 도시락(A)을 데워서 그 도시락(A)을 먹는 동안에 다른 도시락(B)을 데우고, 
  A 도시락을 다 먹은 후에 B 도시락을 먹기 시작한다는 줄 알고 문제를 풀다가
  힘들게 생각해낸 풀이 방법이 너무 복잡한 것 같아서 구글링한 결과, A 도시락을 다 못 먹어도 B 도시락을 먹을 수 있었음을 알게 되었다.
  되게 간단한 문제였는데 영어 독해를 잘못해서 산으로 갔던 문제.
*/

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

bool compare(const pair<int, int>& a, const pair<int, int>& b);
int LUNCHBOX();

vector<pair<int, int>> food;

int main(void) {
	int C;
	cin >> C;
	vector<int> answer(C);

	for (int i = 0; i < C; i++) {
		int N;
		cin >> N;
		food = vector<pair<int, int>>(N);

		for (int k = 0; k < N; k++) {
			cin >> food[k].first;
		}
		for (int k = 0; k < N; k++) {
			cin >> food[k].second;
		}
		sort(food.begin(), food.end(), compare);

		answer[i] = LUNCHBOX();
	}

	for (int output : answer) {
		cout << output << endl;
	}

	return 0;
}

bool compare(const pair<int, int>& a, const pair<int, int>& b) {
	return a.second > b.second;
}

int LUNCHBOX() {
	int ret = 0;
	int microTime = 0;

	for (int i = 0; i < food.size(); i++) {
		microTime += food[i].first;
		ret = max(ret, microTime + food[i].second);
	}

	return ret;
}
