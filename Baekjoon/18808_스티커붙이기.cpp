/*
  url: https://www.acmicpc.net/problem/18808
*/

#include <iostream>
#include <vector>

using namespace std;

int N, M, K;
vector<vector<int>> map;

bool check(vector<vector<int>>& sticker, int R, int C) {
	for (int r = 0; r < sticker.size(); r++) {
		for (int c = 0; c < sticker[0].size(); c++) {
			if (sticker[r][c] == 1 && map[r + R][c + C] == 1)			return false;
		}
	}

	for (int r = 0; r < sticker.size(); r++) {
		for (int c = 0; c < sticker[0].size(); c++) {
			if (sticker[r][c] == 1)			map[r + R][c + C] = 1;
		}
	}
	return true;
}

vector<vector<int>> rotate(vector<vector<int>> sticker) {
	vector<vector<int>> ret = vector<vector<int>>(sticker[0].size(), vector<int>(sticker.size(), 0));

	for (int i = 0; i < ret.size(); i++) {
		for (int j = 0; j < ret[i].size(); j++) {
			ret[i][j] = sticker[sticker.size() - j - 1][i];
		}
	}

	return ret;
}

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> N >> M >> K;
	map = vector<vector<int>>(N, vector<int>(M));

	int answer = 0;
	for (int i = 0; i < K; i++) {
		int R, C;
		cin >> R >> C;
		vector<vector<int>> sticker(R, vector<int>(C, 0));

		int count = 0;
		for (int r = 0; r < R; r++) {
			for (int c = 0; c < C; c++) {
				cin >> sticker[r][c];

				if (sticker[r][c] == 1)			count += 1;
			}
		}

		bool flag = false;
		for (int j = 0; j < 4; j++) {
			for (int r = 0; r <= N - (int)sticker.size(); r++) {
				for (int c = 0; c <= M - (int)sticker[0].size(); c++) {
					flag = check(sticker, r, c);
					if (flag)			break;
				}
				if (flag)			break;
			}
			if (flag)			break;
			else				sticker = rotate(sticker);
		}

		if (flag) {
			answer += count;
		}
	}

	cout << answer << "\n";

	return 0;
}
