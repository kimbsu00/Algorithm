/*
  url: https://algospot.com/judge/problem/read/HELLOWORLD
*/

#include<iostream>
#include<vector>
#include<string>

using namespace std;

int main(void) {
	int C;
	cin >> C;

	for (int i = 0; i < C; i++) {
		string name;
		cin >> name;
		cout << "Hello, " << name << "!" << endl;
	}

	return 0;
}
