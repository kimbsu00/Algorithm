/*
  url: https://algospot.com/judge/problem/read/MATCHORDER
*/

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int MATCHORDER(vector<int>& Russia, vector<int>& Korea);

int main(void) {
	int C;
	cin >> C;
	vector<int> answer(C, 0);

	for (int i = 0; i < C; i++) {
		int N;
		cin >> N;

		vector<int> Russia(N);
		for (int k = 0; k < N; k++)
			cin >> Russia[k];

		vector<int> Korea(N);
		for (int k = 0; k < N; k++)
			cin >> Korea[k];

		answer[i] = MATCHORDER(Russia, Korea);
	}

	for (int output : answer) {
		cout << output << endl;
	}

	return 0;
}

int MATCHORDER(vector<int>& Russia, vector<int>& Korea) {
	vector<bool> win(Korea.size(), false);

	sort(Russia.begin(), Russia.end(), less<int>());
	sort(Korea.begin(), Korea.end(), less<int>());

	for (int i = 0; i < Korea.size(); i++) {
		if (Korea[i] >= Russia[i]) {
			win[i] = true;
		}
	}
  
  // 오름차순 정렬했을 때, 지고있는 라운드에 대하여 레이팅이 더 높지만 지고있는 다른 선수들과 바꿔서 이길 수 있으면 바꿔준다.
	for (int i = 0; i < Korea.size(); i++) {
		if (!win[i]) {
			for (int k = i + 1; k < Korea.size(); k++) {
				if (!win[k] && Russia[i] <= Korea[k]) {
					int temp = Korea[k];
					Korea[k] = Korea[i];
					Korea[i] = temp;
					win[i] = true;
					break;
				}
			}
		}
	}

	int ret = 0;
	for (bool boool : win) {
		if (boool)		ret += 1;
	}
	return ret;
}
