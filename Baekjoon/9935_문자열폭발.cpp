/*
  url: https://www.acmicpc.net/problem/9935
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

string solve(string& input, string& bomb) {
	char* str = new char[1000005];
	fill(&str[0], &str[1000005], ' ');
	int idx = 0;

	for (char ch : input) {
		str[idx++] = ch;

		if (ch == bomb.back()) {
			bool check = true;
			for (int i = 0; i < bomb.size(); i++) {
				if (idx - i - 1 < 0) {
					check = false;
					break;
				}
				if (str[idx - i - 1] != bomb[bomb.size()- i - 1]) {
					check = false;
				}
			}

			if (check) {
				idx -= bomb.size();
			}
		}
	}

	string ret = "";
	for (int i = 0; i < idx; i++) {
		ret.append(1, str[i]);
	}

	return ret;
}

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	string input, bomb;
	cin >> input >> bomb;

	string output = solve(input, bomb);
	cout << (output.empty() ? "FRULA" : output) << "\n";

	return 0;
}
