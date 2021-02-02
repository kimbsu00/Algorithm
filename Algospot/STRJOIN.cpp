/*
  url: https://algospot.com/judge/problem/read/STRJOIN
*/

#include<iostream>
#include<vector>
#include<queue>

using namespace std;

int STRJOIN(int sum);

priority_queue<int> input;

int main(void) {
	int C;
	cin >> C;
	vector<int> answer(C);

	for (int i = 0; i < C; i++) {
		while (!input.empty())			input.pop();

		int N;
		cin >> N;

		for (int j = 0; j < N; j++) {
			int num;
			cin >> num;
			input.push(-num);
		}

		answer[i] = STRJOIN(0);
	}

	for (int output : answer) {
		cout << output << endl;
	}

	return 0;
}

int STRJOIN(int sum) {
	if (input.size() == 2) {
		int num1 = input.top();
		input.pop();
		int num2 = input.top();
		input.pop();
		return sum - (num1 + num2);
	}

	int num1 = input.top();
	input.pop();
	int num2 = input.top();
	input.pop();
	input.push(num1 + num2);
	
	return STRJOIN(sum - (num1 + num2));
}
