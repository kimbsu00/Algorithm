/*
  url: https://www.acmicpc.net/problem/1687
  
  Algospot의 FENCE 문제 아이디어를 가져다가 사용했음.
  https://github.com/kimbsu00/Algorithm/blob/master/Algospot/FENCE.cpp
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int N, M;
vector<vector<int>> list;

int get_left(int row, int idx) {
	int ret = idx;

	for (int i = idx - 1; i >= 0; i--) {
		if (list[row][i] < list[row][idx])			break;
		ret = i;
	}

	return ret;
}

int get_right(int row, int idx) {
	int ret = idx;

	for (int i = idx + 1; i < list[row].size(); i++) {
		if (list[row][i] < list[row][idx])			break;
		ret = i;
	}

	return ret;
}

int solve(int row) {
	int ret = 0;

	for (int i = 0; i < list[row].size(); i++) {
		if (list[row][i] == 0)			continue;

		int left = get_left(row, i);
		int right = get_right(row, i);
		int size = (right - left + 1) * list[row][i];

		ret = max(ret, size);
	}

	return ret;
}

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> N >> M;
	list = vector<vector<int>>(N, vector<int>(M, 0));

	string tmp;
	cin >> tmp;
	for (int j = 0; j < tmp.size(); j++) {
		list[0][j] = tmp[j] == '0' ? 1 : 0;
	}
	for (int i = 1; i < N; i++) {
		cin >> tmp;
		for (int j = 0; j < tmp.size(); j++) {
			if (tmp[j] == '0') {
				list[i][j] = 1 + list[i - 1][j];
			}
			else {
				list[i][j] = 0;
			}
		}
	}

	int answer = 0;
	for (int i = 0; i < N; i++) {
		answer = max(answer, solve(i));
	}
	cout << answer << "\n";

	return 0;
}
