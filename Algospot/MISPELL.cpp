/*
  url: https://algospot.com/judge/problem/read/MISPELL
*/

#include<iostream>
#include<vector>
#include<string>

using namespace std;

int main(void) {
	int C;
	cin >> C;
	vector<string> answer(C, "");

	for (int i = 0; i < C; i++) {
		int index;
		string input;
		cin >> index >> input;
		
		answer[i] += input.substr(0, index - 1);
		answer[i] += input.substr(index, input.size());
	}

	for (int i = 0; i < C; i++)
		cout << i + 1 << " " << answer[i] << endl;

	return 0;
}
