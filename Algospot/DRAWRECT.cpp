/*
  url: https://algospot.com/judge/problem/read/DRAWRECT
*/

#include<iostream>
#include<vector>

using namespace std;

int main(void) {
	int C;
	cin >> C;
	vector <pair<int, int>> answer(C);

	for (int i = 0; i < C; i++) {
		int* x = new int[3];
		int* y = new int[3];
		for (int k = 0; k < 3; k++) {
			cin >> x[k] >> y[k];
		}

		if (x[0] != x[1] && y[0] != y[1]) {
			if (x[0] == x[2]) {
				answer[i].first = x[1];
				answer[i].second = y[0];
			}
			else if (x[1] == x[2]) {
				answer[i].first = x[0];
				answer[i].second = y[1];				
			}
		}
		else if (x[0] != x[2] && y[0] != y[2]) {
			if (x[0] == x[1]) {
				answer[i].first = x[2];
				answer[i].second = y[0];
			}
			else if (x[2] == x[1]) {
				answer[i].first = x[0];
				answer[i].second = y[2];
			}
		}
		else if (x[1] != x[2] && y[1] != y[2]) {
			if (x[1] == x[0]) {
				answer[i].first = x[2];
				answer[i].second = y[1];
			}
			else if (x[2] == x[0]) {
				answer[i].first = x[1];
				answer[i].second = y[2];
			}
		}
	}

	for (int i = 0; i < C; i++)
		cout << answer[i].first << " " << answer[i].second << endl;

	return 0;
}
