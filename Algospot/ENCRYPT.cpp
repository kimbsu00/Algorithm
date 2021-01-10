/*
  url: https://algospot.com/judge/problem/read/ENCRYPT
*/

#include<iostream>
#include<vector>
#include<string>

using namespace std;

int main(void) {
	int C;
	cin >> C;

	for (int i = 0; i < C; i++) {
		string input;
		cin >> input;
		
		for (int k = 0; k < input.size(); k += 2) {
			cout << input[k];
		}
		for (int k = 1; k < input.size(); k += 2) {
			cout << input[k];
		}
		cout << endl;
	}

	return 0;
}
