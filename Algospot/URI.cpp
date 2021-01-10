/*
  url: https://algospot.com/judge/problem/read/URI
*/

#include<iostream>
#include<string>
#include<vector>

#define BLANK " "
#define EXCLAMAITION "!"
#define DOLLAR "$"
#define PERCENT "%"
#define OPENB "("
#define CLOSEB ")"
#define ASTERISK "*"

using namespace std;

string URI(string input);

int main(void) {
	int C;
	cin >> C;
	vector<string> answer(C);

	for (int i = 0; i < C; i++) {
		string input;
		cin >> input;

		answer[i] = URI(input);
	}

	for (int i = 0; i < C; i++) 
		cout << answer[i] << endl;

	return 0;
}

string URI(string input) {
	string ret = input;

	for (int i = ret.size() - 2; i >= 0; i--) {
		if (ret[i] == '%') {
			string substr = ret.substr(i + 1, 2);
			if (substr == "20") {
				ret.replace(i, 3, BLANK);
			}
			else if (substr == "21") {
				ret.replace(i, 3, EXCLAMAITION);
			}
			else if (substr == "24") {
				ret.replace(i, 3, DOLLAR);
			}
			else if (substr == "25") {
				ret.replace(i, 3, PERCENT);
			}
			else if (substr == "28") {
				ret.replace(i, 3, OPENB);
			}
			else if (substr == "29") {
				ret.replace(i, 3, CLOSEB);
			}
			else if (substr == "2a") {
				ret.replace(i, 3, ASTERISK);
			}
		}
	}

	return ret;
}
