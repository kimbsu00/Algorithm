/*
  url: https://algospot.com/judge/problem/read/LECTURE
*/

#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

int main(void) {
	int C;
	cin >> C;
	vector<string> answer(C, "");

	for (int i = 0; i < C; i++) {
		string input;
		cin >> input;

		vector<string> temp;
		for (int k = 0; k < input.size(); k += 2) {
			temp.push_back(input.substr(k, 2));
		}
		sort(temp.begin(), temp.end());

		for (string str : temp) {
			answer[i] += str;
		}
	}

	for (int i = 0; i < C; i++)
		cout << answer[i] << endl;

	return 0;
}
