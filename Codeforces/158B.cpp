/*
  url: https://codeforces.com/problemset/problem/158/B
*/

#include<iostream>
#include<vector>

using namespace std;

vector<int> input(4);

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int N;
	cin >> N;

	for (int i = 0; i < N; i++) {
		int num;
		cin >> num;
		input[num - 1] += 1;
	}

	int answer = input[3];
	
	if (input[0] > input[2]) {
		answer += input[2];
		input[0] -= input[2];
		answer += (input[0] / 4);
		input[0] %= 4;

		if (input[1] % 2 == 0) {
			answer += input[1] / 2;
			if (input[0] > 0)			answer += 1;
		}
		else {
			answer += input[1] / 2;
			if (input[0] / 3 >= 1)			answer += 2;
			else			answer += 1;
		}
		
	}
	else if (input[0] < input[2]) {
		answer += input[0];
		input[2] -= input[0];
		answer += input[2];
		answer += (input[1] / (double)2 + 0.5);
	}
	else {
		answer += input[0];
		answer += (input[1] / (double)2 + 0.5);
	}

	cout << answer << "\n";

	return 0;
}
