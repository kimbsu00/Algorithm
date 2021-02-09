/*
  url: https://www.acmicpc.net/problem/14425
  
  map 을 이용하여 해결함.
*/ 

#include<iostream>
#include<string>
#include<map>

using namespace std;

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int N, M;
	cin >> N >> M;

	map<string, bool> hash;
	for (int i = 0; i < N; i++) {
		string input;
		cin >> input;
		hash.insert(make_pair(input, true));
	}

	int output = 0;
	for (int i = 0; i < M; i++) {
		string target;
		cin >> target;
		if (hash.find(target) != hash.end()) {
			output += 1;
		}
	}

	cout << output << "\n";

	return 0;
}
