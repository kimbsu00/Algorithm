/*
  url: https://www.acmicpc.net/problem/2096
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int N;
	cin >> N;
	
	int max_list[3] = { 0,0,0 };
	int min_list[3] = { 0,0,0 };

	cin >> max_list[0] >> max_list[1] >> max_list[2];
	min_list[0] = max_list[0];
	min_list[1] = max_list[1];
	min_list[2] = max_list[2];

	for (int i = 1; i < N; i++) {
		int input[3];
		cin >> input[0] >> input[1] >> input[2];

		int tmp_0 = max_list[0], tmp_2 = max_list[2];
		max_list[0] = max(max_list[0], max_list[1]) + input[0];
		max_list[2] = max(max_list[1], max_list[2]) + input[2];
		max_list[1] = max(max_list[1], max(tmp_0, tmp_2)) + input[1];

		tmp_0 = min_list[0], tmp_2 = min_list[2];
		min_list[0] = min(min_list[0], min_list[1]) + input[0];
		min_list[2] = min(min_list[1], min_list[2]) + input[2];
		min_list[1] = min(min_list[1], min(tmp_0, tmp_2)) + input[1];
	}

	cout << max(max_list[0], max(max_list[1], max_list[2])) << " " << min(min_list[0], min(min_list[1], min_list[2])) << "\n";

	return 0;
}
