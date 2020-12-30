/*
  url: https://algospot.com/judge/problem/read/PI
  
  삽질 없이 한 번에 통과한 문제라 기분이 좋았다.
*/

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

int PI(int index);

int cache[10001];
string input;

int main(void) {
	int C;
	cin >> C;
	vector<int> answer(C);

	for (int i = 0; i < C; i++) {
		fill(&cache[0], &cache[10001], 100000);

		cin >> input;

		answer[i] = PI(0);
	}

	for (int i = 0; i < C; i++) {
		cout << answer[i] << endl;
	}
	
	return 0;
}

int PI(int index) {
	if (index > input.size())
		return 100000;

	if (index == input.size())
		return 0;

	int& ret = cache[index];
	if (ret != 100000)
		return ret;

	// 연속하는 5개의 숫자에 대하여
	if (index + 4 < input.size()) {
		// 숫자가 같은 경우
		if ((input[index] == input[index + 1]) && (input[index + 1] == input[index + 2]) &&
			(input[index] == input[index + 3]) && (input[index] == input[index + 4])) {
			ret = min(ret, 1 + PI(index + 5));
		}
		// 숫자가 1씩 단조 증가 하는 경우
		else if ((input[index] + 1 == input[index + 1]) && (input[index] + 2 == input[index + 2]) &&
			input[index] + 3 == input[index + 3] && (input[index] + 4 == input[index + 4])) {
			ret = min(ret, 2 + PI(index + 5));
		}
		// 숫자가 1씩 단조 감소 하는 경우
		else if ((input[index] - 1 == input[index + 1]) && (input[index] - 2 == input[index + 2]) &&
			(input[index] - 3 == input[index + 3]) && (input[index] - 4 == input[index + 4])) {
			ret = min(ret, 2 + PI(index + 5));
		}
		// 두 개의 숫자가 번갈아 가며 출현하는 경우
		else if ((input[index] == input[index + 2]) && input[index + 2] == input[index + 4] && (input[index + 1] == input[index + 3])) {
			ret = min(ret, 4 + PI(index + 5));
		}
		// 숫자가 등차수열을 이루는 경우
		else if ((input[index] - input[index + 1] == input[index + 1] - input[index + 2]) &&
			(input[index + 1] - input[index + 2] == input[index + 2] - input[index + 3]) &&
			(input[index + 2] - input[index + 3] == input[index + 3] - input[index + 4])) {
			ret = min(ret, 5 + PI(index + 5));
		}
		// 그 외의 경우
		else {
			ret = min(ret, 10 + PI(index + 5));
		}
	}

	// 연속하는 4개의 숫자에 대하여
	if (index + 3 < input.size()) {
		// 숫자가 같은 경우
		if ((input[index] == input[index + 1]) && (input[index + 1] == input[index + 2]) &&
			(input[index] == input[index + 3])) {
			ret = min(ret, 1 + PI(index + 4));
		}
		// 숫자가 1씩 단조 증가 하는 경우
		else if ((input[index] + 1 == input[index + 1]) && (input[index] + 2 == input[index + 2]) &&
			(input[index] + 3 == input[index + 3])) {
			ret = min(ret, 2 + PI(index + 4));
		}
		// 숫자가 1씩 단조 감소 하는 경우
		else if ((input[index] - 1 == input[index + 1]) && (input[index] - 2 == input[index + 2]) &&
			(input[index] - 3 == input[index + 3])) {
			ret = min(ret, 2 + PI(index + 4));
		}
		// 두 개의 숫자가 번갈아 가며 출현하는 경우
		else if ((input[index] == input[index + 2]) && (input[index + 1] == input[index + 3])) {
			ret = min(ret, 4 + PI(index + 4));
		}
		// 숫자가 등차수열을 이루는 경우
		else if ((input[index] - input[index + 1] == input[index + 1] - input[index + 2]) &&
			(input[index + 1] - input[index + 2] == input[index + 2] - input[index + 3])) {
			ret = min(ret, 5 + PI(index + 4));
		}
		// 그 외의 경우
		else {
			ret = min(ret, 10 + PI(index + 4));
		}
	}

	// 연속하는 3개의 숫자에 대하여
	if (index + 2 < input.size()) {
		// 숫자가 같은 경우
		if ((input[index] == input[index + 1]) && (input[index + 1] == input[index + 2])) {
			ret = min(ret, 1 + PI(index + 3));
		}
		// 숫자가 1씩 단조 증가 하는 경우
		else if ((input[index] + 1 == input[index + 1]) && (input[index] + 2 == input[index + 2])) {
			ret = min(ret, 2 + PI(index + 3));
		}
		// 숫자가 1씩 단조 감소 하는 경우
		else if ((input[index] - 1 == input[index + 1]) && (input[index] - 2 == input[index + 2])) {
			ret = min(ret, 2 + PI(index + 3));
		}
		// 두 개의 숫자가 번갈아 가며 출현하는 경우
		else if ((input[index] == input[index + 2])) {
			ret = min(ret, 4 + PI(index + 3));
		}
		// 숫자가 등차수열을 이루는 경우
		else if ((input[index] - input[index + 1] == input[index + 1] - input[index + 2])) {
			ret = min(ret, 5 + PI(index + 3));
		}
		// 그 외의 경우
		else {
			ret = min(ret, 10 + PI(index + 3));
		}
	}

	return ret;
}
